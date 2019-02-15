#ifndef BLOCK_COMMUNICATOR_H
#define BLOCK_COMMUNICATOR_H

class BlockCommunicator {
    public:
        BlockCommunicator() {}
        ~BlockCommunicator() {}

        int number_of_processes_;
        int process_id_;
        int* block_process_id_;
        int n_blocks_;
        int n_inter_block_boundaries_;
        // BoundaryCellIds* inter_block_boundaries_;

        void updateBoundaries();
        void addCellIdInConnexion();
        void getMyBlocks(int &n_blocks, int* my_blocks);
        void initialize();
        double getGlobal(double coeff_local);
        void setBoundaryOffset();
};
#endif