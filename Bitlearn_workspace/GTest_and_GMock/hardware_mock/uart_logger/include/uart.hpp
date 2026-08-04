#ifndef UART_HPP
#define UART_HPP

class Uart
{
    public:
    virtual ~Uart() = default; //virtual destructor in base class intended for polymorphism, ensures deleting an object through base-class pointer correctly calls the derived class destructor.
    virtual bool send(const std::string &data) = 0;//pure virtual function derived class has to implement
};

#endif