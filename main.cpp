
#include <iostream>
#include <mpi.h>
#include "Block.h"
#include "ConcreteBlockBuilder.h"
#include "Metrics/src/MetricsInitializer.h"


using namespace std;

int main()
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    cout << "This is the main" << endl;
    
    // Finalize the MPI environment.
    MPI_Finalize();

    Block* new_block = new Block(0);
    string block_file ="../UnstructuredMesh5x5.su2";
    // string block_file ="../TestMesh2x1.su2";

    ConcreteBlockBuilder concrete_block_builder = ConcreteBlockBuilder(block_file);
    concrete_block_builder.preReadMyBlock(new_block);
    concrete_block_builder.readMyBlock(new_block);

    concrete_block_builder.createMyFaces(new_block);

    concrete_block_builder.setConnectivity(new_block);

    MetricsInitializer metricsInit(new_block);
    metricsInit.doInit();  
/*
    cout<<"Cellules\n";
    Cell* test_cell;
    for(int i=0;i<new_block->n_real_cells_in_block_;i++)
    {
    	test_cell = new_block ->block_cells_[i];
    	cout<<"cell_id_\t"<<test_cell->cell_id_<<endl;
	    cout<<"cell_2_nodes_connectivity_\t"<<test_cell->cell_2_nodes_connectivity_[0]<<"\t"<<test_cell->cell_2_nodes_connectivity_[1]<<"\t"<<test_cell->cell_2_nodes_connectivity_[2]<<"\t"<<test_cell->cell_2_nodes_connectivity_[3]<<"\t"<<test_cell->cell_2_nodes_connectivity_[4]<<"\t"<<test_cell->cell_2_nodes_connectivity_[5]<<"\t"<<test_cell->cell_2_nodes_connectivity_[6]<<"\t"<<test_cell->cell_2_nodes_connectivity_[7]<<endl;
	    cout<<"n_nodes_per_cell_\t"<<test_cell->n_nodes_per_cell_<<endl;
	    cout<<"n_faces_per_cell_\t"<<test_cell->n_faces_per_cell_<<endl;
	    cout<<"block_id_\t"<<test_cell->block_id_<<endl;
    }

    for(int i=new_block->n_real_cells_in_block_;i<new_block->n_all_cells_in_block_;i++)
    {
    	test_cell = new_block ->block_cells_[i];
    	cout<<"cell_id_\t"<<test_cell->cell_id_<<endl;
	    cout<<"cell_2_nodes_connectivity_\t"<<test_cell->cell_2_nodes_connectivity_[0]<<"\t"<<test_cell->cell_2_nodes_connectivity_[1]<<"\t"<<test_cell->cell_2_nodes_connectivity_[2]<<"\t"<<test_cell->cell_2_nodes_connectivity_[3]<<endl;
	    cout<<"n_nodes_per_cell_\t"<<test_cell->n_nodes_per_cell_<<endl;
	    cout<<"n_faces_per_cell_\t"<<test_cell->n_faces_per_cell_<<endl;
	    cout<<"block_id_\t"<<test_cell->block_id_<<endl;
    }

    // test_cell = new_block ->block_cells_[12];
    // cout<<test_cell->cell_2_nodes_connectivity_[1]<<endl;
    cout<<"Noeuds\n";
    Node* test_node;
    for(int i=0;i<new_block->n_nodes_in_block_;i++)
    {
    	test_node = new_block ->block_nodes_[i];
    	cout<<"node_id_\t"<<test_node->node_id_<<endl;
	    cout<<"node_coordinates_\t"<<test_node->node_coordinates_[0]<<"\t"<<test_node->node_coordinates_[1]<<"\t"<<test_node->node_coordinates_[2]<<endl;
	    cout<<"block_id_\t"<<test_node->block_id_<<endl;
    }
    // test_node = new_block ->block_nodes_[12];
    // cout<<test_node->node_coordinates_[1]<<endl;
    // cout<<test_node->node_coordinates_[2]<<endl;
    Face* test_face;
    cout<<"Faces\n";
    for(int i=0;i<new_block->n_faces_in_block_;i++)
    {
    	test_face = new_block ->block_faces_[i];
    	cout<<"face_id_\t"<<test_face->face_id_<<endl;
	    cout<<"face_2_nodes_connectivity_\t"<<test_face->face_2_nodes_connectivity_[0]<<"\t"<<test_face->face_2_nodes_connectivity_[1]<<"\t"<<test_face->face_2_nodes_connectivity_[2]<<"\t"<<test_face->face_2_nodes_connectivity_[3]<<endl;
	    cout<<"n_nodes_per_face_\t"<<test_face->n_nodes_per_face_<<endl;
	    cout<<"block_id_\t"<<test_face->block_id_<<endl;
    }

*/

        cout<<"HAAAAAAAAAAAAAAAAAAAAAAAA Si tu m'entends crier c'est que le code a roulé au complet, en parlant de rouler, connais-tu le concours déroule le rebors, Tim Hortons offre un service et des produits de qualité à un prix qui fait envier"<<endl;

    // for (int i=0; i<new_block->n_real_boundaries_in_block_;i++) 
    // {
    //     std::cout << "test de boundary: "<< ((new_block->block_boundary_cell_ids_[i])->n_cell_in_boundary_) <<std::endl;
    //     (new_block->block_boundary_cell_ids_[i])->updateBoundary();
    // }
    // std::cout << "test de boundary deep: "<< new_block->n_real_boundaries_in_block_ <<std::endl;


}
