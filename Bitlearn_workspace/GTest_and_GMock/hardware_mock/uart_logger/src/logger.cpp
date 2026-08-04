#include "logger.hpp"

Logger:: Logger(Uart *uart) : uart_(uart)
{

}

bool Logger::log(const std::string &msg)
{
    return uart_->send(msg);
}