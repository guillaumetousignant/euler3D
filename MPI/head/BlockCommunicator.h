#ifndef BLOCK_COMMUNICATOR_H
#define BLOCK_COMMUNICATOR_H

#include "CompleteMesh.h"
#include "ConnexionCellIds.h"

class BlockCommunicator {
    public:
        BlockCommunicator(int nblocks); // Should take a mesh as input
        ~BlockCommunicator();

        int number_of_processes_;
        int process_id_;
        int* block_process_id_;
        int n_blocks_;
        int n_inter_block_boundaries_;
        ConnexionCellIds** inter_block_boundaries_;

        void updateBoundaries(CompleteMesh* mesh) const;
        void addCellIdInConnexion(ConnexionCellIds* boundary);
        void getMyBlocks(int& n_blocks_in_process, int* &my_blocks) const;
        void initialize();
        double getGlobal(double const coeff_local) const;
        void setBoundaryOffset();
};
#endif