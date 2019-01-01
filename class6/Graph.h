#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

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
};

struct Airline {
    int id_ = 0;
    Time start_time_in_;
    Time end_time_in_;
    Time start_time_out_;
    Time end_time_out_;
    int cost_ = 0;
    Time duration_;
};

struct Edge;

struct Vertex {
    Edge *first_in = nullptr;
    Edge *first_out = nullptr;
};

struct Edge {
    Airline data_;
    string vertex1_ = "";
    string vertex2_ = "";
    Edge *next_in_ = nullptr;
    Edge *next_out_ = nullptr;
};

class Graph {
private:
    unordered_map<string, Vertex> vertexes_ = {};

  public:
    Graph(string filename);
};



#endif