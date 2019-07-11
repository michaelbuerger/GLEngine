#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream>
#include <exception>

struct GLE_IMAGE_DATA_NULL : public std::exception
{
    const char *what() const throw()
    {
        return "GLE_IMAGE_DATA_NULL";
    }
};

#endif