#include <boost/filesystem/fstream.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/filesystem/operations.hpp>

#include "FileHandler.hpp"
#include "strConstants.hpp"

namespace hashCreator {

    FileHandler::FileHandler(std::string file_name, const openType open_mode) : file_name_(std::move(file_name)),
                                                                                open_mode_(open_mode)
    {
        if (openRead == open_mode_)
        {
            open();
        }
    }

    void FileHandler::write(const unsigned data)
    {
        if (openWrite != open_mode_)
        {
            throw std::logic_error(CommonConstants::ERROR_INPUT_FILE_OPEN_TO_WRITE_STR);
        }
        boost::filesystem::ofstream(file_name_, std::ios_base::app) << data;
    }

    bool FileHandler::isExist()
    {
        return boost::filesystem::exists(file_name_);
    }

    unsigned long long FileHandler::size()
    {
        return isExist() ? boost::filesystem::file_size(file_name_) : 0;
    }

    void FileHandler::open()
    {
        if (!isExist())
        {
            throw std::logic_error(CommonConstants::ERROR_INPUT_FILE_NOT_EXIST_STR);
        }
        map_of_file_to_hash_ = std::make_shared<boost::interprocess::file_mapping>(file_name_.c_str(), file_open_mode_);
    }

    std::string FileHandler::read(const long long offset, const unsigned long long bytes_to_read)
    {
        if (openRead != open_mode_)
        {
            throw std::logic_error(CommonConstants::ERROR_OUTPUT_FILE_OPEN_TO_READ_STR);
        }
        boost::interprocess::mapped_region region_of_file_to_hash(*map_of_file_to_hash_, file_open_mode_, offset,
                                                                  bytes_to_read);
        return {reinterpret_cast<const char *>(region_of_file_to_hash.get_address()),
                region_of_file_to_hash.get_size()};
    }

    FileHandlerPtr makeFileHandler(std::string file_name, const FileHandler::openType open_mode)
    {
        return std::make_shared<FileHandler>(std::move(file_name), open_mode);
    }
}