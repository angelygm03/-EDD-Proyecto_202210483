#include "friendlist.h"
#include <iostream>

// Constructor de FriendList
FriendList::FriendList() : head(nullptr) {}

// Agrega un amigo al final de la lista
void FriendList::addFriend(const std::string& email) {
    FriendNode* newFriend = new FriendNode(email);
    if (!head) {
        head = newFriend;
    } else {
        FriendNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newFriend;
    }
}

// Muestra la lista de amigos
void FriendList::showFriends() const {
    FriendNode* temp = head;
    while (temp != nullptr) {
        std::cout << temp->friendEmail << " -> ";
        temp = temp->next;
    }
    std::cout << "null" << std::endl;
}

// Cuenta el número de amigos
int FriendList::countFriends() const {
    int count = 0;
    FriendNode* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
