#ifndef HEAD_BLOCK_H
#define HEAD_BLOCK_H

#include <string>
#include <iostream>
using namespace std;

Block::Block(int block_id)
{
	block_id_=block_id;
}

void addCell(Cell* new_cell);
void addNode(Node* new_node);
void addFace(Face* new_face);
void addCellIdInBoundary(int cell_id_);
void addFaceIdInWall(int face_id);