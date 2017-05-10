#include <iostream>
using namespace std;

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




struct NODE * lca(struct NODE* root, int v1,int v2)
{
    
    int max = (v1>v2) ? v1 : v2;
    int min = (v1<v2) ? v1 : v2;
    
    if(max==root->data || min==root->data)
        return root;
    
    if(max > root->data && min < root->data)
        return root;
    
    
    struct NODE* ptr1 = root;
    while(ptr1->data!=v1){
        
        if(ptr1->data > v1)
            ptr1=ptr1->left;
        else
            ptr1=ptr1->right;
        
        if(ptr1->data == v2)
            return ptr1;
    }
    
    struct NODE* ptr2 = root;
    while(ptr2->data!=v2){
        
        if(ptr2->data > v2)
            ptr2=ptr2->left;
        else
            ptr2=ptr2->right;
        
        if(ptr2->data == v1)
            return ptr2;
    }
    
    struct NODE* ptr = root;
    
    while(true){
        
        if(ptr->data < min)
            ptr=ptr->right;
        else
            ptr=ptr->left;
        
        if (ptr->data > min && ptr->data<max)
            return ptr;
    }
    
    return NULL;
}

void printTreeInOrder(struct NODE* ptr){
    if(ptr!=NULL){
        printTreeInOrder(ptr->left);
        cout << ptr->data << endl;
        printTreeInOrder(ptr->right);
    }
}


int main() {
    
    struct NODE* root=NULL;
    
    root = insertNode(root, 5);
    root = insertNode(root, 3);
    root = insertNode(root, 8);
    root = insertNode(root, 0);
    root = insertNode(root, 4);
    root = insertNode(root, 7);
    root = insertNode(root, 8);
    root = insertNode(root, 10);

    //printTreeInOrder(root);
    
    struct NODE* anc = lca(root, 0, 4);
    
    if(anc!=NULL)
        cout << "Ancestor: " << anc->data << endl;
    else
        cout << "Error" << endl;
    
    return 0;
}
