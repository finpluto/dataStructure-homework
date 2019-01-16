#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "Query.h"

class Console {
private:
    vector<function<DataSet(DataSet &&,int)> > basic_method = {};
    DataSet example{"data.txt"};

public:
    Console(); //初始化基本查询方法
    ~Console();
    void Run();
    void NormalQuery();
    void StatisticQuery();
    void SortQuery();
};

#endif