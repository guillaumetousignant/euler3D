#ifndef SOLVERSKELETON_SRC_TESTMAIN_CPP
#define SOLVERSKELETON_SRC_TESTMAIN_CPP

#include "Block.h"

#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"
#include "BlockCommunicator.h"


#include <iostream>
#include <string>
#ifdef MPI_VERSION
#include <mpi.h>
#endif
using namespace std;

int main()
{
	#ifdef MPI_VERSION
	MPI_Init(NULL, NULL);
	#endif

    int n_blocks_in_process;
    int* my_blocks;
    int n_blocks;
    int test_block;

	cout << "This is the main" << endl;

    n_blocks = 5;
	test_block=69;
	Block* block= new Block(test_block);
	CompleteMesh* complete_mesh;
  	complete_mesh= new CompleteMesh();
	Initializer* initializer= new Initializer();
	Interface* interface= new Interface();

    BlockCommunicator* communicator = new BlockCommunicator(n_blocks);
    communicator->getMyBlocks(n_blocks_in_process, my_blocks);

	Solver *solver=initializer->initializeSolver(interface);
	solver->solve(block, complete_mesh);


	// Initialize the MPI environment


	// Finalize the MPI environment.
	#ifdef MPI_VERSION
	MPI_Finalize();
	#endif


	/*
	double gamma=1.5;
	double cfl=1.0;
	int stage_number=5;
	double alpha_rk[5]={420,420,420,420,420};
	double beta_rk[5]={1337,1337,1337,1337,1337};
	string interpolation_choice = "Second";
	string gradient_choice = "Least Squares";
	string limiter_choice = "Venkatakrishnan";
	string flux_scheme_choice = "Roe";
	string residual_smoother_choice = "Central IRS";



	Solver *solver= new Solver(gamma, cfl, stage_number, alpha_rk, beta_rk, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice);

	cout<<"Salut"<<endl;
	cout<<solver->gamma_<<endl;
	cout<<solver->runge_kutta_->alpha_rk_[1]<<endl;
	cout<<solver->runge_kutta_->beta_rk_[1]<<endl;
	cout<<block->test_block_<<endl;


	solver->solve(block);

	cout<<block->test_block_<<endl;
	*/

}


#endif