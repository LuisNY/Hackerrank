#include <iostream>
using namespace std;

typedef struct NODE {
    
    int data;
    NODE *left;
    NODE *right;
}node;

node * lca(node * root, int v1,int v2)
{
    
    int max = (v1>v2) ? v1 : v2;
    int min = (v1<v2) ? v1 : v2;
    
    if(max==root->data || min==root->data)
        return root;
    
    if(max > root->data && min < root->data)
        return root;
    
    
    node *ptr1 = root;
    while(ptr1->data!=v1){
        
        if(ptr1->data > v1)
            ptr1=ptr1->left;
        else
            ptr1=ptr1->right;
        
        if(ptr1->data == v2)
            return ptr1;
    }
    
    node *ptr2 = root;
    while(ptr2->data!=v2){
        
        if(ptr2->data > v2)
            ptr2=ptr2->left;
        else
            ptr2=ptr2->right;
        
        if(ptr2->data == v1)
            return ptr2;
    }
    
    node *ptr = root;
    
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




int main() {

    //manually construct the tree
    
    node *newNode3 = new(node);
    newNode3->data = 3;
    
    node *newNode4 = new(node);
    newNode4->data = 4;
    
    node *newNode5 = new(node);
    newNode5->data = 5;
    
    node *newNode6 = new(node);
    newNode6->data = 6;
    
    node *newNode8 = new(node);
    newNode8->data = 8;

    node *newNode9 = new(node);
    newNode9->data = 9;
    
    node *newNode10 = new(node);
    newNode10->data = 10;
    
    node *newNode13 = new(node);
    newNode13->data = 13;
    
    node *newNode15 = new(node);
    newNode15->data = 15;
    
    node *newNode17 = new(node);
    newNode17->data = 17;
    
    node *newNode18 = new(node);
    newNode18->data = 18;
    
    node *newNode20 = new(node);
    newNode20->data = 20;
    
    
    
    node *root=newNode9;
    
    newNode9->left = newNode5;
    newNode9->right = newNode15;
    
    newNode5->left = newNode3;
    newNode5->right = newNode6;
    
    newNode3->left = NULL;
    newNode3->right = newNode4;
    
    newNode4->left = NULL;
    newNode4->right = NULL;
    
    newNode6->left = NULL;
    newNode6->right = newNode8;
    
    newNode8->left = NULL;
    newNode8->right = NULL;
    
    newNode15->left = newNode13;
    newNode15->right = newNode18;
    
    newNode13->left = newNode10;
    newNode13->right = NULL;
    
    newNode10->left = NULL;
    newNode10->right = NULL;
    
    newNode18->left = newNode17;
    newNode18->right = newNode20;
    
    newNode17->left = NULL;
    newNode17->right = NULL;
    
    newNode20->left = NULL;
    newNode20->right = NULL;
    
    node *anc = lca(root, 9, 3);
    
    if(anc!=NULL)
        cout << anc->data << endl;
    else
        cout << "Error" << endl;
    
    return 0;
}
