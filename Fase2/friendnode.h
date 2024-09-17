#ifndef FRIENDNODE_H
#define FRIENDNODE_H

#include <string>

class FriendNode {
public:
    std::string friendEmail;
    FriendNode* next;

    // Constructor
    FriendNode(const std::string& email);
};

#endif
