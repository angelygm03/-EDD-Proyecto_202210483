#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include <string>
using namespace std;

class Neighbor {
public:
    string friendName;
    Neighbor *next;

    Neighbor(const string& name);
};

#endif // NEIGHBOR_H
