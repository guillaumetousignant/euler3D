#ifndef SOLVERSKELETON_SRC_CENTRALIRSSMOOTHER_CPP
#define SOLVERSKELETON_SRC_CENTRALIRSSMOOTHER_CPP

#include "Block.h"
#include "ResidualSmoother.h"
#include "CentralIrsSmoother.h"


#include <iostream>
using namespace std;

void CentralIrsSmoother::smoothResidual(Block* block)
{
	block->test_block_+=2;
	cout<<"\t\t\t\tExécution smoothResidual: Central IRS Smoother: "<<block->test_block_<<endl;
}



CentralIrsSmoother::CentralIrsSmoother()
{
	
}

CentralIrsSmoother::~CentralIrsSmoother()
{

}


#endif