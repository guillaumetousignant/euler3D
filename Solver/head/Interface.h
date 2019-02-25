#ifndef SOLVERSKELETON_HEAD_INTERFACE_H
#define SOLVERSKELETON_HEAD_INTERFACE_H


#include <string>
#include <math.h>
using namespace std;


class Interface
{
	public:

		double gamma_interface_;
		double cfl_interface_;
		int stage_number_interface_;
		string interpolation_choice_interface_;
		string gradient_choice_interface_;
		string limiter_choice_interface_;
		string flux_scheme_choice_interface_;
		string residual_smoother_choice_interface_;

		int n_blocks_interface_;
		int max_iter_interface_;
		double convergence_criterion_interface_;
		double cmac_interface_;
		double aoa_deg_interface_;
		double mach_aircraft_interface_;

		Interface(double gamma, double cfl, int stage_number,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice);
		Interface();
		~Interface();




};


#endif