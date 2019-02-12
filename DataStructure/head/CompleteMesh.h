#ifndef DATASTRUCTURE_HEAD_COMPLETEMESH_H
#define DATASTRUCTURE_HEAD_COMPLETEMESH_H

#include Block.h

class CompleteMesh
{
public:
	int n_blocks_;
	int n_block_in_process_;
	int* my_blocks_;
	Block* all_blocks_;
	
	CompleteMesh();
	~CompleteMesh();
	
};

#endif