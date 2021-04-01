
#include "ImageCollection.h"

#include <iostream>

using namespace std;

void  ImageCollection::printCompressed() {//ektypwsi syntetagmenwn se symptigmeni morfi px 3 [0] , diladi poses fores vrethike to tade noumero
    for (unsigned i =0;i<this->size();i++) {
        vector<int> & temp = (*this)[i];
        
        unsigned int s = temp.size();
        
        int counterzero = 0;
        int counter = 0;
        
        for (unsigned  i=0;i<s && counter < 15;i++) {
            if (temp[i] != 0) {
                if (counterzero != 0 && i != 0) {
                    cout << "["<<counterzero << "]  ";
                    cout << temp[i] << " ";                    
                    counterzero = 0;
                    counter++;
                }
            } else {
                counterzero++;
            }
        }
        cout << "... \n";
    }
}

void  ImageCollection::print() { //ektypwsi olwn twn syntetagmenwn twn simeiwn
    for (unsigned i =0;i<this->size();i++) {
        vector<int> & temp = (*this)[i];
        
        unsigned int s = temp.size();
        
        for (unsigned i=0;i<s;i++) {
            cout << temp[i] << " ";                    
        }
        cout << "\n";
    }
}