#ifndef HYPERCUBECLUSTERING_H
#define HYPERCUBECLUSTERING_H

#include "../Cube/Cube.h"
#include "../Cube/h_Function_Cube.h"
#include "../Cube/Cube_Struct.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "../Functions_for_both_algorithms/Modulos.h"


#include "Clustering.h"

class HypercubeClustering : public Clustering {
public:
    HypercubeClustering(ImageCollection * imagecol, int C,int k, int W, int M, int probes, int dimensions);
    virtual ~HypercubeClustering();

    virtual AssignmentDefinition * assignment(ImageCollection * centers);
private:
    int Num_of_Buckets; // oxi- diladi den to xreiazomai, mporw na to ypologisw apo allou alla to krataw gia synoxi
    int k; // nai
    int W; // nai
    int MM; // nai
    int max_integer_bucket_num; // oxi (d)
    int probes; // nai
    long int M; // oxi (k)
    long int m; // oxi (k)
    int dimensions;
    
    vector <vector <int> > h_function;
    vector < unordered_map <int, int> > values_of_f;
    vector <int> modulo_Exponents_of_m;
    vector <Corner> cube;
};

#endif /* HYPERCUBECLUSTERING_H */

