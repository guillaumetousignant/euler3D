#ifndef SOLVERSKELETON_SRC_INTERFACE_CPP
#define SOLVERSKELETON_SRC_INTERFACE_CPP

#include "Interface.h"
#include "Solver.h"
//#include "Initializer.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void Interface::readInputFile(string input_file_name)
{
	string line_in_file;
	std::cout << std::boolalpha;

	ifstream input_file;
	cout << "Reading Input File..."<<endl;
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
	cout << "Topology File Name is: " << topology_file_name_interface_ << endl;

	// Skipping "INPUT" Line
	input_file.ignore(256, '\n');

	// Skipping "cfl gamma angleattackdeg" Line
	input_file.ignore(256, '\n');

	// Reading CFL Number
	getline(input_file, line_in_file);
	input_file >> cfl_interface_;
	cout << "CFL Number is: " << cfl_interface_ << endl;

	// Reading Gamma
	input_file >> gamma_interface_;
	cout << "Gamma is: " << gamma_interface_ << endl;

	// Reading Angle of Attack (°)
	input_file >> aoa_deg_interface_;
	cout << "Angle of Attack (°) is: " << aoa_deg_interface_ << endl;

	// Skipping "rkstage mach cmac" Line
	input_file.ignore(256, '\n');

	// Reading Number of Runge-Kutta Stages
	getline(input_file, line_in_file);
	input_file >> stage_number_interface_;
	cout << "Number of Runge-Kutta Stages is: " << stage_number_interface_ << endl;

	// Reading Mach Number
	input_file >> mach_aircraft_interface_;
	cout << "Mach Number is: " << mach_aircraft_interface_ << endl;

	// Reading Mean Aerodynamic Chord
	input_file >> cmac_interface_;
	cout << "Mean Aerodynamic Chord is: " << cmac_interface_ << endl;

	// Skipping "nbitermax convcriterion" Line
	input_file.ignore(256, '\n');

	// Reading Maximum Number of Iterations
	getline(input_file, line_in_file);
	input_file >> max_iter_interface_;
	cout << "Maximum Number of Iterations is: " << max_iter_interface_ << endl;

	// Reading Convergence Criterion
	input_file >> convergence_criterion_interface_;
	cout << "Convergence Criterion is: " << convergence_criterion_interface_ << endl;

	// Skipping "residual smoothing (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Reading Residual Smoother Choice
	getline(input_file, line_in_file);
	input_file >> residual_smoother_choice_interface_;
	cout << "Residual Smoother Choice is: " << residual_smoother_choice_interface_ << endl;

	// Skipping "fluxscheme schemeorder" Line
	input_file.ignore(256, '\n');

	// Reading Flux Scheme Choice
	getline(input_file, line_in_file);
	input_file >> flux_scheme_choice_interface_;
	cout << "Flux Scheme Choice is: " << flux_scheme_choice_interface_ << endl;

	// Reading Flux Scheme Order
	input_file >> interpolation_choice_interface_;
	cout << "Residual Interpolation Order is: " << interpolation_choice_interface_ << endl;

	// Skipping "gradient limiter" Line
	input_file.ignore(256, '\n');

	// Reading Gradient Choice
	getline(input_file, line_in_file);
	input_file >> gradient_choice_interface_;
	cout << "Gradient Choice is: " << gradient_choice_interface_ << endl;

	// Reading Limiter Choice
	input_file >> limiter_choice_interface_;
	cout << "Limiter Choice is: " << limiter_choice_interface_ << endl;

	// Skipping "omega k" Line
	input_file.ignore(256, '\n');

	// Reading Omega Parameter
	getline(input_file, line_in_file);
	input_file >> omega_interface_;
	cout << "Omega Parameter is: " << omega_interface_ << endl;

	// Reading K Parameter
	input_file >> k_interface_;
	cout << "K Parameter is: " << k_interface_ << endl;

	/// A IMPLEMENTER !!!!!!!!

	// Skipping "EXECUTABLE (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Skipping "build execute" Line
	input_file.ignore(256, '\n');

	// Reading Build Choice
	getline(input_file, line_in_file);
	input_file >> build_choice_interface_;
	cout << "Build Choice is: " << build_choice_interface_ << endl;

	// Reading Execute Choice
	input_file >> execute_choice_interface_;
	cout << "Execute Choice is: " << execute_choice_interface_ << endl;

	// Skipping "OUTPUT (0-no 1-yes)" Line
	input_file.ignore(256, '\n');

	// Skipping "clalpha cdalpha cmalpha" Line
	input_file.ignore(256, '\n');

	// Reading Cl vs Alpha Output Choice
	getline(input_file, line_in_file);
	input_file >> cl_alpha_output_choice_interface_;
	cout << "Cl vs Alpha Output Choice is: " << cl_alpha_output_choice_interface_ << endl;

	// Reading Cd vs Alpha Output Choice
	input_file >> cd_alpha_output_choice_interface_;
	cout << "Cd vs Alpha Output Choice is: " << cd_alpha_output_choice_interface_ << endl;

	// Reading Cm vs Alpha Output Choice
	input_file >> cm_alpha_output_choice_interface_;
	cout << "Cm vs Alpha Output Choice is: " << cm_alpha_output_choice_interface_ << endl;

	// Skipping "clconv cdconv cmconv residualconv" Line
	input_file.ignore(256, '\n');

	// Reading Cl Convergence Output Choice
	getline(input_file, line_in_file);
	input_file >> cl_conv_output_choice_interface_;
	cout << "Cl Convergence Output Choice is: " << cl_conv_output_choice_interface_ << endl;

	// Reading Cd Convergence Output Choice
	input_file >> cd_conv_output_choice_interface_;
	cout << "Cd Convergence Output Choice is: " << cd_conv_output_choice_interface_ << endl;

	// Reading Cm Convergence Output Choice
	input_file >> cm_conv_output_choice_interface_;
	cout << "Cm Convergence Output Choice is: " << cm_conv_output_choice_interface_ << endl;

	// Reading Residual Convergence Output Choice
	input_file >> res_conv_output_choice_interface_;
	cout << "Residual Convergence Output Choice is: " << res_conv_output_choice_interface_ << endl;

	// Skipping "cpxc machcontour cpcontour" Line
	input_file.ignore(256, '\n');

	// Reading Cp vs Xc Output Choice
	getline(input_file, line_in_file);
	input_file >> cp_xc_output_choice_interface_;
	cout << "Cp vs Xc Output Choice is: " << cp_xc_output_choice_interface_ << endl;

	// Reading Mach Contour Output Choice
	input_file >> mach_contour_output_choice_interface_;
	cout << "Mach Contour Output Choice is: " << mach_contour_output_choice_interface_ << endl;

	// Reading Cp Contour Output Choice
	input_file >> cp_contour_output_choice_interface_;
	cout << "Cp Contour Output Choice is: " << cp_contour_output_choice_interface_ << endl;

	// Skipping "slicecp" Line
	input_file.ignore(256, '\n');

	// Slice Output Choice
	getline(input_file, line_in_file);
	input_file >> slice_cp_output_choice_interface_;
	cout << "Slice Output Choice is: " <<slice_cp_output_choice_interface_ << endl;

	// Skipping "axis xcoord ycoord zcoord" Line
	input_file.ignore(256, '\n');

	// Slice Axis Choice
	getline(input_file, line_in_file);
	input_file >> slice_axis_choice_interface_;
	cout << "Slice Axis Choice is: " <<slice_axis_choice_interface_ << endl;

	// Slice X Coordinate
	input_file >> slice_x_coord_interface_;
	cout << "Slice X Coordinate is: " <<slice_x_coord_interface_ << endl;

	// Slice Y Coordinate
	input_file >> slice_y_coord_interface_;
	cout << "Slice Y Coordinate is: " <<slice_y_coord_interface_ << endl;

	// Slice Z Coordinate
	input_file >> slice_z_coord_interface_;
	cout << "Slice Z Coordinate is: " <<slice_z_coord_interface_ << endl;


	input_file.close();


}

void Interface::readNBlocks()
{
	// READ N BLOCKS
	string line_in_file;
	char str_temp[200];
	ifstream topology_file(topology_file_name_interface_);
	cout << "Reading Topology File: "<<topology_file_name_interface_<<endl;
	
	if (topology_file.is_open())
	{
		// Reading NBlocks
		getline(topology_file, line_in_file);
		sscanf (line_in_file.c_str(), "%s %d",str_temp,&n_blocks_interface_);
		cout<<"Number of blocks is: "<<n_blocks_interface_<<endl;
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


Interface::Interface(char* argv) : n_blocks_interface_(0)
{
	string input_file_name;
	input_file_name=argv;
	readInputFile(input_file_name);
	readNBlocks();
}

Interface::~Interface()
{

}


#endif
