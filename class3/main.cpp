#include "Stack.hpp"
#include "StrMani.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class expressionAnlys
{
private:
    vector<string> suffixExpres;
public:
    expressionAnlys(){}
    expressionAnlys(string expression);
    ~expressionAnlys(){}
    void output();
    //输出所转换的逆波兰表达式
    
    void caculate();
    //输出逆波兰表达式的计算值
};

int main()
{
    string expression("");
    getline(cin, expression);

    //去除空格
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    expressionAnlys example(expression);
    example.output();
    example.caculate();
    return 0;
}

expressionAnlys::expressionAnlys(string expression)
{
    //设置优先级
    //这里使用直接寻址法有点浪费空间，可以考虑改为hash表
    int priority[256] = {0};
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;

    vector<string> splitRes = split(expression, "+-*/()");
    Stack<string> opt;
    for(auto i : splitRes){
        if(isNumber(i)){
            suffixExpres.push_back(i);
        }
        else if(i=="("){
            opt.push(i);
        }
        else if(i==")"){
            while(opt.getTop()!="("){
                suffixExpres.push_back(opt.pop());
            }
            opt.pop();     //丢弃左括号
        }
        else if(opt.isEmpty() ||
                opt.getTop()=="(" ||
                priority[opt.getTop()[0]] < priority[i[0]]){
            opt.push(i);
        }
        else{
            while(!opt.isEmpty() &&
                    opt.getTop()[0] >= priority[i[0]]){
                suffixExpres.push_back(opt.pop());
            }
            opt.push(i);
        }
    }
    while(!opt.isEmpty()){
        suffixExpres.push_back(opt.pop());
    }
}

void expressionAnlys::caculate()
{
    Stack<int> res;
    for(auto i : suffixExpres){
        if(isNumber(i)){
            res.push(stoi(i));
        }
        switch(i[0]){
            case '+':{
                         int a = res.pop();
                         int b = res.pop();
                         res.push(b+a);
                         break;
                     }
            case '-':{
                         int a = res.pop();
                         int b = res.pop();
                         res.push(b-a);    //注意前数减后数
                         break;
                     }
            case '*':{
                         int a = res.pop();
                         int b = res.pop();
                         res.push(b*a);
                         break;
                     }
            case '/':{
                         int a = res.pop();
                         int b = res.pop();
                         res.push(b/a);    //注意前数除后数
                         break;
                     }
        }
    }
    cout << '\n' << res.getTop() << '\n';
}

void expressionAnlys::output()
{
    for(auto i : suffixExpres){
        cout << i << " ";
    }
    cout << '\n';
}
