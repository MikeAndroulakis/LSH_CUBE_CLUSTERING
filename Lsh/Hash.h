#ifndef HASH_H
#define HASH_H

#include <vector>
#include <list>


using namespace std;

class Hash{
    int buckets;
    list<int> *table;
public:
    Hash(int b);
    void InsertItem(int num_of_picture,long int value_of_g);
    int hashFunction(long int x){
        return x%buckets;
    }
	void Loadhash(vector <int>* pictures,int index);
};

#endif
