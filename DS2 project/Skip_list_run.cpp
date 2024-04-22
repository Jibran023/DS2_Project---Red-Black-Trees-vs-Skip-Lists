#include "Skip_list.cpp"
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

// int calculateSingleWordAscii(const string& word) {
//     int asciiValue = 0;
//     for (char c : word) {
//         asciiValue += static_cast<int>(c);
//     }
//     return asciiValue;
// }

// vector<vector<pair<string, int>>> calculateWordsAscii(const string& filename) {
//     ifstream inputFile(filename);

//     if (!inputFile.is_open()) {
//         cerr << "Error opening the file." << endl;
//         return {}; 
//     }

//     vector<vector<pair<string, int>>> asciiValues;
//     string line;
//     while (getline(inputFile, line)) {
//         istringstream iss(line);
//         string word;
//         vector<pair<string, int>> wordsAndAscii;
//         while (iss >> word) {
//             int asciiValue = calculateSingleWordAscii(word);
//             wordsAndAscii.push_back(make_pair(word, asciiValue));
//         }
//         asciiValues.push_back(wordsAndAscii);
//     }

//     inputFile.close();
//     return asciiValues;
// }

int main() {

    
    srand(time(nullptr)); 


    Skiplist skiplist;

    vector<vector<pair<string, int>>> asciiValues = calculateWordsAscii("Ten_0000_words.txt");
    
   

    for (const auto& line : asciiValues) {
        for (const auto& pair : line) {
            

            const string& word = pair.first;
            int asciiValue = pair.second;
            skiplist.add(asciiValue, word);

        }
    }

    std::cout<<"total words in lsit" <<asciiValues.size()<< endl;

    // skiplist.print();


    std::cout << "search participating " << boolalpha << skiplist.search("participating") << endl;
    std::cout << "search dasd? " << boolalpha << skiplist.search("dsad") << endl;
    std::cout << "search a? " << boolalpha << skiplist.search("a") << endl;

    std::cout << "revome a" << boolalpha << skiplist.remove("a")<< endl;

    



    // std::cout <<  " new skip list after remove"<<endl;

    // skiplist.print();

    return 0;
}
