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
	block->test_block_+=2;
	cout<<"\t\tExécution computeSpectralRadius: "<<block->test_block_<<endl;
	// P.211 Blazek !!!	watch out pour delta_s s'il doit multiplier juste c ou non (dépend de comment n définit face_normals_y)
	/*
	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;
	double* my_ro_array,my_uu_array,my_vv_array,my_ww_array,my_pp_array;
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	double c;

	Cell* my_cells;
	my_cells = block -> block_cells_;
	ncell = block -> n_real_cells_in_block_;

	Face* my_faces;
	my_faces = block -> bloc_faces_;
	nface = block -> n_faces_in_block_;

	TimeVariables* time_variables;
	time_variables = block -> block_time_variables_;
	double** spectral_radius_array;
	spectral_radius_array = time_variables -> spectral_radius_;

	double* cell_spectral_radius;

	for(int cell_idx = 0; cell_idx < ncell; cell_idx++)
	{
		my_cell = my_cells[cell_idx];
		c = sqrt(gamma_*my_pp_array[my_cell]/my_ro_array[my_cell]);

		// (Je peux faire un sizeof de cell2face, mais on perdrait de la performance, Laurent va pt le faire dans la connectivité, à suivre....)
		for(int face_idx = 0; face_idx < face_in_cell; face_idx++) HOW TO I ACCCES face_in_cell?????
		{
			face_idx =

			cell_spectral_radius = spectral_radius_array[cell_idx];


			// .old
			delta_s = sqrt(norm_x[face_idx]*norm_x[face_idx]+norm_y[face_idx]*norm_y[face_idx]+norm_z[face_idx]*norm_z[face_idx]) !!!!!!!!!!!!!! DELTA_S ATTENTION SCALAIRE/VOLUME
			spectral_radius[cell_idx] += fabs(my_uu_array[cell_idx]*(*face_normals_x)[face_idx]+my_vv_array[cell_idx]*(*face_normals_y)[face_idx]+my_ww_array[cell_idx]*(*face_normals_z)[face_idx])+c*delta_s
		}
	}
	*/
}

void Timestep::computeTimestep(Block* block)
{
	block->test_block_-=2;
	cout<<"\t\tExécution computeTimestep: "<<block->test_block_<<endl;

	// for(int cell = 0; cell < ncell; cell++) HOW TO I ACCCES ncell?????
	//{
	//delta_t[cell] = cfl_*cells_areas[cell]/spectral_radius[cell]; VOLUMEEEEEEEEE!
	//}
}


#endif
