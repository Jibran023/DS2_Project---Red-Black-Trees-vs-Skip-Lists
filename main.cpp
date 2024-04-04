#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>



// #include <bits/stdc++.h>
#include "RBTree.cpp"

bool isIgnoredChar(char c) {
    // Defining the characters to ignore here
    return c == '(' || c == ')' || c=='{' || c=='}' || c=='[' || c==']' || c==',' 
        || c == '@' || c == '#' || c=='$' || c=='%' || c=='^'  || c=='*'
            || c=='!' || c == '.' || (c >= '0' && c <= '9');
}

int main(){
    RBTree tree;
    // Open the input file
    std::ifstream inputFile("sample_unique_words.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Exit with error
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Print the original line

        // Tokenize the line into words
        std::istringstream iss(line);
        
        std::string word;
        while (iss >> word) {
            // std::cout<<"the word is: "<<word<<std::endl;
            int word_asci=0;
            for (char c : word) {
                // std::cout << c << " ";
                if (!isIgnoredChar(c)){
                    int asciiValue = static_cast<int>(c);
                    word_asci+=asciiValue;
                }
        
            }
            Node* returned_node=tree.GetTargetNode(word_asci);//will check if the node with this asci value exists or not
            if(returned_node!=nullptr){
                returned_node->words.push_back(word);
            }
            else{
                tree.insertValue(word_asci,word);
            
            }
            // std::cout<<"the asci value of the word is: "<<word_asci<<std::endl;
        }

        // Print each word
        std::cout << "Words: ";
        
    }

    tree.inorder();

    Node* returned_node=tree.search("god"); //disordinance Magnetizable have asci values 1235
    // std::cout<<"the word on the returned node is: "<<returned_node->word<<std::endl;
    tree.print_words_on_node(returned_node);
    
    // Close the file
    inputFile.close();


    return 0;
}