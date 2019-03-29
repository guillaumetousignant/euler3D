#ifndef DATASTRUCTURE_HEAD_SYMMETRYCELLIDS_H
#define DATASTRUCTURE_HEAD_SYMMETRYCELLIDS_H

#include "BoundaryCellIds.h"

class SymmetryCellIds : public BoundaryCellIds
{
public:
	SymmetryCellIds();
	~SymmetryCellIds();

	void updateBoundary();
	
};

#endif