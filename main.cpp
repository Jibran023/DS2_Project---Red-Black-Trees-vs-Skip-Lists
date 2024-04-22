#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>



// #include <bits/stdc++.h>
#include "RBTree.cpp"

bool isIgnoredChar(char c) 
{
    // Defining the characters to ignore here
    return c == '(' || c == ')' || c=='{' || c=='}' || c=='[' || c==']' || c==',' 
        || c == '@' || c == '#' || c=='$' || c=='%' || c=='^'  || c=='*'
            || c=='!' || c == '.' || (c >= '0' && c <= '9');
}

int main(){
    RBTree tree; //the tree object
    // Open the input file

    // std::string filePath = "unique_dataset/unique_sample_100words.txt";
    std::string filePath = "duplicate_dataset/duplicate_sample_100words.txt";
    // std::string filePath= "unique_dataset.txt";
    // std::string filePath = "unique_dataset/unique_medium_5000words.txt";

    // Open the file for reading
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        // std::cerr << "Error opening the file." << std::endl;
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
            Node* returned_node=tree.GetTargetNode_for_insertion(word_asci);//will check if the node with this asci value exists or not
            if(returned_node!=nullptr){
                returned_node->words.push_back(word);
            }
            else{
                tree.insertValue(word_asci,word);
            
            }
            // std::cout<<"the asci value of the word is: "<<word_asci<<std::endl;
        }

       
        
    }
    //printing the total_insertion_time attribute after the entire file has been inserted, to give us the 
    //total time taken for insertion

    cout<<"Total time taken for insertion: "<<tree.total_insertion_time<<"nanoseconds"<<endl;
    tree.inorder();
    // std::string ans=tree.search("particular");
    // tree.deleteWord("particular");
    // std::string ans_2=tree.search("particular");

    // cout<<"total nodes in tree: "<<tree.CountNodes(tree.root);    
    // Close the file
    inputFile.close();


    return 0;
}