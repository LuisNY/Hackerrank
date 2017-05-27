#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::queue;
using std::set;




struct NODE {
    int data;
    vector<pair<NODE*, int>> edges;
};

struct comparator {
    bool operator()(pair<NODE*, int> i, pair<NODE*, int> j){
        return i.second > j.second;
    }
};



bool comp(pair < pair<int, int>, int > i, pair < pair<int, int>, int > j){
    return (i.second < j.second);
}


class GRAPH {
    
public:
    vector<NODE> nodes;
    vector< pair < pair<int, int>, int > > edges;
    
    GRAPH(){
        this->nodes.resize(1);
    }
    
    void insertNode(int node){
        NODE newNode;
        newNode.data =  node;
        this->nodes.push_back(newNode);
    }
    
    void insertEdge(NODE* node1, NODE* node2, int w){
        
        if(node1==NULL || node2==NULL)
            return;
        
        node1->edges.push_back(make_pair(node2, w));
        
        pair<int, int> nodesPair = make_pair(node1->data, node2->data);
        pair < pair<int, int>, int > newEdge = make_pair(nodesPair, w);
        this->edges.push_back(newEdge);
    }
    
    
    
    
    void insertBidirectionalEdge(NODE* node1, NODE* node2, int w){
        
        if(node1==NULL || node2==NULL)
            return;
        
        node1->edges.push_back(make_pair(node2, w));
        node2->edges.push_back(make_pair(node1, w));
        
        pair<int, int> nodesPair = make_pair(node1->data, node2->data);
        pair < pair<int, int>, int > newEdge = make_pair(nodesPair, w);
        this->edges.push_back(newEdge);
    }
    
    
    
    void printConnections(){
        
        
        for(int i=1; i<nodes.size(); i++){
            cout << "\nValue of this node " << nodes[i].data << endl;
            for(vector<pair<NODE*, int>>::iterator it=nodes[i].edges.begin(); it!=nodes[i].edges.end(); it++){
                cout << "Connected to " << it->first->data << " by edge of weight " << it->second << endl;
            }
        }
        
    }
    
    /***************************************************************************/
    
    //Breadth-frist-search algorithm. Does not take into account the weight of the edges.
    //Computes the minimum distance of all edges from a given node in terms of number of edges.
    void BFS(NODE *node){
        
        if(node==NULL)
            return;
        
        set<int> mySet;//set needed to keep track of nodes already visited
        
        queue<pair<NODE*, int>> myQueue;//we save the pointer to the node and the distance from the first node in terms of number of edges
        
        myQueue.push(make_pair(node,0));//first node has distance 0 from itself
        
        while(!myQueue.empty()){
            
            pair<NODE*, int> currNode = myQueue.front();
            myQueue.pop();
            
            if(mySet.find(currNode.first->data)!=mySet.end()){
                continue;
            }
            
            cout<< "Visiting node " << currNode.first->data << ";  dist from origin " << currNode.second << endl;
            
            mySet.insert(currNode.first->data);
            for(vector<pair<NODE*, int>>::iterator it=currNode.first->edges.begin(); it!=currNode.first->edges.end(); it++){
                myQueue.push(make_pair(it->first, currNode.second+1));
            }
        }
    }
    
    /***************************************************************************/
    
    //Only positive edges - finds the shortest path to all nodes starting from a given node
    void Dijkstra(NODE *node){
        
        set<int> mySet;
        priority_queue<pair<NODE*, int>, std::vector<pair<NODE*, int>>, comparator> myQueue;
        myQueue.push(make_pair(node,0));
        
        while(!myQueue.empty()){
            
            pair<NODE*, int> currNode = myQueue.top();
            myQueue.pop();
            
            if(mySet.find(currNode.first->data)!=mySet.end()){
                continue;
            }
            
            cout<< "Visiting node " << currNode.first->data << ";  dist from origin " << currNode.second << endl;
            mySet.insert(currNode.first->data);
            
            for(vector<pair<NODE*, int>>::iterator it=currNode.first->edges.begin(); it!=currNode.first->edges.end(); it++){
                myQueue.push(make_pair(it->first, currNode.second+it->second));
            }
        }
    }
    
    /***************************************************************************/
    
    //Negative edges are permitted - negative cycles detection
    void BellmanFord(NODE *node){
        
        int N = (int)nodes.size();
        vector<pair<int, int>> dist(N);
        
        for(int i=1; i<N; i++){
            dist[i].first = nodes[i].data;
            dist[i].second = INT_MAX;
        }
        dist[node->data].second = 0;
        
        for(int i=1; i<=N; i++){
            bool flag=false;
            for(int i=0; i<(int)edges.size(); i++){
                
                if(dist[edges[i].first.first].second!= INT_MAX && dist[edges[i].first.first].second + edges[i].second < dist[edges[i].first.second].second){
                    dist[edges[i].first.second].second = dist[edges[i].first.first].second + edges[i].second;
                    flag=true;
                }
            }
            if(!flag)
                break;
        }
        
        for(int i=0; i<(int)edges.size(); i++){
            if(dist[edges[i].first.first].second!= INT_MAX && dist[edges[i].first.first].second + edges[i].second < dist[edges[i].first.second].second){
                cout << "Negative cycle detected" << endl;
                return;
            }
        }
        
        cout << "Distance from " << node->data << " to all nodes:" << endl;
        for(int i=1; i<N; i++){
            if(dist[i].second==INT_MAX){
                cout << "Node " << dist[i].first << " is not reachable" << endl;
                continue;
            }
            cout << "Node " << dist[i].first << "   distance " << dist[i].second << endl;
        }
    }
    
    /***************************************************************************/
    
    void makeSets(vector<int>& mySets){
        for(int i=1; i<(int)mySets.size(); i++)
            mySets[i]=i;
    }
    
    int findRoot(const vector<int>& mySets, int node){
        while(mySets[node] != node)
            node = mySets[node];
        return node;
    }
    
    void connectSets(vector<int>& mySets, int node1, int node2){
        mySets[node1] = node2;
    }
    
    
    //Finds the minimum spanning tree in a graph - all edges are considered undirected
    void Kruskal(){
        
        int sum=0;
        int N = (int)nodes.size();
        vector<int> mySets(N,1);
        
        makeSets(mySets);
        
        vector< pair < pair<int, int>, int > > myEdges(edges.size());
        for(int i=0; i<myEdges.size(); i++){
            myEdges[i] = edges[i];
        }
        
        std::sort(myEdges.begin(), myEdges.end(), comp);
        
        
        for(int i=0; i<myEdges.size(); i++){
            
            int root1 = findRoot(mySets, myEdges[i].first.first);
            int root2 = findRoot(mySets, myEdges[i].first.second);
            if(root1 != root2){
                sum+=myEdges[i].second;
                connectSets(mySets, root1, root2);
            }
        }
        cout << "Minimum Spanning Tree with Kruskal's Algorithm: " << sum << endl;
    }
    
    /***************************************************************************/
    
    
    
    bool visitedAll(bool visitedArray[], int N){
        for(int i=1; i<N; i++){
            if(visitedArray[i]==false)
                return false;
        }
        return true;
    }
    
    
    //Find minumum spanning tree (you are given an initial node) - all edges are considered undirected
    void Prim(NODE *node){
        
        int sum=0;
        int N=(int)nodes.size();
        cout << "N " << N << endl;
        set<int> mySet;
        bool visitedArray[N];
        for (int i = 0; i<N; i++)
            visitedArray[i] = false;
        
        priority_queue<pair<NODE*,int>, std::vector<pair<NODE*, int>>, comparator> myQueue;
        
        int currentNode=node->data;
        int currentEdge=0;
        cout << N << endl;
        
        while(!visitedAll(visitedArray, N)){
            
            if(!visitedArray[currentNode]){
                
                sum += currentEdge;
            
                visitedArray[currentNode] = true;
                
                for(int j=0; j<nodes[currentNode].edges.size(); j++){
                    pair<NODE*,int> myPair = make_pair(nodes[currentNode].edges[j].first, nodes[currentNode].edges[j].second);
                    myQueue.push(myPair);
                }
            }
            
            pair<NODE*,int> topNode = myQueue.top();
            myQueue.pop();
            currentNode = topNode.first->data;
            currentEdge = topNode.second;
        }
        
        cout << "Minimum spanning tree with Prim's Algorithm: " << sum << endl;
    }
    
};


int main() {
    
    
    GRAPH myGraph;
    myGraph.insertNode(1);
    myGraph.insertNode(2);
    myGraph.insertNode(3);
    myGraph.insertNode(4);
    myGraph.insertNode(5);
    myGraph.insertNode(6);
    myGraph.insertNode(7);
    myGraph.insertNode(8);
    
    myGraph.insertEdge(&myGraph.nodes[1], &myGraph.nodes[2], 3);
    myGraph.insertEdge(&myGraph.nodes[1], &myGraph.nodes[5], 5);
    myGraph.insertEdge(&myGraph.nodes[2], &myGraph.nodes[3], 7);
    myGraph.insertEdge(&myGraph.nodes[2], &myGraph.nodes[8], 2);
    myGraph.insertEdge(&myGraph.nodes[3], &myGraph.nodes[6], 8);
    myGraph.insertEdge(&myGraph.nodes[4], &myGraph.nodes[3], 2);
    myGraph.insertEdge(&myGraph.nodes[5], &myGraph.nodes[8], 1);
    myGraph.insertEdge(&myGraph.nodes[6], &myGraph.nodes[4], 4);
    myGraph.insertEdge(&myGraph.nodes[7], &myGraph.nodes[6], 5);
    myGraph.insertEdge(&myGraph.nodes[8], &myGraph.nodes[2], 9);
    myGraph.insertEdge(&myGraph.nodes[8], &myGraph.nodes[7], 1);
    
    
    myGraph.printConnections();
    

    cout << endl;
    myGraph.BFS(&myGraph.nodes[1]);
    cout << endl;
    myGraph.Dijkstra(&myGraph.nodes[1]);
    
    
    cout << endl;
    
    
    
    GRAPH myGraph2;
    
    myGraph2.insertNode(1);
    myGraph2.insertNode(2);
    myGraph2.insertNode(3);
    myGraph2.insertNode(4);
    myGraph2.insertNode(5);
    myGraph2.insertNode(6);
    myGraph2.insertNode(7);
    myGraph2.insertNode(8);
    
    myGraph2.insertEdge(&myGraph2.nodes[1], &myGraph2.nodes[2], 5);
    myGraph2.insertEdge(&myGraph2.nodes[1], &myGraph2.nodes[5], -3);
    myGraph2.insertEdge(&myGraph2.nodes[2], &myGraph2.nodes[3], -1);
    myGraph2.insertEdge(&myGraph2.nodes[2], &myGraph2.nodes[8], -2);
    myGraph2.insertEdge(&myGraph2.nodes[3], &myGraph2.nodes[6], 5);
    myGraph2.insertEdge(&myGraph2.nodes[4], &myGraph2.nodes[3], 2);
    myGraph2.insertEdge(&myGraph2.nodes[5], &myGraph2.nodes[8], 2);
    myGraph2.insertEdge(&myGraph2.nodes[6], &myGraph2.nodes[4], -2);
    myGraph2.insertEdge(&myGraph2.nodes[7], &myGraph2.nodes[6], 6);
    myGraph2.insertEdge(&myGraph2.nodes[8], &myGraph2.nodes[2], 2);
    myGraph2.insertEdge(&myGraph2.nodes[8], &myGraph2.nodes[7], -1);
    
    myGraph2.printConnections();
    
    myGraph2.BellmanFord(&myGraph.nodes[2]);
    cout << endl;
    myGraph2.BellmanFord(&myGraph.nodes[1]);
    
    
    GRAPH myGraph3;
    
    myGraph3.insertNode(1);
    myGraph3.insertNode(2);
    myGraph3.insertNode(3);
    myGraph3.insertNode(4);
    myGraph3.insertNode(5);
    myGraph3.insertNode(6);
    myGraph3.insertNode(7);
    myGraph3.insertNode(8);
    
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[1], &myGraph3.nodes[2], 3);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[1], &myGraph3.nodes[5], 5);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[2], &myGraph3.nodes[3], 7);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[2], &myGraph3.nodes[8], 2);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[3], &myGraph3.nodes[6], 8);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[4], &myGraph3.nodes[3], 2);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[5], &myGraph3.nodes[8], 1);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[6], &myGraph3.nodes[4], 4);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[7], &myGraph3.nodes[6], 5);
    myGraph3.insertBidirectionalEdge(&myGraph3.nodes[8], &myGraph3.nodes[7], 8);
    
    myGraph3.printConnections();
    
    myGraph3.Prim(&myGraph.nodes[4]);
    cout << endl;
    myGraph3.Kruskal();
    
    
    return 0;
}
