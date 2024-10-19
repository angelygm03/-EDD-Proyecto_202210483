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
    SimpleList priorityQueue;

    // Contar frecuencias de los caracteres
    std::unordered_map<char, int> freqMap = countFrequencies(text);

    // Verificar si el mapa de frecuencias está vacío
    if (freqMap.empty()) {
        std::cerr << "Error: No se han creado nodos para el árbol de Huffman." << std::endl;
        return; // Salir si no hay caracteres
    }

    // Crear un nodo hoja para cada carácter y añadirlo a la cola de prioridad
    for (const auto& pair : freqMap) {
        qDebug() << "Creando nodo para el caracter: " << QString(pair.first) << ", Frecuencia: " << pair.second;
        priorityQueue.push(new HuffmanNode(pair.first, pair.second));
    }

    // Si solo hay un único nodo, lo asignamos a la raíz
    if (priorityQueue.size == 1) {
        root = priorityQueue.pop()->huffNode;
        return;
    }

    // Iterar hasta que solo quede un nodo en la cola de prioridad
    while (priorityQueue.size > 1) {
        // Extraer los dos nodos con las frecuencias más bajas
        HuffmanNode* left = priorityQueue.pop()->huffNode;
        HuffmanNode* right = priorityQueue.pop()->huffNode;

        // Crear un nuevo nodo que los combine
        int sum = left->freq + right->freq;
        HuffmanNode* newNode = new HuffmanNode('\0', sum);
        newNode->left = left;
        newNode->right = right;

        qDebug() << "Combinando nodos: " << left->freq << " y " << right->freq << " en un nuevo nodo de frecuencia: " << sum;

        priorityQueue.push(newNode);
    }

    // El último nodo restante es la raíz del árbol de Huffman
    root = priorityQueue.pop()->huffNode;
}

std::unordered_map<char, std::string> Huffman::getHuffmanCodes()
{
    std::unordered_map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    return huffmanCode;
}

void Huffman::generateCodes(HuffmanNode *node, std::string code, std::unordered_map<char, std::string> &huffmanCode)
{
    if (!node)
        return;

    // Si es un nodo hoja, asignamos el código
    if (!node->left && !node->right)
    {
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
    }
    qDebug() << "Texto comprimido: " << QString::fromStdString(compressedText);
    return compressedText;
}

std::string Huffman::decompress(const std::string &compressedText)
{
    std::string decompressedText = "";
    HuffmanNode* currentNode = root;

    if (root == nullptr) { //root no sea nulo.
        qDebug() << "Error: La raíz del árbol es nula.";
        return decompressedText; // Retorna vacío si no hay árbol para descomprimir
    }

    if (!currentNode)
    {
        qDebug() << "Error: La raíz del árbol es nula.";
        return decompressedText; // Retorna vacío si no hay árbol para descomprimir
    }

    for (char bit : compressedText)
    {
        qDebug() << "Bit actual: " << bit;

        if (bit == '0')
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }

        // Verificación nula
        if (!currentNode)
        {
            qDebug() << "Error: Acceso a un nodo nulo durante la descompresión.";
            return decompressedText; // Termina el proceso si ocurre un error
        }

        // Si es un nodo hoja se encuentra un carácter
        if (!currentNode->left && !currentNode->right)
        {
            decompressedText += currentNode->data;
            qDebug() << "Carácter descomprimido: " << QString(currentNode->data);
            currentNode = root; // Volver a la raíz
        }
    }

    qDebug() << "Texto descomprimido completo: " << QString::fromStdString(decompressedText);
    return decompressedText;
}
