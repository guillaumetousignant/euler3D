#ifndef SOLVERSKELETON_SRC_LEASTSQUARES_CPP
#define SOLVERSKELETON_SRC_LEASTSQUARES_CPP

#include "Block.h"
#include "Gradient.h"
#include "LeastSquares.h"


#include <iostream>
using namespace std;

void LeastSquares::computeGradients(Block* block)
{
	block->test_block_-=4;
	cout<<"\t\t\t\t\tExécution computeGradients: LeastSquares: "<<block->test_block_<<endl;
}



LeastSquares::LeastSquares()
{
	
}

LeastSquares::~LeastSquares()
{

}


#endif