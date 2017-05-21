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

using namespace std;


int main(){
    
    int n, k;
    vector<int> x;
    
    cin >> n >> k;
    x.resize(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    
    std::sort(x.begin(), x.end());
   
    int count=0;
    
    int index_left = 0;
    int index_right=0;
    int left_end = x[index_left];
    int right_end = x[index_right];
    
    while(right_end<=x[n-1]){
        
        int center = x[index_left] + k;
        left_end = x[index_left];
        right_end = x[index_right];
        
        int i=index_left;
        while(i<n && x[i] < center){
            i++;
        }
        if(x[i]==center){
            count++;            
            left_end = x[i]-k;
            right_end = x[i]+k;
            
            int j = index_left;
            while(j<n && x[j]<=right_end)
                j++;
            
            index_left = j;
            index_right=index_left; 
        }
        else {
            i--;
            while(x[i] > center)
                i--;
            count++;
                        
            left_end = x[i]-k;
            right_end = x[i]+k;
            
            int j = index_left;
            while(j<n && x[j]<=right_end)
                j++;
            
            index_left = j;
            index_right=index_left;
        }  
    }
    
    std::cout << count << std::endl;
    
    return 0;
}
