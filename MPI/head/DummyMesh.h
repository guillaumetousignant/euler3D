#ifndef DUMMY_MESH_H
#define DUMMY_MESH_H

#include "DummyBlock.h"

class DummyMesh {
    public:
        DummyMesh(int n_blocks, int n_blocks_in_process, int* my_blocks);
        ~DummyMesh();

        int n_blocks_;
        DummyBlock** blocks_;
        int n_blocks_in_process_;
        int* my_blocks_;
};
#endif