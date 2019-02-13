#ifndef BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_CONCRETEBLOCKBUILDER_H

class ConcreteBlockBuilder:public BlockBuilder
{
public:
	ConcreteBlockBuilder();
	~ConcreteBlockBuilder();
	
	void readMyBlocks(Block* block);

};