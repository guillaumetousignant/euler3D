#ifndef BLOCKBUILDER_SRC_BLOCKBUILDER_CPP
#define BLOCKBUILDER_SRC_BLOCKBUILDER_CPP

#include "BlockBuilder.h"
#include "CellCreator.h"
#include "FaceCreator.h"
#include "NodeCreator.h"
#include "Cell.h"
#include "Node.h"
#include "Face.h"
#include "Block.h"
#include <iostream>
#include <string>

BlockBuilder::BlockBuilder(FILE* block_file)
{
	block_file_ = block_file;

}

BlockBuilder::~BlockBuilder()
{

}

Cell* buildCell(int cell_id, std::string cell_type, std::string cell_2_nodes_connectivity_temp, CellCreator* creators,std::string ghost_cell_type = "")
{

	int key;
	Cell* new_cell;

	if (cell_type == "10") // tetrahede
	{
		key = 0;
		int (cell_2_nodes_connectivity*)[4];
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);

	}
	else if (cell_type == "13") //prism
	{
		key = 1;
		int (cell_2_nodes_connectivity*)[8];
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d %d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4],&cell_2_nodes_connectivity[5],&cell_2_nodes_connectivity[6],&cell_2_nodes_connectivity[7]);

	}
	else if (cell_type == "14") //pyramid
	{
		key = 2;
		int (cell_2_nodes_connectivity*)[5];
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4]);

	}
	else if (cell_type == "ghost")
	{
		key = 3;
		std::string temp_str;
		sscanf (ghost_cell_type.c_str(),"%s",&temp_str);
		if(temp_str == "5")
		{
			int (cell_2_nodes_connectivity*)[3];
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2]);
		}
		else(temp_str == "9")
		{
			int (cell_2_nodes_connectivity*)[4];
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);
		}
	}

	new_cell = creators[key]->createCell();
	return new_cell;
	new_cell -> cell_2_nodes_connectivity_ = cell_2_nodes_connectivity;

}

Node* buildNode(int node_id,double node_coordinates[3], NodeCreator* node_creator)
{
	Node* new_node;
	new_node = node_creator->createNode();

	int node_id_tmp = new_node ->node_id_;
	node_id_tmp = node_id;

	double* node_coordinates_tmp = new_node->node_coordinates_;
	node_coordinates_tmp = node_coordinates;

	return new_node;

}

void buildFace(int face_type)
{

}

void setConnectivity(Block* block)
{

}

void setMetrics(Block* block)
{

}
#endif