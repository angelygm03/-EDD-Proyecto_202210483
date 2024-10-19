#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include "simplelist.h"
#include "huffmannode.h"

class Huffman {
private:
    HuffmanNode* root;
    void generateCodes(HuffmanNode* node, std::string code, std::unordered_map<char, std::string> &huffmanCode);

public:
    Huffman() : root(nullptr) {}
    void buildHuffmanTree(std::string text);
    std::unordered_map<char, std::string> getHuffmanCodes();
    std::string compress(const std::string& text, std::unordered_map<char, std::string>& huffmanCodes);
    std::string decompress(const std::string& compressedText);
    std::unordered_map<char, int> countFrequencies(const std::string& text);
};

#endif // HUFFMAN_H
