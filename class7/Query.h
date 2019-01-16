#ifndef QUERY_H_
#define QUERY_H_

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

using std::function;
using std::string;
using std::unordered_map;
using std::vector;

class DataADay {
public:
    int city_id_;
    string city_name_;
    string pollution_kind_;
    int quality_index_;
    string grade_;
    string pollution_;
    int year_;
    int month_;
    int day_;

    DataADay() = delete;
    DataADay(
        int city_id,
        string city_name,
        string pollution_kind,
        int quality_index,
        string grade,
        string pollution,
        int year,
        int month,
        int day
    );
    void Show();
};

struct statistic_data {
    string city_name_;
    double statistic_number_;
};

class DataSet {
private:
    vector<DataADay *> data_array_ = {};


    vector<statistic_data *> avg_ = {};
    void statisticSort(function<bool(statistic_data *, statistic_data *)> compare);

  public:
    DataSet() = delete;
    DataSet(string input_filename);
    DataSet(vector<DataADay *> &data_array);

    DataSet &Qsort(function<bool(DataADay*, DataADay *)> compare);
    DataSet SelectCity(int city_id);
    DataSet SelectByName(string city_name);
    DataSet SelectByTime(int month, int day = 0);
    DataSet SelectByRange(int begin_month, int begin_day, int end_month, int end_day);
    DataSet operator+(const DataSet &obj);

    int PollutionDays(string pollution);
    unordered_map<string, int> CountByCityGroup(string pollution);
    void ShowTopK(int k);

    void DisplayDetail();
    bool Empty();
    void ReleaseMemo();
};

#endif