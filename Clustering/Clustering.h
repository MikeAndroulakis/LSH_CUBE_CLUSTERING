#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <string>
#include <set>
#include <unordered_map>

#include "ImageCollection.h"

using namespace std;


class AssignmentDefinition {
public:
    ImageCollection * centers;
    unordered_map<int, int> point_to_nearest_cluster;
    unordered_map<int, int> point_to_second_best;
    unordered_map<int, set<int> > cluster_to_points; 
    
    AssignmentDefinition() {
    }
    
    ~AssignmentDefinition() {
        
    }
    
    void print();
};

class Clustering {
public:
    ImageCollection * collection;
    int C;
   
    Clustering(ImageCollection * collection, int C);

    virtual ~Clustering() {
    };

    // ----------------- clustering algorithm --------------------- //

    ImageCollection * initialize(); // Kmeans++

    virtual AssignmentDefinition * assignment(ImageCollection * centers) = 0;

    ImageCollection * update(ImageCollection * centers, AssignmentDefinition * assignments); // Kmedian

    
    bool shouldStop(ImageCollection * oldcenters,ImageCollection * newcenters);

    AssignmentDefinition * execute(int limit = -1);
    
    void printResults(AssignmentDefinition * def);
    
    vector<float> silhouette(AssignmentDefinition * def);
    
    float avg_distance_from_objects_of_cluster(AssignmentDefinition * ,int,int);
};



#endif /* CLUSTERING_H */

