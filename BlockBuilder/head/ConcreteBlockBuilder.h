#ifndef BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H

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





class ConcreteBlockBuilder:public BlockBuilder
{
public:
	ConcreteBlockBuilder(std::string block_file);
	~ConcreteBlockBuilder();

	void readMyBlock(Block* block);
	void createMyFaces(Block* block);


};

#endif