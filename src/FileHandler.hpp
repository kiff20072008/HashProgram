#ifndef HASHPROGRAM_FILEHANDLER_HPP
#define HASHPROGRAM_FILEHANDLER_HPP

#include <memory>
#include <string>
#include <boost/interprocess/file_mapping.hpp>

namespace hashCreator {

    class FileHandler
    {
    public:
        enum openType
        {
            openRead,
            openWrite
        };

        FileHandler(std::string file_name, openType open_mode);

        void write(unsigned data);

        bool isExist();

        unsigned long long size();

        std::string read(long long offset, unsigned long long bytes_to_read);

    private:
        std::string file_name_;
        std::shared_ptr<boost::interprocess::file_mapping> map_of_file_to_hash_;
        openType open_mode_;
        const boost::interprocess::mode_t file_open_mode_ = boost::interprocess::read_only;

        void open();
    };

    using FileHandlerPtr = std::shared_ptr<FileHandler>;
}

#endif //HASHPROGRAM_FILEHANDLER_HPP
