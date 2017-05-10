#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::stack;


class editor{
    
    stack< pair<int, string> > operStack;    
    
public:
    
    string myStr;
    
    void oper1(const string& str){
        myStr.append(str);
        operStack.push(std::make_pair(1, str));
    }
    
    void oper2(int k){
        
        int N=(int)myStr.size()-1;
        string delStr;
        for(int i=N-(k-1); i<=N; i++){
            delStr.push_back(myStr[i]);
        }
        myStr.erase(N-(k-1), N+1);
        operStack.push(std::make_pair(2, delStr));
    }
    
    void oper3(int k){
        cout << myStr[k-1] << endl;
    }
    
    void oper4(){
        
        pair<int, string> topStack = operStack.top();
        
        operStack.pop();
        
        if(topStack.first == 1){
            int len = (int)topStack.second.size()-1;
            int N = (int)myStr.size()-1;
            myStr.erase(N-len, N+1);
        }
        
        else {
            myStr.append(topStack.second);
        }
    }
};
    
    
    
    
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    editor myEditor;
    int Q;
    cin >> Q;
    
    while(Q>0){
        
        int oper;
        
        cin >> oper;
        
        if(oper==1){
            string myStr;
            cin>>myStr;
            myEditor.oper1(myStr);
        }
        
        else if(oper==2){
            
            int k;
            cin>>k;
            myEditor.oper2(k);
        }
        
        else if(oper==3){
            int k;
            cin>>k;
            myEditor.oper3(k);
        }
        
        else {
            myEditor.oper4();
        }
        //cout << myEditor.myStr << endl;
        Q--;
    }
    
    return 0;
}
