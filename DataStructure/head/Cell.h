#ifndef DATASTRUCTURE_HEAD_CELL_H
#define DATASTRUCTURE_HEAD_CELL_H

#include <vector>

class Cell
{
public:
	int cell_id_;
	int block_id_;
	int* cell_2_cells_connectivity_;
	int* cell_2_nodes_connectivity_;
	int* cell_2_faces_connectivity_;
	double cell_volume_;
	double* cell_coordinates_;
	std::vector<std::vector<double>> cell_weights_;
	int n_nodes_per_cell_;
	int n_faces_per_cell_;
	int creator_key_;

	Cell();
	~Cell();
	
};

#endif