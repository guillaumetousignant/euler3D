#ifndef SOLVERSKELETON_HEAD_INTERPOLATION_H
#define SOLVERSKELETON_HEAD_INTERPOLATION_H

#include "Block.h"

class Block;

class Interpolation
{
	public:
		
		Interpolation();
		~Interpolation();

		virtual void computeInterpolation(Block* block)=0;


};


#endif