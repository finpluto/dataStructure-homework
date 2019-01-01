#include "Graph.h"
#include <iostream>
using std::cin;
using std::cout;

int main() {
    Graph example{"routes.txt"};
    example.Show();
    int departure, destination, method;
    cout << "请按顺序输入出发地与目的地，用空格隔开：\n";
    cin >> departure >> destination;
    cout << "请选择筛选方案：\n"
         << "(1) 中转次数最少 (2) 飞行时间最短 (3) 费用最小\n";
    cin >> method;
    string shortWord[3] = {"最少中转次数（次）", "最短飞行时间（分钟）", "最小费用（元）"};
    auto cost = example.Dijstra(departure-1, destination-1, method-1);
    cost = (method == 1) ? cost - 1 : cost;
    cout << shortWord[method - 1] << "为" << cost << '\n';
    return 0;
}