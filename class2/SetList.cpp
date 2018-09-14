/* the implement file of SetList.hpp
 * created by finp 
 * 18-09-13 version 0.1
 */
#include<iostream>
#include "SetList.hpp"

SetList::SetList(int values[], int length): head(nullptr)
{
    for(int i=0; i<length; i++){
        if(!findObj(values[i]))
            addAtTail(values[i]);
    }
}

SetList::SetList(const SetList &obj)
{
    ListNode *copyHead = new ListNode(obj.head->val);
    this->head = copyHead;
    ListNode *tmp = obj.head->next;
    for(;tmp!=nullptr;tmp=tmp->next){
        ListNode *addingNode = new ListNode(tmp->val);
        copyHead->next = addingNode;
        copyHead = copyHead->next;
    }
    copyHead->next = nullptr;
}

SetList::~SetList()
{
    for(;head!=nullptr;head=head->next){
        ListNode *tmp = head;
        delete tmp;
    }
}

void SetList::addAtTail(int value)
{
    if(head==nullptr){
        ListNode *addingNode = new ListNode(value);
        head = addingNode;
        return;
    }
    ListNode *tail = head;
    for(;tail->next!=nullptr;tail=tail->next){}
    ListNode *addingNode = new ListNode(value);
    tail->next = addingNode;
}

bool SetList::findObj(int value)
{
    bool flag = false;
    ListNode *tmp = head;
    for(;tmp!=nullptr;tmp=tmp->next){
        if(tmp->val==value)
            flag = true;
    }
    return flag;
}

void SetList::insertObj(int value)
{
    if(findObj(value)) return;
    ListNode *tmp = head;
    ListNode *prevOfTmp =nullptr;
    while(tmp!=nullptr&&tmp->val<value){
        prevOfTmp = tmp;
        tmp = tmp->next;
    }
    ListNode *addingNode = new ListNode(value);
    if(prevOfTmp==nullptr){
        addingNode->next = head;
        head = addingNode;
    }
    else{
        prevOfTmp->next = addingNode;
        addingNode->next = tmp;
    }
}

void SetList::deleteObj(int value)
{
    if(!findObj(value)) return;
    ListNode *tmp = head;
    ListNode *prevOfTmp = nullptr;
    while(tmp->val!=value){
        prevOfTmp = tmp;
        tmp = tmp->next;
    }
    if(prevOfTmp==nullptr){
        head = head->next;
        delete tmp;
    }
    else{
        prevOfTmp->next = tmp->next;
        delete tmp;
    }
}

void SetList::print()
{
    ListNode *tmp = head;
    for(;tmp!=nullptr;tmp=tmp->next){
        std::cout << tmp->val << "->";
    }
    std::cout << "NULL" << std::endl;
}

SetList unite(SetList A,SetList B){
    SetList *C = new SetList;
    *C = A;
    ListNode *tmp = B.head;
    for(;tmp!=nullptr;tmp=tmp->next){
        C->insertObj(tmp->val);
    }
    return *C;
}

SetList intersect(SetList A,SetList B){
    SetList *C = new SetList;
    ListNode *tmp = B.head;
    for(;tmp!=nullptr;tmp=tmp->next){
        if(A.findObj(tmp->val))
            C->insertObj(tmp->val);
    }
    return *C;
}
