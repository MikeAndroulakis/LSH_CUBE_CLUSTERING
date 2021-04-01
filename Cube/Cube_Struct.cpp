#include "Cube_Struct.h"
#include <vector>
#include <iostream>

using namespace std;

Corner::Corner(int Num_of_Corner) {
    this->Num_of_Corner = Num_of_Corner;
}

void Corner::InsertItem(int num_of_picture) {
    pictures.push_back(num_of_picture);
}

void Corner::Display() {
    cout << this->Num_of_Corner;
}

void Corner::Loadhash(vector <int>* pics) {
    for (int i = 0; i < (int) pictures.size(); i++) {
        (*pics).push_back(pictures[i]);
    }

}

