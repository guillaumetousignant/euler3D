#ifndef DATASTRUCTURE_HEAD_COMPLETEMESH_H
#define DATASTRUCTURE_HEAD_COMPLETEMESH_H

#include <string>
#include "Block.h"
#include "BlockCommunicator.h"
using namespace std;

class Interface;
class BlockCommunicator;

class CompleteMesh
{
public:
	int n_blocks_;
	int n_blocks_in_process_;
	int* my_blocks_;
	Block** all_blocks_;
	string topology_file_name_;

	CompleteMesh(int n_blocks, int n_block_in_process, int* my_blocks, string topology_file_name);
	~CompleteMesh();
	void InitializeMyBlocks(Interface* interface, BlockCommunicator* communicator);
	void RecomputeConnexionInterVect(BlockCommunicator* communicator);
	string getBlockFileName(int block_id);

};

#endif
