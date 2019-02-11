#ifndef SOLVERSKELETON_HEAD_BARTHJESPERSEN_H
#define SOLVERSKELETON_HEAD_BARTHJESPERSEN_H

#include "Block.h"
#include "Limiter.h"

class Block;

class BarthJespersen : public Limiter
{
	public:
		
		double omega_;

		BarthJespersen();
		~BarthJespersen();

		void computeLimiters(Block* block);

};


#endif