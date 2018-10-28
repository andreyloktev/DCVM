#include <foo.hpp>
#include <iostream>

void PrintHelloWord() noexcept
{
    try
    {
        std::cout << "Hello, World!!!" << std::endl;
    }
    catch (std::exception&)
    {
    }
}