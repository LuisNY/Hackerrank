#include <iostream>
#include <deque>
#include <stdio.h>
#include <vector>

using namespace std;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

struct Node {
    
    int value;
    int parent;
    vector<Node *> children;
    vector<int> overallChildrenNum;
};


class tree{
    
public:
    vector<Node> myVect;
    
    tree(int N){
        myVect.resize(N);
    }
    
    void findChildren(){
        
        for(int i=1; i<myVect.size(); i++){            
            for (int j=2; j<myVect.size(); j++){
                if(this->myVect[j].parent == i){
                    this->myVect[i].children.push_back(&this->myVect[j]);
                }
            }
            this->myVect[i].overallChildrenNum.resize(this->myVect[i].children.size());
        }
    }
        
    void findMaxEdges() {
        
        for(int j=1; j<this->myVect.size(); j++){
            int cont=0;
            cont = countNumbChildren(&this->myVect[j], cont);
         }
        return;
    }
    
    
    int countNumbChildren(Node *myNode, int cont){
        
        if(myNode->children.size()==0)
            return cont;
        
        for(int i=0; i<myNode->children.size(); i++){
            cont++;
            cont = countNumbChildren(myNode->children[i], cont);
            
            if(i>0){
                int prevSum=0;
                for(int index = i-1; index>=0; index--){
                    prevSum+=myNode->overallChildrenNum[index];
                    myNode->overallChildrenNum[i] = cont - prevSum;
                }
            }
            else
                myNode->overallChildrenNum[i] = cont;
        }
        
        return cont;
    }
    
    
    bool isLeaf(Node myNode){
        if(myNode.children.size() == 0)
            return true;
        return false;
    }
    
    void printMaxEdges(){
        int cont=0;
        for(int i=0; i<this->myVect.size(); i++){
            for(int j=0; j<this->myVect[i].overallChildrenNum.size(); j++){
                if(this->myVect[i].overallChildrenNum[j] % 2 == 0)
                    cont++;
            }
        }
        cout << cont << endl;
        return;
    }
};




int main(){
    
    int N, M;
    cin >> N >> M;
    
    tree myTree(N+1);
    myTree.myVect[1].parent=0;
    
    for(int i=2; i<=N; i++){
        int value, index;
        
        cin >> index >> value;
        myTree.myVect[index].value = index;
        myTree.myVect[index].parent = value;
    }
    
    myTree.findChildren();
    myTree.findMaxEdges();
    myTree.printMaxEdges();
    
    return 0;
}
