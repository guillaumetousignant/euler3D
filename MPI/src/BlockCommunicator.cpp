#include "BlockCommunicator.h"
#ifdef HAVE_MPI
#include <mpi.h>
#endif
#include <algorithm>
#include "PostProcessing.h"
#include <iostream>
#include <string>
#include <sstream>

#define N_VARIABLES 40
#define  MAX_REQUESTS  15000
MPI_Request       reqHdl[MAX_REQUESTS];
MPI_Status        reqStat[MAX_REQUESTS];
int               reqCount;

BlockCommunicator::BlockCommunicator(int nblocks): n_blocks_(nblocks), n_inter_block_boundaries_(0), inter_block_boundaries_(nullptr), buffers_(nullptr) {
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

    // Delete buffers_
    if (buffers_ != nullptr){
        for (int i = 0; i < n_inter_block_boundaries_; i++){
            if (buffers_[i] != nullptr){
                for (int j = 0; j < N_VARIABLES*2; j++){
                    if (buffers_[i][j] != nullptr){
                        delete [] buffers_[i][j];
                    }
                }
                delete [] buffers_[i];
            }
        }
        delete [] buffers_; // This line throws "munmap_chunk(): invalid pointer" on process 3 when there are 6 blocks and 6 processes. wtf
    }
}

void BlockCommunicator::updateBoundaries(CompleteMesh* mesh) const {
    #ifdef HAVE_MPI

    reqCount = 0;

    for (int i = 0; i < n_inter_block_boundaries_; i++){
        ConnexionCellIds* boundary = inter_block_boundaries_[i];
        int block_id_origin = boundary->block_origin_;
        int block_id_destination = boundary->block_destination_;
        int n_cells = boundary->n_cell_in_boundary_;
        Block* block_origin = mesh->all_blocks_[block_id_origin];
        int origin_process_id = block_process_id_[block_id_origin];
        int destination_process_id = block_process_id_[block_id_destination];

        // If this process is sender
        if (process_id_ == origin_process_id){

            // Filling send buffer
            for (int k = 0; k < n_cells; k++){
                int cell_id_origin = boundary->cell_ids_in_boundary_other_block_[k];

                //double cell_id_origin_double=cell_id_origin; // Pour debug le transfert MPI

                buffers_[i][0][k] = block_origin->block_primitive_variables_->ro_[cell_id_origin]; // cell_id_origin_double; //Pour debug le transfert MPI
                buffers_[i][1][k] = block_origin->block_primitive_variables_->uu_[cell_id_origin];
                buffers_[i][2][k] = block_origin->block_primitive_variables_->vv_[cell_id_origin];
                buffers_[i][3][k] = block_origin->block_primitive_variables_->ww_[cell_id_origin];
                buffers_[i][4][k] = block_origin->block_primitive_variables_->pp_[cell_id_origin];
                buffers_[i][5][k] = block_origin->block_primitive_variables_->conv_res_ro_[cell_id_origin];
                buffers_[i][6][k] = block_origin->block_primitive_variables_->conv_res_uu_[cell_id_origin];
                buffers_[i][7][k] = block_origin->block_primitive_variables_->conv_res_vv_[cell_id_origin];
                buffers_[i][8][k] = block_origin->block_primitive_variables_->conv_res_ww_[cell_id_origin];
                buffers_[i][9][k] = block_origin->block_primitive_variables_->conv_res_pp_[cell_id_origin];
                buffers_[i][10][k] = block_origin->block_primitive_variables_->diss_res_ro_[cell_id_origin];
                buffers_[i][11][k] = block_origin->block_primitive_variables_->diss_res_uu_[cell_id_origin];
                buffers_[i][12][k] = block_origin->block_primitive_variables_->diss_res_vv_[cell_id_origin];
                buffers_[i][13][k] = block_origin->block_primitive_variables_->diss_res_ww_[cell_id_origin];
                buffers_[i][14][k] = block_origin->block_primitive_variables_->diss_res_pp_[cell_id_origin];
                buffers_[i][15][k] = block_origin->block_primitive_variables_->ro_0_[cell_id_origin];
                buffers_[i][16][k] = block_origin->block_primitive_variables_->ru_0_[cell_id_origin];
                buffers_[i][17][k] = block_origin->block_primitive_variables_->rv_0_[cell_id_origin];
                buffers_[i][18][k] = block_origin->block_primitive_variables_->rw_0_[cell_id_origin];
                buffers_[i][19][k] = block_origin->block_primitive_variables_->re_0_[cell_id_origin];

                buffers_[i][20][k] = block_origin->block_interpolation_variables_->limiter_ro_[cell_id_origin];
                buffers_[i][21][k] = block_origin->block_interpolation_variables_->limiter_uu_[cell_id_origin];
                buffers_[i][22][k] = block_origin->block_interpolation_variables_->limiter_vv_[cell_id_origin];
                buffers_[i][23][k] = block_origin->block_interpolation_variables_->limiter_ww_[cell_id_origin];
                buffers_[i][24][k] = block_origin->block_interpolation_variables_->limiter_pp_[cell_id_origin];

                buffers_[i][25][k] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][0];
                buffers_[i][26][k] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][1];
                buffers_[i][27][k] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][2];
                buffers_[i][28][k] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][0];
                buffers_[i][29][k] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][1];
                buffers_[i][30][k] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][2];
                buffers_[i][31][k] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][0];
                buffers_[i][32][k] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][1];
                buffers_[i][33][k] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][2];
                buffers_[i][34][k] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][0];
                buffers_[i][35][k] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][1];
                buffers_[i][36][k] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][2];
                buffers_[i][37][k] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][0];
                buffers_[i][38][k] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][1];
                buffers_[i][39][k] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][2];
            }

            MPI_Request send_request[N_VARIABLES];
            for (unsigned int j = 0; j < N_VARIABLES; j++){
                MPI_Isend(buffers_[i][j], n_cells, MPI_DOUBLE, destination_process_id, N_VARIABLES*i+j, MPI_COMM_WORLD, &reqHdl[reqCount]);
                reqCount++;
            }
        }

        // If this process is receiver
        if (process_id_ == destination_process_id){

            MPI_Request receive_request[N_VARIABLES];
            for (unsigned int j = 0; j < N_VARIABLES; j++){
                MPI_Irecv(buffers_[i][j+N_VARIABLES], n_cells, MPI_DOUBLE, origin_process_id, N_VARIABLES*i+j, MPI_COMM_WORLD, &reqHdl[reqCount]);
                reqCount++;
            }
        }
    }

    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Waitall(reqCount, reqHdl, reqStat);

    // Put in blocks
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        ConnexionCellIds* boundary = inter_block_boundaries_[i];
        int block_id_destination = boundary->block_destination_;
        int n_cells = boundary->n_cell_in_boundary_;
        Block* block_destination = mesh->all_blocks_[block_id_destination];
        int destination_process_id = block_process_id_[block_id_destination];

        if (process_id_ == destination_process_id){
            for (int k = 0; k < n_cells; k++){
                int cell_id_destination = boundary->cell_ids_in_boundary_[k];

                block_destination->block_primitive_variables_->ro_[cell_id_destination] = buffers_[i][N_VARIABLES][k];
                block_destination->block_primitive_variables_->uu_[cell_id_destination] = buffers_[i][N_VARIABLES+1][k];
                block_destination->block_primitive_variables_->vv_[cell_id_destination] = buffers_[i][N_VARIABLES+2][k];
                block_destination->block_primitive_variables_->ww_[cell_id_destination] = buffers_[i][N_VARIABLES+3][k];
                block_destination->block_primitive_variables_->pp_[cell_id_destination] = buffers_[i][N_VARIABLES+4][k];
                block_destination->block_primitive_variables_->conv_res_ro_[cell_id_destination] = buffers_[i][N_VARIABLES+5][k];
                block_destination->block_primitive_variables_->conv_res_uu_[cell_id_destination] = buffers_[i][N_VARIABLES+6][k];
                block_destination->block_primitive_variables_->conv_res_vv_[cell_id_destination] = buffers_[i][N_VARIABLES+7][k];
                block_destination->block_primitive_variables_->conv_res_ww_[cell_id_destination] = buffers_[i][N_VARIABLES+8][k];
                block_destination->block_primitive_variables_->conv_res_pp_[cell_id_destination] = buffers_[i][N_VARIABLES+9][k];
                block_destination->block_primitive_variables_->diss_res_ro_[cell_id_destination] = buffers_[i][N_VARIABLES+10][k];
                block_destination->block_primitive_variables_->diss_res_uu_[cell_id_destination] = buffers_[i][N_VARIABLES+11][k];
                block_destination->block_primitive_variables_->diss_res_vv_[cell_id_destination] = buffers_[i][N_VARIABLES+12][k];
                block_destination->block_primitive_variables_->diss_res_ww_[cell_id_destination] = buffers_[i][N_VARIABLES+13][k];
                block_destination->block_primitive_variables_->diss_res_pp_[cell_id_destination] = buffers_[i][N_VARIABLES+14][k];
                block_destination->block_primitive_variables_->ro_0_[cell_id_destination] = buffers_[i][N_VARIABLES+15][k];
                block_destination->block_primitive_variables_->ru_0_[cell_id_destination] = buffers_[i][N_VARIABLES+16][k];
                block_destination->block_primitive_variables_->rv_0_[cell_id_destination] = buffers_[i][N_VARIABLES+17][k];
                block_destination->block_primitive_variables_->rw_0_[cell_id_destination] = buffers_[i][N_VARIABLES+18][k];
                block_destination->block_primitive_variables_->re_0_[cell_id_destination] = buffers_[i][N_VARIABLES+19][k];

                block_destination->block_interpolation_variables_->limiter_ro_[cell_id_destination] = buffers_[i][N_VARIABLES+20][k];
                block_destination->block_interpolation_variables_->limiter_uu_[cell_id_destination] = buffers_[i][N_VARIABLES+21][k];
                block_destination->block_interpolation_variables_->limiter_vv_[cell_id_destination] = buffers_[i][N_VARIABLES+22][k];
                block_destination->block_interpolation_variables_->limiter_ww_[cell_id_destination] = buffers_[i][N_VARIABLES+23][k];
                block_destination->block_interpolation_variables_->limiter_pp_[cell_id_destination] = buffers_[i][N_VARIABLES+24][k];

                block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][0] = buffers_[i][N_VARIABLES+25][k];
                block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][1] = buffers_[i][N_VARIABLES+26][k];
                block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][2] = buffers_[i][N_VARIABLES+27][k];
                block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][0] = buffers_[i][N_VARIABLES+28][k];
                block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][1] = buffers_[i][N_VARIABLES+29][k];
                block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][2] = buffers_[i][N_VARIABLES+30][k];
                block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][0] = buffers_[i][N_VARIABLES+31][k];
                block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][1] = buffers_[i][N_VARIABLES+32][k];
                block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][2] = buffers_[i][N_VARIABLES+33][k];
                block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][0] = buffers_[i][N_VARIABLES+34][k];
                block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][1] = buffers_[i][N_VARIABLES+35][k];
                block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][2] = buffers_[i][N_VARIABLES+36][k];
                block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][0] = buffers_[i][N_VARIABLES+37][k];
                block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][1] = buffers_[i][N_VARIABLES+38][k];
                block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][2] = buffers_[i][N_VARIABLES+39][k];
            }
        }
    }

    #else
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        ConnexionCellIds* boundary = inter_block_boundaries_[i];
        int block_id_origin = boundary->block_origin_;
        int block_id_destination = boundary->block_destination_;
        int n_cells = boundary->n_cell_in_boundary_;
        Block* block_origin = mesh->all_blocks_[block_id_origin];
        Block* block_destination = mesh->all_blocks_[block_id_destination];

        for (int j = 0; j < n_cells; j++){
            int cell_id_origin = boundary->cell_ids_in_boundary_other_block_[j];
            int cell_id_destination = boundary->cell_ids_in_boundary_[j];

            block_destination->block_primitive_variables_->ro_[cell_id_destination] = block_origin->block_primitive_variables_->ro_[cell_id_origin];
            block_destination->block_primitive_variables_->uu_[cell_id_destination] = block_origin->block_primitive_variables_->uu_[cell_id_origin];
            block_destination->block_primitive_variables_->vv_[cell_id_destination] = block_origin->block_primitive_variables_->vv_[cell_id_origin];
            block_destination->block_primitive_variables_->ww_[cell_id_destination] = block_origin->block_primitive_variables_->ww_[cell_id_origin];
            block_destination->block_primitive_variables_->pp_[cell_id_destination] = block_origin->block_primitive_variables_->pp_[cell_id_origin];
            block_destination->block_primitive_variables_->conv_res_ro_[cell_id_destination] = block_origin->block_primitive_variables_->conv_res_ro_[cell_id_origin];
            block_destination->block_primitive_variables_->conv_res_uu_[cell_id_destination] = block_origin->block_primitive_variables_->conv_res_uu_[cell_id_origin];
            block_destination->block_primitive_variables_->conv_res_vv_[cell_id_destination] = block_origin->block_primitive_variables_->conv_res_vv_[cell_id_origin];
            block_destination->block_primitive_variables_->conv_res_ww_[cell_id_destination] = block_origin->block_primitive_variables_->conv_res_ww_[cell_id_origin];
            block_destination->block_primitive_variables_->conv_res_pp_[cell_id_destination] = block_origin->block_primitive_variables_->conv_res_pp_[cell_id_origin];
            block_destination->block_primitive_variables_->diss_res_ro_[cell_id_destination] = block_origin->block_primitive_variables_->diss_res_ro_[cell_id_origin];
            block_destination->block_primitive_variables_->diss_res_uu_[cell_id_destination] = block_origin->block_primitive_variables_->diss_res_uu_[cell_id_origin];
            block_destination->block_primitive_variables_->diss_res_vv_[cell_id_destination] = block_origin->block_primitive_variables_->diss_res_vv_[cell_id_origin];
            block_destination->block_primitive_variables_->diss_res_ww_[cell_id_destination] = block_origin->block_primitive_variables_->diss_res_ww_[cell_id_origin];
            block_destination->block_primitive_variables_->diss_res_pp_[cell_id_destination] = block_origin->block_primitive_variables_->diss_res_pp_[cell_id_origin];
            block_destination->block_primitive_variables_->ro_0_[cell_id_destination] = block_origin->block_primitive_variables_->ro_0_[cell_id_origin];
            block_destination->block_primitive_variables_->ru_0_[cell_id_destination] = block_origin->block_primitive_variables_->ru_0_[cell_id_origin];
            block_destination->block_primitive_variables_->rv_0_[cell_id_destination] = block_origin->block_primitive_variables_->rv_0_[cell_id_origin];
            block_destination->block_primitive_variables_->rw_0_[cell_id_destination] = block_origin->block_primitive_variables_->rw_0_[cell_id_origin];
            block_destination->block_primitive_variables_->re_0_[cell_id_destination] = block_origin->block_primitive_variables_->re_0_[cell_id_origin];

            block_destination->block_interpolation_variables_->limiter_ro_[cell_id_destination] = block_origin->block_interpolation_variables_->limiter_ro_[cell_id_origin];
            block_destination->block_interpolation_variables_->limiter_uu_[cell_id_destination] = block_origin->block_interpolation_variables_->limiter_uu_[cell_id_origin];
            block_destination->block_interpolation_variables_->limiter_vv_[cell_id_destination] = block_origin->block_interpolation_variables_->limiter_vv_[cell_id_origin];
            block_destination->block_interpolation_variables_->limiter_ww_[cell_id_destination] = block_origin->block_interpolation_variables_->limiter_ww_[cell_id_origin];
            block_destination->block_interpolation_variables_->limiter_pp_[cell_id_destination] = block_origin->block_interpolation_variables_->limiter_pp_[cell_id_origin];

            block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][0] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][0];
            block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][1] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][1];
            block_destination->block_interpolation_variables_->grad_ro_[cell_id_destination][2] = block_origin->block_interpolation_variables_->grad_ro_[cell_id_origin][2];
            block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][0] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][0];
            block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][1] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][1];
            block_destination->block_interpolation_variables_->grad_uu_[cell_id_destination][2] = block_origin->block_interpolation_variables_->grad_uu_[cell_id_origin][2];
            block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][0] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][0];
            block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][1] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][1];
            block_destination->block_interpolation_variables_->grad_vv_[cell_id_destination][2] = block_origin->block_interpolation_variables_->grad_vv_[cell_id_origin][2];
            block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][0] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][0];
            block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][1] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][1];
            block_destination->block_interpolation_variables_->grad_ww_[cell_id_destination][2] = block_origin->block_interpolation_variables_->grad_ww_[cell_id_origin][2];
            block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][0] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][0];
            block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][1] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][1];
            block_destination->block_interpolation_variables_->grad_pp_[cell_id_destination][2] = block_origin->block_interpolation_variables_->grad_pp_[cell_id_origin][2];
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
        else if (marker == "GhostCount="){
            liness >> ghost_index;
            if (boundary_started){
                save = true;
				boundary_started = false;
			}
        }

		if (boundary_started){
            cell_ids[boundary_index] = std::stoi(marker);
            ghost_ids[boundary_index] = ghost_index + boundary_index;
			boundary_index ++;
		}

		if (marker == "Nelems="){
			boundary_started = true;
			liness >> n_cells;

			cell_ids = new int[n_cells];
            ghost_ids = new int[n_cells];
            boundary_index = 0;

			boundary = new ConnexionCellIds();
			boundary->cell_count_ = nullptr;
            //std::cout << "Process " << process_id_ << " writes block destination " << block_destination << " and block origin " << block_origin << std::endl; // REMOVE
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

    /*if (process_id_ == 0){
    std::cout<<"----------------VÉRIFICATION CONNECTION AU MPI-----------------"<<std::endl;
    std::cout<<"Number of boundaries: "<<n_inter_block_boundaries_<<std::endl;
    for (int i=0;i<n_inter_block_boundaries_;i++)
    {
        std::cout<<"Boundary number: "<<i<<std::endl;
        std::cout<<"Block destination: "<<inter_block_boundaries_[i]->block_destination_<<" Block origin: "<<inter_block_boundaries_[i]->block_origin_<<" Number of cells in boundary: "<<inter_block_boundaries_[i]->n_cell_in_boundary_<<std::endl;
        std::cout<<"Cell ids in boundary\tCell ids in other boundary"<<std::endl;
        for (int j=0;j<inter_block_boundaries_[i]->n_cell_in_boundary_;j++)
        {
            std::cout<<cell_id_destination<<"\t\t\t\t"<<cell_id_origin<<std::endl;
        }
        std::cout<<endl;
    }
    }*/
}

void BlockCommunicator::initializeBuffers(){
    // Delete buffers_
    if (buffers_ != nullptr){
        for (int i = 0; i < n_inter_block_boundaries_; i++){
            if (buffers_[i] != nullptr){
                for (int j = 0; j < N_VARIABLES*2; j++){
                    if (buffers_[i][j] != nullptr){
                        delete [] buffers_[i][j];
                    }
                }
                delete [] buffers_[i];
            }
        }
        delete [] buffers_; // This line throws "munmap_chunk(): invalid pointer" on process 3 when there are 6 blocks and 6 processes. wtf
    }

    buffers_ = new double**[n_inter_block_boundaries_];
    for (int i = 0; i < n_inter_block_boundaries_; i++){
        buffers_[i] = new double*[N_VARIABLES*2];
        for (unsigned int j = 0; j < N_VARIABLES*2; j++){
            buffers_[i][j] = nullptr;
        }
    }

    for (int i = 0; i < n_inter_block_boundaries_; i++){
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_origin_]){
            for (unsigned int j = 0; j < N_VARIABLES; j++){
                buffers_[i][j] = new double[inter_block_boundaries_[i]->n_cell_in_boundary_];
            }
        }
        if (process_id_ == block_process_id_[inter_block_boundaries_[i]->block_destination_]){
            for (unsigned int j = N_VARIABLES; j < N_VARIABLES*2; j++){
                buffers_[i][j] = new double[inter_block_boundaries_[i]->n_cell_in_boundary_];
            }
        }
    }
}
