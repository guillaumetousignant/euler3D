#ifndef DATASTRUCTURE_HEAD_NODE_H
#define DATASTRUCTURE_HEAD_NODE_H

class Node
{
public:
	int node_id_;
	double* node_coordinates_;
	int* node_2_cells_connectivity_;
	int n_cells_per_node_;

	Node();
	~Node();
	
};

#endif