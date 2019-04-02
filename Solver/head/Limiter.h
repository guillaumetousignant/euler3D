#ifndef SOLVERSKELETON_HEAD_LIMITER_H
#define SOLVERSKELETON_HEAD_LIMITER_H

#include "Block.h"

class Block;

class Limiter
{
	public:
		
		Limiter();
		~Limiter();

		virtual void computeLimiters(Block* block)=0;


};


#endif