#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;
using std::list;
using std::map;


int main() {
    
    int AN, BN;
    vector<int> A, B;
    vector<int> outV;
    map<int, int> myMapA, myMapB;
    cin >> AN;
    int temp;
    for(int i=0; i<AN; i++){
        cin >> temp;
        A.push_back(temp);
    }
    
    cin >> BN;
    for(int i=0; i<BN; i++){
        cin >> temp;
        B.push_back(temp);
    }
    
    
    for(int i=0; i<BN; i++){
        
        if(myMapB.find(B[i]) != myMapB.end()){
            int count = myMapB.find(B[i])->second;
            myMapB.erase(B[i]);
            myMapB.insert(make_pair(B[i], count+1));
        }
        else {
            myMapB.insert(make_pair(B[i], 1));
        }
    }
    
    
    for(int i=0; i<AN; i++){
        if(myMapA.find(A[i]) != myMapA.end()){
            int count = myMapA.find(A[i])->second;
            myMapA.erase(A[i]);
            myMapA.insert(make_pair(A[i], count+1));
        }
        else {
            myMapA.insert(make_pair(A[i], 1));
        }
    }
    
    for(map<int, int>::iterator it=myMapB.begin(); it!=myMapB.end(); it++){
        
        if(myMapA.find(it->first)==myMapA.end()){
            outV.push_back(it->first);
        }
        else{
            map<int, int>::iterator it2 = myMapA.find(it->first);
            
            if(it2->second < it->second){
                outV.push_back(it->first);
            }
            
        }
    }
    
    for(int i=0; i<outV.size(); i++)
        cout << outV[i] << " " ;
    
    return 0;
}
