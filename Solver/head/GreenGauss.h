#ifndef SOLVERSKELETON_HEAD_GREENGAUSS_H
#define SOLVERSKELETON_HEAD_GREENGAUSS_H

#include "Block.h"
#include "Gradient.h"

class Block;

class GreenGauss : public Gradient
{
	public:
		
		GreenGauss();
		~GreenGauss();

		void computeGradients(Block* block);

};


#endif