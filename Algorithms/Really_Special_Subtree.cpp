#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;
using std::vector;
using std::unordered_set;
using std::cout;
using std::endl;
using std::cin;

bool  compare(pair < int, pair<int, int> > i, pair < int, pair<int, int> > j){
    return (i.first < j.first);
}

bool compare2(pair < int, pair<int, int> > i, pair < int, pair<int, int> > j){
    
    return ((i.second.first + i.second.second) < (j.second.first + j.second.second));
}


int findRoot(vector<int> mySets, int node){
    
    while(mySets[node]!=node){
        node = mySets[node];
    }
    return node;
}

void Kruskal(int nodes, vector< pair < int, pair<int, int> > > myVect){
    
    vector<int> mySets(nodes+1);
    int weightSum=0;
    for(int i=0; i<nodes; i++){
        mySets[i] = i;
    }
    
    for(vector< pair < int, pair<int, int> > >::iterator it = myVect.begin(); it!=myVect.end(); it++){
        
        int rootSet1 = findRoot(mySets, it->second.first);
        int rootSet2 = findRoot(mySets, it->second.second);
        
        if(rootSet1!=rootSet2){
            weightSum += it->first;
            mySets[rootSet1] = mySets[rootSet2];
        }
    }
    
    cout << weightSum << endl;
}


void minimumSpanningTree(int nodes, vector< pair < int, pair<int, int> > > myVect){
    
    std::sort(myVect.begin(), myVect.end(), compare);
    
    int indexStart=0;
    int indexEnd=0;
    
    for(vector< pair < int, pair<int, int> > >::iterator it = myVect.begin(); it!=myVect.end(); it++){
        
        while(it->first == (it+1)->first){
            indexEnd++;
            it++;
        }
        
        if(indexStart!=indexEnd){
            std::sort(myVect.begin()+indexStart, myVect.begin()+indexEnd+1, compare2);
        }
        
        indexStart=indexEnd+1;
        indexEnd=indexStart;
    }
    
    Kruskal(nodes, myVect);
}



int main() {
    
    int N, E;
    cin >> N >> E;
    vector<pair<int, pair<int, int>>> myVect;
    int i=0;
    while(i<E){
        
        int n1, n2;
        int w;
        
        cin >> n1 >> n2 >> w;
        
        pair<int, int> myPair;
        if (n1<=n2)
            myPair = make_pair(n1, n2);
        else
            myPair = make_pair(n2, n1);
        
        pair<int, pair<int, int>> complexPair(make_pair(w, myPair));
        myVect.push_back(complexPair);
        
        i++;
    }
    
    minimumSpanningTree(N, myVect);
    
    return 0;
}
