#ifndef SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP
#define SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP

#include "Block.h"
#include "Limiter.h"
#include "BarthJespersen.h"


#include <iostream>
using namespace std;

void BarthJespersen::computeLimiters(Block* block)
{
	block->test_block_+=5;
	cout<<"\t\t\t\t\tExécution computeLimiters: BarthJespersen: "<<block->test_block_<<endl;
}



BarthJespersen::BarthJespersen()
{
	omega_=10^-16;
}

BarthJespersen::~BarthJespersen()
{

}


#endif