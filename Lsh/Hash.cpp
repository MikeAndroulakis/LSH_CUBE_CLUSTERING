#include "Hash.h"
#include <vector>
#include <list>

using namespace std;

Hash::Hash(int b) {
    this->buckets = b;
    table = new list<int>[buckets];
}

void Hash::InsertItem(int num_of_picture, long int value_of_g) {
    int index = hashFunction(value_of_g);
    //cout<<"INDEX="<<index<<endl;
    table[index].push_back(num_of_picture);
}

void Hash::Loadhash(vector <int>* pictures, int index) {
    for (auto x : table[index]) {
        (*pictures).push_back(x);
    }
}
