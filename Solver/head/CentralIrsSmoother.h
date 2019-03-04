#ifndef SOLVERSKELETON_HEAD_CENTRALIRSSMOOTHER_H
#define SOLVERSKELETON_HEAD_CENTRALIRSSMOOTHER_H

#include "Block.h"
#include "ResidualSmoother.h"

class Block;

class CentralIrsSmoother : public ResidualSmoother
{
	public:
		
		CentralIrsSmoother();
		~CentralIrsSmoother();

		void smoothResidual(Block* block);

};


#endif