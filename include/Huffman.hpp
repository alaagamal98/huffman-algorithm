#ifndef SBE201_HUFFMAN_HPP
#define SBE201_HUFFMAN_HPP

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

namespace Huffman
{
//create a tree with data and frequancy in each node
struct Node
{
    Node(char d, int f)
    {
        data = d;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
    char data;
    int freq;
    Node *left;
    Node *right;
};

//create a functor to transform a max priorty queue to a min priorty queue
struct greater
{
    bool operator()(Node *left, Node *right)
    {
        return (left->freq > right->freq);
    }
};

//create a huffman tree from the map of characters and its frequencies
Node *makeTree(std::map<char, int> &freq)
{
    Node *Left, *Right, *Parent;
    std::priority_queue<Node *, std::vector<Node *>, greater> minheap;

    for (auto &A : freq)
    {
        minheap.push(new Node(A.first, A.second));
    }
    while (minheap.size() != 1)
    {
        Left = minheap.top();
        minheap.pop();
        Right = minheap.top();
        minheap.pop();
        Parent = new Node('%', Left->freq + Right->freq);
        Parent->left = Left;
        Parent->right = Right;
        minheap.push(Parent);
    }
    return minheap.top();
}

//create a map with each character and its binary code
void makeMap(Node *Tree, std::string code, std::map<char, std::string> &dict)
{
    if (Tree == nullptr)
        return;
    else if (Tree->data == '%')
    {
        makeMap(Tree->left, code + "0", dict);
        makeMap(Tree->right, code + "1", dict);
    }
    else if (Tree->data != '%')
    {
        dict.insert(std::pair<char, std::string>(Tree->data, code));
    }
}

//encode the text input to a binary huffman output using the created map
std::string encode(std::string input, std::map<char, std::string> &dict)
{
    std::string compressed;
    for (int i = 0; i < input.size(); ++i)
    {
        std::string New = dict.find(input[i])->second;
        compressed += New;
    }
    return compressed;
}

//decode the binary code to its original text using huffman tree
std::string decode(std::string output, Node *tree)
{
    std::string words;
    int i = 0;
    while (i < output.size())
    {
        Node *current = tree;
        while (current->data == '%' && i < output.size())
        {
            if (output[i] == '0')
            {
                current = current->left;
                ++i;
            }
            else if (output[i] == '1')
            {
                current = current->right;
                ++i;
            }
        }
        words.push_back(current->data);
    }
    return words;
}

} // namespace Huffman

#endif //SBE201_HUFFMAN_HPP
