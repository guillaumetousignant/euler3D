#ifndef SOLVERSKELETON_SRC_GREENGAUSS_CPP
#define SOLVERSKELETON_SRC_GREENGAUSS_CPP

#include "Block.h"
#include "Gradient.h"
#include "GreenGauss.h"


#include <iostream>
using namespace std;

void GreenGauss::computeGradients(Block* block)
{
	double rho_L,u_L,v_L,w_L,p_L,rho_R,u_R,v_R,w_R,p_R;
	Cell* my_cell;
	int my_cell_n_faces;
	int* my_cell_2_faces_connectivity;
	double real_cell_volume;

	double *face_normals;

	int left_cell, right_cell; // my_face,
	int* neighboor_cells;
	Face* my_face;
	int my_face_in_cell_idx;

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

	int n_dim=3;


	
	int n_all_cells_in_block= block -> n_all_cells_in_block_;

	// Initialize all gradients to 0

	for (int all_cell_idx = 0; all_cell_idx < n_all_cells_in_block; all_cell_idx++)
	{
		// Initialize gradients to 0
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[all_cell_idx][dim_idx]=0.0;
			my_grad_uu_array[all_cell_idx][dim_idx]=0.0;
			my_grad_vv_array[all_cell_idx][dim_idx]=0.0;
			my_grad_ww_array[all_cell_idx][dim_idx]=0.0;
			my_grad_pp_array[all_cell_idx][dim_idx]=0.0;
		}


	}

	int n_real_cells_in_block = block -> n_real_cells_in_block_;
	// Set gradients in real cells

	for (int real_cell_idx = 0; real_cell_idx < n_real_cells_in_block; real_cell_idx++)
	{
		// Loop on cell2faces
		my_cell=block->block_cells_[real_cell_idx];
		my_cell_n_faces=my_cell->n_faces_per_cell_;
		my_cell_2_faces_connectivity=my_cell->cell_2_faces_connectivity_;

		for (int cell_2_faces_idx=0;cell_2_faces_idx<my_cell_n_faces;cell_2_faces_idx++)
		{
			my_face_in_cell_idx=my_cell_2_faces_connectivity[cell_2_faces_idx];
			
			my_face=block->block_faces_[my_face_in_cell_idx];
			
			face_normals=my_face->face_normals_;
			
			// Check if cell is on right or on left

			// n is always left to right
			if(real_cell_idx==my_face->face_2_cells_connectivity_[0])
			{
				// Cell is on left, orientation is ok
			}
			else
			{
				// Cell is on right, orientation needs to be opposite
				for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
				{
					face_normals[dim_idx]*=1.0;
				}

			}

			neighboor_cells = my_face -> face_2_cells_connectivity_;
			left_cell = neighboor_cells[0];
			right_cell = neighboor_cells[1];

			// Left cell
			rho_L = my_ro_array[left_cell];
			u_L = my_uu_array[left_cell];
			v_L = my_vv_array[left_cell];
			w_L = my_ww_array[left_cell];
			p_L = my_pp_array[left_cell];

			// Right cell
			rho_R = my_ro_array[right_cell];
			u_R = my_uu_array[right_cell];
			v_R = my_vv_array[right_cell];
			w_R = my_ww_array[right_cell];
			p_R = my_pp_array[right_cell];

			// Compute gradients

			// Note: face_normals has not been normalized, so no need to muliply by face_area
			for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
			{
				my_grad_ro_array[real_cell_idx][dim_idx]=0.5*(rho_L+rho_R)*face_normals[dim_idx];
				my_grad_uu_array[real_cell_idx][dim_idx]=0.5*(u_L+u_R)*face_normals[dim_idx];
				my_grad_vv_array[real_cell_idx][dim_idx]=0.5*(v_L+v_R)*face_normals[dim_idx];
				my_grad_ww_array[real_cell_idx][dim_idx]=0.5*(w_L+w_R)*face_normals[dim_idx];
				my_grad_pp_array[real_cell_idx][dim_idx]=0.5*(p_L+p_R)*face_normals[dim_idx];
			}

		}

		// Divide by volume
		real_cell_volume=my_cell->cell_volume_;

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[real_cell_idx][dim_idx]/=real_cell_volume;
			my_grad_uu_array[real_cell_idx][dim_idx]/=real_cell_volume;
			my_grad_vv_array[real_cell_idx][dim_idx]/=real_cell_volume;
			my_grad_ww_array[real_cell_idx][dim_idx]/=real_cell_volume;
			my_grad_pp_array[real_cell_idx][dim_idx]/=real_cell_volume;
		}

	}

	// Reflection formlua is r=d-2(d\dot n)*n, where r is reflected vector, d is incident vector and n is normalized face vector

	// Set gradients in wall cells
	int n_wall_faces=block->n_wall_faces_;
	int wall_face_idx;

	int int_cell_idx;
	int ext_cell_idx;

	double* wall_face_normals_normalized;
	double face_area;

	double ro_dot_product, uu_dot_product, vv_dot_product, ww_dot_product, pp_dot_product;

	for (int i = 0; i < n_wall_faces; i++)
	{
		wall_face_idx=block -> block_wall_face_ids_[i];

		int_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[0];
		ext_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[1];

		wall_face_normals_normalized=block->block_faces_[wall_face_idx]->face_normals_;		
		face_area=block->block_faces_[wall_face_idx]->face_area_;

		// Normalized normals
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			wall_face_normals_normalized[dim_idx]/=face_area;
		}

		// Compute dot product
		ro_dot_product=0.0;
		uu_dot_product=0.0;
		vv_dot_product=0.0;
		ww_dot_product=0.0;
		pp_dot_product=0.0;

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
		}

		// Compute reflected gradients

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*wall_face_normals_normalized[dim_idx];
			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*wall_face_normals_normalized[dim_idx];
			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*wall_face_normals_normalized[dim_idx];
			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*wall_face_normals_normalized[dim_idx];
			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*wall_face_normals_normalized[dim_idx];
		}



	}

	// Set gradients in symmetry cells
	int n_symmetry_faces=block->n_symmetry_faces_;
	int symmetry_face_idx;

	double* symmetry_face_normals_normalized;

	for (int i = 0; i < n_symmetry_faces; i++)
	{
		symmetry_face_idx=block -> block_symmetry_face_ids_[i];

		int_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[0];
		ext_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[1];

		symmetry_face_normals_normalized=block->block_faces_[symmetry_face_idx]->face_normals_;		
		face_area=block->block_faces_[symmetry_face_idx]->face_area_;

		// Normalized normals
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			symmetry_face_normals_normalized[dim_idx]/=face_area;
		}

		// Compute dot product
		ro_dot_product=0.0;
		uu_dot_product=0.0;
		vv_dot_product=0.0;
		ww_dot_product=0.0;
		pp_dot_product=0.0;

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
		}

		// Compute reflected gradients

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*symmetry_face_normals_normalized[dim_idx];
			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*symmetry_face_normals_normalized[dim_idx];
			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*symmetry_face_normals_normalized[dim_idx];
			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*symmetry_face_normals_normalized[dim_idx];
			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*symmetry_face_normals_normalized[dim_idx];
		}



	}

	// Set gradients in farfield cells
	int n_farfield_faces=block->n_farfield_faces_;
	int farfield_face_idx;

	double* farfield_face_normals_normalized;

	for (int i = 0; i < n_farfield_faces; i++)
	{
		farfield_face_idx=block -> block_farfield_face_ids_[i];

		int_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[0];
		ext_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[1];

		farfield_face_normals_normalized=block->block_faces_[farfield_face_idx]->face_normals_;		
		face_area=block->block_faces_[farfield_face_idx]->face_area_;

		// Normalized normals
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			farfield_face_normals_normalized[dim_idx]/=face_area;
		}

		// Compute dot product
		ro_dot_product=0.0;
		uu_dot_product=0.0;
		vv_dot_product=0.0;
		ww_dot_product=0.0;
		pp_dot_product=0.0;

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
		}

		// Compute reflected gradients

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*farfield_face_normals_normalized[dim_idx];
			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*farfield_face_normals_normalized[dim_idx];
			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*farfield_face_normals_normalized[dim_idx];
			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*farfield_face_normals_normalized[dim_idx];
			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*farfield_face_normals_normalized[dim_idx];
		}



	}

}



GreenGauss::GreenGauss()
{

}

GreenGauss::~GreenGauss()
{

}


#endif
