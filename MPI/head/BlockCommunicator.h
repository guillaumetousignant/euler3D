#ifndef BLOCK_COMMUNICATOR_H
#define BLOCK_COMMUNICATOR_H

class BlockCommunicator {
    public:
        BlockCommunicator(); // Should take a mesh as input
        ~BlockCommunicator();

        int number_of_processes_;
        int process_id_;
        int** block_process_id_;
        int n_blocks_;
        int n_inter_block_boundaries_;
        // BoundaryCellIds* inter_block_boundaries_;
        // Mesh mesh_;

        void updateBoundaries() const;
        void addCellIdInConnexion();
        void getMyBlocks(int &n_blocks, int* my_blocks) const;
        void initialize();
        double getGlobal(double const coeff_local) const;
        void setBoundaryOffset();
};
#endif