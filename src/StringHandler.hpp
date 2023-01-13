#pragma once
#include <string>
#include <bitset>
#include <vector>

class StringHandler{
public:
    std::vector<std::string> GetSubStrings(std::string s,char separator){
        std::vector<std::string> substrings;
        s.append("&$end$&");
        size_t end(s.find("&$end$&"));
        size_t index(s.find(":"));

        while (index < end)
        {
            substrings.push_back(s.substr(0,index));
            s.erase(0,index+1);
            index = s.find(":");
        }

        return substrings;
    }
    int HexToInt(std::string toParse);
    float HexToFloat(std::string toParse);
    std::string IntToHex(int toConvert);
    std::string FloatToHex(int toConvert);
};