#ifndef MESHREADER_H_
#define MESHREADER_H_
#include <vector>
#include <string>

class MetisMesh
{
private:
    int* nElements_;
    int* nNodes_;
    int* elementType_;
    int* nTotalNode_;
    int nBlock_;
    

    double** x_;
    double** y_;
    double** z_;
    

    std::vector<int>** connectivity_;

public:
    MetisMesh();
    ~MetisMesh();

public:
    void Init(int nBlock, int* nElements, int* nNodes);
    void ReadSingleBlockMesh(std::string fileName);
    void WriteMesh(std::string fileName);
    MetisMesh* Partition(int nPart);
    void SetConnectivity(std::vector<int>** connectivity_);
    int NumberOfNodes(int elementType);


};

#endif
