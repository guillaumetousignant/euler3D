#include "Block.h"

#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"
#include "MetisMesh.h"
#include "ReconstructFaces.h"

#include <iostream>
#include <string>
#ifdef HAVE_MPI
#include <mpi.h>
#endif
#include "Block.h"
#include "ConcreteBlockBuilder.h"
#include "BlockCommunicator.h"
#include "CompleteMesh.h"
#include "MetricsInitializer.h"

using namespace std;

int main(int argc, char* argv[])
{
	#ifdef HAVE_MPI
	MPI_Init(NULL, NULL);
	#endif

	cout << "========================STARTING PROGRAM========================" << endl;

	cout << R"(
		           (        (
		           )\ )     )\ )
		 (      ( (()/( (  (()/(
		 )\     )\ /(_)))\  /(_))
		((_) _ ((_|_)) ((_)(_))
		| __| | | | |  | __| _ \
		| _|| |_| | |__| _||   /
		|___|\___/|____|___|_|_\


	)" << endl;


	// if (argc > 1)
	// {
	// 	cout << "Input file is : " << argv[1] << endl;
	// }
	// else
	// {
	// 	cout << "ERROR: No input file" << endl;
	// 	exit(0);
	// }

	MPI_Init(NULL, NULL);

	// MPI_Finalize();
	//
	// Interface* interface= new Interface(argv[1]);
	// Initializer* initializer= new Initializer();
	//
	// int* my_blocks = new int[1];
	// my_blocks[0] = 0;
	//
	// cout << "In CompleteMesh........." << endl;
	// CompleteMesh* complete_mesh = new CompleteMesh(1,1,my_blocks, interface->topology_file_name_interface_);
	// complete_mesh->InitializeMyBlocks();
	// Block* new_block = complete_mesh->all_blocks_[0];
	//
	// cout << "In MetricsInitializer........." << endl;
	// MetricsInitializer metricsInit(new_block);
	// metricsInit.doInit();
	//
	// cout << "In calculateFreeVariables........." << endl;
	// new_block->block_primitive_variables_->calculateFreeVariables(interface->gamma_interface_, interface->aoa_deg_interface_, interface->mach_aircraft_interface_);
	//
	// cout << "In initializeFlowField........." << endl;
	// new_block->block_primitive_variables_->initializeFlowField(new_block->n_all_cells_in_block_);
	//
	// cout << "In Solver........." << endl;
	// Solver *solver=initializer->initializeSolver(interface);
	// solver->solve(new_block, complete_mesh);

    // Finalize the MPI environment.
    MPI_Finalize();



/*=============================TEST HELENE=============================
		int n_blocks = 2;
		int global_n_elements = 10;

ReconstructFaces reconstruct_faces = ReconstructFaces(n_blocks, global_n_elements);


std::vector<int> common_nodes_vector;
int first_block_id = 0;
int* first_block_node_array = new int[8] {0,1,2,3,4,5,8,9};
int n_nodes_in_first_block = 8;

int second_block_id =1;
int* second_block_node_array = new int[6] {1,2,3,4,6,7};
int n_nodes_in_second_block = 6;


common_nodes_vector = reconstruct_faces.CompareArraysOfGlobalNodes(  first_block_id,  first_block_node_array,  n_nodes_in_first_block,  second_block_id,  second_block_node_array, n_nodes_in_second_block);

std::vector<int>** global_cells_vector =

FindElementsInConnexion(std::vector<int> common_nodes_vector, std::vector<int>** global_cells_vector, std::vector<int>** global_nodes_vector, int block_id )


reconstruct_faces.~ReconstructFaces();
=============================TEST HELENE=============================*/

if (argc != 4)
{
	std::cout << "Usage: ./metis <single block mesh file> <Number of partitions> <Output mesh file name>\n";
	return 0;
}

  //Metis' routine

  //Input arguments
std::string meshFile = argv[1];
int nPart = atoi(argv[2]);
std::string outputMeshFile = argv[3];


MetisMesh reader;
reader.ReadSingleBlockMesh(meshFile);

int n_blocks =nPart;
int* global_n_elements = reader.getnNodes_();


MetisMesh* newMesh = reader.Partition(nPart);

ReconstructFaces reconstruct_faces = ReconstructFaces(n_blocks, global_n_elements[0]);
std::vector<int> common_nodes_vector;

for(int k=0; k<n_blocks; k++)
{
	for(int l=-; l<n_blocks;l++)
	{
		if(reconstruct_faces.block_array_4_comparaison_[i][j]!=1)
		{
			int first_block_id = i;
			int second_block_id = j;
			
			common_nodes_vector = reconstruct_faces.CompareArraysOfGlobalNodes(  first_block_id,  first_block_node_array,  n_nodes_in_first_block,  second_block_id,  second_block_node_array, n_nodes_in_second_block);
		}
	}

}




newMesh->WriteMesh(outputMeshFile);
cout << "asdswf" << endl;

}

		cout << "In Solver........." << endl;
		
	}

	Solver *solver=initializer->initializeSolver(interface);
	solver->solve(complete_mesh, communicator);

	#ifdef HAVE_MPI
	MPI_Finalize();
	#endif
}
