#include <iostream>
#include <cstdlib> // For rand()
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
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




class Skiplist {
private:

    struct Node {
        int value;
        string strValue; 
        Node** next;

        Node(int val, int levels, const std::string& str) : value(val), strValue(str) {
            next = new Node*[levels];
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
    string word;

    int randomLevel();

public:
    Skiplist();
    ~Skiplist();

    bool search(string value);
    bool add(int value, string word);
    bool remove(int value);
    void print();
};



// Skiplist Constructor

Skiplist::Skiplist() {
    maxLevel = 20; 
    word = "";
    head = new Node(-1, maxLevel,word);
    size = 0;
}


//  Skiplist Destructor

Skiplist::~Skiplist() {
    Node* node = head->next[0];
    while (node != nullptr) {
        Node* nextNode = node->next[0];
        delete node;
        node = nextNode;
    }
    delete head;
}


// Probability to promote to next level function

int Skiplist::randomLevel() {
    int level = 1;
    // int probability = rand() % 5 ;
    while (( rand() % 2 == 0  && level < maxLevel))
        level++;
    return level;
}







bool Skiplist::search(string word) {
    int value = calculateSingleWordAscii(word);
    cout << "value to find -----> " << value << " word ----> " << word << endl;
    Node* node = head;
    int nodesVisited = 0; 
    vector<Node*> searchPath;

    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < value) {
            node = node->next[i];
            nodesVisited++; 
            searchPath.push_back(node); 
        }
    }
    node = node->next[0];

    if (node == nullptr) 

    {
        cout << "Value not found" << endl;
        cout << "Number of nodes visited: " << nodesVisited << endl;

        // path
        cout << "Unsucessfull Search path:" << endl;
            for (Node* n : searchPath) {
                cout << "Node value: " << n->value << ", Node word: " << n->strValue << endl;
            }
        return false;
    }

    else
    
    {
        cout << "Value found -> " << node->value << endl;
        cout << "The word found -> " << node->strValue << endl;
        cout << "Number of nodes visited: " << nodesVisited << endl;

        // search path
        cout << "Search path:" << endl;
        for (Node* n : searchPath) {
            cout << "Node value: " << n->value << ", Node word: " << n->strValue << endl;
        }

    return node->value == value;
    }
}




// adding a value function
bool Skiplist::add(int value, string word) {
    Node* update[maxLevel];
    Node* node = head;
    for (int i = maxLevel - 1; i >= 0; --i) {
        while (node->next[i] != nullptr && node->next[i]->value < value)
            node = node->next[i];
        update[i] = node;
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




// displaying a skiplist according to the level
void Skiplist::print() {
    for (int i = maxLevel - 1; i >= 0; --i) {
        Node* node = head->next[i];
        cout << "Level " << i << ":-->  ";
        while (node != nullptr) {
            cout << node->value << " ";
            node = node->next[i];
        }
        cout << endl;
        
    }
}





int main() {

    // to actuallty make rand work properly ans change the seed.....
    srand(time(nullptr)); 


    Skiplist skiplist,skiplist2;

    vector<vector<pair<string, int>>> asciiValues = calculateWordsAscii("unique_words.txt");
    // vector<vector<pair<string, int>>> asciiValues2 = calculateWordsAscii("Unique_Acsii.txt");
    // vector<vector<pair<string, int>>> asciiValues = calculateWordsAscii("sample_unique_words.txt");

    // int count = 0;
    


    for (const auto& line : asciiValues) {
        for (const auto& pair : line) {
            

            const string& word = pair.first;
            int asciiValue = pair.second;
            skiplist.add(asciiValue, word);

        }
    }


    // cout<<"total words in lsit" <<asciiValues.size()<< endl;

    skiplist.print();


    // cout << end<<endl<<endl;

    cout << "search Decalcomania " << boolalpha << skiplist.search("Decalcomania") << endl;
    cout << "search Daniyal? " << boolalpha << skiplist.search("Daniyal") << endl;

    cout << "search ______? " << boolalpha << skiplist.search("Dadshfkjhsdjfhksdhjfdsjhfskdhfskjdhfshfksfhkjshfjksdhfkjhskhfjsdfhskhfksdhfjsyal") << endl;




    // for (const auto& line : asciiValues2) {
    //     for (const auto& pair : line) {
            

    //         const string& word = pair.first;
    //         int asciiValue = pair.second;
    //         skiplist2.add(asciiValue, word);

    //     }
    // }

    // cout<<"_____________________________________________________________________"<<endl;
    // skiplist2.print();
    // cout<<"_____________________________________________________________________"<<endl;
    // cout<<skiplist2.search("Itachi");




    return 0;
}




