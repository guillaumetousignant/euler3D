#ifndef MESHREADER_H_
#define MESHREADER_H_
#include <vector>
#include <string>

class MetisMesh
{
private:
    int* nElements_;
    int* nNodes_;
    int** elementNbrNodes_;
    int** elementType_;
    int** local2GlobalElements_;
    int nTotalNode_;
    int nBlock_;
    
    double** x_;
    double** y_;
    double** z_;
    
    std::vector<int>** connectivity_;
    // std::vector<int>* global2LocalElements_;
    // std::vector<int>** connectivity_boundary;

public:
    MetisMesh();
    ~MetisMesh();

    static int nDimensions_;

public:
    void Init(int nBlock, int* nElements, int* nNodes);
    void ReadSingleBlockMesh(std::string fileName);
    void WriteMesh(std::string fileName);
    MetisMesh* Partition(int nPart);
    void SetConnectivity(std::vector<int>** connectivity_);
    int NumberOfNodes(int elementType);


};

#endif
