#include <iostream>
#include <unordered_map>
using namespace std;
using std::unordered_map;

struct NODE {
    
    int data;
    NODE *left;
    NODE *right;
};

struct NODE* insertNode(struct NODE* root, int x){
    
    struct NODE* myNode = new(struct NODE);
    myNode->data = x;
    myNode->left = NULL;
    myNode->right = NULL;
    
    if(root==NULL){
        root = myNode;
        return root;
    }
    else {
        struct NODE* ptr=root;
        struct NODE* ptr2=NULL;
        
        while(ptr!=NULL) {
            if (myNode->data > ptr->data){
                ptr2=ptr;
                ptr = ptr->right;
            }
            else{
                ptr2=ptr;
                ptr = ptr->left;
            }
        }
        
        if(ptr2->data > myNode->data)
            ptr2->left = myNode;
        else
            ptr2->right = myNode;
    }

    return root;
}


void printTreeInOrder(struct NODE* ptr){
    if(ptr!=NULL){
        printTreeInOrder(ptr->left);
        cout << ptr->data << endl;
        printTreeInOrder(ptr->right);
    }
}




//this function computes the different number of elements that can be found on any path in the tree
//the max number of different elements in a path is saved in a variable passed by reference to the function
void countDiffElem(struct NODE* root, int& max){
    
    static unordered_map<int, int> mySet;
    
    if(root==NULL)
        return;
    
    unordered_map<int, int>::iterator it;
    it = mySet.find(root->data); //look for the current element in the hashTable
    
    //if element already in the table, increase counter by one
    if (it != mySet.end()){
        int temp = it->second;
        mySet.erase(root->data);
        mySet.insert(make_pair(root->data, ++temp));
    }
    //if element not present yet, add it to the hashTable
    else {
        mySet.insert(make_pair(root->data, 1));
    }
    
    //check the left subtree
    countDiffElem(root->left, max);
    
    //if coming back from a non-NULL node from the left
    if(root->left!=NULL){
        it = mySet.find(root->left->data);
        if (it != mySet.end()){
            int temp = it->second;
            mySet.erase(root->left->data);
            if(temp>1){
                mySet.insert(make_pair(root->left->data, --temp));
            }
        }
    }
    
    //check the right subtree
    countDiffElem(root->right, max);
    
    //if coming back from a non-NULL node from the right
    if(root->right!=NULL){
        it = mySet.find(root->right->data);
        if (it != mySet.end()){
            int temp = it->second;
            mySet.erase(root->right->data);
            if(temp>1){
                mySet.insert(make_pair(root->right->data, --temp));
            }
        }
    }
    
    //compare max with the number of different elements in the hashTable
    //update max if necessary
    if(max < (int)mySet.size()){
        max = (int)mySet.size();
    }
    
    return;
}


int main() {
    
    //struct NODE* root=NULL;
    


    //manually construct the tree
    struct NODE *newNode1 = new(struct NODE);
    struct NODE *newNode2 = new(struct NODE);
    struct NODE *newNode3 = new(struct NODE);
    struct NODE *newNode4 = new(struct NODE);
    struct NODE *newNode5 = new(struct NODE);
    struct NODE *newNode6 = new(struct NODE);
    struct NODE *newNode7 = new(struct NODE);
    struct NODE *newNode8 = new(struct NODE);
    struct NODE *newNode9 = new(struct NODE);
    struct NODE *newNode10 = new(struct NODE);
    struct NODE *newNode11 = new(struct NODE);
    struct NODE *newNode12 = new(struct NODE);
    struct NODE *newNode13 = new(struct NODE);
    
    newNode1->data = 5;
    newNode1->left = newNode2;
    newNode1->right = newNode7;
    
    newNode2->data = 3;
    newNode2->left = newNode3;
    newNode2->right = newNode5;
    
    newNode3->data = 5;
    newNode3->left = newNode4;
    newNode3->right = NULL;
    
    newNode4->data = 0;
    newNode4->left = NULL;
    newNode4->right = NULL;
    
    newNode5->data = 4;
    newNode5->left = NULL;
    newNode5->right = newNode6;
    
    newNode6->data = 5;
    newNode6->left = NULL;
    newNode6->right = NULL;
    
    newNode7->data = 8;
    newNode7->left = newNode8;
    newNode7->right = newNode9;
    
    newNode8->data = 7;
    newNode8->left = NULL;
    newNode8->right = newNode11;
    
    newNode9->data = 10;
    newNode9->left = NULL;
    newNode9->right = newNode10;
    
    newNode10->data = 11;
    newNode10->left = NULL;
    newNode10->right = newNode13;
    
    newNode11->data = 3;
    newNode11->left = NULL;
    newNode11->right = newNode12;
    
    newNode12->data = 9;
    newNode12->left = NULL;
    newNode12->right = NULL;
    
    newNode13->data = 11;
    newNode13->left = NULL;
    newNode13->right = NULL;

    
    printTreeInOrder(newNode1);
    cout << endl;
    
    int max=-1;
    
    countDiffElem(newNode1, max);
    
    cout << max << endl;
    return 0;
}
