#ifndef SOLVERSKELETON_SRC_TIMESTEP_CPP
#define SOLVERSKELETON_SRC_TIMESTEP_CPP

#include "Block.h"

#include "Timestep.h"

#include <math.h>
#include <string>
#include <iostream>
using namespace std;

//Constructor
Timestep::Timestep(double gamma, double cfl)
{
	gamma_ = gamma;
	cfl_=cfl;
}


Timestep::~Timestep()
{

}

void Timestep::computeSpectralRadius(Block* block)
{
	cout<<"\t\tExécution computeSpectralRadius: "<<endl;
	// P.211 Blazek !!!	watch out pour delta_s s'il doit multiplier juste c ou non (dépend de comment n définit face_normals_y)

	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;
	double* my_ro_array;
	double* my_uu_array;
	double* my_vv_array;
	double* my_ww_array;
	double* my_pp_array;
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	double c;

	//Cell* my_cell;
	// my_cells = block -> block_cells_;
	int ncell;
	ncell = block -> n_real_cells_in_block_;

	//Face* my_face;
	// my_faces = block -> block_faces_;
	//int nface;
	//nface = block -> n_faces_in_block_;

	TimeVariables* time_variables;
	time_variables = block -> block_time_variables_;
	double* spectral_radius;
	spectral_radius = time_variables -> spectral_radius_;

	int face_id;

	int n_face_per_cell;

	double normalized_x,normalized_y,normalized_z,delta_s;

	for(int cell_idx = 0; cell_idx < ncell; cell_idx++)
	{
		cout << "======================================================================" << endl;
		cout << "cellule id =" << cell_idx << endl;
		c = sqrt(gamma_*my_pp_array[cell_idx]/my_ro_array[cell_idx]);
		cout << "vitesse du son c =" << c << endl;
		cout << "pp cell =" << my_pp_array[cell_idx] << endl;
		cout << "ro cell =" << my_ro_array[cell_idx] << endl;
		n_face_per_cell = block -> block_cells_[cell_idx] -> n_faces_per_cell_;
		spectral_radius[cell_idx] =0.0;
		for(int face_idx = 0; face_idx < n_face_per_cell; face_idx++)
		{
			cout << "face num = " << face_idx << endl;
			face_id = block -> block_cells_[cell_idx] -> cell_2_faces_connectivity_[face_idx];
			cout << "face id = " << face_id << endl;
			normalized_x = block -> block_faces_[face_id] -> face_normals_[0];
			normalized_y = block -> block_faces_[face_id] -> face_normals_[1];
			normalized_z = block -> block_faces_[face_id] -> face_normals_[2];
			delta_s = sqrt(normalized_x*normalized_x+normalized_y*normalized_y+normalized_z*normalized_z);
			normalized_x /= delta_s;
			normalized_y /= delta_s;
			normalized_z /= delta_s;
			cout << "normalized x = " << normalized_x << "       normalized y = " << normalized_y << "        normalized z = " << normalized_z << endl;
			cout << "uu = " << my_uu_array[cell_idx] << endl;
			cout << "vv = " << my_vv_array[cell_idx] << endl;
			cout << "ww = " << my_ww_array[cell_idx] << endl;
			cout << "delta_s = " << delta_s << endl;
			spectral_radius[cell_idx] += fabs(my_uu_array[cell_idx]*normalized_x+my_vv_array[cell_idx]*normalized_y+my_ww_array[cell_idx]*normalized_z) + c*delta_s;
			cout << "spectral_radius cell = " << spectral_radius[cell_idx] << endl;
		}
	}

}

void Timestep::computeTimestep(Block* block)
{
	cout<<"\t\tExécution computeTimestep: "<<endl;

	Cell* my_cell;
	int ncell;
	ncell = block -> n_real_cells_in_block_;
	double cell_volume;

	TimeVariables* time_variables;
	time_variables = block -> block_time_variables_;
	double* spectral_radius;
	spectral_radius = time_variables -> spectral_radius_;
	double* dt;
	dt = time_variables -> dt_;

	for(int cell_idx = 0; cell_idx < ncell; cell_idx++)
	{
		my_cell = block -> block_cells_[cell_idx];
		cell_volume  = my_cell -> cell_volume_;

		dt[cell_idx] = cfl_*cell_volume/spectral_radius[cell_idx];
		// cout << "dt = " << dt[cell_idx] << endl;
	}

}


#endif
