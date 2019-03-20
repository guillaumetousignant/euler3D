#ifndef SOLVERSKELETON_HEAD_GRADIENT_H
#define SOLVERSKELETON_HEAD_GRADIENT_H

#include "Block.h"

class Block;

class Gradient
{
	public:
		
		Gradient();
		~Gradient();

		virtual void computeGradients(Block* block)=0;


};


#endif