#ifndef DATASTRUCTURE_SRC_COMPLETEMESH_CPP
#define DATASTRUCTURE_SRC_COMPLETEMESH_CPP

#include "CompleteMesh.h"
#include "Block.h"
#include "BlockBuilder.h"
#include "ConcreteBlockBuilder.h"
#include <string>
#include <iostream>
using namespace std;

CompleteMesh::CompleteMesh(int n_blocks, int n_blocks_in_process, int* my_blocks, string topology_file_name) : n_blocks_(0), n_blocks_in_process_(0), my_blocks_(nullptr), all_blocks_(nullptr)

{
	n_blocks_=n_blocks;
	n_blocks_in_process_=n_blocks_in_process;

	my_blocks_ = new int[n_blocks_in_process_];
	for(int i=0;i<n_blocks_in_process_;i++)
	{
		my_blocks_[i]=my_blocks[i];

	}

	all_blocks_=new Block*[n_blocks_];


	for(int j=0;j<n_blocks_;j++)
	{

		all_blocks_[j] = new Block(j);
	}
	topology_file_name_ = topology_file_name;
}


CompleteMesh::~CompleteMesh()
{

}

void CompleteMesh::InitializeMyBlocks()
{
	std::string block_id_string;
	std::string block_file;
	Block* new_block;

	int block_id;


	for(int i=0;i<n_blocks_in_process_;i++)
	{
		block_id = my_blocks_[i];

		// std::cout<<block_id<<std::endl;

		block_id_string = std::to_string(block_id);
		// block_file = "../naca0012_coarse_nosidewall.su2";
		block_file = topology_file_name_;
		ConcreteBlockBuilder block_builder=ConcreteBlockBuilder(block_file);
		new_block = all_blocks_[i];

		//std::cout<<new_block -> block_id_<<std::endl;

		block_builder.preReadMyBlock(new_block);
		block_builder.readMyBlock(new_block);

		block_builder.createMyFaces(new_block);

		block_builder.setConnectivity(new_block);

		// cout<<"Cellules\n";
		Cell* test_cell;
		for(int i=0;i<new_block->n_real_cells_in_block_;i++)
		{
			test_cell = new_block ->block_cells_[i];
			// cout<<"cell_id_\t"<<test_cell->cell_id_<<endl;
			// cout<<"cell_2_nodes_connectivity_\t"<<test_cell->cell_2_nodes_connectivity_[0]<<"\t"<<test_cell->cell_2_nodes_connectivity_[1]<<"\t"<<test_cell->cell_2_nodes_connectivity_[2]<<"\t"<<test_cell->cell_2_nodes_connectivity_[3]<<"\t"<<test_cell->cell_2_nodes_connectivity_[4]<<"\t"<<test_cell->cell_2_nodes_connectivity_[5]<<"\t"<<test_cell->cell_2_nodes_connectivity_[6]<<"\t"<<test_cell->cell_2_nodes_connectivity_[7]<<endl;
			// cout<<"n_nodes_per_cell_\t"<<test_cell->n_nodes_per_cell_<<endl;
			// cout<<"n_faces_per_cell_\t"<<test_cell->n_faces_per_cell_<<endl;
			// cout<<"block_id_\t"<<test_cell->block_id_<<endl;
		}

		for(int i=new_block->n_real_cells_in_block_;i<new_block->n_all_cells_in_block_;i++)
		{
			test_cell = new_block ->block_cells_[i];
			// cout<<"cell_id_\t"<<test_cell->cell_id_<<endl;
			// cout<<"cell_2_nodes_connectivity_\t"<<test_cell->cell_2_nodes_connectivity_[0]<<"\t"<<test_cell->cell_2_nodes_connectivity_[1]<<"\t"<<test_cell->cell_2_nodes_connectivity_[2]<<"\t"<<test_cell->cell_2_nodes_connectivity_[3]<<endl;
			// cout<<"n_nodes_per_cell_\t"<<test_cell->n_nodes_per_cell_<<endl;
			// cout<<"n_faces_per_cell_\t"<<test_cell->n_faces_per_cell_<<endl;
			// cout<<"block_id_\t"<<test_cell->block_id_<<endl;
		}

		// test_cell = new_block ->block_cells_[12];
		// cout<<test_cell->cell_2_nodes_connectivity_[1]<<endl;
		// cout<<"Noeuds\n";
		Node* test_node;
		for(int i=0;i<new_block->n_nodes_in_block_;i++)
		{
			test_node = new_block ->block_nodes_[i];
			// cout<<"node_id_\t"<<test_node->node_id_<<endl;
			// cout<<"node_coordinates_\t"<<test_node->node_coordinates_[0]<<"\t"<<test_node->node_coordinates_[1]<<"\t"<<test_node->node_coordinates_[2]<<endl;
			// cout<<"block_id_\t"<<test_node->block_id_<<endl;
		}
		// test_node = new_block ->block_nodes_[12];
		// cout<<test_node->node_coordinates_[1]<<endl;
		// cout<<test_node->node_coordinates_[2]<<endl;



	}


}

void CompleteMesh::InitializeMPIboundaries()
{
	std::string block_id_string;
	std::string block_file;
	std::string topology_file_name;

	topology_file_name="../dummy_topology.txt";

	int block_id;
	int nb_of_blocks;
	int n_nodes_temp;
	int n_real_cells_temp;
	int n_ghost_cells_temp;
	int n_boundaries_temp;
	char boundary_type_temp[50];
	std::ifstream myfile(topology_file_name);

	char str_temp[200];
	std::string line;

	if (myfile.is_open())
	{
		getline(myfile,line);
		getline(myfile,line)
		sscanf (line.c_str(), "%i",&nb_of_blocks);
		for(int i=0;i<nb_of_blocks;i++)
		{
			getline(myfile,line)
			sscanf(line.c_str(),"%s",str_temp);
			block_file=str_temp;
			std::ifstream myblockfile(block_file);

			if (myblockfile.isopen())
			{
				getline(myblockfile, line);

				getline(myblockfile, line);
				getline(myblockfile, line);
				sscanf (line.c_str(), "%s %d",str_temp,&n_nodes_temp);

				for( int node_id = 0; node_id < n_nodes_temp; node_id++)
				{
					getline(myblockfile, line);
				}
				getline(myblockfile, line);
				sscanf (line.c_str(), "%s %d",str_temp,&n_real_cells_temp);
				for(int n_elem_temp=0 ; n_elem_temp < n_real_cells_temp; n_elem_temp++)
				//for(int cell_id = 0; cell_id < n_real_cells; cell_id++)

				{
					getline(myblockfile, line);
				}


				getline(myblockfile, line);
				sscanf (line.c_str(), "%s %i",str_temp,&n_boundaries_temp);				

				for(int boundary_id = 0; boundary_id < n_boundaries_temp; boundary_id++)
				{
					getline(myblockfile, line);
					sscanf (line.c_str(), "%s %s",str_temp,boundary_type_temp);
					std::string boundary_type_temp_str(boundary_type_temp);
					std::size_t found=boundary_type_temp.find("Block_");
					getline(myblockfile, line);
					sscanf (line.c_str(), "%s %i",str_temp,&n_ghost_cells_temp);

						if (boundary_type_temp_str=="WALL") // wall
						{
							for(int compteur_temp_ghost=0 ; compteur_temp_ghost < n_ghost_cells_temp; compteur_temp_ghost++)
							{
								getline(myblockfile, line);
							}
							//std::cout<<"on a un wall"<< std::endl;
							// block->block_boundary_cell_ids_[real_boundary_id]= new WallCellIds;

							// (block->block_boundary_cell_ids_[real_boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_count_= new int;
							// *((block->block_boundary_cell_ids_[real_boundary_id])->cell_count_)=0;
							// (block->block_boundary_cell_ids_[real_boundary_id])->owner_block_=block;
							// real_boundary_id=real_boundary_id+1;


						}
						else if (boundary_type_temp_str == "FARFIELD") //farfield
						{
							for(int compteur_temp_ghost=0 ; compteur_temp_ghost < n_ghost_cells_temp; compteur_temp_ghost++)
							{
								getline(myblockfile, line);
							}
							//std::cout<<"on a un farfield"<< std::endl;
							// block->block_boundary_cell_ids_[real_boundary_id]= new FarfieldCellIds;

							// (block->block_boundary_cell_ids_[real_boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_count_= new int;
							// *((block->block_boundary_cell_ids_[real_boundary_id])->cell_count_)=0;
							// (block->block_boundary_cell_ids_[real_boundary_id])->owner_block_=block;
							// real_boundary_id=real_boundary_id+1;

						}
						else if (boundary_type_temp_str == "SYMMETRY") //symmetry
						{
							for(int compteur_temp_ghost=0 ; compteur_temp_ghost < n_ghost_cells_temp; compteur_temp_ghost++)
							{
								getline(myblockfile, line);
							}
							//std::cout<<"on a un symmetry"<< std::endl;
							// block->block_boundary_cell_ids_[real_boundary_id]= new SymmetryCellIds;

							// (block->block_boundary_cell_ids_[real_boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
							// (block->block_boundary_cell_ids_[real_boundary_id])->cell_count_= new int;
							// *((block->block_boundary_cell_ids_[real_boundary_id])->cell_count_)=0;
							// (block->block_boundary_cell_ids_[real_boundary_id])->owner_block_=block;
							// real_boundary_id=real_boundary_id+1;

						}
						else if (!found=std::string::npos) //Connection inter-bloc
						{
							std::cout<<"on a une connexion boundary"<<std::endl;
							ConnexionCellIds* boundary_connec=new ConnexionCellIds;
							//boundary_type_temp_str.substr(found+7,1)

							for(int compteur_temp_ghost=0 ; compteur_temp_ghost < n_ghost_cells_temp; compteur_temp_ghost++)
							{
								getline(myblockfile, line);
							}
							//block->n_real_boundaries_in_block_=(block->n_real_boundaries_in_block_)-1;

						}

					//std::cout<<"test type bound: "<< boundary_type_temp <<std::endl;
					//std::cout<<"test nbcell in bound: "<< n_ghost_cells_temp <<std::endl;
					//std::cout<<"test la ou on est: "<< cell_id <<std::endl;

				}
			}else{
				//warning that file was not opened!
				std::cout<<"WARNING! BLOCK FILE WAS NOT CORRECTLY OPENED IN DUMMY MPI READ FUNCTION. ERRATIC BEHAVIOR MAY APPEAR!"<<std::endl;
				 }

		}
	}else{
		//warning that file was not opened!
		std::cout<<"WARNING! DUMMYTOPOLOGY FILE WAS NOT CORRECTLY OPENED IN READ FUNCTION. ERRATIC BEHAVIOR MAY APPEAR!"<<std::endl;
		 }


}

#endif
