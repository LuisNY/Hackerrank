//
//  Attending Workshops

//
//

#include <stdio.h>
#include <iostream>
#include <vector>


using namespace std;
using std::cin;
using std::cout;
using std::endl;

struct Workshops {
    
    int start;
    int duration;
    int end;
};




class Available_Workshops {

public:
    int n;
    vector<Workshops> array;
    
    Available_Workshops(int n){
        this->n = n;
        this->array.resize(n);
    }
};

Available_Workshops* initialize (int start_time[], int duration[], int n) {
    
    static Available_Workshops myObj = Available_Workshops(n);
    
    for(int i=0; i<n; i++){
        myObj.array[i].start = start_time[i];
        myObj.array[i].duration = duration[i];
        myObj.array[i].end = start_time[i]+duration[i];
    }
    return &myObj;
}


int CalculateMaxWorkshops(Available_Workshops *ptr) {

    int count=1;
    int currEnd=0;
    
    std::sort(ptr->array.begin(), ptr->array.end(), [] (Workshops el1, Workshops el2) { return el1.end < el2.end; });
    
    currEnd=ptr->array[0].end;
    
    for (int i=1; i<ptr->n; i++){
        
        if (currEnd<=ptr->array[i].start){
            count++;
            currEnd = ptr->array[i].end;
        }
    }

    return count;
}



int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];
    
    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }
    
    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    
    
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
