#ifndef SOLVERSKELETON_HEAD_FIRSTORDER_H
#define SOLVERSKELETON_HEAD_FIRSTORDER_H

#include "Block.h"
#include "Interpolation.h"

class Block;

class FirstOrder : public Interpolation
{
	public:

		FirstOrder();
		~FirstOrder();

		void computeInterpolation(Block* block, int c_iter);

};


#endif
