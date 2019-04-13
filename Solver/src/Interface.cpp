#ifndef SOLVERSKELETON_SRC_INTERFACE_CPP
#define SOLVERSKELETON_SRC_INTERFACE_CPP

#include "Interface.h"
#include "Solver.h"
//#include "Initializer.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void Interface::readInputFile(string input_file_name, bool i_write /* = false */)
{
	string line_in_file;
	ifstream input_file;

	if (i_write){
		std::cout << std::boolalpha;
		cout << "Reading Input File..."<<endl;
	}

	input_file.open(input_file_name);
	if (input_file.fail())
	{
		cout << "Opening File'" << input_file_name << "' Failure..."<<endl;
		/*std::ofstream outfile ("STOP");
		outfile.close();*/
		exit(42);
	}

	// Skipping "MESH" Line
	// Skipping "topogyfilename" Line
	input_file.ignore(256, '\n');

	// Reading Topology File Name
	getline(input_file, line_in_file);
	input_file >> topology_file_name_interface_;

	// Skipping "INPUT" Line
	input_file.ignore(256, '\n');

	// Skipping "cfl gamma angleattackdeg" Line
	input_file.ignore(256, '\n');

	// Reading CFL Number
	getline(input_file, line_in_file);
	input_file >> cfl_interface_;

	// Reading Gamma
	input_file >> gamma_interface_;

	// Reading Angle of Attack (°)
	input_file >> aoa_deg_interface_;

	// Skipping "rkstage mach cmac" Line
	input_file.ignore(256, '\n');

	// Reading Number of Runge-Kutta Stages
	getline(input_file, line_in_file);
	input_file >> stage_number_interface_;

	// Reading Mach Number
	input_file >> mach_aircraft_interface_;

	// Reading Mean Aerodynamic Chord
	input_file >> cmac_interface_;

	// Skipping "nbitermax convcriterion" Line
	input_file.ignore(256, '\n');

	// Reading Maximum Number of Iterations
	getline(input_file, line_in_file);
	input_file >> max_iter_interface_;

	// Reading Convergence Criterion
	input_file >> convergence_criterion_interface_;

	// Skipping "residual smoothing (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Reading Residual Smoother Choice
	getline(input_file, line_in_file);
	input_file >> residual_smoother_choice_interface_;

	// Skipping "fluxscheme schemeorder" Line
	input_file.ignore(256, '\n');

	// Reading Flux Scheme Choice
	getline(input_file, line_in_file);
	input_file >> flux_scheme_choice_interface_;

	// Reading Flux Scheme Order
	input_file >> interpolation_choice_interface_;

	// Skipping "gradient limiter" Line
	input_file.ignore(256, '\n');

	// Reading Gradient Choice
	getline(input_file, line_in_file);
	input_file >> gradient_choice_interface_;

	// Reading Limiter Choice
	input_file >> limiter_choice_interface_;

	// Skipping "omega k" Line
	input_file.ignore(256, '\n');

	// Reading Omega Parameter
	getline(input_file, line_in_file);
	input_file >> omega_interface_;

	// Reading K Parameter
	input_file >> k_interface_;

	/// A IMPLEMENTER !!!!!!!!

	// Skipping "EXECUTABLE (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Skipping "build execute" Line
	input_file.ignore(256, '\n');

	// Reading Build Choice
	getline(input_file, line_in_file);
	input_file >> build_choice_interface_;

	// Reading Execute Choice
	input_file >> execute_choice_interface_;

	// Skipping "OUTPUT (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Skipping "clalpha cdalpha cmalpha" Line
	input_file.ignore(256, '\n');

	// Reading Cl vs Alpha Output Choice
	getline(input_file, line_in_file);
	input_file >> cl_alpha_output_choice_interface_;

	// Reading Cd vs Alpha Output Choice
	input_file >> cd_alpha_output_choice_interface_;

	// Reading Cm vs Alpha Output Choice
	input_file >> cm_alpha_output_choice_interface_;

	// Skipping "clconv cdconv cmconv residualconv" Line
	input_file.ignore(256, '\n');

	// Reading Cl Convergence Output Choice
	getline(input_file, line_in_file);
	input_file >> cl_conv_output_choice_interface_;

	// Reading Cd Convergence Output Choice
	input_file >> cd_conv_output_choice_interface_;

	// Reading Cm Convergence Output Choice
	input_file >> cm_conv_output_choice_interface_;

	// Reading Residual Convergence Output Choice
	input_file >> res_conv_output_choice_interface_;

	// Skipping "cpxc machcontour cpcontour" Line
	input_file.ignore(256, '\n');

	// Reading Cp vs Xc Output Choice
	getline(input_file, line_in_file);
	input_file >> cp_xc_output_choice_interface_;

	// Reading Mach Contour Output Choice
	input_file >> mach_contour_output_choice_interface_;

	// Reading Cp Contour Output Choice
	input_file >> cp_contour_output_choice_interface_;

	// Skipping "slicecp" Line
	input_file.ignore(256, '\n');

	// Slice Output Choice
	getline(input_file, line_in_file);
	input_file >> slice_cp_output_choice_interface_;

	// Skipping "axis xcoord ycoord zcoord" Line
	input_file.ignore(256, '\n');

	// Slice Axis Choice
	getline(input_file, line_in_file);
	input_file >> slice_axis_choice_interface_;

	// Slice X Coordinate
	input_file >> slice_x_coord_interface_;

	// Slice Y Coordinate
	input_file >> slice_y_coord_interface_;

	// Slice Z Coordinate
	input_file >> slice_z_coord_interface_;

	if (i_write){
		cout << "Topology File Name is: " << topology_file_name_interface_ << endl;
		cout << "CFL Number is: " << cfl_interface_ << endl;
		cout << "Gamma is: " << gamma_interface_ << endl;
		cout << "Angle of Attack (°) is: " << aoa_deg_interface_ << endl;
		cout << "Number of Runge-Kutta Stages is: " << stage_number_interface_ << endl;
		cout << "Mach Number is: " << mach_aircraft_interface_ << endl;
		cout << "Mean Aerodynamic Chord is: " << cmac_interface_ << endl;
		cout << "Maximum Number of Iterations is: " << max_iter_interface_ << endl;
		cout << "Convergence Criterion is: " << convergence_criterion_interface_ << endl;
		cout << "Residual Smoother Choice is: " << residual_smoother_choice_interface_ << endl;
		cout << "Flux Scheme Choice is: " << flux_scheme_choice_interface_ << endl;
		cout << "Residual Interpolation Order is: " << interpolation_choice_interface_ << endl;
		cout << "Gradient Choice is: " << gradient_choice_interface_ << endl;
		cout << "Limiter Choice is: " << limiter_choice_interface_ << endl;
		cout << "Omega Parameter is: " << omega_interface_ << endl;
		cout << "K Parameter is: " << k_interface_ << endl;
		cout << "Build Choice is: " << build_choice_interface_ << endl;
		cout << "Execute Choice is: " << execute_choice_interface_ << endl;
		cout << "Cl vs Alpha Output Choice is: " << cl_alpha_output_choice_interface_ << endl;
		cout << "Cd vs Alpha Output Choice is: " << cd_alpha_output_choice_interface_ << endl;
		cout << "Cm vs Alpha Output Choice is: " << cm_alpha_output_choice_interface_ << endl;
		cout << "Cl Convergence Output Choice is: " << cl_conv_output_choice_interface_ << endl;
		cout << "Cd Convergence Output Choice is: " << cd_conv_output_choice_interface_ << endl;
		cout << "Cm Convergence Output Choice is: " << cm_conv_output_choice_interface_ << endl;
		cout << "Residual Convergence Output Choice is: " << res_conv_output_choice_interface_ << endl;
		cout << "Cp vs Xc Output Choice is: " << cp_xc_output_choice_interface_ << endl;
		cout << "Mach Contour Output Choice is: " << mach_contour_output_choice_interface_ << endl;
		cout << "Cp Contour Output Choice is: " << cp_contour_output_choice_interface_ << endl;
		cout << "Slice Output Choice is: " <<slice_cp_output_choice_interface_ << endl;
		cout << "Slice Axis Choice is: " <<slice_axis_choice_interface_ << endl;
		cout << "Slice X Coordinate is: " <<slice_x_coord_interface_ << endl;
		cout << "Slice Y Coordinate is: " <<slice_y_coord_interface_ << endl;
		cout << "Slice Z Coordinate is: " <<slice_z_coord_interface_ << endl;
	}

	input_file.close();
}

void Interface::readNBlocks(bool i_write)
{
	// READ N BLOCKS
	string line_in_file;
	char str_temp[200];
	ifstream topology_file(topology_file_name_interface_);
	if (i_write){
	cout << "Reading Topology File: "<<topology_file_name_interface_<<endl;
	}
	
	if (topology_file.is_open())
	{
		// Reading NBlocks
		getline(topology_file, line_in_file);
		sscanf (line_in_file.c_str(), "%s %d",str_temp,&n_blocks_interface_);
		if (i_write){
		cout<<"Number of blocks is: "<<n_blocks_interface_<<endl;
		}
	}
	else
	{
		cout << "Opening File'" << topology_file_name_interface_ << "' Failure..."<<endl;
		/*std::ofstream outfile ("STOP");
		outfile.close();*/
		exit(42);
	}
	topology_file.close();
}


Interface::Interface(char* argv, bool i_write /* = false */) : n_blocks_interface_(0)
{
	string input_file_name;
	input_file_name=argv;
	readInputFile(input_file_name, i_write);
	readNBlocks(i_write);
}

Interface::~Interface()
{

}


#endif
