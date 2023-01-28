

#include <QFile>
#include "Huffman.h"
#include <iostream>
#include <utility>
Huffman::Huffman(string input, string output)
{
    inputFileName = std::move(input);
    outputFileName = std::move(output);
}


void Huffman::startConversion(const QString& type) {
    if(type==".cmp") {
        for (int i = 0; i < 128; i++)
        {
            nodeArray[i] = new Node;
            nodeArray[i]->id = i;
            nodeArray[i]->freq = 0;
        }
        createPriorityQueue();
        createHuffmanTree();
        traverse(root, "");
        saveCompressed();

    }else{
        recreateHuffmanTree();
        saveDecompressed();
    }
}
void Huffman::createPriorityQueue()
{
    inputFile.open(inputFileName, ios::in);
    inputFile.get(id);
    while (!inputFile.eof())//frequency counter
    {
        nodeArray[id]->freq++;
        inputFile.get(id);
    }
    inputFile.close();
    for (int i = 0; i < 128; i++)
    {
        if (nodeArray[i]->freq)
        {
            pq.push(nodeArray[i]);
        }
    }
}
void Huffman::createHuffmanTree()
{
    priority_queue<nodePtr, vector<nodePtr>, compare> temp(pq);
    while (temp.size() > 1)
    {
        root = new Node;
        root->freq = 0;
        root->left = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        root->right = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        temp.push(root);
    }
}
void Huffman::traverse(Node* node, const string& code)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        node->code = code;
    }
    else
    {
        traverse(node->left, code + '0');
        traverse(node->right, code + '1');
    }
}
void Huffman::saveCompressed()
{
    priority_queue<nodePtr, vector<nodePtr>, compare> temp(pq);
    inputFile.open(inputFileName, ios::in);
    outputFile.open(outputFileName, ios::out | ios::binary);
    string compressedText, str;

    compressedText += (char)pq.size();//save the size of the priority queue
    while(!temp.empty())
    {
        nodePtr current = temp.top();
        compressedText += current->id;
        str.assign(127 - current->code.size(), '0');//128-bit string
        str += '1';
        str.append(current->code);
        compressedText += (char)toDecimal(str.substr(0, 8));
        for (int i = 0; i < 15; i++)
        {//cut into 8-bit binary codes
            str = str.substr(8);
            compressedText += (char)toDecimal(str.substr(0, 8));
        }
        temp.pop();
    }
    str.clear();

    inputFile.get(id);
    while (!inputFile.eof())
    {
        str += nodeArray[id]->code;
        while (str.size() > 8)
        {//cut into 8-bit binary codes
            compressedText += (char)toDecimal(str.substr(0, 8));
            str = str.substr(8);
        }
        inputFile.get(id);
    }
    int count = 8 - str.size();
    if (str.size() < 8)
    {//append number of 'count' '0' to the last few codes
        str.append(count, '0');
    }
    compressedText += (char)toDecimal(str);
    compressedText += (char)count;

    outputFile.write(compressedText.c_str(), compressedText.size());
    inputFile.close();
    outputFile.close();
        for (int i = 0; i < 128; ++i)
        delete nodeArray[i];
}
int Huffman::toDecimal(string binaryNum)
{
    int result = 0;
    for (int i = 0; i < binaryNum.size(); i++)
        result = result * 2 + binaryNum[i] - '0';
    return result;
}

string Huffman::toBinary(int decimalNum)
{
    string temp;
    string result;
    QString myStringOfBits( QString::number(decimalNum, 2 ) );
    temp=myStringOfBits.toStdString();
    result.append(8 - temp.size(), '0');
    result.append(temp);
    return result;
}

void Huffman::build_tree(string& path, char charId)
{
    nodePtr current = root;
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '0')
        {
            if (current->left == nullptr)
                current->left = new Node;
            current = current->left;
        }
        else if (path[i] == '1')
        {
            if (current->right == nullptr)
                current->right = new Node;
            current = current->right;
        }
    }
    current->id = charId;
}

void Huffman::recreateHuffmanTree()
{
    inputFile.open(inputFileName, ios::in | ios::binary);
    unsigned char size;//get number of nodes
    inputFile.read(reinterpret_cast<char*>(&size), 1);
    root = new Node;
    for (int i = 0; i < size; i++)
    {
        char charId;
        unsigned char code[16];
        inputFile.read(&charId, 1);
        inputFile.read(reinterpret_cast<char*>(code), 16);
        string binaryCode;
        for (int k = 0; k < 16; k++)// 128-bit binary string
            binaryCode += toBinary(code[k]);
        int j = 0;
        while (binaryCode[j] == '0')//delete the added '0' to get the real huffman code
            j++;
        binaryCode = binaryCode.substr(j + 1);
        build_tree(binaryCode, charId);
    }
    inputFile.close();
}

void Huffman::saveDecompressed()
{
    inputFile.open(inputFileName, ios::in | ios::binary);
    outputFile.open(outputFileName, ios::out);
    unsigned char size;
    inputFile.read(reinterpret_cast<char*>(&size), 1);
    inputFile.seekg(-1, ios::end);//get the number of '0' append to the string at last
    char count0;
    inputFile.read(&count0, 1);
    inputFile.seekg(1 + 17 * size, ios::beg);//jump to the position where text starts

    vector<unsigned char> text;
    unsigned char temp;
    inputFile.read(reinterpret_cast<char*>(&temp), 1);
    while (!inputFile.eof())
    {//get the text byte by byte
        text.push_back(temp);
        inputFile.read(reinterpret_cast<char*>(&temp), 1);
    }
    nodePtr current = root;
    string path;
    for (int i = 0; i < text.size() - 1; i++)
    {//translate the huffman code
        path = toBinary(text[i]);
        if (i == text.size() - 2)
            path = path.substr(0, 8 - count0);
        for (int j = 0; j < path.size(); j++)
        {
            if (path[j] == '0')
                current = current->left;
            else
                current = current->right;
            if (current->left == nullptr && current->right == nullptr)
            {
                outputFile.put(current->id);
                current = root;
            }
        }
    }
    inputFile.close();
    outputFile.close();
}


