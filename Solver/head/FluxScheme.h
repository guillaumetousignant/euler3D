#ifndef SOLVERSKELETON_HEAD_FLUXSCHEME_H
#define SOLVERSKELETON_HEAD_FLUXSCHEME_H

#include "Block.h"

class Block;

class FluxScheme
{
	public:
		
		FluxScheme();
		~FluxScheme();

		virtual void computeFlux(Block* block)=0;


};


#endif