#ifndef SOLVERSKELETON_HEAD_FLUXSCHEME_H
#define SOLVERSKELETON_HEAD_FLUXSCHEME_H

#include "Block.h"
#include <math.h>

class Block;

class FluxScheme
{
	public:

		double gamma_;
		double current_beta_;

		FluxScheme();
		~FluxScheme();

		virtual void computeFluxDiss(Block* block)=0;
		virtual void computeFluxConv(Block* block);


};


#endif
