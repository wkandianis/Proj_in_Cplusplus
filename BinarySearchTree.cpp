/********************************************
* Comp 15 - Fall 2019
* Homework 4
* Will Kandianis
* 11/04/2019
* 
* BinarySearchTree implementation
*********************************************/

#include "BinarySearchTree.h"
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

BinarySearchTree::BinarySearchTree() {
root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
        // walk tree in post-order traversal and delete
post_order_delete(root);
root = nullptr;  // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}
// delete 
// paramters: none
// returns: none
// does: recursively calls itself in order to delete all nodes
void BinarySearchTree::post_order_delete(Node *node) {
if(node != nullptr) {
post_order_delete(node->right);
post_order_delete(node->left); 
delete node;
}
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
        // use pre-order traversal to copy the tree
root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source) {
        // TODO: Students write code here
if(this == &source) {
return *this;
}

// delete tempent tree if it exists
post_order_delete(root);
root = pre_order_copy(source.root);
// use pre-order traversal to copy the tree
return *this;
        // don't forget to "return *this"
}

BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const {
if(node == nullptr) {
    return nullptr;
}
Node *temp = new Node;
temp->count = node->count;
temp->data = node->data;
temp->left = pre_order_copy(node->left);
temp->right = pre_order_copy(node->right);
return temp;
}

// find_min
// parameters: none
// returns: int
// does: calls private find min function and returns data at that node
int BinarySearchTree::find_min() const {
if (root == nullptr)
        return numeric_limits<int>::max(); // INT_MAX

return find_min(root)->data;
}

// find_min
// parameters: node
// returns: node
// does: finds the furthest left element on the tree which is the smallest
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const {
if(node->left != nullptr) {
    return find_min(node->left);
} 
    return node;
             
}

// find_max
// parameters: none
// returns: int
// does: calls private find max function and returns data at that node
int BinarySearchTree::find_max() const {
if (root == nullptr)
        return numeric_limits<int>::max(); // INT_MAX

return find_max(root)->data;
}

// find_max
// parameters: node
// returns: node
// does: finds the furthest right element on the tree which is the largest
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const {
if(node->right != nullptr) {
    return find_max(node->right);
} 
    return node;
}

// contains
// parameters: value
// returns: bool
// does: calls private contains functions and either returns true or false
bool BinarySearchTree::contains(int value) const {
if(contains(root, value)) {
    return true;
} else {
    return false;
}
}

// contains
// parameters: node, value
// returns: bool
// does: traverses the tree in logN time to see if a value is in the tree
bool BinarySearchTree::contains(Node *node, int value) const {

if(node == nullptr) {
    return false;
}
if(node->data == value) {
    return true;
} 
if(node->data > value) {
    return contains(node->left, value);
}
if(node->data < value) {
    return contains(node->right, value);
} 

return false;

}

// insert
// parameters: value
// returns: none
// does: calls private insert function
void BinarySearchTree::insert(int value) {
        insert(root, nullptr, value);
}

// insert
// parameters: node, parent, value
// returns: none
// does: traverses the tree in logN time to insert value into proper place in tree
void BinarySearchTree::insert(Node *node, Node *parent, int value) {
if(node == nullptr) {
Node *n = new Node;
n->count = 1;
n->data = value;
n->left = nullptr;
n->right = nullptr;

if(parent != nullptr) {
    if(parent->data > value) {
        parent->left = n;
    }
    if(parent->data < value) {
        parent->right = n;
    }
}

if(parent == nullptr) {
    root = n;
}


} else {
    
if(node->data == value) {
    node->count++;
}
if(node->data > value) {
    insert(node->left, node, value);
}
if(node->data < value) {
    insert(node->right, node, value);
}
}
}

// find node
// parameters: node, value
// returns: node
// does: exactly the same as contains, except when it finds the node it is 
// looking for, it returns the node instead of true
BinarySearchTree::Node *BinarySearchTree::find_node(Node *node, int value) {
if(node == nullptr) {
    return nullptr;
}
if(contains(node, value) == false) {
    return nullptr;

} 


if(node->data == value) {
    return node;
} 
else if(node->data > value) {
    return find_node(node->left, value);
}
else if(node->data < value) {
    return find_node(node->right, value);
} else {
    return nullptr;
}
    
    

}
// remove
// parameters: value
// returns: bool
// does: calls private remove function
bool BinarySearchTree::remove(int value) {
        // TODO:  Students pick one of the following calls
        //        depending on which remove function they wrote
        //
return remove(root, nullptr, value);

}

// is_leaf
// paramters: Node
// returns: bool
// does: returns true if both children of given node are null
bool BinarySearchTree::is_leaf(Node *node) {
if(node->left == nullptr and node->right == nullptr) {
    return true;
} else {
    return false;
}
}
// remove
// parameters: node, parent, value
// returns: bool
// does: uses pointers to hold on to nodes and then assign the parent
// pointers to null/the child of the toDelete node, then deletes the node
// to avoid memory leaks. 
// notes: I know this a huge function over 30 lines, but when I tried
// breaking it up it stopped working and I didn't have enough time to
// figure it out so I figured it was better to have it work and have it
// be over 30 lines than for it to not work
bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
if(node == nullptr) {
    return false;
}
Node *toDelete = find_node(node, value);
if(toDelete != nullptr) {
toDelete->count--;
if(toDelete->count == 0) {
parent = find_parent(root, toDelete);
// if the toDelete is a leaf
if(is_leaf(toDelete) == true) {
    // makes parent point to null and delete temp
    if(parent->left->data == toDelete->data) {
        parent->left = nullptr;
    } 
    else if(parent->right->data == toDelete->data) {
        parent->right = nullptr;
    }
    delete toDelete;
    return true;
}
// if toDelete has a right child
if(toDelete->left == nullptr) {
    Node *temp = toDelete->right;
    if(parent->left->data == toDelete->data) {
        parent->left = temp;
    }
    else if(parent->right->data == toDelete->data) {
        parent->right = temp;
    }
    delete toDelete;
    return true;
}
// if toDelete has a left child
if(toDelete->right == nullptr) {
    Node *temp = toDelete->left;
    if(parent->left->data == toDelete->data) {
        parent->left = temp;
    }
    else if(parent->right->data == toDelete->data) {
        parent->right = temp;
    }
delete toDelete;
return true;
}
//if there are two children
Node *min = find_min(toDelete->right);
Node *max = find_max(toDelete->left);
// if both children are leaves
if(is_leaf(toDelete->left) == true and is_leaf(toDelete->right) == true) {
    parent = find_parent(root, toDelete);
    parent->left = max;
    max->left = min;
    delete toDelete;
    return true;
} else {
parent = find_parent(root, min);
if(parent == nullptr) {
    cout << "parent = null" << endl;
}
parent->left = min->right;
toDelete->data = min->data;
toDelete->count = min->count;
delete min;
return true;
}
}
return true;
}
return false;
}

// tree_height
// parameters: none
// returns: int
// does: calls private tree height function
int BinarySearchTree::tree_height() const {
return tree_height(root);
}

// tree_height
// paramters: node
// returns: int
// does: recursively calls itself in order to add the amount of hops
// (height) in the tree
int BinarySearchTree::tree_height(Node *node) const {

if(node == nullptr) {
    return -1;
}

int height_left = tree_height(node->left);
int height_right = tree_height(node->right);

return 1 + max(height_left, height_right);
}

// node_count
// parameters: none
// returns: int
// does: calls private node count function
int BinarySearchTree::node_count() const {
return node_count(root);
}

// node_count
// parameters: none
// returns: int
// does: recursively adds the nodes to return the total amount of nodes in the tree
int BinarySearchTree::node_count(Node *node) const {
int sum = 1;
if(node == nullptr) {
    return 0;
} else {
    sum = sum + node_count(node->left);
    sum = sum + node_count(node->right);
}
return sum;
}

// count_total
// parameters: none
// returns: int
// does: calls private count total function
int BinarySearchTree::count_total() const {
return count_total(root);
}

// node_count
// parameters: none
// returns: int
// does: recursively adds the data in the nodes to return the total 
// number amount in the tree, including duplicates
int BinarySearchTree::count_total(Node *node) const {
      
if(node == nullptr) {
    return 0;
} 
int sum = node->data;
// if the number is a duplicate
if(node->count != 1) {
    sum = sum * node->count;
} 

sum = sum + count_total(node->left);
sum = sum + count_total(node->right);

return sum;
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const {
if (node == nullptr)
        return nullptr;

// if either the left or right is equal to the child,
// we have found the parent
if (node->left == child or node->right == child) {
        return node;
}

// Use the binary search tree invariant to walk the tree
if (child->data > node->data) {
        return find_parent(node->right, child);
} else {
        return find_parent(node->left, child);
}
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const {
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth character for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const tempPos,
                                  const char *const fullLine,
                                  const char *const branch) const {
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(tempPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(tempPos - levelLength, EMPTY);

        // Terminate fullLine at tempent level
        *tempPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(tempPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(tempPos, CONNECT), fullLine, DOWN);
}
