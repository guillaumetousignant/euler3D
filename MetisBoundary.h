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
    MetisBoundary(int nBoundaries);
    //MetisBoundary(int nElements, int* elementType, int* elementNbrNodes, int **boundaryElements);
    ~MetisBoundary();
    void InitBoundary(int* nElements, int nBoundaries);

    string SetBoundaryName(string boundaryName);
    
    //vector<vector<int>> localNodes;
    

    //int** boundariesConnectivity_;

  
    int nBoundaries_;
    string* boundaryNames_;
    int** boundaryElements_;
    std::vector<int>** boundaryConnectivity_;
    //int *nNodes_;
    
    int* boundaryNelements_;
    int** boundaryElementType_;
    int** boundaryElementNbrNodes_;
    
    //int blockID_;
    //int** boundaryType_;
    
    
};

#endif