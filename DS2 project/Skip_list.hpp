#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <iostream>
#include <vector>
#include <string>

class Skiplist {
private:
    struct Node {
        int value;
        std::vector<std::string> strValue;
        Node** next;

        Node(int val, int levels, const std::string& str);
        ~Node();
    };

    Node* head;
    int maxLevel;
    int size;
    std::string word;

    int randomLevel();

public:
    Skiplist();
    ~Skiplist();

    bool search(std::string word);
    bool add(int value, std::string word);
    bool remove(std::string word);
    void print();
};

#endif // SKIPLIST_HPP
