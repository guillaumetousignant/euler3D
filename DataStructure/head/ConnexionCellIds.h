#ifndef DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H
#define DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H

#include "BoundaryCellIds.h"

class ConnexionCellIds : public BoundaryCellIds
{
public:
	ConnexionCellIds();
	~ConnexionCellIds();

	int* cell_ids_in_boundary_other_block_;
	int block_origin_;
	int block_destination_;

	void updateBoundary();
};

#endif