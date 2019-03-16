#ifndef SOLVERSKELETON_SRC_NOSMOOTHER_CPP
#define SOLVERSKELETON_SRC_NOSMOOTHER_CPP

#include "Block.h"
#include "ResidualSmoother.h"
#include "NoSmoother.h"


#include <iostream>
using namespace std;

void NoSmoother::smoothResidual(Block* block)
{
	cout<<"\t\t\t\tExécution smoothResidual: No Smoother: "<<endl;
}



NoSmoother::NoSmoother()
{

}

NoSmoother::~NoSmoother()
{

}


#endif
