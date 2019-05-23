#ifndef SOLVERSKELETON_SRC_LEASTSQUARES_CPP
#define SOLVERSKELETON_SRC_LEASTSQUARES_CPP

#include "Block.h"
#include "Gradient.h"
#include "LeastSquares.h"


#include <iostream>
using namespace std;

void LeastSquares::computeGradients(Block* block)
{
	double rho_0,u_0,v_0,w_0,p_0,rho_i,u_i,v_i,w_i,p_i;
	Cell* my_cell;
	int my_cell_n_faces;
	int* my_cell_2_cells_connectivity;
	int n_dim=3;

	double** cell_weights; // ATTENTION NE PAS MODIFIER

	int my_neighbor_cell_idx;

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





	int n_real_cells_in_block= block -> n_real_cells_in_block_;

	// Initialize real gradients to 0

	for (int real_cell_idx = 0; real_cell_idx < n_real_cells_in_block; real_cell_idx++)
	{
		// Initialize gradients to 0
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[real_cell_idx][dim_idx]=0.0;
			my_grad_uu_array[real_cell_idx][dim_idx]=0.0;
			my_grad_vv_array[real_cell_idx][dim_idx]=0.0;
			my_grad_ww_array[real_cell_idx][dim_idx]=0.0;
			my_grad_pp_array[real_cell_idx][dim_idx]=0.0;
		}


	}

	// int n_real_cells_in_block = block -> n_real_cells_in_block_;
	// Set gradients in real cells

	for (int real_cell_idx = 0; real_cell_idx < n_real_cells_in_block; real_cell_idx++)
	{
		// Loop on cell2cells
		my_cell=block->block_cells_[real_cell_idx];
		my_cell_n_faces=my_cell->n_faces_per_cell_;
		my_cell_2_cells_connectivity=my_cell->cell_2_cells_connectivity_;

		for (int cell_2_cells_idx=0;cell_2_cells_idx<my_cell_n_faces;cell_2_cells_idx++)
		{
			my_neighbor_cell_idx=my_cell_2_cells_connectivity[cell_2_cells_idx];
			cell_weights=my_cell->cell_weights_;

			// Center cell
			rho_0 = my_ro_array[real_cell_idx];
			u_0 = my_uu_array[real_cell_idx];
			v_0 = my_vv_array[real_cell_idx];
			w_0 = my_ww_array[real_cell_idx];
			p_0 = my_pp_array[real_cell_idx];

			// Neighbor cell
			rho_i = my_ro_array[my_neighbor_cell_idx];
			u_i = my_uu_array[my_neighbor_cell_idx];
			v_i = my_vv_array[my_neighbor_cell_idx];
			w_i = my_ww_array[my_neighbor_cell_idx];
			p_i = my_pp_array[my_neighbor_cell_idx];

			// Compute gradients

			for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
			{
				my_grad_ro_array[real_cell_idx][dim_idx]+=cell_weights[cell_2_cells_idx][dim_idx]*(rho_i-rho_0);
				my_grad_uu_array[real_cell_idx][dim_idx]+=cell_weights[cell_2_cells_idx][dim_idx]*(u_i-u_0);
				my_grad_vv_array[real_cell_idx][dim_idx]+=cell_weights[cell_2_cells_idx][dim_idx]*(v_i-v_0);
				my_grad_ww_array[real_cell_idx][dim_idx]+=cell_weights[cell_2_cells_idx][dim_idx]*(w_i-w_0);
				my_grad_pp_array[real_cell_idx][dim_idx]+=cell_weights[cell_2_cells_idx][dim_idx]*(p_i-p_0);
			}

		}

	}



	// Reflection formlua is r=d-2(d\dot n)*n, where r is reflected vector, d is incident vector and n is normalized face vector

/////////////////////////////////////////////////////////////////new method with boundary objects

int n_boundaries_real=block->n_real_boundaries_in_block_;
for (int j=0;j<n_boundaries_real;j++)
{
	int n_boundary_faces=((block->block_boundary_cell_ids_)[j])->n_cell_in_boundary_;
	int boundary_face_idx;

	int int_cell_idx;
	int ext_cell_idx;

	double boundary_face_normals_normalized[n_dim];
	double face_area;

	double ro_dot_product, uu_dot_product, vv_dot_product, ww_dot_product, pp_dot_product;

	for (int i = 0; i < n_boundary_faces; i++)
	{
		ext_cell_idx=(block->block_boundary_cell_ids_[j])->cell_ids_in_boundary_[i];

		boundary_face_idx=(block -> block_cells_[ext_cell_idx])->cell_2_faces_connectivity_[0];
		int_cell_idx=block->block_faces_[boundary_face_idx]->face_2_cells_connectivity_[0];

		face_area=block->block_faces_[boundary_face_idx]->face_area_;

		// Normalized normals
		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			boundary_face_normals_normalized[dim_idx]=block->block_faces_[boundary_face_idx]->face_normals_[dim_idx];
			boundary_face_normals_normalized[dim_idx]/=face_area;
		}

		// Compute dot product
		ro_dot_product=0.0;
		uu_dot_product=0.0;
		vv_dot_product=0.0;
		ww_dot_product=0.0;
		pp_dot_product=0.0;

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*boundary_face_normals_normalized[dim_idx];
			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*boundary_face_normals_normalized[dim_idx];
			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*boundary_face_normals_normalized[dim_idx];
			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*boundary_face_normals_normalized[dim_idx];
			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*boundary_face_normals_normalized[dim_idx];
		}

		// Compute reflected gradients

		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
		{
			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*boundary_face_normals_normalized[dim_idx];
			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*boundary_face_normals_normalized[dim_idx];
			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*boundary_face_normals_normalized[dim_idx];
			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*boundary_face_normals_normalized[dim_idx];
			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*boundary_face_normals_normalized[dim_idx];
		}

	}

}


// /////////////////////////////////////////////////////////////////old method without boundary objects
// 	// Set gradients in wall cells
// 	int n_wall_faces=block->n_wall_faces_;
// 	int wall_face_idx;

// 	int int_cell_idx;
// 	int ext_cell_idx;

// 	double wall_face_normals_normalized[n_dim];
// 	double face_area;

// 	double ro_dot_product, uu_dot_product, vv_dot_product, ww_dot_product, pp_dot_product;

// 	for (int i = 0; i < n_wall_faces; i++)
// 	{
// 		wall_face_idx=block -> block_wall_face_ids_[i];

// 		int_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[0];
// 		ext_cell_idx=block->block_faces_[wall_face_idx]->face_2_cells_connectivity_[1];

// 		face_area=block->block_faces_[wall_face_idx]->face_area_;

// 		// Normalized normals
// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			wall_face_normals_normalized[dim_idx]=block->block_faces_[wall_face_idx]->face_normals_[dim_idx];
// 			wall_face_normals_normalized[dim_idx]/=face_area;
// 		}

// 		// Compute dot product
// 		ro_dot_product=0.0;
// 		uu_dot_product=0.0;
// 		vv_dot_product=0.0;
// 		ww_dot_product=0.0;
// 		pp_dot_product=0.0;

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
// 			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
// 			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
// 			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
// 			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*wall_face_normals_normalized[dim_idx];
// 		}

// 		// Compute reflected gradients

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*wall_face_normals_normalized[dim_idx];
// 			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*wall_face_normals_normalized[dim_idx];
// 			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*wall_face_normals_normalized[dim_idx];
// 			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*wall_face_normals_normalized[dim_idx];
// 			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*wall_face_normals_normalized[dim_idx];
// 		}



// 	}

// 	// Set gradients in symmetry cells
// 	int n_symmetry_faces=block->n_symmetry_faces_;
// 	int symmetry_face_idx;

// 	double symmetry_face_normals_normalized[n_dim];

// 	for (int i = 0; i < n_symmetry_faces; i++)
// 	{
// 		symmetry_face_idx=block -> block_symmetry_face_ids_[i];

// 		int_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[0];
// 		ext_cell_idx=block->block_faces_[symmetry_face_idx]->face_2_cells_connectivity_[1];

// 		face_area=block->block_faces_[symmetry_face_idx]->face_area_;

// 		// Normalized normals
// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			symmetry_face_normals_normalized[dim_idx]=block->block_faces_[symmetry_face_idx]->face_normals_[dim_idx];
// 			symmetry_face_normals_normalized[dim_idx]/=face_area;
// 		}

// 		// Compute dot product
// 		ro_dot_product=0.0;
// 		uu_dot_product=0.0;
// 		vv_dot_product=0.0;
// 		ww_dot_product=0.0;
// 		pp_dot_product=0.0;

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
// 			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
// 			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
// 			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
// 			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*symmetry_face_normals_normalized[dim_idx];
// 		}

// 		// Compute reflected gradients

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*symmetry_face_normals_normalized[dim_idx];
// 			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*symmetry_face_normals_normalized[dim_idx];
// 			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*symmetry_face_normals_normalized[dim_idx];
// 			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*symmetry_face_normals_normalized[dim_idx];
// 			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*symmetry_face_normals_normalized[dim_idx];
// 		}



// 	}

// 	// Set gradients in farfield cells
// 	int n_farfield_faces=block->n_farfield_faces_;
// 	int farfield_face_idx;

// 	double farfield_face_normals_normalized[n_dim];

// 	for (int i = 0; i < n_farfield_faces; i++)
// 	{
// 		farfield_face_idx=block -> block_farfield_face_ids_[i];

// 		int_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[0];
// 		ext_cell_idx=block->block_faces_[farfield_face_idx]->face_2_cells_connectivity_[1];

// 		face_area=block->block_faces_[farfield_face_idx]->face_area_;

// 		// Normalized normals
// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			farfield_face_normals_normalized[dim_idx]=block->block_faces_[farfield_face_idx]->face_normals_[dim_idx];
// 			farfield_face_normals_normalized[dim_idx]/=face_area;
// 		}

// 		// Compute dot product
// 		ro_dot_product=0.0;
// 		uu_dot_product=0.0;
// 		vv_dot_product=0.0;
// 		ww_dot_product=0.0;
// 		pp_dot_product=0.0;

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			ro_dot_product+=my_grad_ro_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
// 			uu_dot_product+=my_grad_uu_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
// 			vv_dot_product+=my_grad_vv_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
// 			ww_dot_product+=my_grad_ww_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
// 			pp_dot_product+=my_grad_pp_array[int_cell_idx][dim_idx]*farfield_face_normals_normalized[dim_idx];
// 		}

// 		// Compute reflected gradients

// 		for (int dim_idx=0; dim_idx<n_dim; dim_idx++)
// 		{
// 			my_grad_ro_array[ext_cell_idx][dim_idx]=my_grad_ro_array[int_cell_idx][dim_idx]-2.0*ro_dot_product*farfield_face_normals_normalized[dim_idx];
// 			my_grad_uu_array[ext_cell_idx][dim_idx]=my_grad_uu_array[int_cell_idx][dim_idx]-2.0*uu_dot_product*farfield_face_normals_normalized[dim_idx];
// 			my_grad_vv_array[ext_cell_idx][dim_idx]=my_grad_vv_array[int_cell_idx][dim_idx]-2.0*vv_dot_product*farfield_face_normals_normalized[dim_idx];
// 			my_grad_ww_array[ext_cell_idx][dim_idx]=my_grad_ww_array[int_cell_idx][dim_idx]-2.0*ww_dot_product*farfield_face_normals_normalized[dim_idx];
// 			my_grad_pp_array[ext_cell_idx][dim_idx]=my_grad_pp_array[int_cell_idx][dim_idx]-2.0*pp_dot_product*farfield_face_normals_normalized[dim_idx];
// 		}



// 	}

}



LeastSquares::LeastSquares()
{


}

LeastSquares::~LeastSquares()
{

}


#endif
