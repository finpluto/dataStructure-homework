#include<iostream>
#include "SeqList.hpp"

SeqList::SeqList(int array[], int sizeOfArray)
{
    element = new int[capacity];
    if(sizeOfArray>capacity)    expand();
    for(int i=0; i<sizeOfArray; i++)
        element[i] = array[i];
    size = sizeOfArray;
}

SeqList::SeqList(int array[], int left, int right)
{
    element = new int[capacity];
    int length = right-left+1;
    if(length>capacity)    expand();
    for(int i=0; i<length; i++)
        element[i] = array[i];
    size = length;
}

SeqList::SeqList(const SeqList &obj)
{
    element = new int[capacity];
    if(capacity<obj.getSize())  expand();
    for(int i=0; i<obj.getSize(); i++)
        element[i] = obj[i];
    size = obj.getSize();
}

int SeqList::findObj(int value) const
{
    if(size==0) return -1;
    for(int i=0; i<size; i++){
        if(element[i]==value)
            return i;
    }
    return -1;
}

void SeqList::insertObj(int value, int index)
{
    if(index>size)    return;
    if(capacity==size)  expand();
    for(int j=size-1; j>=index; j--){
        element[j+1] = element[j];
    }
    element[index] = value;
    size += 1;
}

void SeqList::append(int value){
    if(capacity==size) expand();
    element[size] = value;
    size += 1;
}

void SeqList::deleteObj(int index)
{
    if(index>=size)
        return;
    for(int i=index; i<size-1; i++)
        element[i] = element[i+1];
    size -= 1;
}

void SeqList::expand()
{
    capacity *= 2;
    int *oldElement = element;
    element = new int[capacity];
    for(int i=0; i<size; i++)
        element[i] = oldElement[i];
    delete[] oldElement;
}

void SeqList::print()
{
    for(int i=0; i<size; i++)
        std::cout << element[i] << ' ';
    std::cout << '\n';
}
