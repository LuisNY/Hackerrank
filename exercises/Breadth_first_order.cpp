//C++ program

/*
 
 Insert nodes in a Binary Search Tree and then search the tree in a Breadth-First order
 
 */

#include <iostream>
#include <deque>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;
using std::deque;
using std::queue;
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::vector;

struct NODE {
    int data;
    NODE * left;
    NODE * right;
};


class myTree{
    
public:
    
    NODE *root;
    myTree(){
        root=nullptr;
    };
    
    void insert(NODE *myRoot, int value)
    {
        if (myRoot==NULL){
            NODE *newNode = new(NODE);
            newNode->data = value;
            newNode->left = NULL;
            newNode->right = NULL;
            root = newNode;
        }
        else if (value > myRoot->data){
            
            if (myRoot->right == NULL){
                NODE *newNode = new(NODE);
                newNode->data = value;
                newNode->left = NULL;
                newNode->right = NULL;
                myRoot->right = newNode;
            }
            else {
                insert(myRoot->right, value);
            }
        }
        else {
            if (myRoot->left == NULL){
                NODE *newNode = new(NODE);
                newNode->data = value;
                newNode->left = NULL;
                newNode->right = NULL;
                myRoot->left = newNode;
            }
            else {
                insert(myRoot->left, value);
            }
        }
    }
    
    void breadthFirstSearch(){
        
        queue<NODE*> myQueue;
        myQueue.push(root);
        
        while (!myQueue.empty()){
            NODE *myNode = myQueue.front();
            cout << myNode->data << endl;
            myQueue.pop();
            if(myNode->left!=NULL){
                myQueue.push(myNode->left);
            }
            if(myNode->right!=NULL){
                myQueue.push(myNode->right);
            }
        }
        return;
    }
};




int main(){
    
    myTree tree;
    
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 5);
    tree.insert(tree.root, 0);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 6);
    tree.insert(tree.root, 7);
    tree.insert(tree.root, 8);
    tree.insert(tree.root, 15);
    tree.insert(tree.root, 12);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 18);
    tree.insert(tree.root, 22);
    
    tree.breadthFirstSearch();
    
    return 0;
}
