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
	// loop on cell
	//c = sqrt(gamma*pp[cell]/ro[cell]);
	//		loop on face (on cell)
	//face =
	//delta_s = sqrt(norm_x[face]*norm_x[face]+norm_y[face]*norm_y[face]+norm_z[face]*norm_z[face]) !!!!!!!!!!!!!! DELTA_S ATTENTION SCALAIRE/VOLUME
	//spectral_radius[cell] += fabs(uu[cell]*(*face_normals_x)[face]+vv[cell]*(*face_normals_y)[face]+ww[cell]*(*face_normals_z)[face])+c*delta_s
	//end loop
	//end loop
}

void Timestep::computeTimestep(Block* block)
{
	block->test_block_-=2;
	cout<<"\t\tExécution computeTimestep: "<<block->test_block_<<endl;

	// loop on CELL
	//delta_t[cell] = cfl_*cells_areas[cell]/spectral_radius[cell]; VOLUMEEEEEEEEE!
	//that's it
}


#endif
