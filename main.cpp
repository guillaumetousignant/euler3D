#ifndef SOLVERSKELETON_SRC_TESTMAIN_CPP
#define SOLVERSKELETON_SRC_TESTMAIN_CPP

#include "Block.h"

#include "Initializer.h"
#include "Interface.h"
#include "Solver.h"


#include <iostream>
#include <string>
using namespace std;

int main()
{

	int test_block=69;
	Block* block= new Block(test_block);
	Initializer* initializer= new Initializer();
	Interface* interface= new Interface();

	Solver *solver=initializer->initializeSolver(interface);
	solver->solve(block);

	/*
	double gamma=1.5;
	double cfl=1.0;
	int stage_number=5;
	double alpha_rk[5]={420,420,420,420,420};
	double beta_rk[5]={1337,1337,1337,1337,1337};
	string interpolation_choice = "Second";
	string gradient_choice = "Least Squares";
	string limiter_choice = "Venkatakrishnan";
	string flux_scheme_choice = "Roe";
	string residual_smoother_choice = "Central IRS";



	Solver *solver= new Solver(gamma, cfl, stage_number, alpha_rk, beta_rk, interpolation_choice, gradient_choice, limiter_choice, flux_scheme_choice, residual_smoother_choice);

	cout<<"Salut"<<endl;
	cout<<solver->gamma_<<endl;
	cout<<solver->runge_kutta_->alpha_rk_[1]<<endl;
	cout<<solver->runge_kutta_->beta_rk_[1]<<endl;
	cout<<block->test_block_<<endl;


	solver->solve(block);

	cout<<block->test_block_<<endl;
	*/

	return 0;
}
#endif
