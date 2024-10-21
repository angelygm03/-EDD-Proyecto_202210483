#include "huffman.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <QString>
#include <QDebug>

std::unordered_map<char, int> Huffman::countFrequencies(const std::string &text)
{
    std::unordered_map<char, int> freqMap;
    for (char ch : text)
    {
        freqMap[ch]++;
    }

    // Imprimir la frecuencia de caracteres
    for (const auto &pair : freqMap)
    {
        qDebug() << "Caracter: " << QString(pair.first) << ", Frecuencia: " << pair.second;
    }

    return freqMap;
}

void Huffman::buildHuffmanTree(std::string text) {
    qDebug() << "Construyendo el árbol de Huffman para el texto:";
    qDebug() << QString::fromStdString(text);

    SimpleList priorityQueue;
    auto freqMap = countFrequencies(text);

    for (const auto& pair : freqMap) {
        priorityQueue.push(new HuffmanNode(pair.first, pair.second));
        qDebug() << "Nodo agregado: " << QString(pair.first) << " con frecuencia: " << pair.second;
    }

    while (priorityQueue.size > 1) {
        NodeList* leftNode = priorityQueue.pop();
        NodeList* rightNode = priorityQueue.pop();

        // que leftNode y rightNode no sean nulos
        if (leftNode != nullptr && rightNode != nullptr) {
            qDebug() << "Combinando nodos con frecuencias: " << leftNode->huffNode->freq << " y " << rightNode->huffNode->freq;
            HuffmanNode* newNode = new HuffmanNode('\0', leftNode->huffNode->freq + rightNode->huffNode->freq);
            newNode->left = leftNode->huffNode;
            newNode->right = rightNode->huffNode;
            priorityQueue.push(newNode);
            delete leftNode;
            delete rightNode;
        } else {
            qDebug() << "Error: No se han podido construir los nodos." << (leftNode == nullptr ? "leftNode es nulo." : "") << (rightNode == nullptr ? "rightNode es nulo." : "");
        }
    }

    root = priorityQueue.pop()->huffNode; // que solo quede un nodo
    qDebug() << "El árbol de Huffman ha sido construido correctamente.";
}

std::unordered_map<char, std::string> Huffman::getHuffmanCodes()
{
    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    return huffmanCode;
}

void Huffman::generateCodes(HuffmanNode *node, std::string code, std::unordered_map<char, std::string> &huffmanCode) {
    if (!node)
        return;

    // Si es un nodo hoja se asigna el código
    if (!node->left && !node->right) {
        huffmanCode[node->data] = code;
        qDebug() << "Asignado código: " << QString::fromStdString(code) << " al carácter: " << QString(node->data);
    }

    generateCodes(node->left, code + "0", huffmanCode);
    generateCodes(node->right, code + "1", huffmanCode);
}

std::string Huffman::compress(const std::string &text, std::unordered_map<char, std::string> &huffmanCodes)
{
    std::string compressedText = "";
    for (char ch : text)
    {
        compressedText += huffmanCodes[ch];
        qDebug() << "Carácter: " << QString(ch) << " comprimido a: " << QString::fromStdString(huffmanCodes[ch]);
    }
    qDebug() << "Texto comprimido: " << QString::fromStdString(compressedText);
    return compressedText;
}

std::string Huffman::decompress(const std::string& compressedData, const std::unordered_map<std::string, char>& huffmanCodes) {
    std::string decompressedText = "";
    HuffmanNode* currentNode = root;

    if (root == nullptr) {
        qDebug() << "Error: La raíz del árbol es nula.";
        return decompressedText; // Retorna vacío si no hay árbol para descomprimir
    }

    qDebug() << "Texto comprimido para descomprimir: " << QString::fromStdString(compressedData);

    // que compressedData contenga los bits representados como 0s y 1s
    for (char bit : compressedData) {
        qDebug() << "Bit actual: " << bit;

        // Moverse en el árbol dependiendo del valor del bit
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        // Verificación nula
        if (!currentNode) {
            qDebug() << "Error: Acceso a un nodo nulo durante la descompresión.";
            return decompressedText; // Termina el proceso si ocurre un error
        }

        // Si es un nodo hoja se encuentra un carácter
        if (!currentNode->left && !currentNode->right) {
            decompressedText += currentNode->data; // Agregar carácter descomprimido
            qDebug() << "Carácter descomprimido: " << QString(currentNode->data);
            currentNode = root; // Volver a la raíz
        }
    }

    qDebug() << "Texto descomprimido completo: " << QString::fromStdString(decompressedText);
    return decompressedText;
}
