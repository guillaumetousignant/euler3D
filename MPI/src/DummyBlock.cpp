#include "DummyBlock.h"

DummyBlock::DummyBlock() : boundary_values_(nullptr){

}

DummyBlock::~DummyBlock(){
    if (boundary_values_ != nullptr){
        delete [] boundary_values_;
    }
}