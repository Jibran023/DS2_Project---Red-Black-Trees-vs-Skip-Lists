#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


// #include <bits/stdc++.h>
#include "RBTree.cpp"

bool isIgnoredChar(char c) {
    // Define characters to ignore here
    return c == '(' || c == ')' || c=='{' || c=='}' || c=='[' || c==']' || c==',' 
        || c == '@' || c == '#' || c=='$' || c=='%' || c=='^'  || c=='*'
            || c=='!' || c == '.' || (c >= '0' && c <= '9');
}

int main(){
    RBTree tree;
    // Open the input file
    std::ifstream inputFile("letters_100.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Exit with error
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Print the original line
        std::cout << "Line: " << line << std::endl;

        // Tokenize the line into words
        std::istringstream iss(line);
        
        std::string word;
        while (iss >> word) {
            std::cout<<"the word is: "<<word<<std::endl;
            int word_asci=0;
            for (char c : word) {
                // std::cout << c << " ";
                if (!isIgnoredChar(c)){
                    int asciiValue = static_cast<int>(c);
                    word_asci+=asciiValue;
                }
        
            }
            std::cout<<"the asci value of the word is: "<<word_asci<<std::endl;
            tree.insertValue(word_asci,word);
        }

        // Print each word
        std::cout << "Words: ";
        
    }

    // Close the file
    inputFile.close();


    return 0;
}