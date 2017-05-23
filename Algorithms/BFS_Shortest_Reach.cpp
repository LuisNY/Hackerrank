#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
using std::vector;
using std::queue;
using std::set;


class NODE {
    
public:
    int ID;
    vector<NODE*> neighbors;
};

class GRAPH {
    
public:
    vector<NODE> nodes;
    vector<int> paths;
    
    GRAPH(int n){
        paths.resize(n);
        nodes.resize(n);
        for(int i=0; i<n; i++){
            nodes[i].ID = i+1;
            nodes[i].neighbors.resize(0);
            paths[i] = 0;
        }
    }
    
    void addEdge(int node1, int node2){
        
        NODE newNode1;
        newNode1.ID = node1;
        newNode1.neighbors.resize(0);
        
        NODE newNode2;
        newNode2.ID = node2;
        newNode2.neighbors.resize(0);
        
        nodes[node1-1].neighbors.push_back(&nodes[node2-1]);
        nodes[node2-1].neighbors.push_back(&nodes[node1-1]);
    }
    
    void findPaths(int s){
        
        set<int> mySet;
        queue<pair<NODE*, int>> myQueue;
        int len=0;
        myQueue.push(make_pair(&nodes[s-1], len));
        
        while(!myQueue.empty()){
            
            pair<NODE*, int> currentNode = myQueue.front();
            myQueue.pop();
            
            if(mySet.find(currentNode.first->ID) != mySet.end()){
                continue;
            }
            
            mySet.insert(currentNode.first->ID);
            paths[currentNode.first->ID-1] += currentNode.second;
            
            for(vector<NODE*>::iterator it = currentNode.first->neighbors.begin(); it!=currentNode.first->neighbors.end(); it++) {
                myQueue.push(make_pair(*it, currentNode.second+1));
            }
        }
        
        for(int i = 0; i < (int)paths.size(); i++){
            if (i!=(s-1)){
                if(paths[i]==0)
                    cout << -1 << " " ;
                else
                    cout << paths[i]*6 << " " ;
            }
        }
        cout << endl;
    }
};



int main() {
    
    int N;
    cin >> N;
    
    for(int i=0; i<N; i++){
        
        int n, m;
        cin >> n >> m;
        
        GRAPH myGraph(n);
        
        for(int j=0; j<m; j++){
            int node1, node2;
            cin >> node1 >> node2;
            myGraph.addEdge(node1, node2);
        }
        
        int s;
        cin >> s;
        myGraph.findPaths(s);
    }
    return 0;
}
