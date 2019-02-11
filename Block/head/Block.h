#ifndef HEAD_BLOCK_H
#define HEAD_BLOCK_H


class Block
{
	public:
		int block_id_;

		int nb_cells_in_block_;
		int nb_nodes_in_block_;
		int nb_faces_in_block_;
		Cell* block_cells_;
		Node* block_nodes_;
		Face* block_faces_;

		TimeVariables* block_time_variables_;
		PrimitiveVariables* block_primitive_variables_;
		InterpolationVariables* block_interpolation_variables_;

		BoundaryCellIds* block_boundary_cell_ids_;
		int* block_wall_face_ids_;

		void addCell(Cell* new_cell);
		void addNode(Node* new_node);
		void addFace(Face* new_face);
		void addCellIdInBoundary(int cell_id_);
		void addFaceIdInWall(int face_id);

		Block(int block_id);
		~Block();
};


#endif