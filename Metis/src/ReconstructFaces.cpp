#ifndef METIS_SRC_RECONSTRUCTFACES_CPP
#define METIS_SRC_RECONSTRUCTFACES_CPP

#include "ReconstructFaces.h"

ReconstructFaces::ReconstructFaces(int n_blocks, int global_n_elements):n_blocks_(n_blocks), global_n_elements_(global_n_elements), block_array_4_comparaison_(nullptr), cell_flag_4_face_reconstruction(nullptr)
{
	block_array_4_comparaison_ = new int*[n_blocks_];

	cell_flag_4_face_reconstruction_ = new int[global_n_elements_](0);



	for(int i = 0, i< n_blocks_, i++)
	{
		block_array_4_comparaison_[i] = new int[n_blocks_]();
		for(int j = 0, j < n_blocks_, j++)
		{
			if(i==j)
			{
				block_array_4_comparaison_[i][j] = 1;
			}
		}
	}

}

ReconstructFaces::~ReconstructFaces()
{
	if(block_array_4_comparaison_)
	{
		for(int i = 0, i< n_blocks_, i++)
		{
			if(block_array_4_comparaison_[i])
			{
				delete [] block_array_4_comparaison_[i];
			}
		}
		delete [] block_array_4_comparaison_
	}

	if(cell_flag_4_face_reconstruction_)
	{
		delete [] cell_flag_4_face_reconstruction_;
	}

}

std::vector<int> ReconstructFaces::CompareArraysOfGlobalNodes( int first_block_id, int* first_block_node_array, int n_nodes_in_first_block, int second_block_id, int* second_block_node_array, int n_nodes_in_second_block)
{

	std::vector<int>::iterator it;

	std::vector<int> common_nodes_vector (n_nodes_in_first_block+n_nodes_in_second_block);

	std::sort(first_block_node_array,first_block_node_array+n_nodes_in_first_block);
	std::sort(second_block_node_array,second_block_node_array+n_nodes_in_second_block);

	it = std::set_intersection( first_block_node_array, first_block_node_array + n_nodes_in_first_block, second_block_node_array, second_block_node_array + n_nodes_in_second_block, common_nodes_vector.begin() )

	if(!common_nodes_vector.empty())
	{

		common_nodes_vector.resize(it-common_nodes_vector.begin());

		block_array_4_comparaison_[first_block_id][second_block_id] =1;
		block_array_4_comparaison_[second_block_id][first_block_id] =1;

	}
	return common_nodes_vector
}

ReconstructFaces::FindElementsInConnexion(std::vector<int> common_nodes_vector, std::vector<int>** global_cells_vector, std::vector<int>** global_nodes_vector, int block_id )
{

	int n_common_nodes = common_nodes_vector.size();
	int node_id;
	int cell_id;
	int n_cells_in_node;
	int n_nodes_in_cell;

	for(int i=0; i<n_common_nodes; i++)
	{
		node_id = common_nodes_vector[i];
		std::vector<int> node_2_cells_connectivity = global_nodes_vector[block_id][node_id];

		n_cells_in_node = node_2_cells_connectivity.size();

		for(int j=0; j<n_cells_in_node; j++)
		{
			cell_id = node_2_cells_connectivity[j];

			std::vector<int> cell_2_nodes_connectivity = global_cells_vector[block_id][cell_id];

			n_nodes_in_cell = cell_2_nodes_connectivity.size();

			if(cell_flag_4_face_reconstruction_[cell_id]==0)
			{
				std::vector<int>::iterator it;
				std::vector<int> face_2_nodes_connectivity (4);

				std::sort(cell_2_nodes_connectivity, cell_2_nodes_connectivity+n_nodes_in_cell);

				it = std::set_intersection( common_nodes_vector, common_nodes_vector + n_common_nodes, cell_2_nodes_connectivity, cell_2_nodes_connectivity + n_nodes_in_cell, face_2_nodes_connectivity.begin() );

				if(!face_2_nodes_connectivity.empty())
				{
					face_2_nodes_connectivity.resize(it - face_2_nodes_connectivity.begin());

					cell_flag_4_face_reconstruction_[cell_id] = 1;
				}

				

			}
		}


	}



}





