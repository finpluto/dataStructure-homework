#include "StrMani.hpp"
#include<string>
#include<vector>
using std::vector;
using std::string;

vector<string> split(const string &s, const string &del)
{
    const int dictSize = 256;
    static bool dict[dictSize] = {false};

    vector<string> res;
    for(int i = 0; i < del.size(); ++i){      
        dict[del[i]] = true;
    }

    string token("");
    for(auto i : s){
        if (dict[i]){
            if(!token.empty()){
                res.push_back(token);
                string addingToken(1, i);
                res.push_back(addingToken);
                token.clear();
            }           
            else{
                string addingToken(1, i);
                res.push_back(addingToken);
            }
        }
        else{
            token += i;
        }
    }
    if(!token.empty()){
        res.push_back(token);
    }
    return res;
}

bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
