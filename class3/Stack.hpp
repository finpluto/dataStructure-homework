#ifndef STACK_HPP
#define STACK_HPP
// Custom template class of stack
// 自定义的栈模板类
// 使用带头节点的单链表实现

template<typename Elem>
class Stack
{
private:
    struct ListNode{
        Elem val;
        ListNode* prev;
        ListNode(Elem x): val(x), prev(nullptr){}
    };
    // struct of list node and constructor.
    
    ListNode *top;
    // use head as top
public:
    Stack(): top(nullptr){}
    // default constructor.
    
    ~Stack();
    // destructor.
    
    bool isEmpty(){ return top==nullptr; }
    // if the stack is empty, return false.
    
    void push(Elem input);
    // push an element on the top of stack.
    
    Elem pop();
    // pop the top element and return it.
    
    Elem getTop();
    // return the top element without pop it.
};

template<typename Elem>
Stack<Elem>::~Stack()
{
    while(top!=nullptr){
        ListNode* tmp = top;
        top = top->prev;
        delete tmp;
    }
}

template<typename Elem>
void Stack<Elem>::push(Elem input)
{
    ListNode *newNode = new ListNode(input);
    newNode->prev = top;
    top = newNode;
}

template<typename Elem>
Elem Stack<Elem>::pop()
{
    if(top==nullptr){
        throw "Stack is empty!";
    }
    ListNode* tmp = top;
    Elem output = tmp->val;
    top = top->prev;
    delete tmp;
    return output;
}

template<typename Elem>
Elem Stack<Elem>::getTop()
{
    if(top==nullptr) throw "Stack is empty!";
    return top->val;
}

#endif
