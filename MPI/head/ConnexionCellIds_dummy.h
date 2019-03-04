#ifndef CONNEXIONCELLIDS_DUMMY_H
#define CONNEXIONCELLIDS_DUMMY_H

#include "BoundaryCellIds_dummy.h"

class ConnexionCellIds_dummy : public BoundaryCellIds_dummy {
    public:
        ConnexionCellIds_dummy(int* cell_ids_in_boundary, int n_cell_in_boundary, int* cell_ids_in_boundary_other_block, int block_origin, int block_destination); // Should take a mesh as input
        ~ConnexionCellIds_dummy();

        int* cell_ids_in_boundary_other_block_;
        int block_origin_;
        int block_destination_;
};
#endif