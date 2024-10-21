#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <string>
#include <fstream>
#include "usernode.h"

class AdjacencyList {
private:
    UserNode* head; // Puntero a la cabeza de la lista

public:
    AdjacencyList();
    ~AdjacencyList();
    void insert(const std::string& userName);
    void createConnection(const std::string& userName1, const std::string& userName2);
    void graph(const std::string &filename);
};


#endif // ADJACENCYLIST_H
