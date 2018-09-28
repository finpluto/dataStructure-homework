#include<iostream>
#include "SetList.hpp"
using namespace std;

int main()
{
    int initArray1[4] = {2,3,5,7};
    int initArray2[5] = {2,4,6,8,10};
    SetList A(initArray1,4);
    SetList B(initArray2,5);
    cout << "Set A is ";
    A.print();
    cout << "Set B is ";
    B.print();
    cout << "add 11 to A:";
    A.insertObj(11);
    A.print();
    cout << "delete 10 in B:";
    B.deleteObj(10);
    B.print();
    cout << "Is 3 in the Set A? " << A.findObj(3) << '\n';
    cout << "Is 15 in the Set A? " << A.findObj(15) << '\n';
    cout << "The union of A and B is ";
    unite(A,B).print();
    cout << "The intersection of A and B is ";
    intersect(A,B).print();
    cout << "Set A-B is ";
    substract(A,B).print();
    cout << "Set B-A is ";
    substract(B,A).print();
}
