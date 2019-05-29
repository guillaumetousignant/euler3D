#ifndef BLOCK_COMMUNICATOR_H
#define BLOCK_COMMUNICATOR_H

#include "CompleteMesh.h"
#include "ConnexionCellIds.h"
#include <string>
#include <chrono>

class PostProcessing;
class CompleteMesh;

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
        std::chrono::high_resolution_clock::time_point t_start;
        std::chrono::high_resolution_clock::time_point t_end; // make list?


        double *** buffers_;
        void passRVectors(CompleteMesh* mesh) const;
        void updateBoundaries(CompleteMesh* mesh) const;
        void addCellIdInConnexion(ConnexionCellIds* boundary);
        void getMyBlocks(int& n_blocks_in_process, int* &my_blocks) const;
        void initialize();
        void getGlobal(CompleteMesh* mesh, PostProcessing* postprocess);
        void createBoundaries(std::string  &topology_filename);
        void sync();

        void setBoundaryOffset();
        void initializeBuffers();
};
#endif
