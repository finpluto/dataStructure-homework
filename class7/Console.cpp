#include "Console.h"
#include <iostream>
#include <unordered_map>

using std::cin;
using std::cout;
using std::unordered_map;

Console::Console() {
    auto byWeek = [](DataSet &&origin, int week) -> DataSet {
        int month_days[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int start_day = 1 + (week-1) * 7;
        int start_month = 1;
        while(start_day - month_days[start_month+1] > 0) {
            start_day -= month_days[start_month];
            start_month++;
        }
        int end_month = start_month;
        int end_day = start_day;
        while(end_day - month_days[end_month+1] > 0) {
            end_day -= month_days[end_month];
            end_month++;
        }
        return origin.SelectByRange(start_month, start_day, end_month, end_day);
    };
    auto byMonth = [](DataSet &&origin, int month) -> DataSet {
        return origin.SelectByTime(month);
    };
    auto byQuarter = [](DataSet &&origin, int quarter) -> DataSet {
        int start_month = 1 + (quarter - 1) * 3;
        return origin.SelectByTime(start_month) +
               origin.SelectByTime(start_month + 1) +
               origin.SelectByTime(start_month + 2);
    };
    auto byYear = [](DataSet &&origin, int) -> DataSet {
        DataSet return_set = origin; // 将右值赋给左值
        return return_set; //返回左值
    };
    basic_method.push_back(byWeek);
    basic_method.push_back(byMonth);
    basic_method.push_back(byQuarter);
    basic_method.push_back(byYear);
}

Console::~Console() {
    example.ReleaseMemo();
}

void Console::Run() {
    int input_flag;
    string exit_flag;
    auto main_menu = [&]() {
        cout << "欢迎使用全国空气质量查询工具！\n";
        cout << "请选择查询种类：\n(1) 普通查询\n(2) 统计查询\n(3) 排序查询\n";
        cin.sync();
        cin >> input_flag;
    };
    auto exit_judge = [&]() {
        cout << "是否还要继续？(Y/N)：";
        cin.sync();
        cin >> exit_flag;
    };
    while (true) {
        main_menu();
        if (input_flag == 1) {
            NormalQuery();
        }
        else if (input_flag == 2) {
            StatisticQuery();
        }
        else if (input_flag == 3) {
            SortQuery();
        }
        else {
            cout << "输入有误！请重新选择。";
            continue;
        }

        exit_judge();
        while (exit_flag != "Y" && exit_flag != "N" && exit_flag != "y" && exit_flag != "n") {
            cout << "输入有误！请重新输入。";
            exit_judge();
        }
        if (exit_flag == "N" || exit_flag == "n") {
            cout << "退出程序。";
            break;
        }
    }
}

void Console::NormalQuery() {

    auto isNumber = [](const string &s) ->bool {
        auto it = s.begin();
        while(it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    };

    string input;
    int query_method, request;
    cout << "请输入欲查询城市名或城市id：";
    cin.sync();
    cin >> input;
    cout << "请选择查询日期依据：\n(1)周(2)月(3)季度(4)全年\n";
    cin.sync();
    cin >> query_method;
    if(query_method!=4){
        cout << "请输入欲查询的数据：";
        cin.sync();
        cin >> request;
    }

    DataSet output = example;
    if(isNumber(input)) {
        output = basic_method[query_method - 1](output.SelectCity(std::stoi(input)),request);
    }
    else {
        output = basic_method[query_method - 1](output.SelectByName(input), request);
    }
    output.DisplayDetail();
}

void Console::StatisticQuery() {
    int query_flag;
    cout << "请选择统计查询的类型：\n(1)污染天数查询\n(2)受污染城市查询\n";
    cin.sync();
    cin >> query_flag;

    //污染天数
    if(query_flag == 1) {
        string city_name, pollution;
        int query_method, request=0;
        cout << "请输入欲查询的城市名：";
        cin >> city_name;
        cout << "请选择查询日期依据：\n(1)周(2)月(3)季度(4)全年\n";
        cin.sync();
        cin >> query_method;
        if(query_method!=4){
            cout << "请输入欲查询的数据：";
            cin.sync();
            cin >> request;
        }
        cout << "请输入欲查询的空气质量:\n(优、良、轻微污染、轻度污染、重污染)\n";
        cin.sync();
        cin >> pollution;

        string prefix = (query_method != 4) ? "第"+std::to_string(request) : "";
        
        string suffix[] = {"周", "月", "季度", "全年"};
        cout << "2006年 " << city_name << prefix << suffix[query_method - 1]
             << "空气质量为" << pollution << "的天数为"
             << basic_method[query_method - 1](example.SelectByName(city_name), request).PollutionDays(pollution)
             << "\n";
    } // end of if query_flag == 1

    //污染情况
    if(query_flag==2) {
        string pollution;
        int query_method, request=0;
        int threhold;
        cout << "请选择查询日期依据：\n(1)周(2)月(3)季度(4)全年\n";
        cin.sync();
        cin >> query_method;
        if(query_method!=4){
            cout << "请输入欲查询的数据：";
            cin.sync();
            cin >> request;
        }
        cout << "请输入欲查询的空气质量:\n(优、良、轻微污染、轻度污染、重污染)\n";
        cin.sync();
        cin >> pollution;
        cout << "请输入筛选天数(至少):";
        cin.sync();
        cin >> threhold;

        DataSet selected_dataset = basic_method[query_method - 1](std::move(example), request);
        auto count_map = selected_dataset.CountByCityGroup(pollution);
        
        string prefix = (query_method != 4) ? "第"+std::to_string(request) : "";
        string suffix[] = {"周", "月", "季度", "全年"};
        cout << "2006年" << prefix << suffix[query_method - 1] << "空气质量为"
             << pollution << "在" << threhold << "天以上的城市有：\n";
        for(auto i : count_map) {
            if(i.second >= threhold) {
                cout << i.first << "：" << i.second << "天\n";
            }
        }
        cout << "\n";
    } //end of if query_flag == 2
}

void Console::SortQuery() {
    int query_method, request=0;
    int limit;
    cout << "请选择查询日期依据：\n(1)周(2)月(3)季度(4)全年\n";
    cin.sync();
    cin >> query_method;
    if(query_method!=4) {
        cout << "请输入欲查询的数据：";
        cin.sync();
        cin >> request;
    }
    cout << "请输入显示排行榜的城市个数：";
    cin.sync();
    cin >> limit;

    basic_method[query_method - 1](std::move(example), request).ShowTopK(limit);
}