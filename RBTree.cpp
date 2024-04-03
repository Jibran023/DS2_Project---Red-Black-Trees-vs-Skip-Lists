#include <iostream>
#include "RBTree.h"
#include <utility>// For swap function
#include <chrono> //for measuring the time intervals
using namespace std;



Node* sentinal_node = nullptr;


Node::Node(int data,std::string inp_word) //constructor for a node
{ 
    this->data = data;
    color = RED;
    parent = nullptr; //Initialize parent pointers as nullptr
    left = right = sentinal_node;  //making the left and right pointer point to the sentinal
    word=inp_word;
}

RBTree::RBTree() //constructor for the RBTree class 
{ 
    root = nullptr;
}

int RBTree::getColor(Node *&node) 
{
    if (node == nullptr)
        return BLACK; // If node is nullptr, it's considered black

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return; //if node is null then dont do anything

    node->color = color; //else set the color
}

Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

// Function to insert a value into the Red Black Tree
void RBTree::insertValue(int n,std::string inp_word) 
{
    Node *node = new Node(n,inp_word);
    root = insertBST(root, node);
    fixInsertRBTree(node); // After insertion, fixing the Red Black Tree properties
    std::cout<<"oki insertion done! asci value: "<<n<<" word: "<<inp_word<<std::endl;
}


// Function to perform left rotation
void RBTree::rotateLeft(Node *&ptr) 
{
    // Store the right child of ptr
    Node *right_child = ptr->right;
    
    // Update ptr's right child to be the left child of right_child
    ptr->right = right_child->left;

    // Update parent pointers if ptr's right child is not null
    if (ptr->right != sentinal_node)
        ptr->right->parent = ptr;

    // Update the parent of right_child
    right_child->parent = ptr->parent;

    // Update root if ptr was the root of the tree
    if (ptr->parent == nullptr)
        root = right_child;
    // Update parent's left or right child to be right_child
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    // Update the left child of right_child to be ptr
    right_child->left = ptr;
    
    // Update ptr's parent to be right_child
    ptr->parent = right_child;
}


// Function to perform right rotation
void RBTree::rotateRight(Node *&ptr) 
{
    // Store the left child of ptr
    Node *left_child = ptr->left;
    
    // Update ptr's left child to be the right child of left_child
    ptr->left = left_child->right;

    // Update parent pointers if ptr's left child is not null
    if (ptr->left != sentinal_node)
        ptr->left->parent = ptr;

    // Update the parent of left_child
    left_child->parent = ptr->parent;

    // Update root if ptr was the root of the tree
    if (ptr->parent == nullptr)
        root = left_child;
    // Update parent's left or right child to be left_child
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    // Update the right child of left_child to be ptr
    left_child->right = ptr;
    
    // Update ptr's parent to be left_child
    ptr->parent = left_child;
}



// Function to fix Red Black Tree properties after insertion
void RBTree::fixInsertRBTree(Node *&ptr) 
{
    // Initialize parent and grandparent nodes
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    
    // Continue loop until the current node is not the root and both the current node and its parent are red
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) 
    {
        // Update parent and grandparent nodes
        parent = ptr->parent;
        grandparent = parent->parent;
        
        // Check if parent is the left child of grandparent
        if (parent == grandparent->left) 
        {
            // Get the uncle of the current node
            Node *uncle = grandparent->right;//uncle is the sibling of the current node's parent
            // if the uncle is red, it indicates a violation of the Red-Black Tree properties

            //so first we Check if uncle is red
            if (getColor(uncle) == RED) 
            {
                // Case 1: Uncle is red
                // Recolor parent, uncle, and grandparent
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                // Move up to grandparent
                ptr = grandparent;
            } 
            else 
            {
                // Case 2: Uncle is black and current node is right child of parent
                if (ptr == parent->right) 
                {
                    // Rotate left at parent to make the current node left child of parent
                    rotateLeft(parent);
                    // Update current node and parent
                    ptr = parent;
                    parent = ptr->parent;
                }
                // Case 3: Uncle is black and current node is left child of parent
                // Rotate right at grandparent
                rotateRight(grandparent);
                // Swap colors of parent and grandparent
                swap(parent->color, grandparent->color);
                // Update current node to parent
                ptr = parent;
            }
        } 
        else // If parent is the right child of grandparent
        {
            // Get the uncle of the current node
            Node *uncle = grandparent->left;
            
            // Check if uncle is red
            if (getColor(uncle) == RED) 
            {
                // Case 1: Uncle is red
                // Recolor parent, uncle, and grandparent
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                // Move up to grandparent
                ptr = grandparent;
            } 
            else 
            {
                // Case 2: Uncle is black and current node is left child of parent
                if (ptr == parent->left) 
                {
                    // Rotate right at parent to make the current node right child of parent
                    rotateRight(parent);
                    // Update current node and parent
                    ptr = parent;
                    parent = ptr->parent;
                }
                // Case 3: Uncle is black and current node is right child of parent
                // Rotate left at grandparent
                rotateLeft(grandparent);
                // Swap colors of parent and grandparent
                swap(parent->color, grandparent->color);
                // Update current node to parent
                ptr = parent;
            }
        }
    }
    // Set the color of the root to black
    setColor(root, BLACK); 
}


void RBTree::inorderBST(Node *&ptr) { //for traversing and printing the data
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    // cout << ptr->data << " " << ptr->color << endl;
    cout<<"ASCI value is: "<<ptr->data<<" and the word stored is: "<<ptr->word<<endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    cout<<"STARTING TRAVERSAL "<<endl;
    inorderBST(root);
}



Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != sentinal_node)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != sentinal_node)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}



Node* RBTree::search(const std::string& inp_word) {
    auto start = std::chrono::steady_clock::now(); // Start the timer

    // Calculate the ASCII value of the input string
    double n = 2000;
    int asciiValue = 0;
    for (char c : inp_word) {
        asciiValue += static_cast<int>(c);
    }

    // Start searching from the root
    Node* current = root;

    // Traverse the tree to find the node with the matching ASCII value
    while (current != nullptr) {
        // Calculate the ASCII value of the word stored in the current node
        int currentNodeAsciiValue = 0;
        for (char c : current->word) {
            currentNodeAsciiValue += static_cast<int>(c);
        }

        // Compare the calculated ASCII values
        if (asciiValue == currentNodeAsciiValue) {
            // Stop the timer
            auto end = std::chrono::steady_clock::now();
            // Calculate the duration in nanoseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            // Print the time taken
            
            // Return the node if found
            std::cout << "Found it! Word: " << current->word << " and the ASCII value is: " << current->data << std::endl;
            std::cout << "our Search time: " << duration.count() << " nanoseconds" << std::endl;
            std::cout<<"expected time is: "<<  std::log2(n) * 1e9<<std::endl;

            return current;
        } else if (asciiValue < currentNodeAsciiValue) {
            // If the input ASCII value is less than the current node's value, move to the left child
            current = current->left;
        } else {
            // If the input ASCII value is greater than the current node's value, move to the right child
            current = current->right;
        }
    }

    // Stop the timer
    auto end = std::chrono::steady_clock::now();
    // Calculate the duration in nanoseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    // Print the time taken
    std::cout << "Search time: " << duration.count() << " nanoseconds" << std::endl;
    // Print a message indicating the word was not found
    std::cout << "Couldn't find the word, returning nullptr!" << std::endl;
    // Return nullptr if the node with the input ASCII value is not found in the tree
    return nullptr;
}

   