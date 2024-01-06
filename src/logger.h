#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

/**
 * @todo write docs
 */
class Logger
{
public:
    static void message(std::string str);
    static void error(std::string str);
};

#endif // LOGGER_H
