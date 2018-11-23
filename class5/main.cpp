#include "HuffmanTree.h"
#include <vector>
#include <iostream>

int main() {
    std::unordered_map<char, int> input = {{'a', 4}, {'b', 7}, {'c', 5}, {'d', 2}, {'e', 9}};

    Huffman example(input);
    example.printDict();
    std::cout << '\n';

    std::cout << "the orgin string of code \"11000111000101011\" is:\n";
    std::cout << example.decode("11000111000101011") << '\n' << '\n';
    std::cout << "the code of \"ecabcbbe\" is:\n";
    std::cout << example.encode("ecabcbbe") << '\n';

    return 0;
}