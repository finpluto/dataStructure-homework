#ifndef STRMANI_CPP
#define STRMANI_CPP
// Custom string manipulation class
// 自定义字符串操作类
// including :
// 1. split string by multiple delimiters
// 2. determine if a string consist of numbers.

#include<string>
#include<vector>
using std::vector;
using std::string;
vector<string> split(const string &s, const string &del);
// split string by a string including delimiters.
// input the string s and string whose character is as delimiters.
// ouput a vector<string> including split parts and delimiters.
bool isNumber(const string& s);
// determine if a string consist of numbers.
#endif
