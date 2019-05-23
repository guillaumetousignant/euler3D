#ifndef SOLVERSKELETON_HEAD_SECONDORDER_H
#define SOLVERSKELETON_HEAD_SECONDORDER_H

#include "Block.h"

#include "Interpolation.h"

#include "GreenGauss.h"
#include "LeastSquares.h"
#include "Gradient.h"

#include "BarthJespersen.h"
#include "Venkatakrishnan.h"
#include "Limiter.h"

#include <string>
using namespace std;

class Block;
class Gradient;
class Limiter;

class SecondOrder : public Interpolation
{
	public:

		// Gradient *gradient_;
		Limiter *limiter_;

		void setGradient(string gradient_choice);
		void setLimiter(string limiter_choice, double omega, double k);


		SecondOrder();
		SecondOrder(string gradient_choice, string limiter_choice, double omega, double k);
		~SecondOrder();

		void computeInterpolation(Block* block);

};


#endif
