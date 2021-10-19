#include <boost/filesystem/fstream.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem/operations.hpp>
#include <cstdio>
#include <gtest/gtest.h>
#include <string>

#include "FileHandler.hpp"
#include "HashCreator.hpp"

namespace hashCreator {

    namespace {

        const std::string test_data = "TestData";
        constexpr size_t default_block_size = 1;
        constexpr size_t test_number = 7;
    }

    extern FileHandlerPtr makeFileHandler(std::string file_name, FileHandler::openType open_mode);

    TEST(FileHandlerTest, TestNotExistWriteFile)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openWrite);
        EXPECT_EQ(fileHandler->isExist(), false);
        EXPECT_EQ(fileHandler->size(), 0);
    }

    TEST(FileHandlerTest, TestNotExistReadFile)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        EXPECT_THROW(FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openRead),
                     std::logic_error);
    }

    TEST(FileHandlerTest, TestWriteToReadFile)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openRead);
        EXPECT_THROW(fileHandler->write(test_number), std::logic_error);
    }

    TEST(FileHandlerTest, TestReadFromWriteFile)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openWrite);
        EXPECT_THROW(fileHandler->read(0, test_data.size()), std::logic_error);
    }

    TEST(FileHandlerTest, TestCorrectFile)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openRead);
        EXPECT_EQ(fileHandler->isExist(), true);
        EXPECT_EQ(fileHandler->size(), test_data.size());
    }

    TEST(FileHandlerTest, TestCorrectFileRead)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openRead);
        EXPECT_EQ(fileHandler->read(0, test_data.size()), test_data);
    }

    TEST(FileHandlerTest, TestCorrectFileWrite)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;
        FileHandlerPtr fileHandler = makeFileHandler(input_exist_file, FileHandler::openWrite);
        fileHandler->write(test_number);
        EXPECT_EQ(fileHandler->size(), test_data.size() + 1);
    }

    TEST(HashCreatorTest, TestInputFileNotExist)
    {
        std::string input_not_exist_file = std::tmpnam(nullptr);
        std::string output_not_exist_file = std::tmpnam(nullptr);
        EXPECT_THROW(hashCreator::HashCreatorPtr HashCreator_ = std::make_shared<hashCreator::HashCreator>(
                input_not_exist_file,
                output_not_exist_file,
                             default_block_size), std::logic_error);
    }

    TEST(HashCreatorTest, TestOutputFileExist)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;

        std::string output_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(output_exist_file, std::ios_base::app) << test_data;
        EXPECT_THROW(
                hashCreator::HashCreatorPtr HashCreator_ = std::make_shared<hashCreator::HashCreator>(input_exist_file,
                                                                                                      output_exist_file,
                default_block_size),
                std::logic_error);
    }

    TEST(HashCreatorTest, TestWrongBlockSize)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;

        std::string output_exist_file = std::tmpnam(nullptr);
        size_t wrong_block_size = 0;

        EXPECT_THROW(
                hashCreator::HashCreatorPtr HashCreator_ = std::make_shared<hashCreator::HashCreator>(input_exist_file,
                                                                                                      output_exist_file,
                wrong_block_size),
                std::logic_error);
    }

    TEST(HashCreatorTest, TestCorrect)
    {
        std::string input_exist_file = std::tmpnam(nullptr);
        boost::filesystem::ofstream(input_exist_file, std::ios_base::app) << test_data;

        std::string output_exist_file = std::tmpnam(nullptr);
        hashCreator::HashCreatorPtr HashCreator_ = std::make_shared<hashCreator::HashCreator>(input_exist_file,
                                                                                              output_exist_file,
                                                                                              default_block_size);
        HashCreator_->processFile();
        boost::filesystem::ifstream output_exist_file_stream(output_exist_file);
        unsigned hash_creator_result;
        output_exist_file_stream >> hash_creator_result;
        boost::hash<std::string> hash_string;
        unsigned test_data_hash = hash_string(test_data);
        EXPECT_EQ(hash_creator_result, test_data_hash);
    }

}

