#ifndef DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H
#define DATASTRUCTURE_HEAD_CONNEXIONCELLIDS_H

#include "BoundaryCellIds.h"

class ConnexionCellIds : public BoundaryCellIds
{
public:
	ConnexionCellIds();
	~ConnexionCellIds();

	void updateBoundary();
	
};

#endif