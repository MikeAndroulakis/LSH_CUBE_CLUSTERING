
#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H

#include <vector>

using namespace std;


class ImageCollection : public vector<vector<int>> {
public:
    int rows, columns;  
    void printCompressed();
    void print();
};

#endif /* IMAGECOLLECTION_H */

