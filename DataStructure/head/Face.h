#ifndef DATASTRUCTURE_HEAD_FACE_H
#define DATASTRUCTURE_HEAD_FACE_H

class Face
{
public:
	int is_in_wall_;
	int face_id_;
	int block_id_;
	int* face_2_nodes_connectivity_;
	int* face_2_cells_connectivity_;
	double face_area_;
	double* face_normals_;
	double* right_cell_r_vector_;
	double* left_cell_r_vector_;
	int n_nodes_per_face_;
	double* face_center_;

	Face();
	~Face();

};

#endif
