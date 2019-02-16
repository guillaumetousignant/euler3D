#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include "BlockCommunicator.h"
#include <fstream>

int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    DummyMesh* mesh = new DummyMesh(5);

    BlockCommunicator* communicator = new BlockCommunicator(mesh);

    communicator->getMyBlocks(mesh);

    // Print off a hello world message
    std::cout << "Hello from process " << communicator->process_id_ << " out of " 
                    << communicator->number_of_processes_ << " processes. I have " 
                    << mesh->n_my_blocks_;
    if (mesh->n_my_blocks_ > 1){
        std::cout << " blocks.";
    }
    else{
        std::cout << " block.";
    } 
    std::cout << std::endl;

    for (int i = 0; i < mesh->n_my_blocks_; i++){
        mesh->blocks_[mesh->my_blocks_[i]]->fillBlock(i);
    }

    communicator->updateBoundaries(mesh);

    std::ofstream myfile;
    std::string filename;
    for (int i = 0; i < mesh->n_my_blocks_; i++){
        filename = "example" + mesh->my_blocks_[i] + ".txt";
        myfile.open(filename);
            for (int j = 0; j < 10; j++){
                myfile << mesh->blocks_[mesh->my_blocks_[i]]->boundary_values_[j] << std::endl;
            }    
        myfile.close();
    }

    // Gather test
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

        std::cout << "Blocks ownership:";
        for (int i = 0; i < communicator->n_blocks_; i++){
            std::cout << " " << communicator->block_process_id_[i];
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
