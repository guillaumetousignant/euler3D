#ifndef SOLVERSKELETON_HEAD_VENKATAKRISHNAN_H
#define SOLVERSKELETON_HEAD_VENKATAKRISHNAN_H

#include "Block.h"
#include "Limiter.h"

class Block;

class Venkatakrishnan : public Limiter
{
	public:
		
		double k_;

		Venkatakrishnan(double k);
		~Venkatakrishnan();

		void computeLimiters(Block* block);

};


#endif