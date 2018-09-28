#include<iostream>
#include<iomanip>
#include "SeqList.hpp"
using namespace std;

int main()
{
    int initArray[5] = {1,2,3,4,5};
    SeqList example(initArray,5);
    cout << "The array now is ";
    example.print();

    for(int i=6; i<9; i++)
        example.append(i);
    cout << "The array now is ";
    example.print();

    for(int i=9; i<13; i++)
        example.append(i);
    cout << "The array now is ";
    example.print();

    int sum = 0;
    double avg = 0;
    for(int i=0; i<example.getSize(); i++)
        sum += example[i];
    avg = double(sum) / double(example.getSize());
    cout << "The sum is " << sum << " and the average is "<< avg << '\n';
    return 0;
}
