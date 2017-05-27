#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::string;
using std::pair;

void checkAnagrams(string myStr){
    
    int N=(int)myStr.size();
    vector<string> myVect;
    int count=0;
    
    for(int len=1; len<N; len++){
        
        for(int i=0; i<=N-len; i++){
            
            string str;
            str = myStr.substr (i,len);
            //cout << "str1 " << str << endl;
            std::sort(str.begin(), str.end());
            myVect.push_back(str);
        }
    }
    
    for(int i=0; i<myVect.size(); i++){
        for(int j=0; j<myVect.size(); j++){
            if(i != j && myVect[i] == myVect[j]){
                count++;
            }
        }
    }
    cout << count/2 << endl;
}


int main() {

    int T;
    cin >> T;
    
    for(int i=0; i<T; i++){
        
        string myStr;
        
        cin >> myStr;
        
        checkAnagrams(myStr);
    }    
    
    return 0;
}
