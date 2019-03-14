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

  public:
    MetisBoundary();
    ~MetisBoundary();

  private:
    string boundaryName_;
    int *nElements_;
    int *nNodes_;
    int *elementType_;
    int blockID_;
    BoundaryType boundaryType_; 

    vector<int> **connectivity_;
};

#endif