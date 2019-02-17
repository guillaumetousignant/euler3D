#include "DummyMesh.h"

DummyMesh::DummyMesh(int n_blocks): n_blocks_(n_blocks), n_my_blocks_(0), my_blocks_(nullptr) {
    blocks_ = new DummyBlock*[n_blocks_];
    for (int i = 0; i < n_blocks_; i++){
        blocks_[i] = new DummyBlock();
    }
};

DummyMesh::~DummyMesh(){
    if (blocks_ != nullptr){
        for (int i = 0; i < n_blocks_; i++){
            delete blocks_[i];
        }
        delete [] blocks_;
    }

    if (my_blocks_ != nullptr){
        delete [] my_blocks_;
    }
};