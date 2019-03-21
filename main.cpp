#include "Block.h"

#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"


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

	if (argc > 1)
	{
		cout << "Input file is : " << argv[1] << endl;
	}
	else
	{
		cout << "ERROR: No input file" << endl;
		#ifdef HAVE_MPI
		MPI_Finalize();
		#endif
		exit(0);
	}

	Interface* interface= new Interface(argv[1]);
	Initializer* initializer= new Initializer();

	int n_blocks_in_process;
    int* my_blocks;
    int n_blocks = 1;

	BlockCommunicator* communicator = new BlockCommunicator(n_blocks);
    communicator->getMyBlocks(n_blocks_in_process, my_blocks);

	cout << "In CompleteMesh........." << endl;
	CompleteMesh* complete_mesh = new CompleteMesh(n_blocks, n_blocks_in_process, my_blocks, interface->topology_file_name_interface_);
	complete_mesh->InitializeMyBlocks();
	Block* new_block = complete_mesh->all_blocks_[0];

	cout << "In MetricsInitializer........." << endl;
	MetricsInitializer metricsInit(new_block);
	metricsInit.doInit();

	cout << "In calculateFreeVariables........." << endl;
	new_block->block_primitive_variables_->calculateFreeVariables(interface->gamma_interface_, interface->aoa_deg_interface_, interface->mach_aircraft_interface_);

	cout << "In initializeFlowField........." << endl;
	new_block->block_primitive_variables_->initializeFlowField(new_block->n_all_cells_in_block_);

	cout << "In Solver........." << endl;
	Solver *solver=initializer->initializeSolver(interface);
	solver->solve(new_block, complete_mesh);

	#ifdef HAVE_MPI
	MPI_Finalize();
	#endif
}