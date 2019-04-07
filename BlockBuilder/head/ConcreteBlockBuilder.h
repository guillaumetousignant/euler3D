
#ifndef BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H

#include <string>
#include "BlockBuilder.h"
#include "NodeCreator.h"
#include "FaceCreator.h"
#include "TempFaceCreator.h"
// #include "TempGhostFaceCreator.h"
#include "TempPyramidFaceCreator.h"
#include "TempPrismFaceCreator.h"
#include "TempTetrahedralFaceCreator.h"
#include "CellCreator.h"
#include "GhostCellCreator.h"
#include "PyramidCellCreator.h"
#include "PrismCellCreator.h"
#include "TetrahedralCellCreator.h"
#include "BoundaryCellIds.h"
#include "FarfieldCellIds.h"
#include "WallCellIds.h"
#include "SymmetryCellIds.h"


#include "BlockCommunicator.h"






class ConcreteBlockBuilder:public BlockBuilder
{
public:
	ConcreteBlockBuilder(std::string block_file, std::string topology_file);
	~ConcreteBlockBuilder();

	void preReadMyBlock(Block* block);
	void readMyBlock(Block* block, BlockCommunicator* block_communicator);
	void createMyFaces(Block* block);
	void setTopology(Block* block, BlockCommunicator* block_communicator, int count_connexions);


};

#endif