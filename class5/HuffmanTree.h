#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <vector>
#include <unordered_map>
#include <string>
using std::string;

struct TreeNode {
    char word_;
    int weight_;
    TreeNode *leftChild_;
    TreeNode *rightChild_;
    TreeNode(char word, int weight,
             TreeNode* leftChild = nullptr, TreeNode* rightChild = nullptr) {
        word_ = word;
        weight_ = weight;
        leftChild_ = leftChild;
        rightChild_ = rightChild;
    }
};

class SmartTreeNodePtr {
// Wrapped class of TreeNode pointer
// make TreeNode pointer comparable for PriorityQueue
  private:
    TreeNode *ptr;
  public:
    SmartTreeNodePtr(TreeNode *p) { ptr = p; }
    TreeNode *operator->() { return ptr; }
    TreeNode operator*() { return *ptr; }

    operator TreeNode *() { return ptr; }
    bool operator<(SmartTreeNodePtr stnp) { return ptr->weight_ < stnp->weight_; }
    bool operator>(SmartTreeNodePtr stnp) { return ptr->weight_ > stnp->weight_; }
};

class Huffman {
  private:
    TreeNode *root_;
    std::unordered_map<char, string> dict_;
    void destroyTree(TreeNode *root);
    void generateDict(TreeNode *root);
  public:
    Huffman(std::unordered_map<char, int> &input);
    ~Huffman();
    string encode(string input);
    string decode(string input);
    void printDict();
};

#endif