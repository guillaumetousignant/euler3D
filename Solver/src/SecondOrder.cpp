#ifndef SOLVERSKELETON_SRC_SECONDORDER_CPP
#define SOLVERSKELETON_SRC_SECONDORDER_CPP

#include "Block.h"
#include "Interpolation.h"

#include "GreenGauss.h"
#include "LeastSquares.h"
#include "Gradient.h"

#include "BarthJespersen.h"
#include "Venkatakrishnan.h"
#include "Limiter.h"

#include "SecondOrder.h"

#include <iostream>
using namespace std;

void SecondOrder::computeInterpolation(Block* block)
{
	block->test_block_-=3;
	cout<<"\t\t\t\tExécution computeInterpolation: SecondOrder: "<<block->test_block_<<endl;

	cout<<endl<<"\t\t\t\tDans Gradient"<<endl;
	gradient_->computeGradients(block);
	cout<<"\t\t\t\tFin Gradient"<<endl;
	cout<<endl<<"\t\t\t\tDans Limiter"<<endl;
	limiter_->computeLimiters(block);
	cout<<"\t\t\t\tFin Limiter"<<endl;
}

void SecondOrder::setGradient(string gradient_choice)
{
	delete gradient_;
	if (gradient_choice=="leastsquares")
		gradient_=new LeastSquares();
	else
		gradient_=new GreenGauss();
}

void SecondOrder::setLimiter(string limiter_choice)
{
	delete limiter_;
	if (limiter_choice=="venkatakrishnan")
		limiter_=new Venkatakrishnan();
	else
		limiter_=new BarthJespersen();
}

SecondOrder::SecondOrder(string gradient_choice, string limiter_choice)
{
	if (gradient_choice=="leastsquares")
		gradient_=new LeastSquares();
	else
		gradient_=new GreenGauss();

	if (limiter_choice=="venkatakrishnan")
		limiter_=new Venkatakrishnan();
	else
		limiter_=new BarthJespersen();
}


SecondOrder::SecondOrder()
{
	gradient_=NULL;
	limiter_=NULL;
}

SecondOrder::~SecondOrder()
{

}


#endif
