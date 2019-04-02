#ifndef SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP
#define SOLVERSKELETON_SRC_BARTHJESPERSEN_CPP

#include "Block.h"
#include "Limiter.h"
#include "BarthJespersen.h"

#include <limits>
#include <math.h> 
#include <cmath>
#include <iostream>
using namespace std;

void BarthJespersen::computeLimiters(Block* block)
{
	int n_dim=3;

	double ro_max, uu_max, vv_max, ww_max, pp_max;
	double ro_min, uu_min, vv_min, ww_min, pp_min;
	double ro_neighbor, uu_neighbor, vv_neighbor, ww_neighbor, pp_neighbor;

	double delta_ro_max, delta_uu_max, delta_vv_max, delta_ww_max, delta_pp_max;
	double delta_ro_min, delta_uu_min, delta_vv_min, delta_ww_min, delta_pp_min;
	double delta_2_ro, delta_2_uu, delta_2_vv, delta_2_ww, delta_2_pp;

	double ro_limiter_face, uu_limiter_face, vv_limiter_face, ww_limiter_face, pp_limiter_face;

	double* my_ro_array;
	double* my_uu_array;
	double* my_vv_array;
	double* my_ww_array;
	double* my_pp_array;

	PrimitiveVariables* my_primitive_variables;
	my_primitive_variables = block -> block_primitive_variables_;
	
	my_ro_array = my_primitive_variables -> ro_;
	my_uu_array = my_primitive_variables -> uu_;
	my_vv_array = my_primitive_variables -> vv_;
	my_ww_array = my_primitive_variables -> ww_;
	my_pp_array = my_primitive_variables -> pp_;

	InterpolationVariables* my_interpolation_variables;
	my_interpolation_variables=block->block_interpolation_variables_;

	double** my_grad_ro_array;
	double** my_grad_uu_array;
	double** my_grad_vv_array;
	double** my_grad_ww_array;
	double** my_grad_pp_array;

	my_grad_ro_array=my_interpolation_variables->grad_ro_;
	my_grad_uu_array=my_interpolation_variables->grad_uu_;
	my_grad_vv_array=my_interpolation_variables->grad_vv_;
	my_grad_ww_array=my_interpolation_variables->grad_ww_;
	my_grad_pp_array=my_interpolation_variables->grad_pp_;

	double* my_ro_limiters;
	double* my_uu_limiters;
	double* my_vv_limiters;
	double* my_ww_limiters;
	double* my_pp_limiters;

	my_ro_limiters = my_interpolation_variables -> limiter_ro_;
	my_uu_limiters = my_interpolation_variables -> limiter_uu_;
	my_vv_limiters = my_interpolation_variables -> limiter_vv_;
	my_ww_limiters = my_interpolation_variables -> limiter_ww_;
	my_pp_limiters = my_interpolation_variables -> limiter_pp_;

	double* face_r_vector;


	Cell* my_cell;
	Face* my_neighbor_face;
	
	int my_cell_n_faces;

	int* my_cell_2_cells_connectivity;
	int my_neighbor_cell_idx;

	int* my_cell_2_faces_connectivity;
	int my_neighbor_face_idx;

	int n_all_cells_in_block=block->n_all_cells_in_block_;

	// Find U_max and U_min for a given cell
	// Loop on all cells
	for (int all_cell_idx = 0; all_cell_idx < n_all_cells_in_block; all_cell_idx++)
	{

		my_cell=block->block_cells_[all_cell_idx];


		// Initialize U_min & U_max to cell values
		ro_max=my_ro_array[all_cell_idx];
		uu_max=my_uu_array[all_cell_idx];
		vv_max=my_vv_array[all_cell_idx];
		ww_max=my_ww_array[all_cell_idx];
		pp_max=my_pp_array[all_cell_idx];

		ro_min=my_ro_array[all_cell_idx];
		uu_min=my_uu_array[all_cell_idx];
		vv_min=my_vv_array[all_cell_idx];
		ww_min=my_ww_array[all_cell_idx];
		pp_min=my_pp_array[all_cell_idx];

		// Loop on neighbor cells with cell2cells
		my_cell_n_faces=my_cell->n_faces_per_cell_;
		my_cell_2_cells_connectivity=my_cell->cell_2_cells_connectivity_;

		for (int cell_2_cells_idx=0;cell_2_cells_idx<my_cell_n_faces;cell_2_cells_idx++)
		{	
			my_neighbor_cell_idx=my_cell_2_cells_connectivity[cell_2_cells_idx];
			
			ro_neighbor=my_ro_array[my_neighbor_cell_idx];
			uu_neighbor=my_uu_array[my_neighbor_cell_idx];
			vv_neighbor=my_vv_array[my_neighbor_cell_idx];
			ww_neighbor=my_ww_array[my_neighbor_cell_idx];
			pp_neighbor=my_pp_array[my_neighbor_cell_idx];

			if (ro_neighbor>ro_max)
			{
				ro_max=ro_neighbor;
			}
			if (uu_neighbor>uu_max)
			{
				uu_max=uu_neighbor;
			}
			if (vv_neighbor>vv_max)
			{
				vv_max=vv_neighbor;
			}
			if (ww_neighbor>ww_max)
			{
				ww_max=ww_neighbor;
			}
			if (pp_neighbor>pp_max)
			{
				pp_max=pp_neighbor;
			}

			if (ro_neighbor<ro_min)
			{
				ro_min=ro_neighbor;
			}
			if (uu_neighbor<uu_min)
			{
				uu_min=uu_neighbor;
			}
			if (vv_neighbor<vv_min)
			{
				vv_min=vv_neighbor;
			}
			if (ww_neighbor<ww_min)
			{
				ww_min=ww_neighbor;
			}
			if (pp_neighbor<pp_min)
			{
				pp_min=pp_neighbor;
			}

		}

		// Find delta min and delta max

		delta_ro_max=ro_max-my_ro_array[all_cell_idx];
		delta_uu_max=uu_max-my_uu_array[all_cell_idx];
		delta_vv_max=vv_max-my_vv_array[all_cell_idx];
		delta_ww_max=ww_max-my_ww_array[all_cell_idx];
		delta_pp_max=pp_max-my_pp_array[all_cell_idx];

		delta_ro_min=ro_min-my_ro_array[all_cell_idx];
		delta_uu_min=uu_min-my_uu_array[all_cell_idx];
		delta_vv_min=vv_min-my_vv_array[all_cell_idx];
		delta_ww_min=ww_min-my_ww_array[all_cell_idx];
		delta_pp_min=pp_min-my_pp_array[all_cell_idx];
		
		// Set limiters to infinity
		my_ro_limiters[all_cell_idx]= std::numeric_limits<double>::infinity();
		my_uu_limiters[all_cell_idx]= std::numeric_limits<double>::infinity();
		my_vv_limiters[all_cell_idx]= std::numeric_limits<double>::infinity();
		my_ww_limiters[all_cell_idx]= std::numeric_limits<double>::infinity();
		my_pp_limiters[all_cell_idx]= std::numeric_limits<double>::infinity();

		// Loop on neighbor faces
		my_cell_2_faces_connectivity=my_cell->cell_2_faces_connectivity_;


		for (int cell_2_faces_idx=0;cell_2_faces_idx<my_cell_n_faces;cell_2_faces_idx++)
		{	
			my_neighbor_face_idx=my_cell_2_faces_connectivity[cell_2_faces_idx];
			my_neighbor_face=block->block_faces_[my_neighbor_face_idx];

			// Find corresponding r vector
			// if cell is on left
			if (all_cell_idx==my_neighbor_face->face_2_cells_connectivity_[0])
			{
				face_r_vector=my_neighbor_face->left_cell_r_vector_;
			}
			// if cell is on right
			else
			{
				face_r_vector=my_neighbor_face->right_cell_r_vector_;
			}

			
			// Initialize delta2
			delta_2_ro=0.0;
			delta_2_uu=0.0;
			delta_2_vv=0.0;
			delta_2_ww=0.0;
			delta_2_pp=0.0;

			// Find delta2
			for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
			{
				delta_2_ro+=my_grad_ro_array[all_cell_idx][dim_idx]*face_r_vector[dim_idx];
				delta_2_uu+=my_grad_uu_array[all_cell_idx][dim_idx]*face_r_vector[dim_idx];
				delta_2_vv+=my_grad_vv_array[all_cell_idx][dim_idx]*face_r_vector[dim_idx];
				delta_2_ww+=my_grad_ww_array[all_cell_idx][dim_idx]*face_r_vector[dim_idx];
				delta_2_pp+=my_grad_pp_array[all_cell_idx][dim_idx]*face_r_vector[dim_idx];
			}

			// Apply Omega correction
			delta_2_ro=(copysign(1.0,delta_2_ro))*(fabs(delta_2_ro)+omega_);
			delta_2_uu=(copysign(1.0,delta_2_uu))*(fabs(delta_2_uu)+omega_);
			delta_2_vv=(copysign(1.0,delta_2_vv))*(fabs(delta_2_vv)+omega_);
			delta_2_ww=(copysign(1.0,delta_2_ww))*(fabs(delta_2_ww)+omega_);
			delta_2_pp=(copysign(1.0,delta_2_pp))*(fabs(delta_2_pp)+omega_);

			// Apply Venkatakrishnan
			//ro
			if (delta_2_ro>0.0)
			{
				ro_limiter_face=fmin(1.0,delta_ro_max/delta_2_ro);
			}
			else if (delta_2_ro<0.0)
			{
				ro_limiter_face=fmin(1.0,delta_ro_min/delta_2_ro);
			}
			else
			{
				ro_limiter_face=1.0;
			}

			if (ro_limiter_face<my_ro_limiters[all_cell_idx])
			{
				my_ro_limiters[all_cell_idx]=ro_limiter_face;
			}

			//uu
			if (delta_2_uu>0.0)
			{
				uu_limiter_face=fmin(1.0,delta_uu_max/delta_2_uu);
			}
			else if (delta_2_uu<0.0)
			{
				uu_limiter_face=fmin(1.0,delta_uu_min/delta_2_uu);
			}
			else
			{
				uu_limiter_face=1.0;
			}

			if (uu_limiter_face<my_uu_limiters[all_cell_idx])
			{
				my_uu_limiters[all_cell_idx]=uu_limiter_face;
			}

			//vv
			if (delta_2_vv>0.0)
			{
				vv_limiter_face=fmin(1.0,delta_vv_max/delta_2_vv);
			}
			else if (delta_2_vv<0.0)
			{
				vv_limiter_face=fmin(1.0,delta_vv_min/delta_2_vv);
			}
			else
			{
				vv_limiter_face=1.0;
			}

			if (vv_limiter_face<my_vv_limiters[all_cell_idx])
			{
				my_vv_limiters[all_cell_idx]=vv_limiter_face;
			}

			//ww
			if (delta_2_ww>0.0)
			{
				ww_limiter_face=fmin(1.0,delta_ww_max/delta_2_ww);
			}
			else if (delta_2_ww<0.0)
			{
				ww_limiter_face=fmin(1.0,delta_ww_min/delta_2_ww);
			}
			else
			{
				ww_limiter_face=1.0;
			}

			if (ww_limiter_face<my_ww_limiters[all_cell_idx])
			{
				my_ww_limiters[all_cell_idx]=ww_limiter_face;
			}

			//pp
			if (delta_2_pp>0.0)
			{
				pp_limiter_face=fmin(1.0,delta_pp_max/delta_2_pp);
			}
			else if (delta_2_pp<0.0)
			{
				pp_limiter_face=fmin(1.0,delta_pp_min/delta_2_pp);
			}
			else
			{
				pp_limiter_face=1.0;
			}

			if (pp_limiter_face<my_pp_limiters[all_cell_idx])
			{
				my_pp_limiters[all_cell_idx]=pp_limiter_face;
			}

		}
		

	}

}



BarthJespersen::BarthJespersen(double omega)
{
	omega_=omega;
}

BarthJespersen::~BarthJespersen()
{

}


#endif
