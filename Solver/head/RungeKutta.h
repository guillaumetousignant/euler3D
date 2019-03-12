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
		ResidualCalculator *residual_calculator_;
		Updater *updater_;

		void computeRungeKutta(Block* block);


		RungeKutta(double gamma, int stage_number, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice);
		
		~RungeKutta();




};


#endif