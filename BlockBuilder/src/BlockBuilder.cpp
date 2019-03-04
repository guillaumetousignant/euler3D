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

	int key=0;
	Cell* new_cell;
	Face* new_face;
	int* cell_2_nodes_connectivity=NULL;
	int n_nodes_per_cell=0;
	int n_faces_per_cell=0;
	FaceCreator* face_creator= new FaceCreator();
	

	if (cell_type == "10") // tetrahede
	{
		key = 0;
		cell_2_nodes_connectivity =new int[4];
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);
		n_nodes_per_cell = 4;
		n_faces_per_cell = 4;

		// int (*face_2_nodes_connectivity_local)[3] = new int[4][3];

		// int face_2_nodes_connectivity_local[4][3] = {{0,1,2},{0,1,3},{1,2,3},{0,3,2}};
		// int n_nodes_per_face[4] = {3,3,3,3};

		// for(int i=0;i<n_faces_per_cell;i++)
		// {
		// 	new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
		// 	for(int j=0;j<n_nodes_per_face[i];j++)
		// 	{
		// 		new_face -> face_2_nodes_connectivity_[j] = cell_2_nodes_connectivity_temp[face_2_nodes_connectivity_local[i][j]];
		//		face_count_+=1;
		// 	} 
		// }



		// new_face = buildFace(face_count_,3,face_creator);
		// face_2_nodes_connectivity_local={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[2],cell_2_nodes_connectivity[1]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,3,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[1],cell_2_nodes_connectivity[3]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,3,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[1],cell_2_nodes_connectivity[2],cell_2_nodes_connectivity[3]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,3,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[3],cell_2_nodes_connectivity[2]};
		// face_count_+=1;

	}
	else if (cell_type == "13") //prism
	{
		key = 1;
		cell_2_nodes_connectivity =new int[8];
		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d %d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4],&cell_2_nodes_connectivity[5],&cell_2_nodes_connectivity[6],&cell_2_nodes_connectivity[7]);
		n_nodes_per_cell = 8;
		n_faces_per_cell = 6;

		// new_face = buildFace(face_count_,4,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[3],cell_2_nodes_connectivity[2],cell_2_nodes_connectivity[1]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,4,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[1],cell_2_nodes_connectivity[4],cell_2_nodes_connectivity[4]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,4,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[1],cell_2_nodes_connectivity[3],cell_2_nodes_connectivity[7],cell_2_nodes_connectivity[5]};
		// face_count_+=1;
		// new_face = buildFace(face_count_,3,face_creator);
		// new_face ->face_2_nodes_connectivity_={ cell_2_nodes_connectivity[0],cell_2_nodes_connectivity[3],cell_2_nodes_connectivity[2]};
		// face_count_+=1;

	}
	else if (cell_type == "14") //pyramid
	{
		key = 2;
		// int* cell_2_nodes_connectivity;
		cell_2_nodes_connectivity =new int[5];

		sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3],&cell_2_nodes_connectivity[4]);
		n_nodes_per_cell = 5;
		n_faces_per_cell = 5;

	}
	else if (cell_type == "ghost")
	{
		if (ghost_cell_type == "5")
		{
			// int* cell_2_nodes_connectivity;
			cell_2_nodes_connectivity =new int[3];
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2]);
			n_nodes_per_cell = 3;
			n_faces_per_cell = 1;
		
		}
		else if (ghost_cell_type == "9")
		{
			// int* cell_2_nodes_connectivity;
			cell_2_nodes_connectivity =new int[4];
			sscanf (cell_2_nodes_connectivity_temp.c_str(), "%d %d %d %d",&cell_2_nodes_connectivity[0],&cell_2_nodes_connectivity[1],&cell_2_nodes_connectivity[2],&cell_2_nodes_connectivity[3]);
			n_nodes_per_cell = 4;
			n_faces_per_cell = 1;
			
		}
	}

	new_cell = creators[key].createCell();
	new_cell -> cell_2_nodes_connectivity_ = cell_2_nodes_connectivity;
	new_cell -> n_nodes_per_cell_ = n_nodes_per_cell;
	new_cell -> n_faces_per_cell_ = n_faces_per_cell;
	return new_cell;



	delete cell_2_nodes_connectivity; delete face_creator; 

}

Node* BlockBuilder::buildNode(int node_id,double node_coordinates[3], NodeCreator* node_creator)
{
	Node* new_node;
	new_node = node_creator->createNode();

	new_node ->node_id_= node_id;

	new_node->node_coordinates_ = node_coordinates;

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

void BlockBuilder::face_2_Nodes_Connectivity_Builder(int n_faces_per_cell, int* face_2_nodes_connectivity_local, int* n_nodes_per_face, int* cell_2_nodes_connectivity_temp, FaceCreator* face_creator)
{
	Face* new_face;
	for(int i=0;i<n_faces_per_cell;i++)
		{
			new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
			for(int j=0;j<n_nodes_per_face[i];j++)
			{
				new_face -> face_2_nodes_connectivity_[j] = cell_2_nodes_connectivity_temp[face_2_nodes_connectivity_local[i][j]];
			} 
		} 
}







#endif