#ifndef BLOCKBUILDER_SRC_BLOCKBUILDER_CPP
#define BLOCKBUILDER_SRC_BLOCKBUILDER_CPP

#include "BlockBuilder.h"
#include "CellCreator.h"
#include "FaceCreator.h"
#include "NodeCreator.h"
#include "Cell.h"
#include "Node.h"
#include "Face.h"
#include "Block.h"
#include <iostream>
#include <string>

BlockBuilder::BlockBuilder()
{

}

BlockBuilder::~BlockBuilder()
{

}

void readMyBlocks(Block* block)
{
	


}

Cell* buildCell(string cell_type, CellCreator* creators)
{

	int key;
	Cell* new_cell;

	if (cell_type == "13")
	{
		key = 0;
	}
	else if (cell_type == "14")
	{
		key = 1;
	}
	else if (cell_type == "ghost")
	{
		key = 2;
	}

	new_cell = creators[key];
	return new_cell
}

void buildNode()
{

}

void buildFace(int face_type)
{

}

void setConnectivity(Block* block)
{

}

void setMetrics(Block* block)
{

}