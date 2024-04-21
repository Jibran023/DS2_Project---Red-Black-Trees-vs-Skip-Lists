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
    int asci; 
    int color;//red=0 , black =1
    Node *left, *right, *parent;
    
    std::vector<std::string> words;

    explicit Node(int);  //explicit means: cannot be used for implicit conversions,stops the computer from using this function automatically in certain situations.
};

class RBTree
{
            
    public:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void inorderBST(Node *&);
        
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node* insertBST(Node *&, Node *&);


    
        Node *root;
        float total_insertion_time;
        float node_deletion_time;
        RBTree();
        void insertValue(int n,std::string  word);
       
        void inorder();
        
        std::string search(const std::string& inp_word);
        // Node* search(const std::string& inp_word);
        Node* GetTargetNode_for_insertion(int asci);
        void print_words_on_node(Node*&  node);
        int GetTreeHeight();
        int GetTreeHeightHelper(Node* node);

        //deletion
        void fixDeleteRBTree(Node *&);
        Node* deleteBST(Node *&, int);
        void deleteValue(int);
        Node *minValueNode(Node *&);
        void deleteWord(std::string word);
        int CountNodes(Node* node);



};


#endif //RED_BLACK_TREE_RBTREE_H