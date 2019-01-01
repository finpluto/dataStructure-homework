#ifndef GRAPH_H_
#define GRAPH_H_

#include "Time.h"
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
using std::function;
using std::string;
using std::unordered_map;
using std::vector;

struct Airline {
    int airline_id_ = 0;
    Time start_time_;
    Time end_time_;
    int cost_ = 0;
    Time duration_;
};

struct Edge;

struct Vertex {
    string city_name_;
    Edge *first_edge_;
    Vertex(string city_name):
        city_name_(city_name), first_edge_(nullptr) {}
};

struct Edge {
    Airline data_;
    int id_;
    Edge *next_edge_;
    Edge(Airline data, int id):
        data_(data), id_(id), next_edge_(nullptr) {}
};

class Graph {
private:
    vector<Vertex*> vertexes_ = {};
    unordered_map<string, int> city_id_table_ = {};
    vector<function<int(Edge *)>> selectWeight = {
        [](Edge *) { return 1; },
        [](Edge *edge_node) { return edge_node->data_.duration_; },
        [](Edge *edge_node) { return edge_node->data_.cost_; }};

    void LinkEdge(int departure_id, Edge *LinkingEdge);
    float selectLine(int departure, int destination, function<int(Edge *)> weight);
    void traceRoute(int *prev, int departure, int destination);
    Edge *selectEdge(int departure, int destination);

  public:
    Graph() = delete;
    Graph(const Graph &) = delete;
    Graph(string file_name_);
    ~Graph();
    void Show();
    float Dijstra(int source,int destination, int method);
};

#endif