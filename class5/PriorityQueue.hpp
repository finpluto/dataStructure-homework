#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_
// 使用最小堆实现优先队列
// 该容器可以存放各种实现了"<"操作符的对象
#include <vector>
#include <algorithm>

template<typename T>
class PrioQueue {
  private:
    std::vector<T> heap_;
    void siftDown(std::size_t index);
    void siftUp(std::size_t index);
    void heapify();
  public:
    bool empty() { return heap_.empty(); }
    std::size_t size() { return heap_.size(); }
    PrioQueue() { heap_ = {}; };
    PrioQueue(std::vector<T> input);
    void insert(T element);
    T pop();
};

template<typename T>
void PrioQueue<T>::siftDown(std::size_t index) {
    while(index < heap_.size()) {
        std::size_t smallest = index;
        std::size_t leftChild = 2 * index + 1;
        std::size_t rightChild = 2 * (index + 1);
        if(leftChild < heap_.size() && heap_[leftChild] < heap_[smallest]) {
            smallest = leftChild;
        }
        if(rightChild < heap_.size() && heap_[rightChild] < heap_[smallest]) {
            smallest = rightChild;
        }
        if(smallest == index) {
            break;
        }
        std::swap(heap_[index], heap_[smallest]);
    }
}

template<typename T>
void PrioQueue<T>::siftUp(std::size_t index) {
    while (index != 0) {
        std::size_t parent = (index - 1) / 2;
        if(heap_[parent] < heap_[index]) {
            break;
        }
        std::swap(heap_[parent], heap_[index]);
        index = parent;
    }
}

template<typename T>
void PrioQueue<T>::heapify() {
    for (int i = int(heap_.size()) / 2; i >= 0; i--) {
        siftDown(i);
    }
}

template<typename T>
PrioQueue<T>::PrioQueue(std::vector<T> input) {
    heap_ = {};
    for(auto i : input) {
        heap_.push_back(i);
    }
    heapify();
}

template<typename T>
void PrioQueue<T>::insert(T element) {
    heap_.push_back(element);
    siftUp(heap_.size() - 1);
}

template<typename T>
T PrioQueue<T>::pop() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    T return_element = heap_.back();
    heap_.pop_back();
    siftDown(0);
    return return_element;
}

#endif