#ifndef SOLVERSKELETON_HEAD_INTERFACE_H
#define SOLVERSKELETON_HEAD_INTERFACE_H


#include <string>
#include <math.h>
using namespace std;


class Interface
{
	public:

		void readInputFile();

		// MESH
		string topology_file_name_interface_;

		// INPUT
		double cfl_interface_;
		double gamma_interface_;
		double aoa_deg_interface_

		int stage_number_interface_;
		double mach_aircraft_interface_;
		double cmac_interface_;

		int max_iter_interface_;
		double convergence_criterion_interface_;

		bool residual_smoother_choice_interface_;

		string flux_scheme_choice_interface_;
		int interpolation_choice_interface_;

		string gradient_choice_interface_;
		string limiter_choice_interface_;
		
		double omega_interface_;
		double k_interface_;


		// EXECUTABLE
		bool build_choice_interface_;
		bool execute_choice_interface_;

		// OUTPUT
		bool cl_alpha_output_choice_interface_;
		bool cd_alpha_output_choice_interface_;
		bool cm_alpha_output_choice_interface_;

		bool cl_conv_output_choice_interface_;
		bool cd_conv_output_choice_interface_;
		bool cm_conv_output_choice_interface_;
		bool res_conv_output_choice_interface_;

		bool cp_xc_output_choice_interface_;
		bool mach_contour_output_choice_interface_;
		bool cp_contour_output_choice_interface_;

		bool slice_cp_output_choice_interface_;

		string slice_axis_choice_interface_;
		double slice_x_coord_interface_;
		double slice_y_coord_interface_;
		double slice_z_coord_interface_;






		int n_blocks_interface_; // RÉGLER CE PROBLÈME LÀ
		

		Interface(double gamma, double cfl, int stage_number,int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice);
		Interface();
		~Interface();




};


#endif