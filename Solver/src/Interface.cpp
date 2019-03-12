#ifndef SOLVERSKELETON_SRC_INTERFACE_CPP
#define SOLVERSKELETON_SRC_INTERFACE_CPP

#include "Interface.h"

#include <string>
#include <iostream>
using namespace std;

void Interface::readInputFile(string input_file_name)
{
	string line_in_file;

	ifstream input_file;
	cout << "Reading Input File..."<<endl;
	input_file.open(input_file_name);
	if (input_file.fail())
	{
		cout << "Opening File Failure..."<<endl;
	}

	// Skipping "MESH" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);
	// Skipping "topogyfilename" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);


	// Reading Topology File Name
	input_file >> topology_file_name_interface_;
	cout << "Topology File Name is: " << topology_file_name_ << endl;

	// Skipping "INPUT" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);
	
	// Skipping "cfl gamma angleattackdeg" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);

	// Reading CFL Number
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
	getline(input_file, line_in_file);

	// Reading Number of Runge-Kutta Stages
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
	getline(input_file, line_in_file);

	// Reading Maximum Number of Iterations
	input_file >> max_iter_interface_;
	cout << "Maximum Number of Iterations is: " << max_iter_interface_ << endl;

	// Reading Convergence Criterion
	input_file >> convergence_criterion_interface_;
	cout << "Convergence Criterion is: " << convergence_criterion_interface_ << endl;

	// Skipping "residual smoothing (0-no 1-yes)" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);

	// Reading Residual Smoother Choice
	input_file >> residual_smoother_choice_interface_;
	cout << "Residual Smoother Choice is: " << residual_smoother_choice_interface_ << endl;

	// Skipping "fluxscheme schemeorder" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);

	// Reading Flux Scheme Choice
	input_file >> flux_scheme_choice_interface_;
	cout << "Flux Scheme Choice is: " << flux_scheme_choice_interface_ << endl;

	// Reading Flux Scheme Order
	input_file >> interpolation_choice_interface_;
	cout << "Residual Interpolation Order is: " << interpolation_choice_interface_ << endl;

	// Skipping "gradient limiter" Line
	input_file.ignore(256, '\n');
	getline(input_file, line_in_file);

	// Reading Gradient Choice
	input_file >> gradient_choice_interface_;
	cout << "Gradient Choice is: " << gradient_choice_interface_ << endl;

	// Reading Limiter Choice
	input_file >> limiter_choice_interface_;
	cout << "Limiter Choice is: " << limiter_choice_interface_ << endl;


}

Interface::Interface(double gamma, double cfl, int stage_number, int interpolation_choice, string gradient_choice, string limiter_choice, string flux_scheme_choice, bool residual_smoother_choice)
{
	gamma_interface_=gamma;
	cfl_interface_=cfl;
	stage_number_interface_=stage_number;
	interpolation_choice_interface_=interpolation_choice;
	gradient_choice_interface_=gradient_choice;
	limiter_choice_interface_=limiter_choice;
	flux_scheme_choice_interface_=flux_scheme_choice;
	residual_smoother_choice_interface_=residual_smoother_choice;
}


Interface::Interface()
{
	gamma_interface_=1.5;
	cfl_interface_=1.0;
	stage_number_interface_=5;
	interpolation_choice_interface_=1;
	gradient_choice_interface_="LeastSquares";
	limiter_choice_interface_="Venkatakrishnan";
	flux_scheme_choice_interface_="Roe";
	residual_smoother_choice_interface_=TRUE;

	n_blocks_interface_=5;
	max_iter_interface_=25;
	convergence_criterion_interface_=pow(10,-16);
	cmac_interface_=1.0;
}

Interface::~Interface()
{

}


#endif
