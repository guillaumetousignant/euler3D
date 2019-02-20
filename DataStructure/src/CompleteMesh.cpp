#ifndef DATASTRUCTURE_SRC_COMPLETEMESH_CPP
#define DATASTRUCTURE_SRC_COMPLETEMESH_CPP

#include "CompleteMesh.h"
#include "Block.h"
#include <string>
#include <iostream>
using namespace std;

CompleteMesh::CompleteMesh(int n_blocks, int n_blocks_in_process, int my_blocks[], Block all_blocks[])

{
		n_blocks_=n_blocks;
		n_blocks_in_process_=n_blocks_in_process;
		my_blocks_=my_blocks;
		all_blocks_=all_blocks;
}


CompleteMesh::~CompleteMesh()
{

}