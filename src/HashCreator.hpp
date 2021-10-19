#ifndef HASHPROGRAM_HASHCREATOR_HPP
#define HASHPROGRAM_HASHCREATOR_HPP

#include <future>
#include <map>
#include <memory>
#include <string>

#include "FileHandler.hpp"
#include "Logger.hpp"

namespace hashCreator {

    class HashCreator
    {
    public:
        HashCreator(std::string input_file_path, std::string output_file_path, unsigned long long block_size);

        void processFile();

    private:
        FileHandlerPtr input_file_, output_file_;
        struct Blocks_info
        {
            unsigned long long block_size_, current_block_, blocks_amount_, blocks_written_;
        } blocks_info_;
        unsigned long long bytes_to_read_left_;
        std::map<unsigned long long, std::future<unsigned>> threads_;
        std::map<unsigned long long, unsigned> result_hashes_;
        unsigned threads_available_;
        LoggerPtr logger_;

        void resetBlockInfo();

        void validateVariables();

        void setCurrentThreadsAvailable();

        void setBlocksAmount();

        unsigned getHashOfFileBlock(unsigned long long offset, unsigned long long block_size);

        void addThreadsToQueue();

        void checkThreadsQueue();

        void writeHashesPartsInOrderToFile();
    };

    using HashCreatorPtr = std::shared_ptr<HashCreator>;
}

#endif //HASHPROGRAM_HASHCREATOR_HPP
