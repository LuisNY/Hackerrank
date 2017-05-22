#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;
using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::pair;

bool myfunction (pair<long long,int> i,pair<long long,int> j) {
    return (i.first > j.first);
}


int main() {
    
    int N;
    cin >> N;

    int min_diff = INT_MAX;
    vector<pair<long long, int>> myVect(N);
    long long temp;
    for(int i=0; i<N; i++){
        
        cin >> temp;
        pair<long long, int> myPair = make_pair(temp, i);
        myVect[i] = myPair;
    }
    
    std::sort(myVect.begin(), myVect.end(), myfunction);
    
    
    for(int i=0; i<N-1; i++){
        
        if(min_diff>(myVect[i].first-myVect[i+1].first) && (myVect[i].second < myVect[i+1].second)){
            min_diff=(myVect[i].first-myVect[i+1].first);
        }
    }
    
    cout << min_diff << endl;
    
    
    
    return 0;
}
