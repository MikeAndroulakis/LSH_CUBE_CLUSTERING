#ifndef CLASSICCLUSTERING_H
#define CLASSICCLUSTERING_H

#include "Clustering.h"


class ClassicClustering : public Clustering {
public:
    ClassicClustering(ImageCollection * imagecol, int C);
    virtual ~ClassicClustering();
    
    virtual AssignmentDefinition * assignment(ImageCollection * centers);

};

#endif /* CLASSICCLUSTERING_H */

