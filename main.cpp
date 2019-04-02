#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"

#include <iostream>
#include <string>
#include <chrono>
#ifdef HAVE_MPI
#include <mpi.h>
#endif
#include "Block.h"
#include "ConcreteBlockBuilder.h"
#include "BlockCommunicator.h"
#include "CompleteMesh.h"

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
		exit(-1);
	}

	Interface* interface= new Interface(argv[1]);
	Initializer* initializer= new Initializer();

	int n_blocks_in_process;
    int* my_blocks;
    int n_blocks = 6;

	BlockCommunicator* communicator = new BlockCommunicator(n_blocks);
    communicator->getMyBlocks(n_blocks_in_process, my_blocks);

	cout << "I am process " << communicator->process_id_ << " and I have " << n_blocks_in_process << " blocks." << endl;

	cout << "In CompleteMesh........." << endl;
	CompleteMesh* complete_mesh = new CompleteMesh(n_blocks, n_blocks_in_process, my_blocks, interface->topology_file_name_interface_);
	complete_mesh->InitializeMyBlocks(interface);

	Solver *solver=initializer->initializeSolver(interface);

	auto t_start = std::chrono::high_resolution_clock::now();
    solver->solve(complete_mesh, communicator);
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed solving: " 
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()/1000.0 
            << "s." << std::endl;

	#ifdef HAVE_MPI
	MPI_Finalize();
	#endif
}
