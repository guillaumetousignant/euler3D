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

    
    // Cell* test_cell;
    // test_cell = new_block ->block_cells_[12];
    // cout<<test_cell->cell_2_nodes_connectivity_[1]<<endl;
    // Node* test_node;
    // test_node = new_block ->block_nodes_[12];
    // cout<<test_node->node_coordinates_[1]<<endl;
    // cout<<test_node->node_coordinates_[2]<<endl;


}
