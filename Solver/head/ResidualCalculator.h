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
#include <vector>
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
		std::vector<double> beta_rk_;

		void setInterpolation(int interpolation_choice, string gradient_choice, string limiter_choice, double omega, double k);
		void setFluxScheme(double gamma, string flux_scheme_choice);
		void setResidualSmoother(bool residual_smoother_choice);

		void computeResidual(Block* block);


		ResidualCalculator();
		ResidualCalculator(double gamma, std::vector<double> beta_rk, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice, double omega, double k);
		~ResidualCalculator();


};


#endif