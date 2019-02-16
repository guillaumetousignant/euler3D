#include "BlockCommunicator.h"
#include <mpi.h>
#include <algorithm>
#include <iostream> // REMOVE

BlockCommunicator::BlockCommunicator(DummyMesh* mesh): n_blocks_(mesh->n_blocks_){
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes_);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id_);

    block_process_id_ = new int[n_blocks_];
    int n = mesh->n_blocks_/number_of_processes_;
    int remainder = mesh->n_blocks_%number_of_processes_; 

    // Calculates which process owns what block
    for (int i = 0; i < number_of_processes_; i++){
        for (int j = 0; j < n + (i < remainder); j++){
            block_process_id_[i * n + std::min(i, remainder) + j] = i;
        }
    }
}

BlockCommunicator::~BlockCommunicator(){
    if (block_process_id_ != nullptr){
        delete [] block_process_id_;
    }
}

void BlockCommunicator::updateBoundaries() const {

}

void BlockCommunicator::addCellIdInConnexion(){

}

void BlockCommunicator::getMyBlocks(DummyMesh* mesh) const {
    int n = mesh->n_blocks_/number_of_processes_;
    int remainder = mesh->n_blocks_%number_of_processes_; 
    int index_start = process_id_ * n + std::min(process_id_, remainder);
    mesh->n_my_blocks_ = n + (process_id_ < remainder);

    /*if (mesh->my_blocks_ != nullptr){
        delete [] mesh->my_blocks_;
    }*/

    mesh->my_blocks_ = new DummyBlock*[mesh->n_my_blocks_];
    for (int i = 0; i < mesh->n_my_blocks_; i++){
        mesh->my_blocks_[i] = mesh->blocks_[index_start + i];
    }    
}

void BlockCommunicator::initialize(){

}

double BlockCommunicator::getGlobal(double const coeff_local) const {
    return 0.0;
}

void BlockCommunicator::setBoundaryOffset(){

}