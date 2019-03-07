#ifndef SOLVERSKELETON_HEAD_INTERFACE_H
#define SOLVERSKELETON_HEAD_INTERFACE_H


#include <string>
#include <fstream>



class Interface
{
	public:
		std::string topology_file_name_interface_;
		std::string output_file_name_interface_;
		double cfl_interface_;
		double gamma_interface_;
		double angle_of_attack_deg_interface_;
		double angle_of_attack_rad_interface_;
		int stage_number_interface_;
		double mach_interface_;
		double cmac_interface_;
		int max_iter_interface_;
		double convergence_criteria_interface_;
		std::string flux_scheme_choice_interface_;
		std::string flux_scheme_order_choice_interface_;
		std::string gradient_choice_interface_;
		std::string limiter_choice_interface_;
		double omega_interface_;
		double k_interface_;
		bool residual_smoothing_interface_;
		bool build_interface_;
		bool execute_interface_;

		// Interface(std::string topology_file_name, double gamma, double cfl, double angle_of_attack_rad, double angle_of_attack_deg, int stage_number, double mach, double cmac, string interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoothing, double omega, double k);
		Interface(std::string output_file_name);
		Interface();
		~Interface();

		void readInterfaceOutput();
};


#endif

// MESH
// topologyfilename
// topology.x
// INPUT
// cfl gamma angleattackrad
// 7.5 1.4 0.00
// rkstage mach cmac
// 5 0.80 1.00
// nbitermax convcriterion
// 300 1e-15
// residual smoothing (0-no 1-yes)
// 1
// fluxscheme schemeorder
// roe 1
// gradient limiter
// greengauss barthjespersen
// omega k
// 1.0e6 5.00
// EXECUTABLE (0-no 1-yes)
// build execute
// 1 1
// OUTPUT (0-no 1-yes)
// clalpha cdalpha cmalpha
// 1 1 1
// clconv cdconv cmconv residualconv
// 1 1 1 1
// cpxc machcontour cpcontour
// 1 1 1
// slicecp
// 1
// axis xcoord ycoord zcoord
// x 1.00 1.00
