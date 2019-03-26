#ifndef SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP
#define SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP

#include "Block.h"
#include "Limiter.h"
#include "BarthJespersen.h"


#include <iostream>
using namespace std;

void BarthJespersen::computeLimiters(Block* block)
{

	//cout<<"\t\t\t\t\tExécution computeLimiters: BarthJespersen: "<<endl;
}



BarthJespersen::BarthJespersen(double omega)
{
	omega_=omega;
}

BarthJespersen::~BarthJespersen()
{

}


#endif
