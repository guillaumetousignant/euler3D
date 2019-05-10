#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"
#include "BlockCommunicator.h"
#include "CompleteMesh.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
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

	communicator->sync();
	communicator->passConnexionCellCenters(complete_mesh);

	complete_mesh->RecomputeConnexionInterVect(communicator);

	for (int i=0;i<communicator->n_inter_block_boundaries_;i++)
	{
		for (int k=0; k<complete_mesh->n_blocks_in_process_; k++)
		{
			if (communicator->inter_block_boundaries_[i]->block_destination_==complete_mesh->my_blocks_[k])
			{
				std::string filename = "B" + to_string(communicator->inter_block_boundaries_[i]->block_destination_) + "OW" + to_string(i) + ".dat";
  			std::ofstream tempf;
  			tempf.open("./bin/" + filename);
				tempf << "BLOCK OWNER: " << communicator->inter_block_boundaries_[i]->block_destination_ << " OF BOUNDARY: " << i << endl;
				tempf << "centers: " << endl;
				for (int j=0; j<communicator->inter_block_boundaries_[i]->n_cell_in_boundary_;j++)
				{
				tempf << "Xowner: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_destination_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_[j]]->cell_coordinates_[0]<<endl;
				tempf << "Yowner: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_destination_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_[j]]->cell_coordinates_[1]<<endl;
				tempf << "Zowner: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_destination_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_[j]]->cell_coordinates_[2]<<endl;
				}
				tempf.close();
			}
		}

		for (int k=0; k<complete_mesh->n_blocks_in_process_; k++)
		{
			if (communicator->inter_block_boundaries_[i]->block_origin_==complete_mesh->my_blocks_[k])
			{
				std::string filename = "B" + to_string(communicator->inter_block_boundaries_[i]->block_origin_) + "OT" + to_string(i) + ".dat";
  			std::ofstream tempf;
  			tempf.open("./bin/" + filename);
				tempf << "BLOCK OTHER: " << communicator->inter_block_boundaries_[i]->block_origin_ << " OF BOUNDARY: " << i << endl;
				tempf << "centers: " << endl;
				for (int j=0; j<communicator->inter_block_boundaries_[i]->n_cell_in_boundary_;j++)
				{
				tempf << "Xother: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_origin_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]->cell_coordinates_[0]<<endl;
				tempf << "Yother: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_origin_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]->cell_coordinates_[1]<<endl;
				tempf << "Zother: " << complete_mesh->all_blocks_[communicator->inter_block_boundaries_[i]->block_origin_]->block_cells_[communicator->inter_block_boundaries_[i]->cell_ids_in_boundary_other_block_[j]]->cell_coordinates_[2]<<endl;
				}
				tempf.close();
			}
		}
	}

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
