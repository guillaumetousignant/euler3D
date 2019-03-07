#ifndef DATASTRUCTURE_HEAD_BOUNDARYCELLIDS_H
#define DATASTRUCTURE_HEAD_BOUNDARYCELLIDS_H
class Block;
#include "Block.h"
class BoundaryCellIds
{
public:
	int* cell_count_;
	int n_cell_in_boundary_;
	int* cell_ids_in_boundary_;
	Block* owner_block_;

	virtual void updateBoundary() = 0;

	BoundaryCellIds();
	~BoundaryCellIds();
	
};

#endif
