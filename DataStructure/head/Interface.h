#ifndef SOLVERSKELETON_HEAD_INTERFACE_H
#define SOLVERSKELETON_HEAD_INTERFACE_H


#include <string>
using namespace std;


class Interface
{
	public:
		string mesh_file_name_interface_;
		string output_file_name_interface_;
		double gamma_interface_;
		double cfl_interface_;
		double angle_of_attack_rad_interface_;
		double angle_of_attack_deg_interface_;
		int stage_number_interface_;
		double mach_interface_;
		double *alpha_rk_interface_;
		double *beta_rk_interface_;
		int max_iter_interface_;
		double convergence_criteria_interface_;
		string interpolation_choice_interface_;
		string gradient_choice_interface_;
		string limiter_choice_interface_;
		string flux_scheme_choice_interface_;
		string residual_smoother_choice_interface_;
		double omega_interface_;
		double k_interface_;

		Interface(string mesh_file_name,string output_file_name, double gamma, double cfl, double angle_of_attack_rad, double angle_of_attack_deg, int stage_number, double mach, double *alpha_rk, double *beta_rk,string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, string residual_smoother_choice, double omega, double k);
		Interface();
		~Interface();




};


#endif