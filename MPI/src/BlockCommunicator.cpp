#include "BlockCommunicator.h"
#include <mpi.h>

BlockCommunicator::BlockCommunicator(DummyMesh* mesh) : mesh_(mesh) {
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes_);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id_);
}

BlockCommunicator::~BlockCommunicator(){
    
}

void BlockCommunicator::updateBoundaries() const {

}

void BlockCommunicator::addCellIdInConnexion(){

}

void BlockCommunicator::getMyBlocks(int &n_blocks, int* my_blocks) const {
    
}

void BlockCommunicator::initialize(){

}

double BlockCommunicator::getGlobal(double const coeff_local) const {
    return 0.0;
}

void BlockCommunicator::setBoundaryOffset(){

}