//
// Red Black Tree Definition
//
#include <iostream>
#include <vector>
#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};


struct Node
{
    int data; 
    int color;//red=0 , black =1
    Node *left, *right, *parent;
    std::string word;
    std::vector<std::string> words;

    explicit Node(int,std::string);  //explicit means: cannot be used for implicit conversions,stops the computer from using this function automatically in certain situations.
};

class RBTree
{
            
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void inorderBST(Node *&);
        
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node* insertBST(Node *&, Node *&);
    public:
        Node *root;
        RBTree();
        void insertValue(int,std::string);
       
        void inorder();
        
        Node* search(const std::string& inp_word);
        Node* GetTargetNode(int asci);
        void print_words_on_node(Node*&  node);
        int GetTreeHeight();
        int GetTreeHeightHelper(Node* node);

        //deletion
        void fixDeleteRBTree(Node *&);
        Node* deleteBST(Node *&, int);
        void deleteValue(int);
        Node *minValueNode(Node *&);
        void deleteWord(std::string word);



};


#endif //RED_BLACK_TREE_RBTREE_H