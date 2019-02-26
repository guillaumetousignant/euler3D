#ifndef SOLVERSKELETON_SRC_FIRSTORDER_CPP
#define SOLVERSKELETON_SRC_FIRSTORDER_CPP

#include "Block.h"
#include "Interpolation.h"
#include "FirstOrder.h"


#include <iostream>
using namespace std;

void FirstOrder::computeInterpolation(Block* block)
{
	block->test_block_+=3;
	cout<<"\t\t\t\tExécution computeInterpolation: FirstOrder: "<<block->test_block_<<endl;
}



FirstOrder::FirstOrder()
{
	
}

FirstOrder::~FirstOrder()
{

}


#endif