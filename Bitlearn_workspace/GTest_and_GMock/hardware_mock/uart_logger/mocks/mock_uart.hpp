#ifndef MOCK_UART_HPP
#define MOCK_UART_HPP

#include <gmock/gmock.h>
#include "uart.hpp"

class MockUart : public Uart
{
    public:
    MOCK_METHOD(bool, send, (const std::string &data), (override));
};

#endif