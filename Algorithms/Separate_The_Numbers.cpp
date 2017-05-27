#include <bits/stdc++.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;

int main() {
    
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        string s;
        cin >> s;
        
        bool flag = false;
        int len=1;
        
        long long saveFirst=0;
        while(len<=s.size()/2){
            
            flag=true;
            int i=0;
            while(i<s.size()-len){
                
                string sub1, sub2;
                
                sub1 = s.substr(i, len);
                
                long long x = std::stol(sub1);
                if(i==0)
                    saveFirst = x;
                int oldLen=len;
                int oldI=i;
                bool last=true;
                for(int k=0; k<sub1.size(); k++){
                    if((char)sub1[k]!=48+9){
                        last=false;
                        break;
                    }
                }
                
                if(last){
                    
                    sub2 = s.substr(i+len, len+1);
                    len++;
                    i--;
                }
                else sub2 = s.substr(i+len, len);
                
                long y = std::stol(sub2);
                
                if(y!=x+1 || (char)sub1[0]==48){
                    flag=false;
                    i=oldI;
                    len= oldLen;
                    break;
                }
                
                i+=len;
            }
            
            if(flag==true){
                break;
            }
            
            len++;
        }
        
        if(flag){
            printf("YES %lld\n", saveFirst);
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
