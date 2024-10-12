#include "arbolb.h"
#include <fstream>

// Constructor del nodo
NodoB::NodoB(bool esHoja) {
    hoja = esHoja;
    numComentarios = 0;
    comentarios = new Comentario*[4];  // Puntero a 4 comentarios
    hijos = new NodoB*[5];             // Puntero a 5 hijos
}

// Método para insertar en un nodo vacio
void NodoB::insertarComentario(Comentario* comentario) {
    int i = numComentarios - 1;

    // Si el nodo es una hoja, insertar en el lugar correcto
    if (hoja) {
        while (i >= 0 && comentarios[i]->compararFechaYHora(comentario)) {
            comentarios[i + 1] = comentarios[i];
            i--;
        }
        comentarios[i + 1] = comentario;
        numComentarios++;
    } else {
        // Encontrar el hijo adecuado
        while (i >= 0 && comentarios[i]->compararFechaYHora(comentario)) {
            i--;
        }
        if (hijos[i + 1]->numComentarios == 4) {
            dividirNodo(i + 1, hijos[i + 1]);
            if (comentarios[i + 1]->compararFechaYHora(comentario)) {
                i++;
            }
        }
        hijos[i + 1]->insertarComentario(comentario);
    }
}

// Método para dividir un nodo lleno
void NodoB::dividirNodo(int i, NodoB* y) {
    NodoB* z = new NodoB(y->hoja);
    z->numComentarios = 2;

    for (int j = 0; j < 2; j++) {
        z->comentarios[j] = y->comentarios[j + 2];
    }

    if (!y->hoja) {
        for (int j = 0; j < 3; j++) {
            z->hijos[j] = y->hijos[j + 2];
        }
    }

    y->numComentarios = 2;

    for (int j = numComentarios; j >= i + 1; j--) {
        hijos[j + 1] = hijos[j];
    }
    hijos[i + 1] = z;

    for (int j = numComentarios - 1; j >= i; j--) {
        comentarios[j + 1] = comentarios[j];
    }
    comentarios[i] = y->comentarios[2];

    numComentarios++;
}

void NodoB::graficar(std::ofstream &file) {
    if (hoja) { // Nodo hoja
        for (int i = 0; i < numComentarios; i++) {
            file << "    \"" << comentarios[i]->correo << "\" [label=\"" << comentarios[i]->comentario << "\"];\n";
        }
    }
    else {
        for (int i = 0; i < numComentarios; i++) {
            file << "    \"" << comentarios[i]->correo << "\";\n";
            // Conectar con el hijo izquierdo
            if (hijos[i] != nullptr) {
                file << "    \"" << comentarios[i]->correo << "\" -> \"" << hijos[i]->comentarios[0]->correo << "\";\n";
                hijos[i]->graficar(file);
            }
        }
        // Conectar al último hijo
        if (hijos[numComentarios] != nullptr) {
            hijos[numComentarios]->graficar(file);
        }
    }
}

void ArbolB::graficar(const std::string &filename) {
    std::ofstream file(filename);
    file << "digraph G {\n";
    if (raiz != nullptr) {
        raiz->graficar(file);
    }
    file << "}\n";
    file.close();
}

// Constructor del Árbol B
ArbolB::ArbolB() {
    raiz = nullptr;
}

// Método para insertar un comentario en el Árbol B
void ArbolB::insertar(Comentario* comentario) {
    if (raiz == nullptr) {
        raiz = new NodoB(true);
        raiz->comentarios[0] = comentario;
        raiz->numComentarios = 1;
    } else {
        if (raiz->numComentarios == 4) {
            NodoB* s = new NodoB(false);
            s->hijos[0] = raiz;
            s->dividirNodo(0, raiz);
            int i = 0;
            if (s->comentarios[0]->compararFechaYHora(comentario)) {
                i++;
            }
            s->hijos[i]->insertarComentario(comentario);
            raiz = s;
        } else {
            raiz->insertarComentario(comentario);
        }
    }
}

// Método para imprimir el árbol
void NodoB::imprimir() {
    for (int i = 0; i < numComentarios; i++) {
        if (!hoja) {
            hijos[i]->imprimir();
        }
        comentarios[i]->mostrarComentario();
    }
    if (!hoja) {
        hijos[numComentarios]->imprimir();
    }
}

// Imprimir el Árbol B
void ArbolB::imprimir() {
    if (raiz != nullptr)
        raiz->imprimir();
}
