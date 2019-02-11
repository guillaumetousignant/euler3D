#ifndef SOLVERSKELETON_SRC_GREENGAUSS_CPP
#define SOLVERSKELETON_SRC_GREENGAUSS_CPP

#include "Block.h"
#include "Gradient.h"
#include "GreenGauss.h"


#include <iostream>
using namespace std;

void GreenGauss::computeGradients(Block* block)
{
	block->test_block_+=4;
	cout<<"\t\t\t\t\tExécution computeGradients: GreenGauss: "<<block->test_block_<<endl;
}



GreenGauss::GreenGauss()
{
	
}

GreenGauss::~GreenGauss()
{

}


#endif