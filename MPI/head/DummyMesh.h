#ifndef DUMMY_MESH_H
#define DUMMY_MESH_H

#include "DummyBlock.h"

class DummyMesh {
    public:
        DummyMesh(int n_blocks);
        ~DummyMesh();

        int n_blocks_;
        DummyBlock** blocks_;
        int n_my_blocks_;
        DummyBlock** my_blocks_;
};
#endif