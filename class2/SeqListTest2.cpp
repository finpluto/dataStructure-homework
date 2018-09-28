#include<iostream>
#include "SeqList.hpp"
using namespace std;

int main()
{
    int initArray[5] = {1,2,3,4,5};
    SeqList A(initArray,5);
    A.print();
    SeqList B(initArray,3,4);
    B.print();
    SeqList C = A;
    C.print();
    cout << &C << '\n' << &A << '\n';
    C.append(10);
    C.print();
    C.insertObj(125,3);
    C.print();
    C.deleteObj(5);
    C.print();
    return 0;
}
