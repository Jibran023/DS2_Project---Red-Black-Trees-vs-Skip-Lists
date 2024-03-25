//
// Red Black Tree Definition
//
#include <iostream>
#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};


struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;
    std::string word;

    explicit Node(int,std::string);
};

class RBTree
{
    
        
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        int getBlackHeight(Node *);
    public:
        Node *root;
        RBTree();
        void insertValue(int,std::string);
        void deleteValue(int);
        void merge(RBTree);
        void inorder();
        void preorder();

};


#endif //RED_BLACK_TREE_RBTREE_H