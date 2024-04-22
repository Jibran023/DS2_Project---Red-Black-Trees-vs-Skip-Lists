#include "Skip_list.hpp"
#include <cstdlib> // For rand()
#include <iostream>
#include <vector>
#include <iostream>
#include <cstdlib> // For rand()
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime> // for time
using namespace std;








int calculateSingleWordAscii(const string& word) {
    int asciiValue = 0;
    for (char c : word) {
        asciiValue += static_cast<int>(c);
    }
    return asciiValue;
}

vector<vector<pair<string, int>>> calculateWordsAscii(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return {}; 
    }

    vector<vector<pair<string, int>>> asciiValues;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;
        vector<pair<string, int>> wordsAndAscii;
        while (iss >> word) {
            int asciiValue = calculateSingleWordAscii(word);
            wordsAndAscii.push_back(make_pair(word, asciiValue));
        }
        asciiValues.push_back(wordsAndAscii);
    }

    inputFile.close();
    return asciiValues;
}




Skiplist::Node::Node(int val, int levels, const std::string& str) : value(val) {
    strValue.push_back(str);
    next = new Node*[levels];
    for (int i = 0; i < levels; ++i)
        next[i] = nullptr;
}

Skiplist::Node::~Node() {
    delete[] next;
}


Skiplist::Skiplist() {
    maxLevel = 20; 
    word = "";
    head = new Node(-1, maxLevel,word);
    size = 0;
}

Skiplist::~Skiplist() {
    Node* node = head->next[0];
    while (node != nullptr) {
        Node* nextNode = node->next[0];
        delete node;
        node = nextNode;
    }
    delete head;
}

int Skiplist::randomLevel() {
    int level = 1;
    while ((rand() % 2 == 0 && level < maxLevel))
        level++;
    return level;
}



bool Skiplist::search(string word) {
    int value = calculateSingleWordAscii(word);

    std::cout << "value to find -----> " << value << " word ----> " << word << endl;
    Node* node = head;
    int nodesVisited = 0; 
    vector<Node*> searchPath;

    // std::cout<<"passed stage 1"<<endl;

    for (int i = maxLevel -1 ; i >= 0; --i) {
        
        while (node->next[i] != nullptr && node->next[i]->value < value) {
            node = node->next[i];
            nodesVisited++; 
            searchPath.push_back(node); 
        }
    }
    node = node->next[0];
    searchPath.push_back(node);
    nodesVisited++;

    // std::cout<<"passed stage 2"<<endl;

    for (const auto& str : node -> strValue){

            // std::cout<<"passed stage 2.1"<<endl;


            std::cout<<"words found with key value:"<<node-> value<<"->> "<<str<<endl;


                if (str == word){
                    std::cout << "Value found -> " << node->value << endl;
                    std::cout << "The word found -> " << str << endl;
                    std::cout << "Number of nodes visited: " << nodesVisited << endl;

                     // search path
                    std::cout << "Search path:" << endl;
                    for (Node* n : searchPath) 
                    {
                        std::cout << "Node value: " << n->value<< endl;
                    }

                    return node->value == value;
                }
                // std::cout<<word<<"->";

                
                

                    
                
            }


    // std::cout<<"passed stage 3"<<endl;


            std::cout << "Value not found" << endl;
                    std::cout << "Number of nodes visited: " << nodesVisited << endl;

                    // path
                    std::cout << "Unsucessfull Search path:" << endl;
                        for (Node* n : searchPath) {
                            std::cout << "Node value: " << n->value << endl;
                        }
                    return false;

    // std::cout<<"completed"<<endl;

    
}




bool Skiplist::add(int value, string word) {
    Node* update[maxLevel];
    Node* node = head;
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < value)
            node = node->next[i];
        update[i] = node;
    }

    // Check if the value already exists
    if (node->next[0] != nullptr && node->next[0]->value == value) {
        // Value already exists, so add the word to the existing node
        node = node->next[0]; // Move to the existing node
        node->strValue.push_back(word); // Add the word to the vector in the node
        return false; // Value already exists, return false
    }

    int level = randomLevel();
    node = new Node(value, level, word);
    for (int i = 0; i < level; ++i) {
        node->next[i] = update[i]->next[i];
        update[i]->next[i] = node;
    }
    size++;
    return true;
}


bool Skiplist::remove(string word) {
    int value = calculateSingleWordAscii(word);

    Node* update[maxLevel];
    Node* node = head;

    // Traverse the skiplist to find the node containing the specified value
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < value)
            node = node->next[i];
        update[i] = node;
    }

    // Check if the value exists in the skiplist
    if (node->next[0] != nullptr && node->next[0]->value == value) {
        node = node->next[0]; // Move to the node containing the value

        // Remove the word from the node
        vector<string>& words = node->strValue;
        for (auto it = words.begin(); it != words.end(); ++it) {
            if (*it == word) {
                words.erase(it);

                // If the node becomes empty after removal, remove it from the skiplist
                if (words.empty()) {
                    for (int i = 0; i < maxLevel; ++i) {
                        if (update[i]->next[i] == node) {
                            update[i]->next[i] = node->next[i];
                        }
                    }
                    delete node;
                }
                return true; // Word removed successfully
            }
        }
    }

    return false; // Word not found in the skiplist
}



void Skiplist::print() {
    for (int i = maxLevel - 1; i >= 0; --i) {
        Node* node = head->next[i];
        std::cout << "Level " << i << ":---->  ";
        while (node != nullptr) {
            std::cout << node->value << " --> ";
            for (const auto& word : node->strValue) {
                std::cout << word << "....";
            }
            node = node->next[i];
        }
        std::cout << std::endl;
    }
}
