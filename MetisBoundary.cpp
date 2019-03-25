#include "MetisBoundary.h"
#include <iostream>
#include <string>


MetisBoundary::MetisBoundary() 
: nBoundaries_(0), boundaryConnectivity_(nullptr), boundaryNelements_(nullptr), boundaryElementNbrNodes_(nullptr) {}
/* MetisBoundary::MetisBoundary(int nElements, int* elementType, int* elementNbrNodes, int **boundaryElements)
    : nElements_(nElements), elementType_(elementType),  
    elementNbrNodes_(elementNbrNodes),  boundaryElements_(boundaryElements) {}
          */

MetisBoundary::~MetisBoundary() {
    //if (nNodes_ != nullptr)
    //    delete[] nNodes_;
    //nNodes_ = nullptr;
}

 
void MetisBoundary::InitBoundary(int* nElements, int nBoundaries) {

  
    boundaryConnectivity_ = new std::vector<int> *[nBoundaries];

    for (int i = 0; i < nBoundaries; i++) {
        cout << nElements[i] << endl;
        boundaryConnectivity_[i] = new std::vector<int>[nElements[i]];
    }

    

} 

/* string MetisBoundary::SetBoundaryName(string boundaryName) {

    boundaryName_ = boundaryName;
    return boundaryName_;
} */
/*
string MetisBoundary::FindBoundaryTypeFromTagStr(string tag_str)
{

}*/