


#include "Json.h"

int main() {
    std::string s = "[{\"fanta\": \"sprite\"}, {\"price\": 777}, {\"pain\": false}]";
    Json json(s);
    Json obj = Json::parse(s);
    std::cout<<obj.is_array();
    return 0;
}