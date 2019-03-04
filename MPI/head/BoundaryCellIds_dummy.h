#ifndef BOUNDARYCELLIDS_DUMMY_H
#define BOUNDARYCELLIDS_DUMMY_H

class BoundaryCellIds_dummy {
    public:
        BoundaryCellIds_dummy(int* cell_ids_in_boundary, int n_cell_in_boundary); // Should take a mesh as input
        ~BoundaryCellIds_dummy();

        int n_cell_in_boundary_;
        int* cell_ids_in_boundary_;
        int cell_count_;

        virtual void updateBoundary();
};
#endif