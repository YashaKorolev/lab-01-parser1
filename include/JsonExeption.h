//
// Created by yasha on 18.11.2019.
//

#ifndef LAB_01_PARSER_JSONEXEPTION_H
#define LAB_01_PARSER_JSONEXEPTION_H

#include "Json.h"
#include <exception>

class JsonException : public std::exception
{
public:

    const char*what() const noexcept
    {
        return "Error: Wrong input\n";
    }
};
#endif //LAB_01_PARSER_JSONEXEPTION_H
