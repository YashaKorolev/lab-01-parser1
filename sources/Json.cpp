//
// Created by yasha on 18.11.2019.
//

#include "Json.h"
#include "JsonExeption.h"





Json::Json(const std::string& s) {
    json_s = clearspaces(s);

}

// Ìåòîä âîçâðàùàåò true, åñëè äàííûé ýêçåìïëÿð ñîäåðæèò â ñåáå JSON-ìàññèâ. Èíà÷å false.
bool Json:: is_array() const {
    if (json_s.size() == 0) {
        return false;
    }
    //[1,2,3,4]
    if (json_s[0] == '[' && json_s[json_s.size() - 1] == ']') {
        return true;
    }
    else {
        return false;
    }
}


// Ìåòîä âîçâðàùàåò true, åñëè äàííûé ýêçåìïëÿð ñîäåðæèò â ñåáå JSON-îáúåêò. Èíà÷å false.
bool Json:: is_object() const {
    if (json_s.size() == 0) {
        return false;
    }
    if (json_s[0] == '{' && json_s[json_s.size() - 1] == '}') {
        return true;
    }
    else {
        return false;
    }
}

// "sd f \tsdf"
std::string Json:: clearspaces(std::string sourse) {
    std::string result;

    int i;
    for (i = 0; i < (int)sourse.size(); i++)
    {
        if (sourse[i] == ' ' || sourse[i] == '\t') {
            continue;
        }
        else {
            break;
        }
    }

    int j;
    for (j = sourse.size() - 1; j >= 0; j--)
    {
        if (sourse[j] == ' ' || sourse[j] == '\t') {
            continue;
        }
        else {
            break;
        }
    }


    for (; i <= j; i++)
    {

        result += sourse[i];

    }

    return result;
}


//Î÷èñòêà îò âåäóùèõ è â êîíöå ïðîáåëîâ, òàáóëÿöèé, åñëè åñòü. È êàâû÷åê
std::string Json:: clearquots(std::string sourse) {

    std::string result;

    std::string t = clearspaces(sourse);

    int l = t.size();
    if (l == 0) {
        throw  JsonException();
    }

    if (t[0] == '"' && t[l-1] != '"') {
        throw  JsonException();
    }
    if (t[0] != '"' && t[l-1] == '"') {
        throw  JsonException();
    }
    int i = 0, j = l - 1;
    if (t[0] == '"' && t[l-1] == '"') {
        i++; j--;
    }

    for(; i <= j; i++)
    {
        if (t[i] != '"') {
            result += t[i];
        }
    }

    return result;
}



std::vector<std::string> Json:: splitarray() {
    std::vector<std::string> json_array;
    std::string str2 = json_s.substr(1, json_s.size() - 2);
    std::string str3;
    for (std::string::iterator it = str2.begin(); it != str2.end(); it++) {
        if (*it != '\n') {
            str3 += *it;
        }
    }

    std::stack<char> bracket;
    std::string new_value;
    for (std::string::iterator it = str3.begin(); it != str3.end(); it++) {
        if (*it == ',' && bracket.empty()) {
            json_array.push_back(new_value);
            new_value.clear();
            continue;
        }

        if (*it == '[' || *it == '{') {
            bracket.push(*it);
        }
        if (*it == ']' || *it == '}') {
            bracket.pop();
        }
        new_value += *it;

    }
    json_array.push_back(new_value);

    return json_array;
}

    std::vector<std::pair<std::string, std::string>> Json:: keyvalue() {

        std::vector<std::pair<std::string, std::string>> json_d;

        std::string str2 = json_s.substr(1, json_s.size() - 2);
        std::string str3;
    for (std::string::iterator it = str2.begin(); it != str2.end(); it++) {
        if (*it != '\n') {
            str3 += *it;
        }
    }

        std::stack<char> bracket;


    bool iskey = true;

        std::string new_key;
        std::string new_value;

    for (std::string::iterator it = str3.begin(); it != str3.end(); it++) {

        if ((*it == ',' && bracket.empty()) || (it + 1) == str3.end()) {
            //
            if ((it + 1) == str3.end() && *it != ',') {
                new_value += *it;
                if (*it == ']' || *it == '}') {
                    if (bracket.empty()) {
                        throw  JsonException();
                    }
                    bracket.pop();

                }
            }
            std::pair<std::string, std::string> new_item;
            new_item.first = new_key;
            new_item.second = new_value;

            json_d.push_back(new_item);

            new_key.clear();
            new_value.clear();
            iskey = true;
            continue;
        }

        if (*it == ':' && bracket.empty()) {
            iskey = false;
            continue;
        }

        if (iskey) {
            new_key += *it;
        }
        else {
            //
            if (*it == '[' || *it == '{') {
                bracket.push(*it);
            }
            if (*it == ']' || *it == '}') {
                if (bracket.empty()) {
                    throw  JsonException();
                }
                bracket.pop();
            }
            new_value += *it;
        }
    }




    for (int i = 0; i <(int) json_d.size(); i++)
    {
        std::pair<std::string, std::string> t = json_d[i];
        t.first = clearquots(t.first);
        t.second = clearquots(t.second);
        json_d[i] = t;
    }
    return json_d;
}

std::any Json:: checkstr(const std::string& str) {

    std::any result;
    std::string clearspc = clearspaces(str);

    // true false
    if (clearspc == "true") {
        result = true;
        return result;
    }

    if (clearspc == "false") {
        result = false;
        return result;
    }


    // JSON
    Json newJson(str);
    if (newJson.is_object() || newJson.is_array())
    {
        result = newJson;
        return result;
    }



    // double
    try {
        double d = std::stod(clearspc);
        result = d;
        return result;
    }
    catch (const std::invalid_argument& ia) {
        //string
        std::string st = clearquots(str);
        if (st.size() > 0) {
            result = st;
            return result;
        }

    }




    return result;
}


std::any Json:: operator[](const std::string& key) {
    if (is_array()) {
        throw  JsonException();
    }


    auto json_d = keyvalue();

    std::any res;
    for (std::vector<std::pair<std::string, std::string>>::iterator it = json_d.begin(); it != json_d.end(); it++) {
        if ((*it).first == key) {
            res = checkstr((*it).second);
        }
    }


    return res;
}


std::any Json:: operator[](int index) {


    auto json_array = splitarray(); //

    std::any res;

    for (int i = 0; i <(int) json_array.size(); i++) {
        if (i == index) {
            res = checkstr(json_array[i]);
        }
    }

    return res;
}

//////////////////////////////////////
Json Json:: parse(const std::string& s) {
    return Json(s);
}


Json Json:: parseFile(const std::string& path_to_file) {
    std::string line;
    std::string result;
    std::ifstream myfile(path_to_file);
    //try {
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                result += line;
            }
            myfile.close();
        }

    //}
    //catch (JsonException e) {
     //   std::cout << e.what();
    //}

    return Json(result);
}
