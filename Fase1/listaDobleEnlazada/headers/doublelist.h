#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include "nodeDoubleList.h"

class DoubleList {
private:
    NodeDoubleList* head;
    NodeDoubleList* tail;
    int size;

public:
    DoubleList();

    void insertAtBeginning(string correo, string contenido, string fecha, string hora);
    void insertAtEnd(const string& correo, const string& contenido, const string& fecha, const string& hora);
    void insertAtPosition(int position, string correo, string contenido, string fecha, string hora);
    void print() const;
    bool deleteAtPosition(int position);
    void printByUser(const string& correoUsuario) const;
    bool deleteByUser(int position, const string& correoUsuario);
    void generateDotFile();
    void printTopUsersByPublications() const;
};

#endif
