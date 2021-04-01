#ifndef CUBE_STRUCT_H
#define CUBE_STRUCT_H
#include <vector>

using namespace std;

class Corner{
	int Num_of_Corner;
    vector <int> pictures;
public:
	Corner(int Num_of_Corner);
	void Display();
    void InsertItem(int num_of_picture);
	void Loadhash(vector <int>* pictures);
};


#endif
