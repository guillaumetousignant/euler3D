#include "BlockCommunicator.h"
#include <mpi.h>
#include <algorithm>
#include <iostream> // REMOVE

BlockCommunicator::BlockCommunicator(DummyMesh* mesh): n_blocks_(mesh->n_blocks_), n_inter_block_boundaries_(2){
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

    boundary_blocks_ = new int*[n_inter_block_boundaries_];
    boundary_blocks_[0] = new int[2];
    boundary_blocks_[1] = new int[2];
    // Blocks from boundary
    boundary_blocks_[0][0] = 0;
    boundary_blocks_[0][1] = 1;
    boundary_blocks_[1][0] = 1;
    boundary_blocks_[1][1] = 2;

    boundary_width_ = new int[n_inter_block_boundaries_];
    // Number of elements in each boundary
    boundary_width_[0] = 3;
    boundary_width_[1] = 4;

    boundary_map_ = new int**[n_inter_block_boundaries_];
    boundary_map_[0] = new int*[2];
    boundary_map_[1] = new int*[2];
    boundary_map_[0][0] = new int[boundary_width_[0]];
    boundary_map_[0][1] = new int[boundary_width_[0]];
    boundary_map_[1][0] = new int[boundary_width_[1]];
    boundary_map_[1][1] = new int[boundary_width_[1]];
    // Mappings
    boundary_map_[0][0][0] = 0;
    boundary_map_[0][0][1] = 1;
    boundary_map_[0][0][2] = 2;
    boundary_map_[0][1][0] = 2;
    boundary_map_[0][1][1] = 3;
    boundary_map_[0][1][2] = 4;

    boundary_map_[1][0][0] = 5;
    boundary_map_[1][0][1] = 6;
    boundary_map_[1][0][2] = 7;
    boundary_map_[1][0][3] = 8;
    boundary_map_[1][1][0] = 6;
    boundary_map_[1][1][1] = 7;
    boundary_map_[1][1][2] = 8;
    boundary_map_[1][1][3] = 9;

}

BlockCommunicator::~BlockCommunicator(){
    if (block_process_id_ != nullptr){
        delete [] block_process_id_;
    }
}

void BlockCommunicator::updateBoundaries(DummyMesh* mesh) const {
    int*** buffers = new int**[n_inter_block_boundaries_];
    for (int i = 0; i < n_inter_block_boundaries_; i++){ // Move ton constructor?
        buffers[i] = new int*[4];
        buffers[i][0] = nullptr;
        buffers[i][1] = nullptr;
        buffers[i][2] = nullptr;
        buffers[i][3] = nullptr;
    }

    for (int i = 0; i < n_inter_block_boundaries_; i++){
        // If this process is sender
        if (process_id_ == block_process_id_[boundary_blocks_[i][0]]){
            buffers[i][0] = new int[boundary_width_[i]]; // Move to constructor?
            buffers[i][1] = new int[boundary_width_[i]];
            MPI_Request send_send_request;
            MPI_Request send_receive_request;

            // Filling send buffer
            for (int j = 0; j < boundary_width_[i]; j++){
                buffers[i][0][j] = mesh->blocks_[boundary_blocks_[i][0]]->boundary_values_[boundary_map_[i][0][j]];
            }

            MPI_Isend(buffers[i][0], boundary_width_[i], MPI_INT, block_process_id_[boundary_blocks_[i][1]], i, MPI_COMM_WORLD, &send_send_request);
            MPI_Irecv(buffers[i][1], boundary_width_[i], MPI_INT, block_process_id_[boundary_blocks_[i][1]], i, MPI_COMM_WORLD, &send_receive_request);
        }

        // If this process is receiver
        if (process_id_ == block_process_id_[boundary_blocks_[i][1]]){
            buffers[i][2] = new int[boundary_width_[i]];
            buffers[i][3] = new int[boundary_width_[i]];
            MPI_Request receive_send_request;
            MPI_Request receive_receive_request;

            // Filling send buffer
            for (int j = 0; j < boundary_width_[i]; j++){
                buffers[i][2][j] = mesh->blocks_[boundary_blocks_[i][1]]->boundary_values_[boundary_map_[i][1][j]];
            }

            MPI_Isend(buffers[i][2], boundary_width_[i], MPI_INT, block_process_id_[boundary_blocks_[i][0]], i, MPI_COMM_WORLD, &receive_send_request);
            MPI_Irecv(buffers[i][3], boundary_width_[i], MPI_INT, block_process_id_[boundary_blocks_[i][0]], i, MPI_COMM_WORLD, &receive_receive_request);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Put in blocks
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        if (process_id_ == block_process_id_[boundary_blocks_[i][0]]){
            if (block_process_id_[boundary_blocks_[i][0]] == block_process_id_[boundary_blocks_[i][1]]) {
                std::cout << boundary_blocks_[i][0] << " AAAAAAAAA";
                for (int j = 0; j < boundary_width_[i]; j++){
                    std::cout << " " << buffers[i][1][j];
                } 
                
            }
            for (int j = 0; j < boundary_width_[i]; j++){
                mesh->blocks_[boundary_blocks_[i][0]]->boundary_values_[boundary_map_[i][0][j]] = buffers[i][1][j];
            }
            if (block_process_id_[boundary_blocks_[i][0]] == block_process_id_[boundary_blocks_[i][1]]) {
                std::cout << "   " << boundary_blocks_[i][0] << " BBBBBBB";
                for (int j = 0; j < boundary_width_[i]; j++){
                    std::cout << " " << mesh->blocks_[boundary_blocks_[i][0]]->boundary_values_[boundary_map_[i][0][j]];
                } 
                std::cout << std::endl;
            } 
        }

        if (process_id_ == block_process_id_[boundary_blocks_[i][1]]){
            if (block_process_id_[boundary_blocks_[i][0]] == block_process_id_[boundary_blocks_[i][1]]) {
                std::cout << boundary_blocks_[i][1] << " AAAAAAAAA";
                for (int j = 0; j < boundary_width_[i]; j++){
                    std::cout << " " << buffers[i][3][j];
                } 
                
            }
            for (int j = 0; j < boundary_width_[i]; j++){
                mesh->blocks_[boundary_blocks_[i][1]]->boundary_values_[boundary_map_[i][1][j]] = buffers[i][3][j];                                                                                                                                             
            }
            if (block_process_id_[boundary_blocks_[i][0]] == block_process_id_[boundary_blocks_[i][1]]) {
                std::cout << "   " << boundary_blocks_[i][1] << " BBBBBBB";
                for (int j = 0; j < boundary_width_[i]; j++){
                    std::cout << " " << mesh->blocks_[boundary_blocks_[i][1]]->boundary_values_[boundary_map_[i][1][j]];
                } 
                std::cout << std::endl;
            } 
        }
    }

    // Delete buffers
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        for (int j = 0; j < 4; j++){
            if (buffers[i][j] != nullptr){
                delete [] buffers[i][j];
            }
        }
        delete [] buffers[i];
    }
    delete [] buffers;
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

    mesh->my_blocks_ = new int[mesh->n_my_blocks_];
    for (int i = 0; i < mesh->n_my_blocks_; i++){
        mesh->my_blocks_[i] = index_start + i;
    }    
}

void BlockCommunicator::initialize(){

}

double BlockCommunicator::getGlobal(double const coeff_local) const {
    return 0.0;
}

void BlockCommunicator::setBoundaryOffset(){

}