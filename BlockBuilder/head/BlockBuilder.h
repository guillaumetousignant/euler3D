#ifndef BLOCKBUILDER_HEAD_BLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_BLOCKBUILDER_H

#include "Block.h"
#include <fstream>

class BlockBuilder
{
public:
	FILE* block_file_;

	BlockBuilder();
	~BlockBuilder();

	virtual void readMyBlock(Block* block) = 0;

	Cell* buildCell(int cell_type);
	void buildNode();
	void buildFace(int face_type);
	void setConnectivity(Block* block);
	void setMetrics(Block* block);
	
};