//
// Created by yasha on 18.11.2019.
//

#ifndef LAB_01_PARSER_JSONEXEPTION_H
#define LAB_01_PARSER_JSONEXEPTION_H

#include "Json.h"
#include <exception>

class JsonException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Exception Json";
    }
}json_exeption;
#endif //LAB_01_PARSER_JSONEXEPTION_H
