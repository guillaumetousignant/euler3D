#ifndef BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP
#define BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP


#include "BlockBuilder.h"
#include "NodeCreator.h"
#include "FaceCreator.h"
#include "CellCreator.h"
#include "GhostCellCreator.h"
#include "PyramidCellCreator.h"
#include "PrismCellCreator.h"
#include "TetrahedralCellCreator.h"
#include "ConcreteBlockBuilder.h"


void ConcreteBlockBuilder::readMyBlocks(Block* block)
{
	NodeCreator* node_creator;
	FaceCreator* face_creator;
	CellCreator (cell_creators*)[4];
	TetrahedralCellCreator* tetrahedral_cell_creator;
	GhostCellCreator* ghost_cell_creator;
	PrismCellCreator* prims_cell_creator;
	PyramidCellCreator* pyramid_cell_creator;

	cell_creators[0] = tetrahedral_cell_creator;
	cell_creators[1] = prims_cell_creator;
	cell_creators[2] = pyramid_cell_creator;
	cell_creators[3] = ghost_cell_creator;

	std::ifstream myfile(block_file_);
	int n_dimensions
	char str_temp[200];
	std::string line;
	double x_temp,y_temp,z_temp;

	int n_nodes_tmp;
	int n_nodes = block->n_nodes_in_block_;
	double node_coordinates_temp[3];

	int n_real_cells_tmp;
	int n_real_cells = block->n_real_cells_in_block_;
	std::string cell_type_tmp;
	std::string cell_2_nodes_connectivity_temp;

	

	if (myfile.is_open())
	{
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_dimensions);

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_nodes_tmp);

		n_nodes = n_nodes_tmp;

		for( int node_id = 0; node_id < n_nodes; node_id++ )
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%lf %lf %lf",&x_temp,&y_temp,&z_temp);

			node_coordinates_temp[0]=x_temp;
			node_coordinates_temp[1]=y_temp;
			node_coordinates_temp[2]=z_temp;

			new_node = buildNode(node_id,node_coordinates_tmp, node_creator)
			block ->addNode(new_node);

		}

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_real_cells_tmp);

		n_real_cells = n_real_cells_tmp;

		for(int cell_id = 0; cell_id < n_real_cells; cell_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",&cell_type_tmp,&cell_2_nodes_connectivity_temp);

			new_cell = buildCell(cell_id, cell_type, cell_2_nodes_connectivity_temp, cell_creators);

			block ->addCell(new_cell);
		}

	
		

}
