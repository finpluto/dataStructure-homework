#ifndef TIME_H_
#define TIME_H_

#include <iostream>
using std::istream;
using std::ostream;

class Time {
private:
    int hour_ = 0;
    int minute_ = 0;
public:
    Time() = default;
    ~Time() = default;
    Time(int hour, int minute);
    //Time operator+(const Time &rhs);
    Time operator-(const Time &rhs);
    operator int();
    friend istream &operator>>(istream &is, Time &obj);
    friend ostream &operator<<(ostream &os, Time &obj);
};

#endif