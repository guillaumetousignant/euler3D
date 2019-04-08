#include "BlockCommunicator.h"
#ifdef HAVE_MPI
#include <mpi.h>
#endif
#include <algorithm>
#include "PostProcessing.h"
#include <iostream>
#include <string>
#include <sstream>

#define N_VARIABLES 20

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

void BlockCommunicator::updateBoundaries(CompleteMesh* mesh) const {
    #ifdef HAVE_MPI
    double *** buffers;

    buffers = new double**[n_inter_block_boundaries_];
    for (int i = 0; i < n_inter_block_boundaries_; i++){ // Move ton constructor?
        buffers[i] = new double*[N_VARIABLES*2];
        for (unsigned int j = 0; j < N_VARIABLES*2; j++){
            buffers[i][j] = nullptr;
        }
    }

    for (int i = 0; i < n_inter_block_boundaries_; i++){
        // If this process is sender
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_origin_]){
            if (process_id_ == 2){
                std::cout << "Process " << process_id_ << " sending to " << inter_block_boundaries_[i]->block_destination_ << std::endl; // REMOVE
            }

            for (unsigned int j = 0; j < N_VARIABLES; j++){
                buffers[i][j] = new double[inter_block_boundaries_[i]->n_cell_in_boundary_]; // Move to constructor?
            }

            // Filling send buffer            
            for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
                buffers[i][0][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]; 
                buffers[i][1][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][2][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][3][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][4][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][5][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]; 
                buffers[i][6][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][7][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][8][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][9][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][10][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]; 
                buffers[i][11][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][12][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][13][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][14][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][15][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ro_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]; 
                buffers[i][16][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ru_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][17][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->rv_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][18][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->rw_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
                buffers[i][19][j] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->re_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            }

            MPI_Request send_request[N_VARIABLES];
            for (unsigned int j = 0; j < N_VARIABLES; j++){
                MPI_Isend(buffers[i][j], inter_block_boundaries_[i]->n_cell_in_boundary_, MPI_DOUBLE, block_process_id_[inter_block_boundaries_[i]->block_destination_], N_VARIABLES*i+j, MPI_COMM_WORLD, &send_request[j]);
            }
        }

        // If this process is receiver
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_destination_]){
            if (process_id_ == 0){
                std::cout << "Process " << process_id_ << " receiving from " << inter_block_boundaries_[i]->block_origin_ << std::endl; // REMOVE
            }
            
            for (unsigned int j = N_VARIABLES; j < N_VARIABLES*2; j++){
                buffers[i][j] = new double[inter_block_boundaries_[i]->n_cell_in_boundary_]; // Move to constructor?
            }

            MPI_Request receive_request[N_VARIABLES];
            for (unsigned int j = N_VARIABLES; j < N_VARIABLES*2; j++){
                MPI_Irecv(buffers[i][j], inter_block_boundaries_[i]->n_cell_in_boundary_, MPI_DOUBLE, block_process_id_[inter_block_boundaries_[i]->block_origin_], N_VARIABLES*i+j, MPI_COMM_WORLD, &receive_request[j-N_VARIABLES]);
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Put in blocks
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_destination_]){
            for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+1][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+2][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+3][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+4][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+5][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+6][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+7][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+8][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+9][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+10][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+11][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+12][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+13][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+14][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ro_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+15][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ru_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+16][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->rv_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+17][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->rw_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+18][j];
                mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->re_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = buffers[i][N_VARIABLES+19][j];
            }
        }
    }

    // Delete buffers
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        for (int j = 0; j < N_VARIABLES*2; j++){
            if (buffers[i][j] != nullptr){
                delete [] buffers[i][j];
            }
        }
        delete [] buffers[i];
    }
    delete [] buffers; // This line throws "munmap_chunk(): invalid pointer" on process 3 when there are 6 blocks and 6 processes. wtf

    #else
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        for (int j = 0; j < inter_block_boundaries_[i]->n_cell_in_boundary_; j++){
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->conv_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->conv_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_ro_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_uu_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_vv_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_ww_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->diss_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->diss_res_pp_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ro_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ro_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->ru_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->ru_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->rv_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->rv_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->rw_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->rw_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
            mesh->all_blocks_[inter_block_boundaries_[i]->block_destination_]->block_primitive_variables_->re_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_[j]] = mesh->all_blocks_[inter_block_boundaries_[i]->block_origin_]->block_primitive_variables_->re_0_[inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]];
        }
    }
    #endif
}

void BlockCommunicator::addCellIdInConnexion(ConnexionCellIds* boundary){
    ConnexionCellIds** inter_block_boundaries = new ConnexionCellIds*[n_inter_block_boundaries_ + 1];
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

void BlockCommunicator::getGlobal(CompleteMesh* mesh, PostProcessing* postprocess) {
    #ifdef HAVE_MPI
    double ro_rms_process=0.0;
    double uu_rms_process=0.0;
    double vv_rms_process=0.0;
    double ww_rms_process=0.0;
    double pp_rms_process=0.0;
    double cl_geometry_process=0.0;
    double cd_geometry_process=0.0;
    double cmx_geometry_process=0.0;
    double cmy_geometry_process=0.0;
    double cmz_geometry_process=0.0;
    int blockid;

    for(int i = 0; i < mesh->n_blocks_in_process_ ; i++) // For each block
    {
        blockid = mesh->my_blocks_[i];
        // Convergence data
        ro_rms_process += postprocess->ro_rms_blocks_[blockid];
        uu_rms_process += postprocess->uu_rms_blocks_[blockid];
        vv_rms_process += postprocess->vv_rms_blocks_[blockid];
        ww_rms_process += postprocess->ww_rms_blocks_[blockid];
        pp_rms_process += postprocess->pp_rms_blocks_[blockid];
        cl_geometry_process += postprocess->cl_geometry_blocks_[blockid];
        cd_geometry_process += postprocess->cd_geometry_blocks_[blockid];
        cmx_geometry_process += postprocess->cmx_geometry_blocks_[blockid];
        cmy_geometry_process += postprocess->cmy_geometry_blocks_[blockid];
        cmz_geometry_process += postprocess->cmz_geometry_blocks_[blockid];
    }

    MPI_Allreduce(&ro_rms_process, &postprocess->ro_rms_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&uu_rms_process, &postprocess->uu_rms_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&vv_rms_process, &postprocess->vv_rms_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&ww_rms_process, &postprocess->ww_rms_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&pp_rms_process, &postprocess->pp_rms_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&cl_geometry_process, &postprocess->cl_geometry_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&cd_geometry_process, &postprocess->cd_geometry_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&cmx_geometry_process, &postprocess->cmx_geometry_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&cmy_geometry_process, &postprocess->cmy_geometry_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&cmz_geometry_process, &postprocess->cmz_geometry_mesh_, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD); // Dunno if needed, check
    #else

    postprocess->ro_rms_mesh_=0.0;
    postprocess->uu_rms_mesh_=0.0;
    postprocess->vv_rms_mesh_=0.0;
    postprocess->ww_rms_mesh_=0.0;
    postprocess->pp_rms_mesh_=0.0;
    postprocess->cl_geometry_mesh_=0.0;
    postprocess->cd_geometry_mesh_=0.0;
    postprocess->cmx_geometry_mesh_=0.0;
    postprocess->cmy_geometry_mesh_=0.0;
    postprocess->cmz_geometry_mesh_=0.0;

    for(i=0; i<complete_mesh->n_blocks_ ; i++) // For each block
    {
        // Convergence data
        postprocess->ro_rms_mesh_ += postprocess->ro_rms_blocks_[i];
        postprocess->uu_rms_mesh_ += postprocess->uu_rms_blocks_[i];
        postprocess->vv_rms_mesh_ += postprocess->vv_rms_blocks_[i];
        postprocess->ww_rms_mesh_ += postprocess->ww_rms_blocks_[i];
        postprocess->pp_rms_mesh_ += postprocess->pp_rms_blocks_[i];
        // Aerodynamic data
        postprocess->cl_geometry_mesh_ += postprocess->cl_geometry_blocks_[i];
        postprocess->cd_geometry_mesh_ += postprocess->cd_geometry_blocks_[i];
        postprocess->cmx_geometry_mesh_ += postprocess->cmx_geometry_blocks_[i];
        postprocess->cmy_geometry_mesh_ += postprocess->cmy_geometry_blocks_[i];
        postprocess->cmz_geometry_mesh_ += postprocess->cmz_geometry_blocks_[i];
    }
    #endif
}

void BlockCommunicator::setBoundaryOffset(){

}

void BlockCommunicator::createBoundaries(std::string  &topology_filename){
	std::ifstream topo(topology_filename);

	if (!topo.is_open()){
		std::cout << "ERROR: Topology file '" << topology_filename << "' not opened, exiting." << std::endl;
		return;
	}

	std::string line;
	std::string marker;
	bool boundary_started = false;
    bool save = false;
	int boundary_index = 0;
    int ghost_index = 0;
	int n_blocks;
	int block_origin;
	int n_cells;
	int block_destination;
	int* cell_ids = nullptr;
    int* ghost_ids = nullptr;
	ConnexionCellIds *boundary = nullptr;


	while (std::getline(topo, line)){
		std::istringstream liness(line);
        liness >> marker;

		if (marker == "Nmark="){
			liness >> block_origin;
			if (boundary_started){
                save = true;
				boundary_started = false;
			}	
		}
		else if (marker == "NBLOCK="){
			liness >> n_blocks;
			for (int i = 0; i < n_blocks; i++){
				std::getline(topo, line);
			}
            if (boundary_started){
                save = true;
				boundary_started = false;
			}			
		}
		else if (marker == "Block="){
            liness >> block_destination;
            //std::cout << "Process " << process_id_ << " reads block destination " << block_destination << std::endl; // REMOVE
            if (boundary_started){
                save = true;
				boundary_started = false;
			}				
		}
		else if (marker == "Nconnexion="){
            if (boundary_started){
                save = true;
				boundary_started = false;
			}
		}
        else if (marker == "GhostCount"){
            liness >> ghost_index;
            if (boundary_started){
                save = true;
				boundary_started = false;
			}
        }

		if (boundary_started){
			liness >> cell_ids[boundary_index];
            ghost_ids[boundary_index] = ghost_index + boundary_index;
			boundary_index ++;
		}

		if (marker == "Nelems="){
			boundary_started = true;
			liness >> n_cells;

			cell_ids = new int[n_cells];
            ghost_ids = new int[n_cells];

			boundary = new ConnexionCellIds();
			boundary->cell_count_ = nullptr;
            std::cout << "Process " << process_id_ << " writes block destination " << block_destination << " and block origin " << block_origin << std::endl; // REMOVE
			boundary->block_destination_ = block_destination;
			boundary->block_origin_ = block_origin;
			boundary->n_cell_in_boundary_ = n_cells;
			boundary->cell_ids_in_boundary_ = nullptr;
			boundary->cell_ids_in_boundary_other_block_ = nullptr;
			boundary->owner_block_ = nullptr;
		}

        if (save){
            save = false;
            boundary->cell_ids_in_boundary_other_block_ = cell_ids;
            boundary->cell_ids_in_boundary_ = ghost_ids;

            addCellIdInConnexion(boundary);

            if (cell_ids != nullptr){
                cell_ids = nullptr;
            }
            if (ghost_ids != nullptr){
                ghost_ids = nullptr;
            }
        }
	}

	if (boundary_started){
        boundary->cell_ids_in_boundary_other_block_ = cell_ids;
        boundary->cell_ids_in_boundary_ = ghost_ids;

        addCellIdInConnexion(boundary);
    }

	topo.close();

    std::cout<<"----------------VÉRIFICATION CONNECTION AU MPI-----------------"<<std::endl;
    std::cout<<"Number of boundarier: "<<n_inter_block_boundaries_<<std::endl;
    for (int i=0;i<n_inter_block_boundaries_;i++)
    {
        std::cout<<"Boundary number: "<<i<<std::endl;
        std::cout<<"Block destination: "<<inter_block_boundaries_[i]->block_destination_<<" Block origin: "<<inter_block_boundaries_[i]->block_origin_<<" Number of cells in boundary: "<<inter_block_boundaries_[i]->n_cell_in_boundary_<<std::endl;
        std::cout<<"Cell ids in boundary\tCell ids in other boundary"<<std::endl;
        for (int j=0;j<inter_block_boundaries_[i]->n_cell_in_boundary_;j++)
        {
            std::cout<<inter_block_boundaries_[i]->cell_ids_in_boundary_[j]<<"\t\t\t\t"<<inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]<<std::endl;
        }
        std::cout<<endl;		
    }
}