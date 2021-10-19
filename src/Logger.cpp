#include <boost/program_options.hpp>
#include "Logger.hpp"

namespace hashCreator {

    LoggerPtr makeLogger()
    {
        return std::make_shared<Logger>();
    }
}
