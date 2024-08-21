#ifndef SOLICITUDLIST_H
#define SOLICITUDLIST_H

#include <iostream>
#include <string>
using namespace std;

class SolicitudNode {
public:
    string emisor;
    string receptor;
    string estado;
    SolicitudNode* next;

    SolicitudNode(string e, string r, string s) : emisor(e), receptor(r), estado(s), next(nullptr) {}
};

class SolicitudList {
private:
    SolicitudNode* head;
    int size;

public:
    SolicitudList();
    void insert(string emisor, string receptor, string estado);
    void print();
    bool eliminar(const string& emisor, const string& receptor);
    SolicitudNode* buscar(const string& emisor, const string& receptor);
    void generateDotFile(const string& fileName);
    bool eliminarPorEmisorYReceptor(const string& emisor, const string& receptor);
};

#endif
