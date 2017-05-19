#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_multimap;
using std::pair;
using std::unordered_map;
using std::queue;
using std::set;


class airport{
    
    string ID;
    string city;
    
public:
    
    vector<airport> connections;
    
    airport(string ID, string city){
        this->ID = ID;
        this->city = city;
    }
    
    string getID(){
        return this->ID;
    }
    
    string getCity(){
        return this->city;
    }
};



class airTrafficMap {
    
    unordered_map<string, airport> myTable;
    
public:
    
    void addAirport(string ID, string city){
        
        if (myTable.find(ID) == myTable.end()){
            airport* newAirport = new airport(ID, city);
            myTable.insert(make_pair(ID, *newAirport));
            cout << ID << " airport was added succesfully." << endl;
        }
        else {
            cout << ID << " airport is already present in the database." << endl;
        }
    }
    
    void printListOfAirports(){
        
        unordered_map<string, airport>::iterator it;
        
        for(it=myTable.begin(); it!=myTable.end(); it++){
            cout << it->first << " " << it->second.getCity() << endl;
        }
        cout << endl;
    }
    
    void addConnection(string departure, string destination){
        
        unordered_map<string, airport>::iterator depa = myTable.find(departure);
        unordered_map<string, airport>::iterator dest = myTable.find(destination);
        bool found=false;
        
        cout << endl;
        cout << "Adding connection between " << depa->second.getCity() << " and " << dest->second.getCity() << endl;
        
        for (int i = 0; i < (int)depa->second.connections.size(); i++) {

            if(depa->second.connections[i].getID() == destination){
                found=true;
                break;
            }
        }
        if(!found){
            if(depa != myTable.end() && dest != myTable.end()){
                depa->second.connections.push_back(dest->second);
                dest->second.connections.push_back(depa->second);
                cout << "Connection added succesfully" << endl;
            }
            else {
                cout << "Departure or destination not present in the database." << endl;
            }
        }
        else {
            cout << "Connection already present" << endl;
        }
    }
    
    
    void printListConnections(string airportID){
        
        unordered_map<string, airport>::iterator it = myTable.find(airportID);
        if(it != myTable.end()){
            cout << it->first << " airport of " << it->second.getCity() << " is connected to: " << endl;
            
            if(!it->second.connections.empty()){
                for(vector<airport>::iterator it2 = it->second.connections.begin(); it2 != it->second.connections.end(); it2++){
                    cout << it2->getID() << " airport of " << it2->getCity() << endl;
                }
            }
            else {
                cout << "No connections found." << endl;
            }
        }
        else {
            cout << "Airport not present in the database." << endl;
        }
        cout << endl;
    }
    
    
    void checkConnection(string departure, string destination){
        
        unordered_map<string, airport>::iterator depa = myTable.find(departure);
        unordered_map<string, airport>::iterator dest = myTable.find(destination);
        
        if(depa!=myTable.end() && dest!=myTable.end()){
            if (verifyConnection(depa->second, dest->second))
                cout << "There is a connection between " << depa->first << " and " << dest->first << endl;
            else
                cout << "There is no connection between " << depa->first << " and " << dest->first << endl;
        }
        else {
            cout << "Departure or destination not present in the database." << endl;
        }
        return;
    }
    
    bool verifyConnection(airport depa, airport dest){
        
        queue<airport> myQueue;
        set<string> mySet;
        
        myQueue.push(depa);
        
        while(!myQueue.empty()){
            
            airport current = myQueue.front();
            myQueue.pop();
            
            if(current.getID() == dest.getID())
                return true;
            
            if(mySet.find(current.getID()) != mySet.end()){
                continue;
            }
            
            mySet.insert(current.getID());
            
            for(vector<airport>::iterator it = current.connections.begin(); it!=current.connections.end(); it++){
                myQueue.push(*it);
            }
        }
        
        return false;
    }

};






int main(){
    
    airTrafficMap *airMap = new airTrafficMap;
    
    
    
    airMap->addAirport("JFK", "New York");
    airMap->addAirport("SFO", "San Francisco");
    airMap->addAirport("CHI", "Chicago");
    airMap->addAirport("LAX", "Los Angeles");
    airMap->addAirport("LAX", "Los Angeles");
    airMap->addAirport("FMO", "Roma");
    cout << endl;
    
    airMap->printListOfAirports();
    
    airMap->addConnection("SFO", "CHI");
    airMap->addConnection("SFO", "JFK");
    airMap->addConnection("CHI", "SFO");
    airMap->addConnection("JFK", "CHI");
    airMap->addConnection("CHI", "JFK");
    airMap->addConnection("LAX", "JFK");
    
    cout << endl;
    
    airMap->printListConnections("SFO");
    airMap->printListConnections("CHI");
    airMap->printListConnections("JFK");
    airMap->printListConnections("LAX");
    
    airMap->checkConnection("JFK", "SFO");
    airMap->checkConnection("LAX", "SFO");
    airMap->checkConnection("LAX", "FMO");
    
    return 0;
}
