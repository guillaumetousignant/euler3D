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

BlockBuilder::BlockBuilder(std::string block_file)
{
	block_file_ = block_file;
	face_count_ = 0;

}

BlockBuilder::~BlockBuilder()
{

}

Cell* BlockBuilder::buildCell(int cell_id, std::string cell_type, std::string cell_2_nodes_connectivity_temp, CellCreator* creators,std::string ghost_cell_type)
{
	char str_temp[2];
	int key=0;
	Cell* new_cell;
	Face* new_face;
	int* cell_2_nodes_connectivity=NULL;
	int n_nodes_per_cell=0;
	int n_faces_per_cell=0;
	


	if (cell_type == "10") // tetrahede
	{
		key = 0;
		cell_2_nodes_connectivity =new int[4]();
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%s %d %d %d %d",str_temp,&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);
		n_nodes_per_cell = 4;
		n_faces_per_cell = 4;

	}
	else if (cell_type == "14") //pyramid
	{
		key = 1;
		// int* cell_2_nodes_connectivity;
		cell_2_nodes_connectivity =new int[5]();

		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%s %d %d %d %d %d",str_temp,&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4]);
		n_nodes_per_cell = 5;
		n_faces_per_cell = 5;

	}
	else if (cell_type == "13") //prism
	{
		key = 2;
		cell_2_nodes_connectivity =new int[8]();
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%s %d %d %d %d %d %d %d %d",str_temp,&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4],&cell_2_nodes_connectivity[5],&cell_2_nodes_connectivity[6],&cell_2_nodes_connectivity[7]);
		n_nodes_per_cell = 8;
		n_faces_per_cell = 6;

	}
	
	else if (cell_type == "ghost")
	{
		if (ghost_cell_type == "5")
		{
			// int* cell_2_nodes_connectivity;
			cell_2_nodes_connectivity =new int[3]();
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%s %d %d %d",str_temp,&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2]);
			n_nodes_per_cell = 3;
			n_faces_per_cell = 1;
		
		}
		else if (ghost_cell_type == "9")
		{
			// int* cell_2_nodes_connectivity;
			cell_2_nodes_connectivity =new int[4]();
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%s %d %d %d %d",str_temp,&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);
			n_nodes_per_cell = 4;
			n_faces_per_cell = 1;
			
		}
	}


	new_cell = creators[key].createCell();
	new_cell ->cell_id_ = cell_id;
	new_cell ->creator_key_ = key;
	new_cell -> n_nodes_per_cell_ = n_nodes_per_cell;
	new_cell -> n_faces_per_cell_ = n_faces_per_cell;

	new_cell -> cell_2_cells_connectivity_ = new int[n_faces_per_cell]();
	new_cell -> cell_2_faces_connectivity_ = new int[n_faces_per_cell]();
	new_cell -> cell_2_nodes_connectivity_ = new int[n_nodes_per_cell]();


	for(int i=0;i<n_nodes_per_cell;i++)
	{

		new_cell -> cell_2_nodes_connectivity_[i] = cell_2_nodes_connectivity[i];

	}

	delete cell_2_nodes_connectivity; 
	return new_cell;


}

Node* BlockBuilder::buildNode(int node_id,double node_coordinates[3], NodeCreator* node_creator)
{
	Node* new_node;
	new_node = node_creator->createNode();

	new_node ->node_id_= node_id;


	new_node->node_coordinates_[0] = node_coordinates[0];
	new_node->node_coordinates_[1] = node_coordinates[1];
	new_node->node_coordinates_[2] = node_coordinates[2];


	return new_node;

}

Face* BlockBuilder::buildFace(int face_id, int n_nodes_per_face,FaceCreator* face_creator)
{
	Face* new_face;
	new_face = face_creator->createFace();

	new_face->face_id_=face_id;
	new_face->n_nodes_per_face_=n_nodes_per_face;
	new_face->face_2_nodes_connectivity_ = new int[n_nodes_per_face];

	return new_face;

}

void BlockBuilder::setConnectivity(Block* block)
{

}

void BlockBuilder::setMetrics(Block* block)
{

}


// void BlockBuilder::face_2_Nodes_Connectivity_Builder(int n_faces_per_cell, int* face_2_nodes_connectivity_local, int* n_nodes_per_face, int* cell_2_nodes_connectivity_temp, FaceCreator* face_creator)
// {
// 	Face* new_face;
// 	for(int i=0;i<n_faces_per_cell;i++)
// 		{
// 			new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
// 			for(int j=0;j<n_nodes_per_face[i];j++)
// 			{
// 				new_face -> face_2_nodes_connectivity_[j] = cell_2_nodes_connectivity_temp[face_2_nodes_connectivity_local[i][j]];
// 			} 
// 		} 
// }







#endif