#ifndef COP3530PROJECT3_RBTREE_H
#define COP3530PROJECT3_RBTREE_H

#include <iostream>
using namespace std;

struct treeNode{
    treeNode* parent = nullptr;
    string name;
    int value;
    bool color = true;
    //bool of true means red node and bool of false means black node
    treeNode* left = nullptr;
    treeNode* right = nullptr;
};

class RBTree{
private:
    treeNode* root = nullptr;
public:
    treeNode* getRoot(){return root;};

    void insert(string& name, int value);
    void helperInsertL(treeNode* r, treeNode* n);
    void helperInsertR(treeNode* r, treeNode* n);

    void balance(treeNode* node);
    void Rotation(treeNode* grandparent, treeNode* parent, treeNode* child);
    void RootRotation(treeNode* grandparent, treeNode* parent);

    treeNode* search(treeNode *r, string& s);
};


#endif //COP3530PROJECT3_RBTREE_H
