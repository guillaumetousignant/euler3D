#ifndef DATASTRUCTURE_HEAD_WALLCELLIDS_H
#define DATASTRUCTURE_HEAD_WALLCELLIDS_H

#include "BoundaryCellIds.h"

class WallCellIds : public BoundaryCellIds
{
public:
	WallCellIds();
	~WallCellIds();

	void updateBoundary();
	
};

#endif