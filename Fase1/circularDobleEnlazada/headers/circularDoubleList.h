#ifndef CIRCULARDOUBLELIST_H
#define CIRCULARDOUBLELIST_H

#include "nodeCircularList.h"

class CircularDoubleList {
private:
    NodeCircularList* head;
    NodeCircularList* tail;
    int size;

public:
    CircularDoubleList();

    void insertAtEnd(string correo, string contenido, string fecha, string hora);
    void print() const;
    bool deleteByPosition(int position);
};

#endif
