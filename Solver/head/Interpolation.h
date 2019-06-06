#ifndef SOLVERSKELETON_HEAD_INTERPOLATION_H
#define SOLVERSKELETON_HEAD_INTERPOLATION_H

#include "Block.h"
#include "Gradient.h"
class Gradient;
class Block;

class Interpolation
{
	public:
		Gradient *gradient_;
		Interpolation();
		virtual ~Interpolation();

		virtual void computeInterpolation(Block* block, int c_iter)=0;


};


#endif
