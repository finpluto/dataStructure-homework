#include "Time.h"

Time::Time(int hour, int minute) : hour_(hour), minute_(minute) {
    if(minute_ > 59) {
        hour_ += minute_ / 60;
        minute_ = minute_ % 60;
    }
    if(hour_ > 23) {
        hour_ = hour_ % 24;
    }
}

Time Time::operator-(const Time &rhs) {
    int left_minute = hour_ * 60 + minute_;
    int right_minute = rhs.hour_ * 60 + rhs.minute_;
    int result = left_minute - right_minute;
    if(result < 0) {
        result = 24 * 60 + result;
    }
    return {0, result};
}

Time::operator int() {
    return hour_ * 60 + minute_;
}

istream &operator>>(istream &is, Time &obj) {
    is >> obj.hour_ >> obj.minute_;
    return is;
}

ostream &operator<<(ostream &os, Time &obj) {
    os << obj.hour_ << ':' << obj.minute_;
    return os;
}