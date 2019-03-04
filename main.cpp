#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include "BlockCommunicator.h"
#include <fstream>
#include <sstream>
#include "ConnexionCellIds_dummy.h"

int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    int n_blocks_in_process;
    int* my_blocks;
    int n_blocks;

    n_blocks = 5;
    BlockCommunicator* communicator = new BlockCommunicator(n_blocks);
    communicator->getMyBlocks(n_blocks_in_process, my_blocks);

    DummyMesh* mesh = new DummyMesh(n_blocks, n_blocks_in_process, my_blocks);

    int coord00[3] = {7, 8, 9};
    int coord01[3] = {2, 3, 4};
    ConnexionCellIds_dummy* boundary0 = new ConnexionCellIds_dummy(coord00, 3, coord01, 1, 0);
    int coord10[3] = {7, 8, 9};
    int coord11[3] = {0, 1, 2};
    ConnexionCellIds_dummy* boundary1 = new ConnexionCellIds_dummy(coord10, 3, coord11, 0, 1);

    int coord20[2] = {5, 6};
    int coord21[2] = {3, 4};
    ConnexionCellIds_dummy* boundary2 = new ConnexionCellIds_dummy(coord20, 2, coord21, 2, 1);
    int coord30[2] = {7, 8};
    int coord31[2] = {0, 1};
    ConnexionCellIds_dummy* boundary3 = new ConnexionCellIds_dummy(coord30, 2, coord31, 1, 2);

    communicator->addCellIdInConnexion(boundary0);
    communicator->addCellIdInConnexion(boundary1);
    communicator->addCellIdInConnexion(boundary2);
    communicator->addCellIdInConnexion(boundary3);


    // Print off a hello world message
    std::cout << "Hello from process " << communicator->process_id_ << " out of " 
                    << communicator->number_of_processes_ << " processes. I have " 
                    << mesh->n_blocks_in_process_;
    if (mesh->n_blocks_in_process_ > 1){
        std::cout << " blocks.";
    }
    else{
        std::cout << " block.";
    } 

    for (int i = 0; i < mesh->n_blocks_in_process_; i++){
        std::cout << " " << mesh->my_blocks_[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < mesh->n_blocks_in_process_; i++){
        mesh->blocks_[mesh->my_blocks_[i]]->fillBlock(mesh->my_blocks_[i]);
    }

    communicator->updateBoundaries(mesh);

    std::ofstream myfile;
    std::stringstream filename;
    for (int i = 0; i < mesh->n_blocks_in_process_; i++){
        filename.str(std::string());
        filename << "output" << mesh->my_blocks_[i] << ".txt";
        myfile.open(filename.str());
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
