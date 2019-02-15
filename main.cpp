#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include "BlockCommunicator.h"

int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    DummyMesh* mesh = new DummyMesh(5);

    BlockCommunicator* communicator = new BlockCommunicator(mesh);

    communicator->getMyBlocks(mesh);

    // Print off a hello world message
    std::cout << "Hello from process " << communicator->process_id_ << " out of " 
                    << communicator->number_of_processes_ << " processes." << std::endl;

    int* proc_list = nullptr;
    if (communicator->process_id_ == 0){
        proc_list = new int[communicator->number_of_processes_];
    }

    MPI_Gather(&communicator->process_id_, 1, MPI_INT, proc_list, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (communicator->process_id_ == 0){
        std::cout << "World content:";
        for (int i = 0; i < communicator->number_of_processes_; i++){
            std::cout << " " << proc_list[i];
        }
        std::cout << std::endl;

        delete[] proc_list; 
    }

    // Test exchanges

    delete mesh;
    delete communicator;

    // Finalize the MPI environment.
    MPI_Finalize();
}
