#include <mpi.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    int* proc_list = nullptr;
    if (world_rank == 0){
        proc_list = new int[world_size];
    }

    MPI_Gather(&world_rank, 1, MPI_INT, proc_list, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (world_rank == 0){
        std::cout << "World content:";
        for (int i = 0; i < world_size; i++){
            std::cout << " " << proc_list[i];
        }
        std::cout << std::endl;

        delete[] proc_list; 
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
