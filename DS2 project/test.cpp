#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Skiplist {
private:
    struct Node {
        int value;
        vector<string> strValue;
        Node** next;

        Node(int val, int levels, const std::string& str) : value(val) {
            strValue.push_back(str);
            next = new Node*[levels]();
            for (int i = 0; i < levels; ++i)
                next[i] = nullptr;
        }

        ~Node() {
            delete[] next;
        }
    };

    Node* head;
    int maxLevel;
    int size;

    int randomLevel();

public:
    Skiplist();
    ~Skiplist();

    bool search(const string& word);
    bool add(int value, const string& word);
    void print();
};

Skiplist::Skiplist() {
    maxLevel = 20;
    head = new Node(-1, maxLevel, "");
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
    while ((rand() % 2 == 0) && (level < maxLevel))
        level++;
    return level;
}

bool Skiplist::search(const string& word) {
    int asciiValue = 0;
    for (char c : word) {
        asciiValue += static_cast<int>(c);
    }

    Node* node = head;
    vector<Node*> searchPath;

    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < asciiValue) {
            node = node->next[i];
            searchPath.push_back(node);
        }
    }
    node = node->next[0];

    for (const auto& str : node->strValue) {
        if (str == word) {
            cout << "Value found -> " << node->value << endl;
            cout << "The word found -> " << str << endl;
            cout << "Search path:" << endl;
            for (Node* n : searchPath) {
                cout << "Node value: " << n->value << endl;
            }
            return true;
        }
    }

    cout << "Value not found" << endl;
    cout << "Unsuccessful Search path:" << endl;
    for (Node* n : searchPath) {
        cout << "Node value: " << n->value << endl;
    }
    return false;
}

bool Skiplist::add(int value, const string& word) {
    Node* update[maxLevel];
    Node* node = head;
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < value)
            node = node->next[i];
        update[i] = node;
    }

    if (node->next[0] != nullptr && node->next[0]->value == value) {
        node = node->next[0];
        node->strValue.push_back(word);
        return false;
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

void Skiplist::print() {
    for (int i = maxLevel - 1; i >= 0; --i) {
        Node* node = head->next[i];
        cout << "Level " << i << ":-->  ";
        while (node != nullptr) {
            cout << node->value << " --> ";
            for (const auto& word : node->strValue) {
                cout << word << " -> ";
            }
            node = node->next[i];
        }
        cout << endl;
    }
}

int main() {
    srand(time(nullptr));

    Skiplist skiplist;

    ifstream inputFile("unique_words.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            int asciiValue = 0;
            for (char c : word) {
                asciiValue += static_cast<int>(c);
            }
            skiplist.add(asciiValue, word);
        }
    }
    inputFile.close();

    skiplist.print();

    cout << "search Nucellus " << boolalpha << skiplist.search("Nucellus") << endl;
    cout << "search Daniyal? " << boolalpha << skiplist.search("Daniyal") << endl;
    cout << "search ______? " << boolalpha << skiplist.search("Dadshfkjhsdjfhksdhjfdsjhfskdhfskjdhfshfksfhkjshfjksdhfkjhskhfjsdfhskhfksdhfjsyal") << endl;

    return 0;
}
