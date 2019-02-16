#include "DummyBlock.h"

DummyBlock::DummyBlock() : boundary_values_(nullptr){

}

DummyBlock::~DummyBlock(){
    if (boundary_values_ != nullptr){
        delete [] boundary_values_;
    }
}

void DummyBlock::fillBlock(int i){
    if (boundary_values_ != nullptr){
        delete [] boundary_values_;
    }

    boundary_values_ = new int[10];
    for (int j = 0; j < 10; j++){
        boundary_values_[j] = i;
    }
}