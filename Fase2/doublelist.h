#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "nodedoublelist.h"

class DoubleList {
private:
    NodeDoubleList* head;
    NodeDoubleList* tail;
    int size;

public:
    DoubleList();

    void insertAtBeginning(string correo, string contenido, string fecha, string hora, string imagenPath);
    void insertAtEnd(const string& correo, const string& contenido, const string& fecha, const string& hora, const string& imagenPath);
    void insertAtPosition(int givenPosition, string correo, string contenido, string fecha, string hora, string imagenPath);
    void print() const;
    bool deleteAtPosition(int position);
    void printByUser(const string& correoUsuario) const;
    bool deleteByUser(int position, const string& correoUsuario);
    void generateDotFile();
    void printTopUsersByPublications() const;
};

#endif // DOUBLELIST_H
