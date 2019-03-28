#ifndef DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H
#define DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H

#include "BoundaryCellIds.h"

class ConnexionCellIds : public BoundaryCellIds
{
public:
	int owner_block_id_;
	int connected_block_id_;
	int* cell_count_connected_;
	int n_cell_in_boundary_connected_;
	int* cell_ids_in_boundary_connected_;
	ConnexionCellIds();
	~ConnexionCellIds();

	void updateBoundary();
	
};

#endif