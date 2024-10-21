#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    // Constructor
    HuffmanNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

#endif // HUFFMANNODE_H
