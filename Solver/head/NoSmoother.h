#ifndef SOLVERSKELETON_HEAD_NOSMOOTHER_H
#define SOLVERSKELETON_HEAD_NOSMOOTHER_H

#include "Block.h"
#include "ResidualSmoother.h"

class Block;

class NoSmoother : public ResidualSmoother
{
	public:
		
		NoSmoother();
		~NoSmoother();

		void smoothResidual(Block* block);

};


#endif