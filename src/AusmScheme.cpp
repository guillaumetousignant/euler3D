#ifndef SOLVERSKELETON_SRC_AUSMSCHEME_CPP
#define SOLVERSKELETON_SRC_AUSMSCHEME_CPP

#include "Block.h"
#include "FluxScheme.h"
#include "AusmScheme.h"


#include <iostream>
using namespace std;

void AusmScheme::computeFlux(Block* block)
{
	block->test_block_--;
	cout<<"\t\t\t\tExécution computeFlux: AUSM: "<<block->test_block_<<endl;
}



AusmScheme::AusmScheme()
{
	
}

AusmScheme::~AusmScheme()
{

}


#endif