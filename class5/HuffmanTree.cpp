#include "HuffmanTree.h"
#include "PriorityQueue.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
using std::cout;
using std::string;

Huffman::Huffman(std::unordered_map<char, int> &input) {
// Build up the Huffman Tree
// and generate the coding dictionary
    PrioQueue<SmartTreeNodePtr> pq;
    SmartTreeNodePtr new_tree_node = nullptr;
    SmartTreeNodePtr leftChild = nullptr;
    SmartTreeNodePtr rightChild = nullptr;
    for(auto i : input) {
        new_tree_node = new TreeNode(i.first, i.second);
        pq.insert(new_tree_node);
    }
    while(pq.size() > 1) {
        leftChild = pq.pop();  //the smallest one
        rightChild = pq.pop();  //second smallest one
        new_tree_node = new TreeNode(char(), rightChild->weight_+leftChild->weight_, leftChild, rightChild);
        pq.insert(new_tree_node);
    }
    root_ = pq.pop();

    generateDict(root_);
}

Huffman::~Huffman() {
    destroyTree(root_);
}

void Huffman::destroyTree(TreeNode *root) {
// release the occupied memory
    if(root != nullptr) {
        destroyTree(root->leftChild_);
        destroyTree(root->rightChild_);
        delete root;
    }
    root = nullptr;
}

void Huffman::generateDict(TreeNode *root) {
// Depth-first algorithm
// to search all the leaf node
// for every character's code
    static string code_of_char = "";
    if(root->leftChild_ == nullptr && root->rightChild_ == nullptr) {
        dict_[root->word_] = code_of_char;
        return;
    }
    code_of_char.append("0");
    generateDict(root->leftChild_);
    code_of_char.pop_back();

    code_of_char.append("1");
    generateDict(root->rightChild_);
    code_of_char.pop_back();
}

void Huffman::printDict() {
    cout << "Coding dictionary:\n";
    for(const auto &i : dict_) {
        cout << i.first << ':' << i.second << '\n';
    }
}

string Huffman::encode(string input) {
    string coding_str = "";
    for(string::iterator it = input.begin(); it != input.end(); it++)
    {
        if(dict_.count(*it) == 0) {
            throw std::invalid_argument("Wrong input string!");
        }
        coding_str.append(dict_[*it]);
    }
    return coding_str;
}

string Huffman::decode(string input) {
    string origin_str = "";
    TreeNode *tnptr = root_;
    for(string::iterator it = input.begin(); it != input.end(); it++) {
        if(*it == '0') {
            tnptr = tnptr->leftChild_;
        }
        if(*it == '1') {
            tnptr = tnptr->rightChild_;
        }
        if(tnptr->leftChild_==nullptr && tnptr->rightChild_==nullptr) {
            origin_str = origin_str + tnptr->word_;
            tnptr = root_;
        }
    }
    if(tnptr != root_) {
        throw std::invalid_argument("Wrong input string!");
    }
    else {
        return origin_str;
    }
}