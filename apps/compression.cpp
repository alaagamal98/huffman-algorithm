#include <iostream>
#include "helpers.hpp"
#include "Huffman.hpp"
#include "serializeTree.hpp"
#include <fstream>

using Node = Huffman::Node;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        //get the file we want to compress in a vector of lines
        std::vector<std::string> in = getFileWords(argv[1]);

        //put the vector of line in a single string
        std::string input;

        for (int i = 0; i < in.size(); ++i)
        {
            input += in[i] + " ";
        }

        //calculate the freqancy of each character
        std::map<char, int> freq;

        for (char A : input)
        {
            freq[A]++;
        }

        //make the tree of huffman algorithm
        Node *Tree = Huffman::makeTree(freq);

        //serialize the data of the tree
        FILE *fp = fopen("data.txt", "w");
        if (fp == NULL)
        {
            puts("Could not open file");
            return 0;
        }
        serializeData(Tree, fp);
        fclose(fp);

        //serialize the freqency of the tree
        FILE *fs = fopen("freq.txt", "w");
        if (fs == NULL)
        {
            puts("Could not open file");
            return 0;
        }
        serializeFreq(Tree, fs);
        fclose(fs);

        //make a map of each character's binary code
        std::map<char, std::string> Map;
        Huffman::makeMap(Tree, "", Map);

        //encode the input file to binary output using huffman
        std::string code = Huffman::encode(input, Map);

        //divide the binary string to a vector of strings with 8 bits in each string
        std::vector<std::string> codebyte;

        for (int i = 0; (i + 7) < code.size(); i = i + 8)
        {
            codebyte.push_back(code.substr(i, 8));
        }

        //converts every 8 bits to a character and print the whole output to a compressed file
        BintoDecPrint(codebyte, "binary.txt");
    }

    return 0;
}