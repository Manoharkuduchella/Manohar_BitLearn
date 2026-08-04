#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include "uart.hpp"

class Logger 
{
    public:
    explicit Logger(Uart *uart_handle);
    bool log(const std::string &msg);

    private:
    Uart *uart_;
};

#endif