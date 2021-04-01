#ifndef LSHCLUSTERING_H
#define LSHCLUSTERING_H

#include "Clustering.h"

#include <vector>

#include "../Lsh/Hash.h"

using namespace std;


class LshClustering : public Clustering {
public:
    LshClustering(ImageCollection * imagecol, int C, int L, int k, int W);
    virtual ~LshClustering();

    virtual AssignmentDefinition * assignment(ImageCollection * centers);
private:
    int Num_of_Buckets;
    long int M;
    long int m;
    int L;
    int k;
    int W;
    int dimensions;
    vector<Hash> g_hash;
    vector<vector <vector <int> > > all_h_values_of_all_g;
    vector <int> modulo_Exponents_of_m;
};

#endif /* LSHCLUSTERING_H */

