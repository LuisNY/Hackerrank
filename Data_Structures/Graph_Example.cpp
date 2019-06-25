#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
using std::endl;
using std::cout;
using std::cin;
using std::set;
using std::queue;

template <typename T>
struct NODE {
public:
    T data;
    vector<NODE<T>*> neighbors;
};

template <typename T>
class GRAPH{
    
    vector<NODE<T>> nodes;
    
public:
    
    void insertNode(T x){
        
        NODE<T>* newNode = new NODE<T>;
        newNode->data = x;
        nodes.push_back(*newNode);
    }
    
    void insertEdge(T str1, T str2){
        
        NODE<T> *ptr1=NULL;
        NODE<T> *ptr2=NULL;
        
        for(typename vector<NODE<T>>::iterator it=nodes.begin(); it!=nodes.end(); it++){
            
            if(it->data==str1){
                ptr1=&*it;
            }
            if(it->data==str2){
                ptr2=&*it;
            }
        }
        if(ptr1==NULL || ptr2==NULL){
            cout << "Impossible to add connection" << endl;
            return;
        }
        
        ptr1->neighbors.push_back(ptr2);
    }
    
    void printNodes(){
        
        for(typename vector<NODE<T>>::iterator it=nodes.begin(); it!=nodes.end(); it++){
            cout << it->data << endl;
        }
        cout << endl;
    }
    
    
    void printConnections(T str){
        
        NODE<T> *ptr=NULL;
        for(typename vector<NODE<T>>::iterator it=nodes.begin(); it!=nodes.end(); it++){
            if(it->data==str){
                ptr=&*it;
            }
        }
        cout << "Connections from " << ptr->data << " to:" << endl;
        
        if(ptr->neighbors.size()==0)
            cout << "No connections available" << endl;
        
        for(int i=0; i<ptr->neighbors.size(); i++){
            cout << ptr->neighbors[i]->data << endl;
        }
    }
    
    
    void depthFirstSearch(NODE<T>* node){
        
        static set<T> mySet;
        if(node==NULL)
            return;
        
        cout << node->data << endl;
        mySet.insert(node->data);
        
        for(int i=0; i<node->neighbors.size(); i++){
            if(mySet.find(node->neighbors[i]->data)==mySet.end()){
                depthFirstSearch(node->neighbors[i]);
            }
        }
    }
    
    
    void breadthFirstSearch(NODE<T>* node){
        
        set<T> mySet;
        queue<NODE<T>> myQueue;
        
        myQueue.push(*node);
        
        while(!myQueue.empty()){
            NODE<T> currNode = myQueue.front();
            myQueue.pop();
            
            if(mySet.find(currNode.data)!=mySet.end()){
                continue;
            }
            cout << currNode.data << endl;
            mySet.insert(currNode.data);
            
            for(int i=0; i<currNode.neighbors.size(); i++){
                myQueue.push(*currNode.neighbors[i]);
            }
        }
    }
    
    void graphSearch(T str){
        
        NODE<T> *ptr=NULL;
        for(typename vector<NODE<T>>::iterator it=nodes.begin(); it!=nodes.end(); it++){
            if(it->data==str){
                ptr=&*it;
            }
        }
        
        if(ptr==NULL){
            cout << "Node not found" << endl;
            return;
        }
        NODE<T> *oldPtr=ptr;
        depthFirstSearch(ptr);
        cout << endl;
        breadthFirstSearch(oldPtr);
    }    
};


int main() {
    
    GRAPH<string> myGraph;
    
    myGraph.insertNode("NewYork");
    myGraph.insertNode("SanFrancisco");
    myGraph.insertNode("Atlanta");
    myGraph.insertNode("Chicago");
    myGraph.insertNode("Boston");
    myGraph.insertNode("London");
    myGraph.insertNode("Rome");
    myGraph.insertNode("Paris");
    myGraph.insertNode("Berlin");
    myGraph.insertNode("Madrid");
    
    myGraph.insertEdge("NewYork", "SanFrancisco");
    myGraph.insertEdge("NewYork", "Madrid");
    myGraph.insertEdge("Berlin", "NewYork");
    myGraph.insertEdge("Madrid", "SanFrancisco");
    myGraph.insertEdge("Berlin", "Madrid");
    myGraph.insertEdge("Madrid", "Boston");
    myGraph.insertEdge("Boston", "Rome");
    myGraph.insertEdge("Boston", "Berlin");
    myGraph.insertEdge("Rome", "London");
    myGraph.insertEdge("SanFrancisco", "London");
    myGraph.insertEdge("SanFrancisco", "Rome");
    myGraph.insertEdge("London", "Paris");
        
    myGraph.printConnections("NewYork");
    cout << endl;
    myGraph.printConnections("SanFrancisco");
    cout << endl;
    myGraph.printConnections("London");
    cout << endl;
    myGraph.printConnections("Berlin");
    cout << endl;
    myGraph.printConnections("Rome");
    cout << endl;
    myGraph.printConnections("Paris");
    cout << endl;
    myGraph.printConnections("Boston");
    cout << endl;
    myGraph.printConnections("Madrid");
    cout << endl;
    
    myGraph.graphSearch("NewYork");




    GRAPH<int> myGraph2;
    
    myGraph2.insertNode(1);
    myGraph2.insertNode(2);
    myGraph2.insertNode(3);
    myGraph2.insertNode(4);
    myGraph2.insertNode(5);
    myGraph2.insertNode(6);
    myGraph2.insertNode(7);
    
    myGraph2.insertEdge(1, 2);
    myGraph2.insertEdge(1, 3);
    myGraph2.insertEdge(1, 7);
    myGraph2.insertEdge(2, 3);
    myGraph2.insertEdge(2, 4);
    myGraph2.insertEdge(3, 5);
    myGraph2.insertEdge(4, 3);
    myGraph2.insertEdge(5, 4);
    myGraph2.insertEdge(5, 6);
    myGraph2.insertEdge(6, 4);
    
    myGraph2.graphSearch(1);

    return 0;
}
