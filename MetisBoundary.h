#ifndef MESHBOUNDARY_H_
#define MESHBOUNDARY_H_
#include <string>
#include <vector>

using namespace std;

enum BoundaryType {
    WALL = 0,
    FAR_FIELD = 1,
    CONNECT = 2
};

class MetisBoundary
{

  static MetisBoundary ComputeGlobalBoundaries(const string boundaryName, int *nElements, const vector<vector<int>> &globalNodes);
  static MetisBoundary ComputeConnectBoundaries(const vector<vector<int>> &globalNodes);
  
  static BoundaryType FindBoundaryTypeFromTagStr(string tag_str);

  public:
    MetisBoundary(int nElements, int* elementType, int* elementNbrNodes, int **boundaryElements);
    ~MetisBoundary();
    //void Init(int nBlock, int nElements, int* nNodes);

  public:
    vector<vector<int>> localNodes;
    int **boundaryElements_;

  private:
    string boundaryName_;
    
    //int *nNodes_;
    
    int nElements_;
    int *elementType_;
    int *elementNbrNodes_;

    //int blockID_;
    //int** boundaryType_;

    //vector<int> **boundariesConnectivity_;
};

#endif