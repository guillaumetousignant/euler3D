#ifndef SOLVERSKELETON_HEAD_SOLVER_H
#define SOLVERSKELETON_HEAD_SOLVER_H

#include "Block.h"
#include "CompleteMesh.h"
#include "Timestep.h"
#include "RungeKutta.h"
#include "PostProcessing.h"

#include <string>
using namespace std;

class Timestep;
class RungeKutta;
class PostProcessing;
class Block;

class Solver
{
	public:
		double gamma_;
		Timestep *timestep_;
		RungeKutta *runge_kutta_;
		PostProcessing *post_processing_;

		void solve(Block* block, CompleteMesh* complete_mesh);
		void saveW0(Block* block);

		Solver(double gamma, double cfl, int stage_number, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice, int n_blocks, int max_iter, double convergence_criterion, double cmac, double aoa_deg, double mach_aircraft);
		Solver();
		~Solver();




};


#endif