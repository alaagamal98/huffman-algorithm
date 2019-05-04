#ifndef SBE201_WORDCOUNT_MAPS_HELPERS_HPP
#define SBE201_WORDCOUNT_MAPS_HELPERS_HPP

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <bitset>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, delim))
        tokens.push_back(token);
    return tokens;
}

//gets a file of text in a vector of lines
std::vector<std::string> getFileWords(const std::string &filePath)
{
    std::ifstream f(filePath);
    std::vector<std::string> words;
    std::string line;
    if (f)
    {
        while (std::getline(f, line))
        {
            line.erase(std::remove_if(line.begin(),
                                      line.end(),
                                      [](char c) { return c == ',' || c == '.' || c == '!' || c == '"'; }),
                       line.end());

            std::transform(line.begin(),
                           line.end(),
                           line.begin(),
                           [](unsigned char c) { return std::tolower(c); });

            for (const auto &word : split(line, ' '))
                words.push_back(word);
        }
    }
    else
        std::cout << "Failed to open file:" << filePath << std::endl;
    return words;
}

//reads the characters in a form of bytes from a file in a vector of characters
std::vector<char> readAllBytes(char const *filename)
{
    std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

//prints the given data in a text file
void printFile(const std::string &code, const std::string &fileName)
{
    std::ofstream outfile(fileName);
    outfile << code;
    outfile.close();
}

//converts the binary strings to decimal characters and then prints them
void BintoDecPrint(const std::vector<std::string> &code, const std::string &fileName)
{
    std::ofstream outfile(fileName);
    for (int i = 0; i < code.size(); ++i)
    {
        std::bitset<8> b(code[i]);
        unsigned char c =static_cast<unsigned char>( b.to_ulong());
        outfile << c;
    }
    outfile.close();
}

//converts each decimal character to an 8 bit binary string
std::string DectoBin(const char code)
{
    std::string binary = std::bitset<8>(code).to_string();
    return binary;
}
#endif //SBE201_WORDCOUNT_MAPS_HELPERS_HPP
