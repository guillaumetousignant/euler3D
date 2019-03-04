#include "DummyMesh.h"

DummyMesh::DummyMesh(int n_blocks, int n_blocks_in_process, int* my_blocks)
    : n_blocks_(n_blocks), n_blocks_in_process_(n_blocks_in_process), my_blocks_(my_blocks) {
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