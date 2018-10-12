#include "StrMani.hpp"
#include<string>
#include<vector>
using std::vector;
using std::string;

vector<string> split(const string &s, const string &del)
{
    // 使用直接寻址法来判断所遍历的字符是否是分隔符
    // 更方便的做法是使用STL中的unordered_map即哈希表来查找
    const int dictSize = 256;
    static bool dict[dictSize] = {false};

    vector<string> res;
    for(int i = 0; i < del.size(); ++i){      
        dict[del[i]] = true;
    }

    // 循环遍历并按dict中的分隔符来切割字符串，存入vector容器
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
