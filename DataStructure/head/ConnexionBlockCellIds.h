#ifndef DATASTRUCTURE_HEAD_CONNEXIONBLOCKCELLIDS_H
#define DATASTRUCTURE_HEAD_CONNEXIONBLOCKCELLIDS_H

#include "BoundaryCellIds.h"

class ConnexionBlockCellIds : public BoundaryCellIds
{
public:
	ConnexionBlockCellIds();
	~ConnexionBlockCellIds();

	void updateBoundary();
	
};

#endif