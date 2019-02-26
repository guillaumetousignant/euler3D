#ifndef MESHREADER_H_
#define MESHREADER_H_
#include <vector>
#include <string>

class Mesh
{
private:
    int* nElements_;
    int* nNodes_;
    int nBlock_;

    double** x_;
    double** y_;
    double** z_;

    std::vector<int>** connectivity_;

public:
    Mesh();
    ~Mesh();

public:
    void Init(int nBlock, int* nElements, int* nNodes);
    void ReadSingleBlockMesh(std::string fileName);
    void WriteMesh(std::string fileName);
    Mesh* Partition(int nPart);
    void SetConnectivity(std::vector<int>** connectivity_);

};

#endif
