#include "MetisBoundary.h"
#include <iostream>

MetisBoundary::MetisBoundary() {
}

MetisBoundary::~MetisBoundary() {
    if (nNodes_ != nullptr)
        delete[] nNodes_;
    nNodes_ = nullptr;
}

void MetisBoundary::Init(int nElements, int* nNodes) {
    std::cout << "NOT IMPLEMENTED INIT" << std::endl;
}