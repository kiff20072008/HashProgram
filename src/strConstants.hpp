#ifndef HASHPROGRAM_STRCONSTANTS_HPP
#define HASHPROGRAM_STRCONSTANTS_HPP
namespace CommonConstants {
    static constexpr const char *PROGRAM_DESCRIPTION_STR = "Hash function";
    static constexpr const char *PATH_TO_INPUT_HELP_STR = "Path to input file";
    static constexpr const char *PATH_TO_INPUT_PR_STR = "input_file,f";
    static constexpr const char *PATH_TO_INPUT_STR = "input_file";
    static constexpr const char *PATH_TO_OUTPUT_HELP_STR = "Path to output file";
    static constexpr const char *PATH_TO_OUTPUT_PR_STR = "output_file,o";
    static constexpr const char *PATH_TO_OUTPUT_STR = "output_file";
    static constexpr const char *SHOW_HELP_HELP_STR = "Show help";
    static constexpr const char *SHOW_HELP_PR_STR = "help,h";
    static constexpr const char *SHOW_HELP_STR = "help";
    static constexpr const char *BLOCK_SIZE_HELP_STR = "Blocks size in Mb";
    static constexpr const char *BLOCK_SIZE_PR_STR = "block_size,b";
    static constexpr const char *BLOCK_SIZE_STR = "block_size";
    static constexpr const char *INPUT_FILE_SIZE_STR = "Input file size in bytes:";
    static constexpr const char *CURRENT_CORES_STR = "Current cores in system:";
    static constexpr const char *ERROR_INPUT_FILE_NOT_EXIST_STR = "Input file doesn't exists";
    static constexpr const char *ERROR_OUTPUT_FILE_EXIST_STR = "Output file exists";
    static constexpr const char *ERROR_INPUT_FILE_OPEN_TO_WRITE_STR = "Can't write to input file";
    static constexpr const char *ERROR_OUTPUT_FILE_OPEN_TO_READ_STR = "Can't read from output file";
    static constexpr const char *ERR_BLOCK_SIZE_STR = "Wrong block size";
    static constexpr const char *BOOST_EXCEPTION_STR = "Boost exception while program work - ";
    static constexpr const char *STD_EXCEPTION_STR = "Std exception while program work - ";
}
#endif //HASHPROGRAM_STRCONSTANTS_HPP
