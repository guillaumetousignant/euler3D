#ifndef BLOCKBUILDER_HEAD_BLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_BLOCKBUILDER_H

#include "CellCreator.h"
#include "FaceCreator.h"
#include "NodeCreator.h"
#include "Cell.h"
#include "Node.h"
#include "Face.h"
#include "Block.h"
#include <fstream>

class BlockBuilder
{
public:
	FILE* block_file_;

	BlockBuilder(FILE* block_file);
	~BlockBuilder();

	virtual void readMyBlock(Block* block) = 0;

	Cell* buildCell(int cell_type);
	void buildNode(int node_id,double node_coordinates[3], NodeCreator* node_creator);
	void buildFace(int face_type);
	void setConnectivity(Block* block);
	void setMetrics(Block* block);
	
};
#endif