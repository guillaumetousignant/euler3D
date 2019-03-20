#ifndef DATASTRUCTURE_HEAD_BLOCK_H
#define DATASTRUCTURE_HEAD_BLOCK_H

#include "Cell.h"
#include "Face.h"
#include "Node.h"
class BoundaryCellIds;
#include "TimeVariables.h"
#include "PrimitiveVariables.h"
#include "InterpolationVariables.h"
#include "BoundaryCellIds.h"
//#include "ConnexionCellIds.h"
//#include "FarfieldCellIds.h"
//#include "WallCellIds.h"

class Block
{
public:
	int block_id_;

	int n_real_cells_in_block_;
	int n_ghost_cells_in_block_;
	int n_all_cells_in_block_;
	int n_nodes_in_block_;
	int n_faces_in_block_;
	int n_real_boundaries_in_block_;
	int nb_face_in_wall_;
	Cell** block_cells_;
	Node** block_nodes_;
	Face** block_faces_;

	TimeVariables* block_time_variables_;
	PrimitiveVariables* block_primitive_variables_;
	InterpolationVariables* block_interpolation_variables_;

	BoundaryCellIds** block_boundary_cell_ids_;
	int* block_farfield_face_ids_;
	int n_farfield_faces_;
	int* block_wall_face_ids_;
	int n_wall_faces_;

	void addCell(Cell* new_cell);
	void addNode(Node* new_node);
	void addFace(Face* new_face);
	void addCellIdInBoundary(int cell_id, BoundaryCellIds* some_boundary);
	void addFaceIdInWall(int face_id,int* face_count);
	void addFaceIdInFarfield(int face_id,int* face_count);

	Block(int block_id);
	~Block();
};


#endif
