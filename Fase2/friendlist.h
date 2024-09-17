#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include "friendnode.h"

class FriendList {
public:
    FriendNode* head;

    // Constructor
    FriendList();

    // Métodos para gestionar la lista de amigos
    void addFriend(const std::string& email);
    void showFriends() const;
    int countFriends() const;
};

#endif
