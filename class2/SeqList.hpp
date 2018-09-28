#ifndef SEQ_LIST_HPP
#define SEQ_LIST_HPP
#define DEFAULT_CAPACITY 10

class SeqList
{
private:
    int size = 0;
    int capacity = DEFAULT_CAPACITY;
    int *element;
public:
    SeqList(){
        element = new int[capacity];
    }
    /* default construct function */
    SeqList(int array[], int sizeOfArray);
    /* construct function: initial by a array */
    SeqList(int array[], int left, int right);
    /* construct function: initial by a part of array */
    SeqList(const SeqList &obj);
    /* copy construct function */
    ~SeqList(){ delete[] element; };
    /* destruct function: release the allocated memory. */
    int findObj(int value) const;
    /* find element which equals to value,
     * if can be found , return the index,
     * otherwise, return -1.
     */
    void insertObj(int value, int index);
    /* insert value at index,
     * the index can be more than size.
     */
    void append(int value);
    /* append value to the end of list */
    void deleteObj(int index);
    /* delete the element on the index of list */
    bool isEmpty(){ return !size; };
    /* if list is empty , return true,
     * otherwise, return false.
     */
    bool isFull(){ return size==capacity; };
    /* if list is full, return true,
     * otherwise, return false.
     */
    void expand();
    /* to expand the available space of list */
    int getSize() const { return size; }
    /* return the size(or length) of list */
    void print();
    /* print all the element of list, seperated by space */
    int operator[](int index)const{
        if(index>=size)
            throw "Out of range";
        else
            return element[index]; 
    }
    /* reload operator[] to return a right value,
     * make list accessible like array.
     */
};
#endif
