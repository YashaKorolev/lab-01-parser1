//
// Created by yasha on 18.11.2019.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H


#include <string>
#include <any>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


class Json {
private:
    std::string json_s;

public:

    Json(const std::string& s);


    bool is_array() const;



    bool is_object() const;


    std::string clearspaces(std::string sourse);



    std::string clearquots(std::string sourse);



    std::vector<std::string> splitarray() ;

    std::vector<std::pair<std::string, std::string>> keyvalue();

    std::any checkstr(const std::string& str);


    std::any operator[](const std::string& key) ;


    std::any operator[](int index) ;


    static Json parse(const std::string& s) ;


    static Json parseFile(const std::string& path_to_file);
};

#endif //JSON_JSON_H
