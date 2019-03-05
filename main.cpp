#include <iostream>
#include <mpi.h>
#include "Block.h"
#include "ConcreteBlockBuilder.h"


using namespace std;

int main()
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    cout << "This is the main" << endl;
    
    // Finalize the MPI environment.
    MPI_Finalize();

    Block* new_block = new Block(0);
    string block_file ="../MeshTest5x5.su2";
    ConcreteBlockBuilder concrete_block_builder = ConcreteBlockBuilder(block_file);

    concrete_block_builder.readMyBlock(new_block);
}
