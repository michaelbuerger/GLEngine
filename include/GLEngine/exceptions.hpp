#ifndef GLE_EXCEPTIONS_HPP
#define GLE_EXCEPTIONS_HPP

#include <iostream>
#include <exception>

struct GLE_IMAGE_DATA_NULL : public std::exception
{
    const char *what() const throw()
    {
        return "GLE_IMAGE_DATA_NULL";
    }
};

struct GLE_CANT_OPEN_FILE : public std::exception
{
    const char *what() const throw()
    {
        return "GLE_CAN'T_OPEN_FILE";
    }
};

#endif