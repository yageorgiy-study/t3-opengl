#include "logger.h"

void Logger::message(std::string str)
{
    std::cout << "[MESSAGE] " << str << std::endl;
};

void Logger::error(std::string str)
{
    std::cerr << "[ERROR] " << str << std::endl;
};
