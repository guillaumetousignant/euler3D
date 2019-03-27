#include "MetisBoundary.h"
#include <iostream>

MetisBoundary::MetisBoundary(int nElements, int* elementType, int* elementNbrNodes, int **boundaryElements) {
    this->nElements_ = nElements;
    this->elementType_ = elementType;
    this->elementNbrNodes_ = elementNbrNodes;
    this->boundaryElements_ = boundaryElements;
}

MetisBoundary::~MetisBoundary() {
    //if (nNodes_ != nullptr)
    //    delete[] nNodes_;
    //nNodes_ = nullptr;
}
/*
void MetisBoundary::Init(int nElements, int* nNodes) {
    for 
}*/

/*
string MetisBoundary::FindBoundaryTypeFromTagStr(string tag_str)
{

}*/