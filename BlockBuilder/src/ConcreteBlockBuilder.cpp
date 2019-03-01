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
#include "BoundaryCellIds.h"
#include "FarfieldCellIds.h"
#include "WallCellIds.h"
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
	int n_real_cells;
	int n_boundaries_temp;
	int n_boundaries;
	int n_ghost_cells_temp;
	int n_ghost_cells;
	int cell_id = 0;
	std::string cell_type_tmp;
	std::string ghost_cell_type_temp;
	std::string cell_2_nodes_connectivity_temp;
	std::string ghost_cell_2_nodes_connectivity_temp;
	std::string boundary_type_temp;

	WallCellIds *wall_boundary_temp;
	FarfieldCellIds *farfield_boundary_temp;

	

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

		for( ; cell_id < n_real_cells; cell_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",&cell_type_tmp,&cell_2_nodes_connectivity_temp);

			new_cell = buildCell(cell_id, cell_type, cell_2_nodes_connectivity_temp, cell_creators);

			block ->addCell(new_cell);
		}

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_boundaries_temp);
		n_boundaries=n_boundaries_temp;

		for(int boundary_id = 0; boundary_id < n_boundaries; boundary_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,&boundary_type_temp);
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,&n_ghost_cells_temp);



			for( ; cell_id < n_ghost_cells_temp+cell_id; cell_id++)
			{
				getline(myfile, line);
				sscanf (line.c_str(), "%s %s",&ghost_cell_type_temp,&ghost_cell_2_nodes_connectivity_temp);

				new_cell = buildCell(cell_id, "ghost", ghost_cell_2_nodes_connectivity_temp, cell_creators, ghost_cell_type_temp);
				block ->addCell(new_cell);

				if (boundary_type_temp == "WALL") // wall
				{
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[boundary_id]);
					//block ->addFaceIdInWall(int face_id, int face_count)

				}
				else if (boundary_type_temp == "FARFIELD") //farfield
				{
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[boundary_id]);

				}
				else if (boundary_type_temp == "CONNECTION") //Connection inter-bloc
				{

				}
				block ->addCellIdInBoundary(cell_id,BoundaryCellIds* some_boundary);

			}

		}



	
		

}
