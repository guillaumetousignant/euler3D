#ifndef METIS_HEAD_RECONSTRUCTFACES_H
#define METIS_HEAD_RECONSTRUCTFACES_H

#include <iostream>     // std::cout
#include <algorithm>    // std::set_intersection, std::sort
#include <vector>

class ReconstructFaces
{
public:
	int n_blocks_;
	int global_n_elements_;
	int** block_array_4_comparaison_;
	int* cell_flag_4_face_reconstruction_;
	ReconstructFaces(int n_blocks, int global_n_elements);
	~ReconstructFaces();

	std::vector<int> CompareArraysOfGlobalNodes( int first_block_id, int* first_block_node_array, int n_nodes_in_first_block, int second_block_id, int* second_block_node_array, int n_nodes_in_second_block);
	void FindElementsInConnexion(std::vector<int> common_nodes_vector, std::vector<int>** global_cells_vector, std::vector<int>** global_nodes_vector, int block_id );
};

#endif
