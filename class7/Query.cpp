#include "Query.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>

using std::cout;
using std::ifstream;
using std::stringstream;

DataADay::DataADay(
    int city_id,
    string city_name,
    string pollution_kind,
    int quality_index,
    string grade,
    string pollution,
    int year,
    int month,
    int day
) {
    city_id_ = city_id;
    city_name_ = city_name;
    pollution_kind_ = pollution_kind;
    quality_index_ = quality_index;
    grade_ = grade;
    pollution_ = pollution;
    year_ = year;
    month_ = month;
    day_ = day;
}

void DataADay::Show() {
    cout << city_id_ << city_name_ << pollution_kind_ << quality_index_
         << grade_ << pollution_ << year_ << month_ << day_;
}

DataSet::DataSet(string input_filename) {
    ifstream in_file(input_filename);
    if(!in_file.is_open()) {
        throw std::invalid_argument("wrong input filename!");
    }
    while(!in_file.eof()) {
        string line_curse;
        getline(in_file, line_curse);
        stringstream ss{line_curse};

        int city_id;
        string city_name;
        string pollution_kind;
        int quality_index;
        string grade;
        string pollution;
        int year;
        int month;
        int day;

        ss >> city_id >> city_name >> pollution_kind >> quality_index
           >> grade >> pollution >> year >> month >> day;

        data_array_.push_back(new DataADay{
            city_id, city_name, pollution_kind, quality_index,
            grade, pollution, year, month, day});
    }
    in_file.close();
}

DataSet::DataSet(vector<DataADay *> &data_array) {
    data_array_.assign(data_array.begin(), data_array.end());
}

void DataSet::ReleaseMemo() {
// 释放new操作符申请的DataADay类型对象的空间
    for(auto i : data_array_) {
        delete i;
    }
    for(auto i : avg_) {
        delete i;
    }
}

DataSet &DataSet::Qsort(function<bool(DataADay *, DataADay *)> compare) {
// 特化快速排序算法
// compare为比较函数，语义等于less(a,b)
// 应用vector中的随机访问迭代器来完成通用算法设计
    typedef vector<DataADay *>::iterator iter;

    auto swap = [](iter a, iter b) {
        auto temp = *a;
        *a = *b;
        *b = temp;
    };
    auto partition = [&](iter left, iter right)->iter {
        auto pivot = right; // select last one as pivot.
        auto i = left - 1;
        for (auto j = left; j < right; j++) {
            if(compare(*j, *pivot)) {
                i++;
                swap(i, j);
            }
        }
        swap(i+1, pivot);
        return i + 1;
    };
    function<void(iter, iter)> quicksort = [&](iter left, iter right) {
        if(left < right) {
            auto p = partition(left, right);
            quicksort(left, p - 1);
            quicksort(p + 1, right);
        }
    };

    quicksort(data_array_.begin(), data_array_.end() - 1);
    return *this;
}

void DataSet::DisplayDetail() {
// 显示当时数据集中的所有数据对象详情
    for(auto &i : data_array_) {
        i->Show();
        cout << '\n';
    }
}

bool DataSet::Empty() {
    return data_array_.empty();
}

DataSet DataSet::SelectCity(int city_id) {
    vector<DataADay *> new_data_array = {};
    for(auto i : data_array_) {
        if(i->city_id_ == city_id) {
            new_data_array.push_back(i);
        }
    }
    DataSet new_data_set{new_data_array};
    return new_data_set;
}

DataSet DataSet::SelectByName(string city_name) {
    vector<DataADay *> new_data_array = {};
    for(auto i : data_array_) {
        if(i->city_name_ == city_name) {
            new_data_array.push_back(i);
        }
    }
    return {new_data_array};
}

DataSet DataSet::SelectByTime(int month, int day) {
    vector<DataADay *> new_data_array = {};
    if(day == 0) {
        for(auto i : data_array_) {
            if(i->month_ == month) {
                new_data_array.push_back(i);
            }
        }
    }
    else {
        for(auto i : data_array_) {
            if(i->month_ == month && i->day_ == day) {
                new_data_array.push_back(i);
            }
        }
    }
    return {new_data_array};
}

DataSet DataSet::SelectByRange(int begin_month, int begin_day, int end_month, int end_day) {
    vector<DataADay *> new_data_array;
    for(auto i : data_array_) {
        if(i->month_>=begin_month &&
           i->month_<=end_month &&
           i->day_>=begin_day &&
           i->day_<=end_day) {
            new_data_array.push_back(i);
        }
    }
    return {new_data_array};
}

DataSet DataSet::operator+(const DataSet &obj) {
    vector<DataADay *> new_data_array = {};
    new_data_array.insert(
        new_data_array.end(),
        data_array_.begin(),
        data_array_.end()
    );
    new_data_array.insert(
        new_data_array.end(),
        obj.data_array_.begin(),
        obj.data_array_.end()
    );
    return {new_data_array};
}

int DataSet::PollutionDays(string pollution) {
    int count = 0;
    for(auto i : data_array_) {
        if(i->pollution_ == pollution) {
            count++;
        }
    }
    return count;
}

unordered_map<string, int> DataSet::CountByCityGroup(string pollution) {
    unordered_map<string, int> count_map;
    for(auto i : data_array_) {
        if(i->pollution_ == pollution) {
            if(count_map.count(i->city_name_) == 0) {
                count_map[i->city_name_] = 1;
            }
            else {
                count_map[i->city_name_]++;
            }
        }
    }
    return count_map;
}

void DataSet::statisticSort(function<bool(statistic_data *, statistic_data*)> compare) {
    typedef vector<statistic_data *>::iterator iter;

    auto swap = [](iter a, iter b) {
        auto temp = *a;
        *a = *b;
        *b = temp;
    };
    auto partition = [&](iter left, iter right)->iter {
        auto pivot = right; // select last one as pivot.
        auto i = left - 1;
        for (auto j = left; j < right; j++) {
            if(compare(*j, *pivot)) {
                i++;
                swap(i, j);
            }
        }
        swap(i+1, pivot);
        return i + 1;
    };
    function<void(iter, iter)> quicksort = [&](iter left, iter right) {
        if(left < right) {
            auto p = partition(left, right);
            quicksort(left, p - 1);
            quicksort(p + 1, right);
        }
    };

    quicksort(avg_.begin(), avg_.end() - 1);
}

void DataSet::ShowTopK(int k) {
    unordered_map<string, double> day_map;
    unordered_map<string, double> index_sum_map;
    for(auto i : data_array_) {
        if(day_map.count(i->city_name_) == 0) {
            day_map[i->city_name_] = 1;
            index_sum_map[i->city_name_] = i->quality_index_;
        }
        else {
            day_map[i->city_name_]++;
            index_sum_map[i->city_name_] += i->quality_index_;
        }
    }

    for(auto i : day_map) {
        avg_.push_back(new statistic_data{i.first, index_sum_map[i.first] / i.second});
    }
    statisticSort([](statistic_data *a, statistic_data *b) ->bool {
        return a->statistic_number_ < b->statistic_number_;
    });
    int count = 0;
    cout << "选择日期区间中的平均空气指数Top" << k << "排行榜\n";
    for(auto i : avg_) {
        cout << i->city_name_ << ": " << i->statistic_number_ << "\n";
        count++;
        if(count == k)
            break;
    }
}