#include <boost/thread.hpp>
#include <boost/functional/hash.hpp>
#include <thread>

#include "constants.hpp"
#include "Logger.hpp"
#include "HashCreator.hpp"
#include "strConstants.hpp"

namespace hashCreator {

    extern FileHandlerPtr makeFileHandler(std::string file_name, FileHandler::openType open_mode);

    extern LoggerPtr makeLogger();

    HashCreator::HashCreator(std::string input_file_path, std::string output_file_path,
                             const unsigned long long block_size) :
            bytes_to_read_left_(0),
            threads_available_(0)
    {
        logger_ = makeLogger();
        blocks_info_.block_size_ = block_size * CommonConstants::BYTES_IN_MEGABYTES;
        input_file_ = makeFileHandler(std::move(input_file_path), FileHandler::openRead);
        output_file_ = makeFileHandler(std::move(output_file_path), FileHandler::openWrite);
        validateVariables();
    }

    void HashCreator::resetBlockInfo()
    {
        blocks_info_.current_block_ = blocks_info_.blocks_amount_ = blocks_info_.blocks_written_ = 0;
    }

    unsigned HashCreator::getHashOfFileBlock(const unsigned long long offset, const unsigned long long block_size)
    {
        boost::hash<std::string> hash_string;
        return hash_string(input_file_->read(offset, block_size));
    }

    void HashCreator::validateVariables()
    {
        if (!input_file_->isExist())
        {
            throw std::invalid_argument(CommonConstants::ERROR_INPUT_FILE_NOT_EXIST_STR);
        }
        if (output_file_->isExist())
        {
            throw std::invalid_argument(CommonConstants::ERROR_OUTPUT_FILE_EXIST_STR);
        }

        if (!blocks_info_.block_size_)
        {
            throw std::invalid_argument(CommonConstants::ERR_BLOCK_SIZE_STR);
        }
    }

    void HashCreator::setCurrentThreadsAvailable()
    {
        threads_available_ = boost::thread::hardware_concurrency();
        logger_->log(CommonConstants::CURRENT_CORES_STR);
        logger_->log(threads_available_);
    }

    void HashCreator::setBlocksAmount()
    {
        bytes_to_read_left_ = input_file_->size();
        logger_->log(CommonConstants::INPUT_FILE_SIZE_STR);
        logger_->log(bytes_to_read_left_);

        const bool is_file_size_more_than_block = bytes_to_read_left_ >= blocks_info_.block_size_;
        const bool is_file_size_divided_by_block = (bytes_to_read_left_ % blocks_info_.block_size_ == 0);
        const unsigned long long file_size_divided_by_block = bytes_to_read_left_ / blocks_info_.block_size_;
        blocks_info_.blocks_amount_ = is_file_size_more_than_block
                                      ? (is_file_size_divided_by_block
                                         ? file_size_divided_by_block
                                         : file_size_divided_by_block + 1)
                                      : 1;
    }

    void HashCreator::addThreadsToQueue()
    {
        unsigned long long bytes_to_read, offset;
        while (threads_.size() < threads_available_ && blocks_info_.current_block_ < blocks_info_.blocks_amount_)
        {
            offset = blocks_info_.current_block_ * blocks_info_.block_size_;
            bytes_to_read = std::min(blocks_info_.block_size_, bytes_to_read_left_);
            threads_[blocks_info_.current_block_++] = (std::async(std::launch::async, &HashCreator::getHashOfFileBlock,
                                                                  this, offset, bytes_to_read));

            bytes_to_read_left_ -= bytes_to_read;
        }
    }

    void HashCreator::checkThreadsQueue()
    {
        for (auto thread_iterator = threads_.begin(); thread_iterator != threads_.end();)
        {
            if (thread_iterator->second.wait_for(std::chrono::seconds(1)) == std::future_status::ready)
            {
                // Write hash of block to result map if ready
                result_hashes_[thread_iterator->first] = thread_iterator->second.get();
                thread_iterator = threads_.erase(thread_iterator);
            } else
            {
                ++thread_iterator;
            }
        }
    }

    void HashCreator::writeHashesPartsInOrderToFile()
    {
        while (result_hashes_.find(blocks_info_.blocks_written_) != result_hashes_.end())
        {
            output_file_->write(result_hashes_[blocks_info_.blocks_written_]);
            result_hashes_.erase(blocks_info_.blocks_written_++);
        }
    }

    void HashCreator::processFile()
    {
        setCurrentThreadsAvailable();
        resetBlockInfo();
        setBlocksAmount();
        while (blocks_info_.blocks_written_ < blocks_info_.blocks_amount_)
        {
            addThreadsToQueue();
            checkThreadsQueue();
            writeHashesPartsInOrderToFile();
        }
    }
}