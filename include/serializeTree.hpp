#include <cstdio>
#include "Huffman.hpp"
#define MARKER1 ')'
#define MARKER2 -1

using namespace std;
using Node = Huffman::Node;

//a tree with freqancy as its key 
struct NodeFreq
{
    int freq;
    NodeFreq *left;
    NodeFreq *right;
    NodeFreq(int key)
    {
        freq = key;
        left = nullptr;
        right = nullptr;
    }
};

//a tree with data as its key
struct NodeData
{
    char data;
    NodeData *left;
    NodeData *right;
    NodeData(char key)
    {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

//copy a tree's freqancy and a tree's data to another tree with both data and freqancy
void *copy(Node *&root, NodeData *&dtree, NodeFreq *&ftree)
{

    if (dtree == NULL || ftree == NULL)
        root = NULL;
    else
    {
        root = new Node(dtree->data, ftree->freq);

        copy(root->left, dtree->left, ftree->left);
        copy(root->right, dtree->right, ftree->right);
    }
}

//move the data of a tree to an external file
void serializeData(Node *root, FILE *fp)
{
    if (root == NULL)
    {
        fprintf(fp, "%c", MARKER1);

        return;
    }
    fprintf(fp, "%c", root->data);

    serializeData(root->left, fp);
    serializeData(root->right, fp);
}

//move the frequency of a tree to an external file
void serializeFreq(Node *root, FILE *fp)
{
    if (root == NULL)
    {
        fprintf(fp, "%u ", MARKER2);

        return;
    }
    fprintf(fp, "%u ", root->freq);

    serializeFreq(root->left, fp);
    serializeFreq(root->right, fp);
}


//take the data of a tree from an external file
void deSerializeData(NodeData *&root, FILE *fp)
{

    char val;

    if (!fscanf(fp, "%c", &val) || val == MARKER1)
        return;

    root = new NodeData(val);

    deSerializeData(root->left, fp);

    deSerializeData(root->right, fp);
}

//take the frequency of a tree from an external file
void deSerializeFreq(NodeFreq *&root, FILE *fp)
{

    int val;
    if (!fscanf(fp, "%u ", &val) || val == MARKER2)
        return;
    root = new NodeFreq(val);

    deSerializeFreq(root->left, fp);

    deSerializeFreq(root->right, fp);
}
