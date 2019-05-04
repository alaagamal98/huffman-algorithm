#include <iostream>
#include "Huffman.hpp"
#include "helpers.hpp"
#include "serializeTree.hpp"

using Node = Huffman::Node;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        //get the file we want to decompress in a vector of characters
        std::vector<char> incode = readAllBytes(argv[1]);

        //translate each character to an 8 bit binary code
        std::string binary;

        for (int i = 0; i < incode.size(); ++i)
        {
            binary += DectoBin(incode[i]);
        }

        //create a tree to deserialize the original tree's data
        NodeData *dataTree = nullptr;
        FILE *fp = fopen("data.txt", "r");
        deSerializeData(dataTree, fp);

        //create a tree to deserialize the original tree's freqancy
        NodeFreq *freqTree = nullptr;
        FILE *fs = fopen("freq.txt", "r");
        deSerializeFreq(freqTree, fs);

        //create a tree with data and freqancy in its nodes
        //copy the data from the data tree, and the freqancy from the freqancy tree
        Node *Tree = new Node{'0', 0};
        copy(Tree, dataTree, freqTree);
        
        //decode the binary string to the orignal text using the tree and then print the file
        std::string output = Huffman::decode(binary, Tree);
        printFile(output, "text.txt");
    }
}
