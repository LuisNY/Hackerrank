#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::stack;
using std::set;



struct NODE {
    
    int data;
    NODE* next;
};

struct NODEChar {
    
    char c;
    NODEChar* next;
};



void insertNode(NODE** root, int x){
    
    NODE* newNode = new(NODE);
    newNode->data = x;
    
    if(*root==NULL){
        *root=newNode;
        newNode->next = NULL;
        return;
    }
    
    if((*root)->data > x){
        
        newNode->next = *root;
        *root = newNode;
        return;
    }
    
    NODE *currNode = *root;
    NODE *prevNode = NULL;
    
    while(currNode!=NULL && currNode->data<=x){
        prevNode = currNode;
        currNode = currNode->next;
    }

    if(currNode==NULL){
        prevNode->next = newNode;
        newNode->next = NULL;
    }
    
    else {
        prevNode->next = newNode;
        newNode->next = currNode;
    }
    return;
}


void deleteNode(NODE *head, NODE* myNode){
    
    if(head == NULL){
        cout << "nothing to delete" << endl;
        return;
    }
    
    if(head==myNode){
        
        if(head->next == NULL){
            printf("There is only one node. The list can't be made empty ");
            return;
        }
        
        head->data = head->next->data;
        head->next = head->next->next;
        delete(myNode);
        return;
    }
    
    while(head->next!=NULL){
        
        if(head->next->data == myNode->data){
            head->next = head->next->next;
            return;
        }
        head=head->next;
    }
    
    if(head->next==NULL){
        printf("\n Given node is not present in Linked List\n");
        return;
    }
    
    delete(myNode);
    
    
    
}


void insertNodeChar(NODEChar** root, char x){
    
    NODEChar* newNode = new(NODEChar);
    newNode->c = x;
    
    if(*root==NULL){
        *root=newNode;
        newNode->next = NULL;
        return;
    }
    
    if((*root)->c > x){
        
        newNode->next = *root;
        *root = newNode;
        return;
    }
    
    NODEChar *currNode = *root;
    NODEChar *prevNode = NULL;
    
    while(currNode!=NULL && currNode->c<=x){
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    if(currNode==NULL){
        prevNode->next = newNode;
        newNode->next = NULL;
    }
    
    else {
        prevNode->next = newNode;
        newNode->next = currNode;
    }
    return;
}


int compareStr(NODEChar* str1, NODEChar* str2){
    
    if(str1==NULL || str2==NULL){
        cout << "one string is empty" << endl;
        return 0;
    }
    
    while(str1!=NULL && str2!=NULL){
        
        if(str1->c == str2->c){
            str1=str1->next;
            str2=str2->next;
        }
        else if(str1->c > str2->c){
            return 1;
        }
        else {
            return -1;
        }
    }
    
    if(str1==NULL && str2==NULL)
        return 0;
    else if(str1!=NULL && str2==NULL)
        return 1;
    else
        return -1;
    
}




void printNodes(NODE* head){
    
    NODE *ptr = head;
    while (ptr!=NULL) {
        cout << ptr->data << " " << endl;
        ptr = ptr->next;
    }
    cout << endl;
    return;
}

void printNodesChar(NODEChar* head){
    
    NODEChar *ptr = head;
    while (ptr!=NULL) {
        cout << ptr->c << " " << endl;
        ptr = ptr->next;
    }
    cout << endl;
    return;
}



int computeSum(NODE* node1, NODE* node2, NODE** result){
    
    if(node1==NULL || node2==NULL)
        return 0;
    
    int temp = node1->data + node2->data + computeSum(node1->next, node2->next, result);
    
    NODE *newNode = new(NODE);
    newNode->data = temp%10;
    newNode->next=*result;
    
    *result = newNode;
    int carry = temp/10;
    
    return carry;
}


void sumLinkedLists(NODE* head1, NODE* head2, NODE** result){
    
    NODE* ptr1=head1;
    int len1=0;
    while(ptr1!=NULL){
        len1++;
        ptr1=ptr1->next;
    }
    
    NODE* ptr2=head2;
    int len2=0;
    while(ptr2!=NULL){
        len2++;
        ptr2=ptr2->next;
    }
    
    if(len1>len2){
        int diff=len1-len2;
        ptr2=head2;
        while(ptr2!=NULL){
            ptr2=ptr2->next;
        }
        
        while(diff>0){
            NODE* newNode = new(NODE);
            newNode->data = 0;
            newNode->next = head2;
            head2=newNode;
            diff--;
        }
    }
        
    else if(len1<len2){
        int diff=len2-len1;
        ptr1=head1;
        while(ptr1!=NULL){
            ptr1=ptr1->next;
        }
        
        while(diff>0){
            NODE* newNode = new(NODE);
            newNode->data = 0;
            newNode->next = head1;
            head1=newNode;
            diff--;
        }
        
        
    }
    
    
    printNodes(head1);
    printNodes(head2);
    
    computeSum(head1, head2, result);
    
    printNodes(*result);
    
    
    return;
}



void mergeLists(NODE* head1, NODE** head2){
    
    NODE* ptr1 = head1;
    NODE* ptr2 = *head2;
    while(ptr1!=NULL && ptr2!=NULL){

        NODE* ptr1Next = ptr1->next;
        NODE* ptr2Next = ptr2->next;
        
        if(ptr2!=NULL){

            ptr1->next = ptr2;
            ptr2->next = ptr1Next;
            ptr2 = ptr2Next;
            *head2 = ptr2;
        }
        else break;
        
        ptr1 = ptr1Next;
    }
}



void reverseList(NODE** head){
    
    if(*head==NULL)
        return;
    
    NODE* ptr = *head;
    NODE* ptrNext = ptr->next;
    NODE* ptrPrev = NULL;
    
    while(ptrNext!=NULL){
        
        ptr->next = ptrPrev;
        ptrPrev=ptr;
        ptr=ptrNext;
        ptrNext=ptrNext->next;
    }
    
    ptr->next=ptrPrev;
    *head=ptr;
}

NODE* reverseListEveryK(NODE* head, int k)
{
    NODE* current = head;
    NODE* next = NULL;
    NODE* prev = NULL;
    int count = 0;
    
    /*reverse first k nodes of the linked list */
    while (current != NULL && count < k)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    /* next is now a pointer to (k+1)th node
     Recursively call for the list starting from current.
     And make rest of the list as next of first node */
    if (next !=  NULL)
        head->next = reverseListEveryK(next, k);
    
    /* prev is new head of the input list */
    return prev;
}





NODE* unionList(NODE* head1, NODE* head2){
    
    NODE* headUnion = NULL;
    
    set<int> mySet;
    
    NODE* ptr=head1;
    while(ptr!=NULL){
        
        if(mySet.find(ptr->data) == mySet.end()){
            mySet.insert(ptr->data);
            NODE* newNode = new(NODE);
            newNode->data = ptr->data;
            newNode->next = headUnion;
            headUnion = newNode;
        }
        ptr=ptr->next;
    }
    
    ptr = head2;
    
    while(ptr!=NULL){
        
        if(mySet.find(ptr->data) == mySet.end()){
            NODE* newNode = new(NODE);
            newNode->data = ptr->data;
            newNode->next = headUnion;
            headUnion = newNode;
        }
        ptr=ptr->next;
    }
    
    return headUnion;
}



NODE* intersectionList(NODE* head1, NODE* head2){
    
    
    NODE* headInter = NULL;
    set<int> mySet;

    NODE* ptr=head1;
    
    while(ptr!=NULL){
        
        if(mySet.find(ptr->data) == mySet.end()){
            mySet.insert(ptr->data);
        }
        
        ptr=ptr->next;
    }
    
    
    ptr=head2;
    while(ptr!=NULL){
        
        if(mySet.find(ptr->data) != mySet.end()){
            NODE* newNode = new(NODE);
            newNode->data = ptr->data;
            newNode->next = headInter;
            headInter = newNode;
        }
        
        ptr=ptr->next;
    }
    
    return headInter;
}


void selectRandom(NODE* head){
    
    if(head==NULL)
        return;
    
    srand((unsigned int)time(NULL));
    
    NODE* ptr=head;
    int result = head->data;
    for(int n=2; ptr!=NULL; n++){
        
        if(rand() % n == 0)
            result = ptr->data;
        ptr=ptr->next;
    }
    
    
    cout << "random node: " << result << endl;
    
}





int main() {
    
    NODE* head1 = NULL;
    NODE* head2 = NULL;
    
    insertNode(&head1, 1);
    insertNode(&head1, 2);
    insertNode(&head1, 3);
    insertNode(&head1, 4);
    insertNode(&head1, 5);
    insertNode(&head1, 6);
    insertNode(&head1, 7);
    insertNode(&head1, 10);
    insertNode(&head2, 6);
    insertNode(&head2, 7);
    insertNode(&head2, 8);
    insertNode(&head2, 9);
    insertNode(&head2, 10);
    //insertNode(&head2, 3);
    printNodes(head1);
    printNodes(head2);
    
    //mergeLists(head1, &head2);
    //printNodes(head1);
    //printNodes(head2);
    //NODE *result=NULL;
    //sumLinkedLists(head1, head2, &result);
    
    //printNodes(head1);
    //reverseListEveryK(head1, 3);
    //printNodes(head1);
    
    
    //selectRandom(head1);
    
    
    
//    NODE* unList=NULL;
//    unList = unionList(head1, head2);
//    printNodes(unList);
//    
//    
//    NODE* interList = NULL;
//    interList = intersectionList(head1, head2);
//    printNodes(interList);
//    deleteNode(head1, head1->next->next);
//    printNodes(head1);
//    
//    deleteNode(head1, head1->next->next);
//    printNodes(head1);
//    
//    deleteNode(head1, head1);
//    printNodes(head1);
//    
//    deleteNode(head1, head1->next);
//    printNodes(head1);
//    
//    deleteNode(head1, head1);
//    printNodes(head1);
    
    
    
//    NODEChar *headChar1 = NULL;
//    NODEChar *headChar2 = NULL;
//    
//    insertNodeChar(&headChar1, 'a');
//    insertNodeChar(&headChar1, 't');
//    insertNodeChar(&headChar1, 'u');
//    insertNodeChar(&headChar1, 'w');
//    
//    insertNodeChar(&headChar2, 'a');
//    insertNodeChar(&headChar2, 't');
//    insertNodeChar(&headChar2, 'u');
//    insertNodeChar(&headChar2, 'w');
//    
//    printNodesChar(headChar1);
//    cout << endl;
//    printNodesChar(headChar2);

    
    
    //cout << compareStr(headChar1, headChar2) << endl;
    
    return 0;
}
