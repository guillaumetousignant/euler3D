#ifndef SOLVERSKELETON_HEAD_ROESCHEME_H
#define SOLVERSKELETON_HEAD_ROESCHEME_H

#include "Block.h"
#include "FluxScheme.h"

class Block;

class RoeScheme : public FluxScheme
{
	public:

		RoeScheme(double gamma);
		~RoeScheme();

		void computeFluxDiss(Block* block);

};


#endif
