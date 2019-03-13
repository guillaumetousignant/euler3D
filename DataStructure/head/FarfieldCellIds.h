#ifndef DATASTRUCTURE_HEAD_FARFIELDCELLIDS_H
#define DATASTRUCTURE_HEAD_FARFIELDCELLIDS_H

#include "BoundaryCellIds.h"

class FarfieldCellIds : public BoundaryCellIds
{
public:
	FarfieldCellIds();
	~FarfieldCellIds();

	void updateBoundary();
	
};

#endif