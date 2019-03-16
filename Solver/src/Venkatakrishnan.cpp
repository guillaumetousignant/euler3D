#ifndef SOLVERSKELETON_SRC_VENKATAKRISHNAN_CPP
#define SOLVERSKELETON_SRC_VENKATAKRISHNAN_CPP

#include "Block.h"
#include "Limiter.h"
#include "Venkatakrishnan.h"


#include <iostream>
using namespace std;

void Venkatakrishnan::computeLimiters(Block* block)
{
	cout<<"\t\t\t\t\tExécution computeLimiters: Venkatakrishnan: "<<endl;
}



Venkatakrishnan::Venkatakrishnan(double k)
{
	k_=k;
}

Venkatakrishnan::~Venkatakrishnan()
{

}


#endif
