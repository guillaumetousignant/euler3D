#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"
#include "BlockCommunicator.h"
#include "CompleteMesh.h"

#include <iostream>
#include <string>
#include <chrono>
//#include <omp.h>  // not needed for pragma, and adds dependency
#ifdef HAVE_MPI
#include <mpi.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
	#ifdef HAVE_MPI
	MPI_Init(NULL, NULL);
	int process_id_temp;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_id_temp);
	#else
	int process_id_temp = 0;
	#endif

	if (process_id_temp == 0){
		//i_print = true;
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
	}

	if (argc > 1)
	{
		if (process_id_temp == 0){
			cout << "Input file is : " << argv[1] << endl;
		}
	}
	else
	{
		if (process_id_temp == 0){
			cout << "ERROR: No input file" << endl;
		}
		#ifdef HAVE_MPI
		MPI_Finalize();
		#endif
		exit(-1);
	}

	Interface* interface= new Interface(argv[1], (process_id_temp == 0));
	Initializer* initializer= new Initializer();

	int n_blocks=interface->n_blocks_interface_;


	int n_blocks_in_process;
    int* my_blocks;

	BlockCommunicator* communicator = new BlockCommunicator(n_blocks);
    communicator->getMyBlocks(n_blocks_in_process, my_blocks);

	if (communicator->process_id_ == 0){
		cout << "I am process " << communicator->process_id_ << " and I have " << n_blocks_in_process << " blocks." << endl;
		cout << "In CompleteMesh........." << endl;
	}

	CompleteMesh* complete_mesh = new CompleteMesh(n_blocks, n_blocks_in_process, my_blocks, interface->topology_file_name_interface_);
	complete_mesh->InitializeMyBlocks(interface, communicator);



	//communicator->createBoundaries(complete_mesh->topology_file_name_);
	communicator->initializeBuffers();

	if (communicator->process_id_ == 0){
		std::cout << "Initialisation du Solver" << std::endl << std::endl;
	}
	Solver *solver=initializer->initializeSolver(interface);

	auto t_start = std::chrono::high_resolution_clock::now();
    solver->solve(complete_mesh, communicator);
    auto t_end = std::chrono::high_resolution_clock::now();
	if (communicator->process_id_ == 0){
		std::cout << "Time elapsed solving: "
			<< std::chrono::duration<double, std::milli>(t_end-t_start).count()/1000.0
			<< "s." << std::endl;
	}

	#ifdef HAVE_MPI
	MPI_Finalize();
	#endif
}
