//
//  Test.cpp
//  Test
//
//  Created by Luigi Pepe on 4/4/17.
//  Copyright © 2017 Luigi Pepe. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <string>
#include <list>
#include <sstream>
#include <deque>

using namespace std;
using std::unordered_map;
using std::string;
using std::list;
using std::vector;
using std::make_pair;
using std::deque;

struct myStruct{
    
    string tag;
    vector< pair<string, string> > attributes;
    vector<myStruct> children;
    myStruct *parent;
};


vector<myStruct> processText(int N){
    
    vector<myStruct> myVect;
    myStruct *currentParent = nullptr;
    deque<string> myDeque;
    string line;
    
    for (int i=0; i<N; i++){  //acquire the HRML text in N consecutive lines.
        
        getline(cin, line);
        
        if (line.find("</") == -1) { //it is an opening tag
            
            char ch;
            string tagName;
            string attribute;
            string attrVal;
            stringstream myStream;
            pair<string, string> myPair;
            myStruct newElem;
            myStream.str(line);
            
            myStream >> ch >> tagName; //the first character is '<', then import tag name
            
            if (tagName.back() == '>'){
                tagName.pop_back();
            }
            
            newElem.tag = tagName;
            
            string frontQueue;
            if(!myDeque.empty()){
                
                frontQueue = myDeque.front();
            }
            else frontQueue = "";
            
            myDeque.push_front(tagName);
            
            while(!myStream.eof()){ //until the end of the stream is not reached
                
                attrVal = "";
                myStream >> attribute;
                
                if (attribute==">") // if '>' is reached then break
                    break;
                
                do{
                    myStream >> ch;
                }while(ch != '"');
                
                do{
                    myStream >> ch;
                    attrVal.push_back(ch);
                }while(ch != '"');
                
                attrVal.pop_back(); // pop the '"' character
                newElem.attributes.push_back(make_pair(attribute, attrVal));
            }
            
            if(tagName == myDeque.back()){ //if it's a new tag (not nested) create a new object and push it into the main vector
                newElem.parent = nullptr;
                myVect.push_back(newElem);
                currentParent = &myVect.back();
            }
            
            else { // if the current tag is nested into other tags, create a new opbject and push it into the children vector of the parent tag
                for(int index=0; index<currentParent->children.size(); index++){
                    if(currentParent->children[index].tag == frontQueue){
                        currentParent = &currentParent->children[index];
                    }
                }
                newElem.parent = currentParent;
                currentParent->children.push_back(newElem);
            }
        }
        
        else { //it is a closing tag
            
            char ch1, ch2;
            stringstream myStream;
            myStream.str(line);
            myStream >> ch1 >> ch2;
            string tagClose;
            myStream >> tagClose;
            tagClose.pop_back();
            myDeque.pop_front();
        }
    }
    
    
    return myVect;
}


void processQueries(int Q, vector<myStruct> myVect){
    
    for (int i=0; i<Q; i++){   // process the Q queries and print out the results.
        string line;
        bool flag=false;
        bool found=false;
        
        getline(cin, line);
        stringstream myStream;
        myStream.str(line);
        
        myStruct currentStruct = myVect[0];
        vector<myStruct> currentVect = myVect;
        
        if (line.find('~') == -1){
            cout << "Not Found!" << endl;
            continue;
        }
        
        while(!myStream.eof()){
            
            string name="";
            char ch;
            
            myStream >> ch;
            while(ch!='.' && ch!='~' && !myStream.eof()){
                
                name.push_back(ch);
                myStream >> ch;
            }
            
            if(!myStream.eof()){
                
                for(int index=0; index<currentVect.size(); index++){
                    if(currentVect[index].tag == name){
                        currentStruct = currentVect[index];
                        flag = true;
                    }
                }
                
                if(flag){
                    
                    if (ch!='~'){
                        
                        if(!currentStruct.children.empty()){
                            currentVect = currentStruct.children;
                        }
                        else {
                            cout << "Not Found!" << endl;
                            break;
                        }
                    }
                    
                    else {
                        
                        string attribute = "";
                        do{
                            myStream >> ch;
                            attribute.push_back(ch);
                            
                        }while(!myStream.eof());
                        
                        attribute.pop_back();
                        
                        for(int i=0; i<currentStruct.attributes.size(); i++){
                            
                            if(attribute == currentStruct.attributes[i].first){
                                cout << currentStruct.attributes[i].second << endl;
                                found = true;
                            }
                        }
                        
                        if (!found){
                            cout << "Not Found!" << endl;
                        }
                        found=false;
                    }
                    flag=false;
                }
                
                else {
                    cout << "Not Found!" << endl;
                    break;
                }
            }
        }
    }
    
    return;
}



int main() {
    
    int N;
    int Q;
    
    vector<myStruct> myVect;
    
    cin >> N;
    cin >> Q;
    getchar();
    
    myVect = processText(N);
    processQueries(Q, myVect);
    
    return 0;
}






