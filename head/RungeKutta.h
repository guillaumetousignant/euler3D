#ifndef SOLVERSKELETON_HEAD_RUNGEKUTTA_H
#define SOLVERSKELETON_HEAD_RUNGEKUTTA_H

#include "Block.h"
#include "ResidualCalculator.h"
#include "Updater.h"

#include <string>
using namespace std;

class ResidualCalculator;
class Updater;
class Block;

class RungeKutta
{
	public:
		int stage_number_;
		double *alpha_rk_;
		double *beta_rk_;
		ResidualCalculator *residual_calculator_;
		Updater *updater_;

		void computeRungeKutta(Block* block);


		RungeKutta(int stage_number, double *alpha_rk, double *beta_rk,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice);
		
		~RungeKutta();




};


#endif