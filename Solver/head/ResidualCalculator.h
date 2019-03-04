#ifndef SOLVERSKELETON_HEAD_RESIDUALCALCULATOR_H
#define SOLVERSKELETON_HEAD_RESIDUALCALCULATOR_H

#include "Block.h"

#include "FirstOrder.h"
#include "SecondOrder.h"
#include "Interpolation.h"

#include "RoeScheme.h"
#include "AusmScheme.h"
#include "FluxScheme.h"

#include "NoSmoother.h"
#include "CentralIrsSmoother.h"
#include "ResidualSmoother.h"

#include <string>
using namespace std;

class Block;
class FluxScheme;

class ResidualCalculator
{
	public:

		Interpolation *interpolation_;
		FluxScheme *flux_scheme_;
		ResidualSmoother *residual_smoother_;

		int current_stage_;
		double *alpha_rk_;
		double *beta_rk_;

		void setInterpolation(string interpolation_choice, string gradient_choice, string limiter_choice);
		void setFluxScheme(double gamma, string flux_scheme_choice);
		void setResidualSmoother(string residual_smoother_choice);

		void computeResidual(Block* block);


		ResidualCalculator();
		ResidualCalculator(double gamma, double *beta_rk, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice);
		~ResidualCalculator();


};


#endif