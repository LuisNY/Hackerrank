#include <iostream>
#include <deque>
#include <stdio.h>

using namespace std;
using std::deque;
using std::cout;
using std::endl;
using std::cin;
using std::ostream;

void printMax(int array[], int n, int sub_len){
    
    deque<int> myDeque(sub_len);
    int max=0;
    for (int i=0; i<sub_len; i++){
        myDeque[i] = array[i];
        if (myDeque[i] > max)
            max = myDeque[i];
    }
    
    cout << max << " ";
    
    for (int i=0; i<(n-sub_len); i++){
        
        myDeque.pop_front();
        myDeque.push_back(array[sub_len+i]);
        
        if(max == array[i]){
            max = 0;
            for(int j=i+1; j<i+sub_len; j++){
                if(max<array[j])
                    max = array[j];
            }
        }
        
        if(max < array[sub_len+i]){
            max=array[sub_len+i];
        }
        
        cout << max << " ";
    }
    
    return;
}


int main(){
    
    
    int Q;
    cin >> Q;
    
    for (unsigned i=0; i<Q; i++){
        
        int n, sub_len;
        
        cin >> n >> sub_len;
        
        int array[n];
        for(unsigned j=0; j<n; j++){
            cin >> array[j];
        }
        
        printMax(array, n, sub_len);
        cout << endl;
    }
    
    
    return 0;
}
