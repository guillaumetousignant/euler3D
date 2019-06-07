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
	//cout<<"\t\t\t\tExécution computeInterpolation: SecondOrder: "<<endl;

	//cout<<endl<<"\t\t\t\tDans Gradient"<<endl;
	gradient_->computeGradients(block);
	//cout<<"\t\t\t\tFin Gradient"<<endl;
	//cout<<endl<<"\t\t\t\tDans Limiter"<<endl;
	// limiter_->computeLimiters(block);
	int n_cells=block->n_all_cells_in_block_;
	for(int i=0; i<n_cells;i++)
	{
		block->block_interpolation_variables_->limiter_ro_[i] = 1.0;
		block->block_interpolation_variables_->limiter_uu_[i] = 1.0;
		block->block_interpolation_variables_->limiter_vv_[i] = 1.0;
		block->block_interpolation_variables_->limiter_ww_[i] = 1.0;
		block->block_interpolation_variables_->limiter_pp_[i] = 1.0;
	}
	//cout<<"\t\t\t\tFin Limiter"<<endl;
}

void SecondOrder::setGradient(string gradient_choice)
{
	delete gradient_;
	if (gradient_choice=="leastsquares")
		gradient_=new LeastSquares();
	else
		gradient_=new GreenGauss();
}

void SecondOrder::setLimiter(string limiter_choice, double omega, double k)
{
	delete limiter_;
	if (limiter_choice=="venkatakrishnan")
		limiter_=new Venkatakrishnan(k);
	else
		limiter_=new BarthJespersen(omega);
}

SecondOrder::SecondOrder(string gradient_choice, string limiter_choice, double omega, double k)
{
	if (gradient_choice=="leastsquares")
		gradient_=new LeastSquares();
	else
		gradient_=new GreenGauss();

	if (limiter_choice=="venkatakrishnan")
		limiter_=new Venkatakrishnan(k);
	else
		limiter_=new BarthJespersen(omega);
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
