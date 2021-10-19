#ifndef HASHPROGRAM_LOGGER_HPP
#define HASHPROGRAM_LOGGER_HPP

#include <iostream>
#include <memory>

namespace hashCreator {
    class Logger
    {
    public:
        Logger() = default;

        template<typename T>
        void log(const T &str)
        {
            std::cout << str << std::endl;
        }
    };

    using LoggerPtr = std::shared_ptr<Logger>;
}

#endif //HASHPROGRAM_LOGGER_HPP
