#ifndef SET_LIST_HPP
#define SET_LIST_HPP
class SetList
{
private:
    struct ListNode{
        int val;
        ListNode* next;
        ListNode(int a):val(a), next(nullptr){}
    };
    ListNode *head;
public:
    SetList(){}
    /* default construct function
     * do nothing.
     */
    SetList(int values[], int length);
    /* initialize the set by and ordered array.
     */
    ~SetList();
    /* destruct function
     * abandon all node of the list,
     * release all occupied memory.
     */
    void addAtTail(int value);
    /* adding an node whose val equals to value,
     * to the end of the list.
     */
    bool findObj(int value);
    /* find object whose val equals to value in the set 
     * if found, return true;
     * otherwise return false.
     */
    void insertObj(int value);
    /* insert an new object to set
     * 'cause the set is unordered,but the list is order
     * this function act like selection sort.
     * if object have already existed, do nothing.
     */
    void deleteObj(int value);
    /* delete an object from the set.
     */
    SetList unite(SetList A, SetList B);
    /* calculate the union of set A and B.
     * return united set.
     */
    SetList intersect(SetList A, SetList B);
    /* calculate the intersection of set A and B.
     * return intersection set.
     */
    SetList subtract(SetList A, SetList B);
    /* calculate the complement of set A and B.
     * return complement set.
     */
    void print();
    /* output all the object in the set by order.
     */
};
#endif
