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

void ConcreteBlockBuilder::preReadMyBlock(Block* block)
{
	std::ifstream myfile(block_file_);

	char str_temp[200];
	std::string line;

	int n_nodes_temp;
	int n_nodes;

	int n_real_cells_temp;
	int n_real_cells;
	int n_all_cells;
	int n_ghost_cells=0;



	std::string cell_type_temp;
	int faces_sum_for_each_cell=0;
	int n_faces;

	int faces_sum_in_boundaries=0;

	int n_boundaries=0;
	int n_elements_in_boundary=0;
	char boundary_type_temp[200];
	std::string boundary_type;

	if (myfile.is_open())
	{

		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_nodes_temp);

		n_nodes = n_nodes_temp;
		block->n_nodes_in_block_=n_nodes;
		block->block_nodes_ = new Node*[n_nodes];
		for( int node_id = 0; node_id < n_nodes; node_id++ )
		{
			getline(myfile, line);
		}

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_real_cells_temp);

		n_real_cells = n_real_cells_temp;
		block->n_real_cells_in_block_ = n_real_cells;

		n_all_cells = n_real_cells;

		for(int cell_id = 0; cell_id < n_real_cells; cell_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s",str_temp);
			cell_type_temp =str_temp;

			if (cell_type_temp == "10") // tetrahede
			{	
				faces_sum_for_each_cell+=4;
			}
			else if (cell_type_temp == "14") //pyramid
			{
				faces_sum_for_each_cell+=5;
			}
			else if (cell_type_temp == "13") //pyramid
			{
				faces_sum_for_each_cell+=6;
			}
		}



		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_boundaries);


		for(int boundary=0;boundary<n_boundaries;boundary++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,boundary_type_temp);
			boundary_type = boundary_type_temp;

			getline(myfile, line);
			sscanf (line.c_str(), "%s %d",str_temp,&n_elements_in_boundary);

			if(boundary_type=="farfield")
			{
				faces_sum_in_boundaries+=n_elements_in_boundary;
			}

			n_ghost_cells +=n_elements_in_boundary;

			for(int element_in_boundary = 0;element_in_boundary<n_elements_in_boundary;element_in_boundary++)
			{
				getline(myfile, line);
			}
		}

		n_all_cells = n_real_cells + n_ghost_cells;
		block->block_cells_ = new Cell*[n_all_cells];

		block->n_ghost_cells_in_block_ = n_ghost_cells;
		block->n_all_cells_in_block_ = n_all_cells;

		n_faces = faces_sum_for_each_cell-(faces_sum_for_each_cell - faces_sum_in_boundaries)/2.;
		block->block_faces_ = new Face*[n_faces];
		block->n_faces_in_block_ = n_faces;



	}
	myfile.close();
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
	int n_boundaries_temp;
	int n_boundaries;
	int n_ghost_cells_temp;
	int n_ghost_cells;
	int cell_id = 0;
	std::string cell_type_temp;
	std::string ghost_cell_type_temp;
	std::string cell_2_nodes_connectivity_temp;
	std::string ghost_cell_2_nodes_connectivity_temp;
	char boundary_type_temp[50];

	WallCellIds *wall_boundary_temp;
	FarfieldCellIds *farfield_boundary_temp;
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
		// block->n_nodes_in_block_=n_nodes;
		// block->block_nodes_ = new Node*[n_nodes];
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
		// block->n_real_cells_in_block_ = n_real_cells;

		// block->block_cells_ = new Cell*[n_real_cells];

		for( ; cell_id < n_real_cells; cell_id++)
		//for(int cell_id = 0; cell_id < n_real_cells; cell_id++)

		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s",str_temp);
			cell_type_temp = str_temp;
			cell_2_nodes_connectivity_temp =line;


			new_cell = buildCell(cell_id, cell_type_temp, cell_2_nodes_connectivity_temp, cell_creators,"0");


			new_cell -> block_id_ = block_id;
			block ->addCell(new_cell);	
		}
	

		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %i",str_temp,&n_boundaries_temp);
		n_boundaries=n_boundaries_temp;
		block->n_real_boundaries_in_block_=n_boundaries;
		std::cout<<"test bound: "<< n_boundaries<<std::endl;
		block ->block_boundary_cell_ids_ = new BoundaryCellIds* [n_boundaries];


		for(int boundary_id = 0; boundary_id < n_boundaries; boundary_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,boundary_type_temp);
			std::string boundary_type_temp_str(boundary_type_temp);
			getline(myfile, line);
			sscanf (line.c_str(), "%s %i",str_temp,&n_ghost_cells_temp);

				if (boundary_type_temp_str=="WALL") // wall
				{
					std::cout<<"on a un wall"<< std::endl;
					block->block_boundary_cell_ids_[boundary_id]= new WallCellIds;

					(block->block_boundary_cell_ids_[boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
					(block->block_boundary_cell_ids_[boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
					(block->block_boundary_cell_ids_[boundary_id])->cell_count_= new int;
					*((block->block_boundary_cell_ids_[boundary_id])->cell_count_)=0;


				}
				else if (boundary_type_temp_str == "FARFIELD") //farfield
				{
					std::cout<<"on a un farfield"<< std::endl;
					block->block_boundary_cell_ids_[boundary_id]= new FarfieldCellIds;
					
					(block->block_boundary_cell_ids_[boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
					(block->block_boundary_cell_ids_[boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
					(block->block_boundary_cell_ids_[boundary_id])->cell_count_= new int;
					*((block->block_boundary_cell_ids_[boundary_id])->cell_count_)=0;

				}
				else if (boundary_type_temp_str == "CONNECTION") //Connection inter-bloc
				{

				}


			std::cout<<"test type bound: "<< boundary_type_temp <<std::endl;
			std::cout<<"test nbcell in bound: "<< n_ghost_cells_temp <<std::endl;
			std::cout<<"test la ou on est: "<< cell_id <<std::endl;
			int cond=n_ghost_cells_temp+cell_id;
			std::cout<<"limite boucle test: "<< cond <<std::endl;
			for( ; cell_id < (cond); cell_id++)
			{
				getline(myfile, line);
				sscanf (line.c_str(), "%s",str_temp);
				ghost_cell_type_temp = str_temp;
				ghost_cell_2_nodes_connectivity_temp =line;

				new_cell = buildCell(cell_id, "ghost", ghost_cell_2_nodes_connectivity_temp, cell_creators, ghost_cell_type_temp);
				new_cell -> block_id_ = block_id; //necessary?
				block ->addCell(new_cell);
				//std::cout<< "comparaison: "<< "WALL" << boundary_type_temp <<std::endl;

				if (boundary_type_temp_str=="WALL") // wall
				{
					//std::cout<<"on a un wall"<< std::endl;
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[boundary_id]);
					//block ->addFaceIdInWall(int face_id, int face_count)

				}
				else if (boundary_type_temp_str == "FARFIELD") //farfield
				{
					//std::cout<<"on a un farfield"<< std::endl;
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[boundary_id]);

				}
				else if (boundary_type_temp_str == "CONNECTION") //Connection inter-bloc
				{

				}
				//block ->addCellIdInBoundary(cell_id,BoundaryCellIds* some_boundary);

			}

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
