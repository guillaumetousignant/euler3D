#ifndef BLOCK_COMMUNICATOR_H
#define BLOCK_COMMUNICATOR_H

#include "DummyMesh.h"

class BlockCommunicator {
    public:
        BlockCommunicator(DummyMesh* mesh); // Should take a mesh as input
        ~BlockCommunicator();

        int number_of_processes_;
        int process_id_;
        int* block_process_id_;
        int n_blocks_;
        int n_inter_block_boundaries_;
        // BoundaryCellIds* inter_block_boundaries_;
        int** boundary_blocks_;
        int* boundary_width_;
        int*** boundary_map_; // this is temporary


        void updateBoundaries(DummyMesh* mesh) const;
        void addCellIdInConnexion();
        void getMyBlocks(DummyMesh* mesh) const;
        void initialize();
        double getGlobal(double const coeff_local) const;
        void setBoundaryOffset();
};
#endif