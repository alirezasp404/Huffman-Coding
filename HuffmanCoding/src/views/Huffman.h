

#ifndef HUFFMANCODING_HUFFMAN_H
#define HUFFMANCODING_HUFFMAN_H


#include <string>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

struct Node
{
    char id;
    int freq;
    string code;
    Node* left;
    Node* right;
    Node()
    {
        left = right = nullptr;
    }
};
typedef Node* nodePtr;

class compare
{//an object function to set comparing rule of priority queue
public:
    bool operator()(const nodePtr& c1, const nodePtr& c2) const
    {
        return c1->freq > c2->freq;
    }
};
class Huffman
{
protected:
    priority_queue<nodePtr, vector<nodePtr>, compare> pq;
    string inputFileName,outputFileName;
    fstream inputFile,outputFile;
    nodePtr nodeArray[128];
    nodePtr root;
    char id;
    void traverse(nodePtr, const string&);
    static int toDecimal(string);
    static string toBinary(int);
    void build_tree(string&, char);
    void createPriorityQueue();
    void createHuffmanTree();
    void saveCompressed();
    void saveDecompressed();
    void recreateHuffmanTree();
public:
    Huffman(string, string);
    void startConversion(const QString&);
};


#endif //HUFFMANCODING_HUFFMAN_H
