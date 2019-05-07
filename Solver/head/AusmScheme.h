#ifndef SOLVERSKELETON_HEAD_AUSMSCHEME_H
#define SOLVERSKELETON_HEAD_AUSMSCHEME_H

#include "Block.h"
#include "FluxScheme.h"

class Block;

class AusmScheme : public FluxScheme
{
	public:
		
		AusmScheme(double gamma);
		~AusmScheme();

		void computeFluxDiss(Block* block);
		void computeFluxConv(Block* block);


};


#endif