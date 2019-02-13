#ifndef BLOCKBUILDER_HEAD_BLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_BLOCKBUILDER_H

#include "Block.h"

class BlockBuilder
{
public:
	BlockBuilder();
	~BlockBuilder();
	virtual void readMyBlocks() = 0;
	void buildCell(int cell_type);
	void buildNode();
	void buildFace(int face_type);
	void setConnectivity(Block* block);
	void setMetrics(Block* block);
	
};