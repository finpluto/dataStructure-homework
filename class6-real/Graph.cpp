#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cfloat>
using std::cout;
using std::ifstream;
using std::stringstream;

Graph::Graph(string file_name) {
    ifstream in_file(file_name);
    if(!in_file.is_open()) {
        throw std::invalid_argument("wrong input filename!");
    }
    int counter = 0;
    while(!in_file.eof()) {
        string line_curse;
        getline(in_file, line_curse);
        stringstream ss{line_curse};

        Airline temp_data;
        string departure, destination;
        ss >> temp_data.airline_id_ >> departure >> destination;
        ss >> temp_data.start_time_ >> temp_data.end_time_ >> temp_data.cost_;
        temp_data.duration_ = temp_data.end_time_ - temp_data.start_time_;

        if(city_id_table_.count(departure) == 0) {
            city_id_table_[departure] = counter;
            vertexes_.push_back(new Vertex{departure});
            counter++;
        }
        if(city_id_table_.count(destination) == 0) {
            city_id_table_[destination] = counter;
            vertexes_.push_back(new Vertex{destination});
            counter++;
        }
        Edge *new_edge = new Edge{temp_data, city_id_table_[destination]};
        LinkEdge(city_id_table_[departure], new_edge);
    }
}

Graph::~Graph() {
    for(auto &i : vertexes_) {
        Edge *head = i->first_edge_;
        while(head!=nullptr) {
            Edge *temp = head;
            head = head->next_edge_;
            delete temp;
        }
    }
    for(auto &i : vertexes_) {
        delete i;
    }
}

void Graph::LinkEdge(int departure_id, Edge *LinkingEdge) {
    if(vertexes_[departure_id]->first_edge_ == nullptr) {
        vertexes_[departure_id]->first_edge_ = LinkingEdge;
        return;
    } else {
        Edge *ptr_i = vertexes_[departure_id]->first_edge_;
        while(ptr_i->next_edge_ != nullptr) {
            ptr_i = ptr_i->next_edge_;
        }
        ptr_i->next_edge_ = LinkingEdge;
        return;
    }
}

void Graph::Show() {
    cout << "城市列表:" << '\n';
    int counter = 1;
    for(auto i : vertexes_) {
        cout << "(" << counter << ")"
             << " " << i->city_name_ << "; ";
        counter++;
    }
    cout << '\n';
}

float Graph::Dijstra(int source, int destination, int method) {
    auto weight = selectWeight[method]; // the way to select weight data.
    int num = vertexes_.size();
    if(source<0 || source>num-1)
        return -1;

    float *dist = new float[num]{FLT_MAX};
    int *prev = new int[num];
    bool *S = new bool[num];

    // initial
    for (int i = 0; i < num; i++) { // except source vertex
        dist[i] = selectLine(source, i, weight);
        S[i] = false;
        if(dist[i] == FLT_MAX) {
            prev[i] = 0;
        }
        else {
            prev[i] = source;
        }
    }
    dist[source] = 0;
    S[source] = true; // add source vertex.

    for (int i = 0; i < num-1; i++) { // loop for num-1 times.
        float temp = FLT_MAX;
        int u = source;
        for (int j = 0; j < num; j++) {
            if(!S[j] && dist[j] < temp) {
                u = j;
                temp = dist[j];
            }
        }

        S[u] = true;

        for(int j = 0; j < num; j++) { // update dist and prev array.
            if(!S[j] && selectLine(u,j,weight) < FLT_MAX) {
                float newDist = dist[u] + selectLine(u, j, weight);
                if(newDist < dist[j]) {
                    dist[j] = newDist;
                    prev[j] = u;
                }
            }
        }

    }

    traceRoute(prev, source, destination);

    auto cost = dist[destination];

    delete[] dist;
    delete[] prev;
    delete[] S;
    return cost;
}


float Graph::selectLine(int departure, int destination, function<int(Edge *)> weight) {
    if(departure < 0 || departure > vertexes_.size())
        return FLT_MAX;
    
    if(departure == destination)
        return 0;

    auto head = vertexes_[departure]->first_edge_;
    while(head!=nullptr) {
        if(head->id_ == destination)
            return weight(head);
        head = head->next_edge_;
    }
    return FLT_MAX;
}

void Graph::traceRoute(int *prev, int departure, int destination) {
    vector<int> route = {};
    int temp = destination;
    route.push_back(temp);
    while(prev[temp] != departure) {
        temp = prev[temp];
        route.push_back(temp);
    }
    route.push_back(departure);
    std::reverse(route.begin(), route.end());
    cout << "搭乘线路: \n";
    for (int i = 0; i < route.size()-1; i++) {
        auto airline = selectEdge(route[i], route[i+1]);
        cout << i+1 << " :" << vertexes_[route[i]]->city_name_
             << " 至 " << vertexes_[airline->id_]->city_name_
             << " 航班号 " << airline->data_.airline_id_
             << '\n';
    }
}

Edge *Graph::selectEdge(int departure, int destination) {
    if(departure < 0 || departure > vertexes_.size())
        return nullptr;
    
    if(departure == destination)
        return nullptr;

    auto head = vertexes_[departure]->first_edge_;
    while(head!=nullptr) {
        if(head->id_ == destination)
            return head;
        head = head->next_edge_;
    }
    return nullptr;

}