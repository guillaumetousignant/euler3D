#ifndef SOLVERSKELETON_HEAD_LEASTSQUARES_H
#define SOLVERSKELETON_HEAD_LEASTSQUARES_H

#include "Block.h"
#include "Gradient.h"

class Block;

class LeastSquares : public Gradient
{
	public:
		
		LeastSquares();
		~LeastSquares();

		void computeGradients(Block* block);

};


#endif