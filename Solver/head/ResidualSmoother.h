#ifndef SOLVERSKELETON_HEAD_RESIDUALSMOOTHER_H
#define SOLVERSKELETON_HEAD_RESIDUALSMOOTHER_H

#include "Block.h"

class Block;

class ResidualSmoother
{
	public:
		
		ResidualSmoother();
		virtual ~ResidualSmoother();

		virtual void smoothResidual(Block* block)=0;


};


#endif