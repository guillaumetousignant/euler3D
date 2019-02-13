#ifndef SOLVERSKELETON_SRC_TIMESTEP_CPP
#define SOLVERSKELETON_SRC_TIMESTEP_CPP

#include "Block.h"

#include "Timestep.h"

#include <math.h>
#include <string>
#include <iostream>
using namespace std;

//Constructor
Timestep::Timestep(double cfl)
{
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
	my_primitive_variables = block -> block_primitive_variables_;
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	gamma = ???
	*/
	double c;
	// for(int cell = 0; cell < ncell; cell++) HOW TO I ACCCES ncell?????
	//{
	//c = sqrt(gamma*my_pp_array[cell]/my_ro_array[cell]);
	//	for(int face = 0; face < face_in_cell; face++) HOW TO I ACCCES face_in_cell?????
	//{
	//face =
	//delta_s = sqrt(norm_x[face]*norm_x[face]+norm_y[face]*norm_y[face]+norm_z[face]*norm_z[face]) !!!!!!!!!!!!!! DELTA_S ATTENTION SCALAIRE/VOLUME
	//spectral_radius[cell] += fabs(my_uu_array[cell]*(*face_normals_x)[face]+my_vv_array[cell]*(*face_normals_y)[face]+my_ww_array[cell]*(*face_normals_z)[face])+c*delta_s
	//}
	//}
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
