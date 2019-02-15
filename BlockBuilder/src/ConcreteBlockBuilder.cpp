#ifndef BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP
#define BLOCKBUILDER_SRC_CONCRETEBLOCKBUILDER_CPP

#include "ConcreteBlockBuilder.h"
#include "BlockBuilder.h"

void readMyBlocks(Block* block)
{

	std::ifstream myfile(block_file_);
	int n_dimensions
	char str_temp[200];
	std::string line;
	double x_temp,y_temp,z_temp;

	int n_nodes_tmp;
	int n_nodes = block->n_nodes_in_block_;

	if (myfile.is_open())
	{
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_dimensions);

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_nodes_tmp);

		n_nodes = n_nodes_tmp;

		for( int i = 0; i < nnode; i++ )
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%lf %lf",&x_temp,&y_temp,&z_temp);
			
			node_x_temp[i]=x_temp;
			node_y_temp[i]=y_temp;
		}

	
		new_cell = buildCell(cell_type, cell_creators)
		block ->addCell(new_cell);

}
