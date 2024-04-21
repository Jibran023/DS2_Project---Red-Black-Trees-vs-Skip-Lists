#include <iostream>
#include "RBTree.h"
#include <utility>// For swap function
#include <chrono> //for measuring the time intervals
#include <ctime> //for meeasuring time interval too

#include <cmath>
using namespace std;



Node* sentinal_node = nullptr;

int RBTree::GetTreeHeightHelper(Node* node) {
    if (node == nullptr)
        return 0;

    int leftHeight = GetTreeHeightHelper(node->left); // Height of the left subtree
    int rightHeight = GetTreeHeightHelper(node->right); // Height of the right subtree

    // Return the maximum of leftHeight and rightHeight, plus 1 for the current node
    // std::cout<<"The height of tree: " <<std::max(leftHeight, rightHeight) + 1<< std::endl;
    return std::max(leftHeight, rightHeight) + 1;
}

int RBTree::CountNodes(Node* node) {
    if (node == nullptr)
        return 0;

    // Recursively count the nodes in the left and right subtrees
    int leftCount = CountNodes(node->left);
    int rightCount = CountNodes(node->right);

    // Return the total number of nodes in the subtree rooted at the current node
    // cout<<"cuount nodes function ended heheh!!"<<endl;
    return leftCount + rightCount + 1;
}


int RBTree::GetTreeHeight() {
    // Start the traversal from the root node
    return GetTreeHeightHelper(root);
}


void RBTree::print_words_on_node(Node*& node){
    std::cout<<"now printing the words on this node"<<std::endl;
    for (const auto& word : node->words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

Node* RBTree::GetTargetNode_for_insertion(int inp_asci) {
    std::clock_t start = std::clock(); // Start the timer
    
    Node* current = root;
    while (current != nullptr) {
        if (current->data == inp_asci) {
            return current; // Found the node
        } else if (current->data < inp_asci) {
            current = current->right; // Move to the right child
        } else {
            current = current->left; // Move to the left child
        }
    }
    std::clock_t end = std::clock();
    double diff = (end - start) * 1.0 / CLOCKS_PER_SEC; // Calculate the difference in seconds
    diff=diff * 1e9;
    if(current!=nullptr){ //if a node is found
        total_insertion_time+=diff;
    }
    // std::cout<<"couldnt find the node with the asci value "<<inp_asci<<std::endl;
    return current; // if node not found, then current will be nullptr, so nullptr will be returned
}



Node::Node(int data) //constructor for a node
{ 
    this->data = data;
    color = RED;
    parent = nullptr; //Initialize parent pointers as nullptr
    left = right = sentinal_node;  //making the left and right pointer point to the sentinal
    // word=inp_word;
}

RBTree::RBTree() //constructor for the RBTree class 
{ 
    root = nullptr;
    node_deletion_time=0; //time for deletion of a node, includes time for fixing properties after deletion
    total_insertion_time=0; // settin the total insertion time to zero when the tree is created
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
    int nodes=CountNodes(root);
    // auto start = std::chrono::steady_clock::now(); // Start the timer
    std::clock_t start = std::clock(); // Start the timer

    Node *node = new Node(n);
    node->words.push_back(inp_word);
    // std::cout<<
    root = insertBST(root, node);
    fixInsertRBTree(node); // After insertion, fixing the Red Black Tree properties
    // std::cout<<"Insertion done! ASCII value: " << n << " || Word: " << inp_word << std::endl;
    // auto end = std::chrono::steady_clock::now(); // End the timer
    std::clock_t end = std::clock(); // End the timer
    // auto diff = end - start; // Calculate the difference
    double diff = (end - start) * 1.0 / CLOCKS_PER_SEC; // Calculate the difference in seconds

    // total_insertion_time += std::chrono::duration <double, std::nano>(diff).count(); //addin the time taken for inseting 
    total_insertion_time += diff * 1e9; // Convert seconds to nanoseconds and add to total_insertion_time

    // std::cout << "Time taken: " << std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;
    std::cout<<"expected insertion time is: "<<  std::log(nodes) * 1e9<<std::endl;


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
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) //ptr is the current node
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
                // Case 1: Uncle is red, violation of properites so we recolor
                // Recolor parent, uncle, and grandparent
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                // Move up to grandparent to check for violations upwards   
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
    print_words_on_node(ptr);
    // cout << ptr->data << " " << ptr->color << endl;
    // cout<<"ASCI value is: "<<ptr->data<<" and the word stored is: "<<ptr->word<<endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    cout<<"STARTING TRAVERSAL "<<endl;
    inorderBST(root);
}






std::string RBTree::search(const std::string& inp_word) {
    std::clock_t start = std::clock(); // Start the timer
    cout<<"search start time: "<<start<<endl;
    std::string ans="";
    // Calculate the ASCII value of the input string
    double n = CountNodes(root); //numbre of nodes
    int asciiValue = 0;
    // std::cout<<"search function: asci value before calculation: "<<asciiValue<<std::endl;

    for (char c : inp_word) {
        asciiValue += static_cast<int>(c);
    }
    // std::cout<<"search function: asci value after calculation: "<<asciiValue<<std::endl;



    // Start searching from the root
    Node* current = root;

    // Traverse the tree to find the node with the matching ASCII value
    while (current != nullptr) {
        // Calculate the ASCII value of the word stored in the current node
        int currentNodeAsciiValue = current->data;
        // for (char c : current->word) {
        //     currentNodeAsciiValue += static_cast<int>(c);
        // }

        // Compare the calculated ASCII values

        if (asciiValue == currentNodeAsciiValue) {
            for (const auto& word : current->words) {
                // cout<<word<<endl;
                if(word==inp_word){
                    ans=word;
                    // break;
                }
            }
            print_words_on_node(current);
            // Stop the timer
            // std::cout<<"asciiValue == currentNodeAsciiValue, asciivalue="<<asciiValue<<" currentnodeascivalue="<<currentNodeAsciiValue<<std::endl;
            std::clock_t end = std::clock();
            cout<<"search end time: "<<end<<endl;
            // Calculate the duration in nanoseconds
            double diff = (end - start) * 1.0 / CLOCKS_PER_SEC; // Calculate the difference in seconds
            // Print the time taken
            
            // Return the node if found
            // std::cout << "Found it! Word: " << current->word << " and the ASCII value is: " << current->data << std::endl;
            // std::cout<<"found the node,returning it!"<<std::endl;
            std::cout << "our Search time: " << diff * 1e9 << " nanoseconds" << std::endl;
            std::cout << "expected search time is: " << std::log(n) * 1e9 << " nanoseconds" << std::endl;

            return ans;
        } else if (asciiValue < currentNodeAsciiValue) {
            // std::cout<<"asciiValue < currentNodeAsciiValue, asciivalue="<<asciiValue<<" currentnodeascivalue="<<currentNodeAsciiValue<<std::endl;

            // If the input ASCII value is less than the current node's value, move to the left child
            current = current->left;
        } else {
            // std::cout<<"else{asciiValue > currentNodeAsciiValue}, asciivalue="<<asciiValue<<" currentnodeascivalue="<<currentNodeAsciiValue<<std::endl;

            
            // If the input ASCII value is greater than the current node's value, move to the right child
            current = current->right;
        }
    }

    // Stop the timer
    std::clock_t end = std::clock();
    // Calculate the duration in nanoseconds
    double diff = (end - start) * 1.0 / CLOCKS_PER_SEC; // Calculate the difference in seconds
    // Print the time taken
    std::cout << "Search time: " << diff * 1e9 << " nanoseconds" << std::endl;
    // Print a message indicating the word was not found
    std::cout << "Couldn't find the word " << inp_word << " in the search function, returning nullptr!" << std::endl;
    // Return nullptr if the node with the input ASCII value is not found in the tree
    return ans;
    // return nullptr;
}


void RBTree::fixDeleteRBTree(Node *&node) {//fixes the properties of the tree afte the node has been removed
    if (node == nullptr) // Check if the node is null, indicating the end of the fix-up process

        return;

    if (node == root) {    // If the node is the root, set the root to null and return
        root = nullptr;
        return;
    }
    // Check if the node or its children are red
    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        // If so, find the child node (either left or right) which is red
        Node *child = node->left != nullptr ? node->left : node->right;
        //we tehn set the parent's pointer to the child node
        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);// Set the color of the child to black
            delete (node); //delete the current node
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);// Set the color of the child to black
            delete (node);// Delete the current node
        }
    } else {
        // If the node and its children are all black,then we will start the fix-up process
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);// Set the color of the node to double black
        
        // Continue the loop until the current node is not the root and its color is double black
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            // Determine the sibling of the current node
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {// Case 1: If the sibling is red
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {//sibling = parent-left

                    // Case 2: If both children of the sibling are black
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);// Set the color of the sibling to red
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);// Set the color of the parent to black
                        else
                            setColor(parent, DOUBLE_BLACK);// Set the color of the parent to double black
                        ptr = parent;// Move up to the parent node
                    } else {
                        // Case 3: If the sibling has at least one red child

                        // If the sibling's child on the opposite side of ptr is black
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}



Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

void RBTree::deleteValue(int data) { //this deletes the node and then fixes the REd black tree properties
    std::clock_t start = std::clock(); // Start the timer

    std::cout<<"will now be deleting the node from the tree :("<<std::endl;
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);

    std::clock_t end = std::clock(); // End the timer
    double diff = (end - start) * 1.0 / CLOCKS_PER_SEC;
    diff=diff * 1e9;
    node_deletion_time=diff; //time taken to delete the node
}

void RBTree::deleteWord(std::string word){
    int nodes=CountNodes(root);
    std::clock_t start = std::clock(); // Start the timer

    std::cout<<"entered the deleteWord function"<<std::endl;
    int word_asci=0;
    for (char c : word) {       
        int asciiValue = static_cast<int>(c);
        word_asci+=asciiValue;    
    }
    
    Node* current=root;//pointer that starts from the root
    Node* targetNode=nullptr;
    while(current != nullptr && current->data != word_asci){//loop to find the node with the asci value of word
        if(current->data < word_asci){
            current=current->right ; //if asci of word is greater than we go to right subtree
        }
        else if(current->data>word_asci){
            current=current->left;   //if asci of word is smaller than we go to left subtree  
        }
         
                          
    }
    targetNode=current; //assinging the current node to the target node 

    if(targetNode==nullptr){
        std::cout<<"couldnt fine the node with this asci value:("<<std::endl;
    }
    else{
        //this part here deals with the removal of the word from the vector of the node
        std::string popped_word="";
        std::vector<std::string> temp_container;
        popped_word = std::move(targetNode->words.back()); // Moving the last element to popped_word
        targetNode->words.pop_back(); //pop only removes the element, doesnt return anything

        while(popped_word!=word){ //this pops the pops elements until the target word is not popped, then the target word is discarded
            temp_container.push_back(popped_word);
            popped_word = std::move(targetNode->words.back()); // Move the last element to popped_word
            targetNode->words.pop_back();
        }

        std::string temp_container_word="";
        while(temp_container.size()>0){ //this pushes back all the words other than the target word
            temp_container_word=std::move(temp_container.back());
            temp_container.pop_back();
            targetNode->words.push_back(temp_container_word);
        }
        std::cout<<"word deleted now!"<<std::endl;


    }
    float total_deletion_time=0;
    if(targetNode->words.size()==0){
        deleteValue(word_asci); //if the node becomes empty then we delete that node by callin this function
        total_deletion_time=total_deletion_time+node_deletion_time;
    }

    std::clock_t end = std::clock(); // End the timer
    double diff = (end - start) * 1.0 / CLOCKS_PER_SEC; // Calculate the difference in seconds
    total_deletion_time+=diff * 1e9;
    std::cout << "deletion Time taken: " << total_deletion_time << " ns" << std::endl;

    // std::cout << "deletion Time taken: " << diff * 1e9 << " ns" << std::endl;
    std::cout << "expected deletion time is: " << std::log(nodes) << std::endl;





}