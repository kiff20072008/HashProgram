#include <boost/program_options.hpp>
#include <boost/exception/all.hpp>
#include <exception>
#include <string>
#include "constants.hpp"
#include "Logger.hpp"
#include "strConstants.hpp"
#include "HashCreator.hpp"

int parseProgramOptions(const int argc, char **argv, std::string &path_to_input_file, std::string &path_to_output_file,
                        unsigned long long &block_size, const hashCreator::LoggerPtr &logger)
{
    // Create program options handler
    boost::program_options::options_description pr_desc(CommonConstants::PROGRAM_DESCRIPTION_STR);
    pr_desc.add_options()
            (CommonConstants::SHOW_HELP_PR_STR, CommonConstants::SHOW_HELP_HELP_STR)
            (CommonConstants::PATH_TO_INPUT_PR_STR, boost::program_options::value<std::string>(),
             CommonConstants::PATH_TO_INPUT_HELP_STR)
            (CommonConstants::PATH_TO_OUTPUT_PR_STR, boost::program_options::value<std::string>(),
             CommonConstants::PATH_TO_OUTPUT_HELP_STR)
            (CommonConstants::BLOCK_SIZE_PR_STR, boost::program_options::value<unsigned long long>(),
             CommonConstants::BLOCK_SIZE_HELP_STR);
    boost::program_options::variables_map vm;
    try
    {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, pr_desc), vm);
        boost::program_options::notify(vm);
    }
    catch (boost::program_options::error &err)
    {
        logger->log(err.what());
        logger->log(pr_desc);
        throw;
    }

    // Handle program options

    if (vm.count(CommonConstants::SHOW_HELP_STR))
    {
        logger->log(pr_desc);
        return 1;
    }

    if (vm.count(CommonConstants::PATH_TO_INPUT_STR))
    {
        path_to_input_file = vm[CommonConstants::PATH_TO_INPUT_STR].as<std::string>();
    }
    if (vm.count(CommonConstants::PATH_TO_OUTPUT_STR))
    {
        path_to_output_file = vm[CommonConstants::PATH_TO_OUTPUT_STR].as<std::string>();
    }
    if (vm.count(CommonConstants::BLOCK_SIZE_STR))
    {
        block_size = vm[CommonConstants::BLOCK_SIZE_STR].as<unsigned long long>();
    }
    return 0;
}

int main(int argc, char **argv)
{
    hashCreator::LoggerPtr logger = std::make_shared<hashCreator::Logger>();
    std::string path_to_input_file, path_to_output_file;
    unsigned long long block_size = CommonConstants::BLOCK_SIZE_DEFAULT;
    if (!parseProgramOptions(argc, argv, path_to_input_file, path_to_output_file, block_size, logger))
    {
        try
        {
            // Calculate file hash
            hashCreator::HashCreatorPtr HashCreator_ = std::make_shared<hashCreator::HashCreator>(path_to_input_file,
                                                                                                  path_to_output_file,
                                                                                                  block_size);
            HashCreator_->processFile();
        }
        catch (boost::exception const &ex)
        {
            logger->log(CommonConstants::BOOST_EXCEPTION_STR + boost::diagnostic_information(ex));
        }
        catch (std::exception const &ex)
        {
            logger->log(CommonConstants::STD_EXCEPTION_STR + std::string(ex.what()));
        }
    }
    return 0;
}
