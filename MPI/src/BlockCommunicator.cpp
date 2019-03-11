#include "BlockCommunicator.h"
#ifdef HAVE_MPI
#include <mpi.h>
#endif
#include <algorithm>
#include <iostream> // REMOVE

BlockCommunicator::BlockCommunicator(int nblocks): n_blocks_(nblocks), n_inter_block_boundaries_(0), inter_block_boundaries_(nullptr) {
    #ifdef HAVE_MPI
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes_);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id_);
    #else
    number_of_processes_ = 1;
    process_id_ = 0;
    #endif

    block_process_id_ = new int[n_blocks_];
    int n = n_blocks_/number_of_processes_;
    int remainder = n_blocks_%number_of_processes_; 

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

    if (inter_block_boundaries_ != nullptr){
        delete [] inter_block_boundaries_;
    }
}

void BlockCommunicator::updateBoundaries(DummyMesh* mesh) const {
    #ifdef HAVE_MPI
    int *** buffers;

    buffers = new int**[n_inter_block_boundaries_];
    for (int i = 0; i < n_inter_block_boundaries_; i++){ // Move ton constructor?
        buffers[i] = new int*[2];
        buffers[i][0] = nullptr;
        buffers[i][1] = nullptr;
    }

    for (int i = 0; i < n_inter_block_boundaries_; i++){
        // If this process is sender
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_origin_]){
            buffers[i][0] = new int[inter_block_boundaries_[i]->n_cell_in_boundary_]; // Move to constructor?

            // Filling send buffer            
            for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
                buffers[i][0][j] = mesh->blocks_[inter_block_boundaries_[i]->block_origin_]->boundary_values_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]; 
            }

            MPI_Request send_request;
            MPI_Isend(buffers[i][0], inter_block_boundaries_[i]->n_cell_in_boundary_, MPI_INT, block_process_id_[inter_block_boundaries_[i]->block_destination_], i, MPI_COMM_WORLD, &send_request);
        }

        // If this process is receiver
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_destination_]){
            buffers[i][1] = new int[inter_block_boundaries_[i]->n_cell_in_boundary_];

            MPI_Request receive_request;
            MPI_Irecv(buffers[i][1], inter_block_boundaries_[i]->n_cell_in_boundary_, MPI_INT, block_process_id_[inter_block_boundaries_[i]->block_origin_], i, MPI_COMM_WORLD, &receive_request);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Put in blocks
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_destination_]){
            for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
                mesh->blocks_[inter_block_boundaries_[i]->block_destination_]->boundary_values_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][1][j];
            }
        }
    }

    // Delete buffers
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        for (int j = 0; j < 2; j++){
            if (buffers[i][j] != nullptr){
                delete [] buffers[i][j];
            }
        }
        delete [] buffers[i];
    }
    delete [] buffers;

    #else
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
            mesh->blocks_[inter_block_boundaries_[i]->block_destination_]->boundary_values_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->blocks_[inter_block_boundaries_[i]->block_origin_]->boundary_values_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
        }
    }
    #endif
}

void BlockCommunicator::addCellIdInConnexion(ConnexionCellIds_dummy* boundary){
    ConnexionCellIds_dummy** inter_block_boundaries = new ConnexionCellIds_dummy*[n_inter_block_boundaries_ + 1];
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        inter_block_boundaries[i] = inter_block_boundaries_[i];
    }
    inter_block_boundaries[n_inter_block_boundaries_] = boundary;
    n_inter_block_boundaries_++;

    delete [] inter_block_boundaries_;
    inter_block_boundaries_ = inter_block_boundaries;
}

void BlockCommunicator::getMyBlocks(int& n_blocks_in_process, int* &my_blocks) const {
    int n = n_blocks_/number_of_processes_;
    int remainder = n_blocks_%number_of_processes_; 
    int index_start = process_id_ * n + std::min(process_id_, remainder);
    n_blocks_in_process = n + (process_id_ < remainder);

    /*if (mesh->my_blocks_ != nullptr){
        delete [] mesh->my_blocks_;
    }*/

    my_blocks = new int[n_blocks_in_process];
    for (int i = 0; i < n_blocks_in_process; i++){
        my_blocks[i] = index_start + i;
    }    
}

void BlockCommunicator::initialize(){

}

double BlockCommunicator::getGlobal(double const coeff_local) const {
    return 0.0;
}

void BlockCommunicator::setBoundaryOffset(){

}