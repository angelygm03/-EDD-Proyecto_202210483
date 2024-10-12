#ifndef ARBOLB_H
#define ARBOLB_H

#include "comentario.h"

class NodoB {
public:
    Comentario** comentarios;   // Puntero a comentarios (hasta 4 comentarios por nodo)
    NodoB** hijos;              // Puntero a hijos (hasta 5 hijos por nodo)
    int numComentarios;         // Número actual de comentarios en el nodo
    bool hoja;                  // True si es un nodo hoja

    NodoB(bool esHoja);
    void insertarComentario(Comentario* comentario);
    void dividirNodo(int i, NodoB* y);
    void imprimir();
    void graficar(std::ofstream &file);
};

class ArbolB {
private:
    NodoB* raiz;

public:
    ArbolB();
    void insertar(Comentario* comentario);
    void imprimir();
    void graficar(const std::string &filename);
};


#endif // ARBOLB_H
