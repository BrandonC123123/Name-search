#include "RBTree.h"

void RBTree::insert(string& name, int value){
    //If a name is in the list multiple years, combines the number
    //of times it was used to get the total value
    treeNode* temp = search(root, name);
    if(temp != nullptr){
        temp->value += value;
        return;
    }
    treeNode* n = new treeNode;
    n->name = name;
    n->value = value;
    if(root == nullptr){
        root = n;
        return;
    }
    else if(root->name > n->name){
        helperInsertL(root, n); //Inserts into the left subtree
    }
    else {
        helperInsertR(root, n); //Inserts into the right subtree
    }
    balance(n);
}

//Checks if r's left child is null, if so, sets n to be r's left child.
//Otherwise, iterates further down the tree
void RBTree::helperInsertL(treeNode* r, treeNode* n){
    if(r->left == nullptr){
        r->left = n;
        n->parent = r;
        return;
    }
    else if(r->left->name > n->name){
        helperInsertL(r->left, n);
        return;
    }
    else{
        helperInsertR(r->left, n);
        return;
    }
}

//Checks if r's right child is null, if so, sets n to be r's right child.
//Otherwise, iterates further down the tree
void RBTree::helperInsertR(treeNode* r, treeNode* n){
    if(r->right == nullptr){
        r->right = n;
        n->parent = r;
        return;
    }
    else if(r->right->name > n->name){
        helperInsertL(r->right, n);
        return;
    }
    else{
        helperInsertR(r->right, n);
        return;
    }
}


void RBTree::balance(treeNode* node){
    //Boolean of true represents the color Red, false represents black
    if (node->parent == nullptr){
        node->color = false;
        return;
    }
    if (!node->parent->color){
        return;
    }
    //If the node is the root, make it black. If the node has a black parent;
    //leave it red. In both cases, the function is complete.
    treeNode* parent = node->parent;
    treeNode* grandparent = parent->parent;
    if(grandparent == nullptr){
        return;
    }

    treeNode* uncle;
    //Find uncle by comparing grandparents two children to the parent node.
    if(grandparent->left == parent){
        uncle = grandparent->right;
    }
    else{
        uncle = grandparent->left;
    }

    //Runs proper recolors and rebalances if uncle is red
    if (uncle != nullptr && uncle->color){
        parent->color = uncle->color = false;
        grandparent->color = true;
        balance(grandparent);
        return;
    }
    //Runs the proper rotations if uncle is black
    Rotation(grandparent, parent, node);
}


void RBTree::Rotation(treeNode* grandparent, treeNode* parent, treeNode* child){
    treeNode* greatgrand = grandparent->parent;
    if(greatgrand == nullptr){
        //If greatgrand is null, grandparent is the root node, and
        //the tree's root node will need to be reassigned
        RootRotation(grandparent, parent);
        return;
    }
    //The following if statements determined the type of rotation
    //Then the pointers are reassigned as needed
    if(grandparent->left == parent){
        if(parent->left == child){
            //Left Left rotation
            if(greatgrand->left == grandparent){
                greatgrand->left = parent;
            }
            else{
                greatgrand->right = parent;
            }
            parent->parent = greatgrand;
            grandparent->left = parent->right;
            if(grandparent->left != nullptr){
                grandparent->left->parent = grandparent;
            }
            parent->right = grandparent;
            grandparent->parent = parent;

            parent->color = false;
            grandparent->color = true;
        }
        else{
            //Left Right rotation
            if(greatgrand->left == grandparent){
                greatgrand->left = child;
            }
            else{
                greatgrand->right = child;
            }
            child->parent = greatgrand;

            grandparent->left = child->right;
            if(grandparent->left != nullptr){
                grandparent->left->parent = grandparent;
            }
            parent->right = child->left;
            if(parent->right != nullptr){
                parent->right->parent = parent;
            }

            child->left = parent;
            child->right = grandparent;
            parent->parent = child;
            grandparent->parent = child;

            child->color = false;
            grandparent->color = true;
        }
    }
    else {
        if (parent->right == child) {
            //Right Right rotation
            if(greatgrand->left == grandparent){
                greatgrand->left = parent;
            }
            else{
                greatgrand->right = parent;
            }
            parent->parent = greatgrand;
            grandparent->right = parent->left;
            if(grandparent->right != nullptr){
                grandparent->right->parent = grandparent;
            }
            parent->left = grandparent;
            grandparent->parent = parent;

            parent->color = false;
            grandparent->color = true;
            if(parent->name == "MMM"){
                cout << parent->parent << endl;
            }
        }
        else {
            //Right Left rotation
            if(greatgrand->left == grandparent){
                greatgrand->left = child;
            }
            else{
                greatgrand->right = child;
            }
            child->parent = greatgrand;

            grandparent->right = child->left;
            if(grandparent->right != nullptr){
                grandparent->right->parent = grandparent;
            }
            parent->left = child->right;
            if(parent->left != nullptr){
                parent->left->parent = parent;
            }

            child->right = parent;
            child->left = grandparent;
            parent->parent = child;
            grandparent->parent = child;

            child->color = false;
            grandparent->color = true;
        }
    }
}

//The performs rotations in which the root will need to be reassigned
void RBTree::RootRotation(treeNode *grandparent, treeNode *parent) {
    if(grandparent->left == parent){
        if(parent->left != nullptr){
            //Left Left rotation
            parent->parent = grandparent->parent;
            grandparent->left = parent->right;
            if(grandparent->left != nullptr){
                grandparent->left->parent = grandparent;
            }
            parent->right = grandparent;
            grandparent->parent = parent;
            root = parent;

            parent->color = false;
            grandparent->color = true;
        }
        else{
            //Left Right rotation
            treeNode* child = parent->right;
            child->parent = grandparent->parent;

            parent->right = child->left;
            if(parent->right != nullptr){
                parent->right->parent = parent;
            }
            grandparent->left = child->right;
            if(grandparent->left != nullptr){
                grandparent->left->parent = grandparent;
            }

            child->left = parent;
            child->right = grandparent;
            parent->parent = child;
            grandparent->parent = child;
            root = child;

            child->color = false;
            grandparent->color = true;
        }
    }
    else {
        if (parent->right != nullptr) {
            //Right Right rotation
            parent->parent = grandparent->parent;
            grandparent->right = parent->left;
            if(grandparent->right != nullptr){
                grandparent->right->parent = grandparent;
            }
            parent->left = grandparent;
            grandparent->parent = parent;
            root = parent;

            parent->color = false;
            grandparent->color = true;
        }
        else {
            //Right Left rotation
            treeNode* child = parent->left;
            child->parent = grandparent->parent;

            parent->left = child->right;
            if(parent->left != nullptr){
                parent->left->parent = parent;
            }
            grandparent->right = child->left;
            if(grandparent->right != nullptr){
                grandparent->right->parent = parent;
            }

            child->right = parent;
            child->left = grandparent;
            parent->parent = child;
            grandparent->parent = child;
            root = child;

            child->color = false;
            grandparent->color = true;
        }
    }
}

//Iterates through the tree to find the node with a given name
treeNode* RBTree::search(treeNode *r, string& s){
    if(r == nullptr){
        return nullptr;
    }
    else if(r->name == s){
        return r;
    }
    else if(r->name > s){
        return search(r->left, s);
    }
    else{
        return search(r->right, s);
    }
}