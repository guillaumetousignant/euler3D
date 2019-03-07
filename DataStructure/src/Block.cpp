#ifndef DATASTRUCTURE_SRC_BLOCK_CPP
#define DATASTRUCTURE_SRC_BLOCK_CPP

#include <string>
#include <iostream>
#include "Block.h"
using namespace std;

Block::Block(int block_id)
{
	block_id_=block_id;
}

Block::~Block()
{

}

void Block::addCell(Cell* new_cell)
{
	int id = new_cell-> cell_id_;

	block_cells_[id] = new_cell;
}

void Block::addNode(Node* new_node)
{
	int id = new_node-> node_id_;

	block_nodes_[id] = new_node;
}
void Block::addFace(Face* new_face)
{
	int id = new_face-> face_id_;

	block_faces_[id] = new_face;
}

void Block::addCellIdInBoundary(int cell_id,BoundaryCellIds* some_boundary)
{
	int* cell_ids_in_boundary = some_boundary->cell_ids_in_boundary_;
	int cell_count = some_boundary->cell_count_;

	cell_ids_in_boundary[cell_count] = cell_id;
	cell_count += 1;
}

void Block::addFaceIdInWall(int face_id, int face_count)
{
	block_wall_face_ids_[face_count] = face_id;
	face_count += 1;

}
#endif
