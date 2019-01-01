#include "Graph.h"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <limits>

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

Graph::Graph(string filename) {
    unordered_map<string, Edge*> in_edge_table = {};
    unordered_map<string, Edge*> out_edge_table = {};
    ifstream in_file(filename);
    if(!in_file.is_open()) {
        throw std::invalid_argument("wrong input filename!");
    }
    while(!in_file.eof()) {
        string line_curse1;
        string line_curse2;
        getline(in_file, line_curse1);
        getline(in_file, line_curse2);
        stringstream ss(line_curse1 + ' ' + line_curse2);

        string vertex1, vertex2;
        Airline temp_data;
        ss >> temp_data.id_ >> vertex1 >> vertex2;
        ss >> temp_data.start_time_out_ >> temp_data.end_time_out_ >> temp_data.cost_;
        for(int i = 0; i < 3; i++) {
            ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        }
        ss >> temp_data.start_time_in_ >> temp_data.end_time_in_;
        temp_data.duration_ = temp_data.start_time_in_ - temp_data.end_time_in_;

        Edge *new_edge_ptr = new Edge{temp_data, vertex1, vertex2};
        if(in_edge_table.count(vertex1) == 0) {
            in_edge_table[vertex1] = new_edge_ptr;
        }
        else {
            Edge *temp_ptr = in_edge_table[vertex1];
            while(temp_ptr->next_in_ != nullptr) {
                temp_ptr = temp_ptr->next_in_;
            }
            temp_ptr->next_in_ = new_edge_ptr;
        }

        if(out_edge_table.count(vertex2) == 0) {
            out_edge_table[vertex2] = new_edge_ptr;
        }
        else {
            Edge *temp_ptr = out_edge_table[vertex2];
            while(temp_ptr->next_out_ != nullptr) {
                temp_ptr = temp_ptr->next_out_;
            }
            temp_ptr->next_out_ = new_edge_ptr;
        }
    }
}