#ifndef BLOCKBUILDER_HEAD_BLOCKBUILDER_H
#define BLOCKBUILDER_HEAD_BLOCKBUILDER_H

#include "CellCreator.h"
#include "FaceCreator.h"
#include "NodeCreator.h"
#include "Cell.h"
#include "Node.h"
#include "Face.h"
#include "Block.h"
#include <fstream>
#include <math.h>

class BlockBuilder
{
public:
	std::string block_file_;
	int face_count_;

	BlockBuilder(std::string block_file);
	~BlockBuilder();

	virtual void readMyBlock(Block* block) = 0;
	virtual void createMyFaces(Block* block) = 0;

	Cell* buildCell(int cell_id, std::string cell_type, std::string cell_2_nodes_connectivity_temp, CellCreator* creators,std::string ghost_cell_type /*= ""*/);
	Node* buildNode(int node_id,double node_coordinates[3], NodeCreator* node_creator);
	Face* buildFace(int face_id, int n_nodes_per_face,FaceCreator* face_creator);
	void setConnectivity(Block* block);
	void setMetrics(Block* block);
	// void face_2_Nodes_Connectivity_Builder(Face* new_face,int* face_2_nodes_connectivity,int n_nodes_per_face);

	
};
#endif