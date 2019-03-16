#ifndef DUMMY_BLOCKCOMMUNICATOR_H
#define DUMMY_BLOCKCOMMUNICATOR_H

#include "Cell.h"
#include "Face.h"
#include "Node.h"
class BoundaryCellIds;
#include "TimeVariables.h"
#include "PrimitiveVariables.h"
#include "InterpolationVariables.h"
#include "BoundaryCellIds.h"
#include "ConnexionCellIds.h"
#include "FarfieldCellIds.h"
#include "WallCellIds.h"
#include "CompleteMesh.h"

 class BlockCommunicator
 {
 public:

 	int n_inter_block_boundaries_;
 	BoundaryCellIds* inter_block_boundaries_;

 	void updateBoundaries(CompleteMesh* mesh);

	BlockCommunicator();
	~BlockCommunicator();
 };


#endif