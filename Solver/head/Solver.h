#ifndef SOLVERSKELETON_HEAD_SOLVER_H
#define SOLVERSKELETON_HEAD_SOLVER_H

#include "Block.h"
#include "Timestep.h"
#include "RungeKutta.h"

#include <string>
using namespace std;

class Timestep;
class RungeKutta;
class Block;

class Solver
{
	public:
		double gamma_;
		bool stop_solver_flag_;
		Timestep *timestep_;
		RungeKutta *runge_kutta_;

		void solve(Block* block);
		void saveW0(Block* block);


		Solver(double gamma, double cfl, int stage_number, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice);
		Solver();
		~Solver();




};


#endif