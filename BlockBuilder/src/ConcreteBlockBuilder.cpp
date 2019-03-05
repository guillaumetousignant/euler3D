#ifndef BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP
#define BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP

#include <iostream>


using namespace std;

#include "ConcreteBlockBuilder.h"


ConcreteBlockBuilder::ConcreteBlockBuilder(std::string block_file):BlockBuilder(block_file)
{

}

ConcreteBlockBuilder::~ConcreteBlockBuilder()
{

}

void ConcreteBlockBuilder::readMyBlock(Block* block)
{
	NodeCreator* node_creator= new NodeCreator();
	CellCreator cell_creators[4];
	TetrahedralCellCreator tetrahedral_cell_creator= TetrahedralCellCreator();
	GhostCellCreator ghost_cell_creator=  GhostCellCreator();
	PrismCellCreator prism_cell_creator= PrismCellCreator();
	PyramidCellCreator pyramid_cell_creator= PyramidCellCreator();

	cell_creators[0] = tetrahedral_cell_creator;
	cell_creators[1] = pyramid_cell_creator;
	cell_creators[2] = prism_cell_creator;
	cell_creators[3] = ghost_cell_creator;

	int block_id = block->block_id_;

	std::ifstream myfile(block_file_);
	int n_dimensions;
	char str_temp[200];
	std::string line;
	double x_temp,y_temp,z_temp;

	int n_nodes_temp;
	int n_nodes;
	double node_coordinates_temp[3];

	int n_real_cells_temp;
	int n_real_cells;
	std::string cell_type_temp;
	std::string cell_2_nodes_connectivity_temp;
	Node* new_node;
	Cell* new_cell;
	
	
	if (myfile.is_open())
	{

		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_dimensions);

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_nodes_temp);

		n_nodes = n_nodes_temp;
		block->n_nodes_in_block_=n_nodes;
		block->block_nodes_ = new Node*[n_nodes];
		for( int node_id = 0; node_id < n_nodes; node_id++ )
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%lf %lf %lf",&x_temp,&y_temp,&z_temp);

			node_coordinates_temp[0]=x_temp;
			node_coordinates_temp[1]=y_temp;
			node_coordinates_temp[2]=z_temp;

			new_node = buildNode(node_id,node_coordinates_temp, node_creator);
			block ->addNode(new_node);

		}

		getline(myfile, line);


		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_real_cells_temp);

		n_real_cells = n_real_cells_temp;
		block->n_real_cells_in_block_ = n_real_cells;

		block->block_cells_ = new Cell*[n_real_cells];


		for(int cell_id = 0; cell_id < n_real_cells; cell_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s",str_temp);
			cell_type_temp = str_temp;
			cell_2_nodes_connectivity_temp =line;


			new_cell = buildCell(cell_id, cell_type_temp, cell_2_nodes_connectivity_temp, cell_creators,"0");


			new_cell -> block_id_ = block_id;
			block ->addCell(new_cell);	
		}
	}
	myfile.close();
	delete node_creator; 

}

void ConcreteBlockBuilder::createMyFaces(Block* block)
{

	TempTetrahedralFaceCreator tetrahedral_face_creator= TempTetrahedralFaceCreator();
	// TempGhostFaceCreator ghost_face_creator=  TempGhostFaceCreator();
	TempPrismFaceCreator prism_face_creator= TempPrismFaceCreator();
	TempPyramidFaceCreator pyramid_face_creator= TempPyramidFaceCreator();

	TempFaceCreator face_creators[4];
	Cell* cell;


	face_creators[0] = tetrahedral_face_creator;
	face_creators[1] = pyramid_face_creator;
	face_creators[2] = prism_face_creator;
	// face_creators[3] = ghost_face_creator;

	// int* face_2_nodes_connectivity_created;

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


	for(int i=0; i<block->n_real_cells_in_block_;i++)
	{
		cell = block -> block_cells_[i];
	}
}

#endif
