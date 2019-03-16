#ifndef SOLVERSKELETON_SRC_TESTMAIN_CPP
#define SOLVERSKELETON_SRC_TESTMAIN_CPP

#include "Block.h"

#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"


#include <iostream>
#include <string>
#include <mpi.h>
#include "Block.h"
#include "ConcreteBlockBuilder.h"
#include "CompleteMesh.h"
#include "Metrics/src/MetricsInitializer.h"


using namespace std;

int main()
{
	MPI_Init(NULL, NULL);

	cout << "This is the main" << endl;

	MPI_Finalize();

  // Block* new_block = new Block(0);
  // string block_file ="../UnstructuredMesh5x5.su2";
  // // string block_file ="../TestMesh2x1.su2";


	int* my_blocks = new int[1];
	my_blocks[0] = 0;
	CompleteMesh* complete_mesh = new CompleteMesh(1,1,my_blocks);
	complete_mesh->InitializeMyBlocks();

	Block* new_block = complete_mesh->all_blocks_[0]; // hard coded right now
	//concrete_block_builder.setConnectivity(new_block);
	MetricsInitializer metricsInit(new_block);
	metricsInit.doInit();

  // ConcreteBlockBuilder concrete_block_builder = ConcreteBlockBuilder(block_file);
  // concrete_block_builder.preReadMyBlock(new_block);
  // concrete_block_builder.readMyBlock(new_block);
	//
  // concrete_block_builder.createMyFaces(new_block);
	//
  // concrete_block_builder.setConnectivity(new_block);
	//
  // MetricsInitializer metricsInit(new_block);
  // metricsInit.doInit();

	// CompleteMesh* complete_mesh;
  // complete_mesh= new CompleteMesh();
	// Initializer* initializer= new Initializer();
	// Interface* interface= new Interface();
	//
	// Solver *solver=initializer->initializeSolver(interface);
	// solver->solve(block, complete_mesh);

    cout << "END OF PROGRAM" << endl;
}


#endif
