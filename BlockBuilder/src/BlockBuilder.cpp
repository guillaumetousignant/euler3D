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
#include <vector>

BlockBuilder::BlockBuilder(std::string block_file, std::string topology_file)
{
	block_file_ = block_file;
	topology_file_ = topology_file;
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
	else if (cell_type == "12") //prism
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

	delete [] cell_2_nodes_connectivity;
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
	int i,j,k,idx,node_0,node_1,node_2; //,n_cells_linked;
	int *idx_node,*idx_cell_2_faces,*idx_cell_2_cells;


	std::cout<<"DÉBUT node2cellsconnectivity"<<std::endl;

		//MISE À JOUR NOMBRE CELLS PAR NODE (VÉRIFIÉ)

		for(i=0;i <= block->n_nodes_in_block_-1 ;i++)
		{
			block->block_nodes_[i]->n_cells_per_node_=0;
		}

		for(i=0;i <= block->n_all_cells_in_block_-1 ;i++)
		{
			for(j=0;j <= block->block_cells_[i]->n_nodes_per_cell_-1;j++)
			{
				block->block_nodes_[block->block_cells_[i]->cell_2_nodes_connectivity_[j]]->n_cells_per_node_+=1;
			}
		}

		//node_2_cells_connectivity_

		idx_node =new int[block->n_nodes_in_block_]();

		for(i=0;i <= block->n_nodes_in_block_-1 ;i++)
		{
			block->block_nodes_[i]->node_2_cells_connectivity_ =new int[block->block_nodes_[i]->n_cells_per_node_]();
		}

		for(i=0;i <= block->n_all_cells_in_block_-1 ;i++)
		{
			for(j=0;j <= block->block_cells_[i]->n_nodes_per_cell_-1 ;j++)
			{
				idx=block->block_cells_[i]->cell_2_nodes_connectivity_[j];
				block->block_nodes_[idx]->node_2_cells_connectivity_[idx_node[idx]]=i;
				idx_node[idx]+=1;
			}

		}

	//VÉRIFICATION CONNECTIVITÉ
/*
	for(i=0;i <= block->n_nodes_in_block_-1 ;i++)
	{
		std::cout <<block->block_nodes_[i]->n_cells_per_node_<<" NODE2CELL "<< i <<" "<< block->block_nodes_[i]->node_2_cells_connectivity_[0] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[1] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[2] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[3] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[4] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[5] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[6] <<" " << block->block_nodes_[i]->node_2_cells_connectivity_[7] <<std::endl;
	}
*/


std::cout<<"DÉBUT face_2_cells"<<std::endl;

	/*
	//face_2_cells_connectivity_
		for(i=0;i <= block->n_faces_in_block_-1 ;i++)
		{
			//block->block_faces_[i]->face_2_cells_connectivity_=allocate_1d_array_int(2, "face_2_cells_connectivity_");
			block->block_faces_[i]->face_2_cells_connectivity_=new int[2]();


			idx=0;
			node_0=block->block_faces_[i]->face_2_nodes_connectivity_[0];
			node_1=block->block_faces_[i]->face_2_nodes_connectivity_[1];
			node_2=block->block_faces_[i]->face_2_nodes_connectivity_[2];

			for(j=0;j<=block->block_nodes_[node_0]->n_cells_per_node_-1;j++)
			{
				n_cells_linked=0;

				for(k=0;k<=block->block_cells_[block->block_nodes_[node_0]->node_2_cells_connectivity_[j]]->n_nodes_per_cell_-1;k++)
				{
						if( (block->block_cells_[block->block_nodes_[node_0]->node_2_cells_connectivity_[j]]->cell_2_nodes_connectivity_[k]==node_1) || (block->block_cells_[block->block_nodes_[node_0]->node_2_cells_connectivity_[j]]->cell_2_nodes_connectivity_[k]==node_2) )
						{
							n_cells_linked+=1;
						}
				}

				if(n_cells_linked==2)
				{
					block->block_faces_[i]->face_2_cells_connectivity_[idx]=block->block_nodes_[node_0]->node_2_cells_connectivity_[j];
					idx+=1;
					if(idx==2)
					{
						break;
					}
				}
			}
		}
		*/


		// METHODE CHARLES
		int* node_0_node_2_cell_connectivity;
		int* node_1_node_2_cell_connectivity;
		int* node_2_node_2_cell_connectivity;
		int node_0_n_cells_per_node,node_1_n_cells_per_node,node_2_n_cells_per_node;

		for(i=0;i < block->n_faces_in_block_ ;i++)
		{

			node_0=block->block_faces_[i]->face_2_nodes_connectivity_[0];
			node_1=block->block_faces_[i]->face_2_nodes_connectivity_[1];
			node_2=block->block_faces_[i]->face_2_nodes_connectivity_[2];

			node_0_node_2_cell_connectivity=block->block_nodes_[node_0]->node_2_cells_connectivity_;
			node_0_n_cells_per_node=block->block_nodes_[node_0]->n_cells_per_node_;

			node_1_node_2_cell_connectivity=block->block_nodes_[node_1]->node_2_cells_connectivity_;
			node_1_n_cells_per_node=block->block_nodes_[node_1]->n_cells_per_node_;

			node_2_node_2_cell_connectivity=block->block_nodes_[node_2]->node_2_cells_connectivity_;
			node_2_n_cells_per_node=block->block_nodes_[node_2]->n_cells_per_node_;

			// is member algorithm node_0-node_1
			std::vector<int> common_cells_node_0_node_1;

			//loop on node_0 cells
			for (j=0;j<node_0_n_cells_per_node;j++)
			{
				//loop on node_1 cells
				for(k=0;k<node_1_n_cells_per_node;k++)
				{
					if(node_0_node_2_cell_connectivity[j]==node_1_node_2_cell_connectivity[k])
					{
						common_cells_node_0_node_1.push_back(node_0_node_2_cell_connectivity[j]);
					}
				}
			}

			// is member algorithm node_0-node_2
			std::vector<int> common_cells_node_0_node_2;

			//loop on node_0 cells
			for (j=0;j<node_0_n_cells_per_node;j++)
			{
				//loop on node_2 cells
				for(k=0;k<node_2_n_cells_per_node;k++)
				{
					if(node_0_node_2_cell_connectivity[j]==node_2_node_2_cell_connectivity[k])
					{
						common_cells_node_0_node_2.push_back(node_0_node_2_cell_connectivity[j]);
					}
				}
			}

			//is member algorithm common_cells_node_0_node_1 & common_cells_node_0_node_2
			int idx_face_2_cells=0;
			std::vector<int> common_cells_node_0_node_1_node_2;
			block->block_faces_[i]->face_2_cells_connectivity_=new int[2]();

			//loop on node_0 cells
			for (size_t j2=0;j2<common_cells_node_0_node_1.size();j2++)
			{
				//loop on node_2 cells
				for(size_t k2=0;k2<common_cells_node_0_node_2.size();k2++)
				{
					if(common_cells_node_0_node_1[j2]==common_cells_node_0_node_2[k2])
					{
						block->block_faces_[i]->face_2_cells_connectivity_[idx_face_2_cells]=common_cells_node_0_node_1[j2];
						idx_face_2_cells++;
						common_cells_node_0_node_1_node_2.push_back(common_cells_node_0_node_1[j2]);
					}
				}
			}



			if (idx_face_2_cells>=3)
			{
				std::cout<<"ERREUR CONNECTIVITÉ FACE2CELLS: ";
				for(size_t k2=0;k2<common_cells_node_0_node_1_node_2.size();k2++)
				{
					std::cout<<"cell :"<<common_cells_node_0_node_1_node_2[k2]<<" ";
				}

				std::cout<<std::endl;

			}

			common_cells_node_0_node_1.clear();
			common_cells_node_0_node_2.clear();
			common_cells_node_0_node_1_node_2.clear();

		}

		//VÉRIFICATION
		/*
		for(i=0;i <= block->n_faces_in_block_-1 ;i++)
		{
			std::cout <<i <<" FACE2CELLS "<< block->block_faces_[i]->face_2_cells_connectivity_[0]<<" "<<block->block_faces_[i]->face_2_cells_connectivity_[1] <<std::endl;
		}
		*/



std::cout<<"DÉBUT cell2facesconnectivity"<<std::endl;

	//cell_2_faces_connectivity_ & cell_2_cells_connectivity_
		idx_cell_2_faces=new int[block->n_all_cells_in_block_]();
		idx_cell_2_cells=new int[block->n_all_cells_in_block_]();
		//idx_cell_2_faces=allocate_1d_array_int(block->n_all_cells_in_block_, "idx_cell_2_faces");
		//idx_cell_2_cells=allocate_1d_array_int(block->n_all_cells_in_block_, "idx_cell_2_cells");

		for(i=0;i <= block->n_all_cells_in_block_-1 ;i++)
		{
			//idx_cell_2_faces[i]=0;
			//idx_cell_2_cells[i]=0;
			block->block_cells_[i]->cell_2_faces_connectivity_=new int[block->block_cells_[i]->n_faces_per_cell_]();
			//block->block_cells_[i]->cell_2_faces_connectivity_=allocate_1d_array_int(block->block_cells_[i]->n_faces_per_cell_, "cell_2_faces_connectivity_");
		}

		for(i=0;i <= block->n_faces_in_block_-1 ;i++)
		{
			block->block_cells_[block->block_faces_[i]->face_2_cells_connectivity_[0]]->cell_2_faces_connectivity_[idx_cell_2_faces[block->block_faces_[i]->face_2_cells_connectivity_[0]]]=i;
			idx_cell_2_faces[block->block_faces_[i]->face_2_cells_connectivity_[0]]+=1;

			block->block_cells_[block->block_faces_[i]->face_2_cells_connectivity_[1]]->cell_2_faces_connectivity_[idx_cell_2_faces[block->block_faces_[i]->face_2_cells_connectivity_[1]]]=i;
			idx_cell_2_faces[block->block_faces_[i]->face_2_cells_connectivity_[1]]+=1;


			block->block_cells_[block->block_faces_[i]->face_2_cells_connectivity_[0]]->cell_2_cells_connectivity_[idx_cell_2_cells[block->block_faces_[i]->face_2_cells_connectivity_[0]]]=block->block_faces_[i]->face_2_cells_connectivity_[1];
			idx_cell_2_cells[block->block_faces_[i]->face_2_cells_connectivity_[0]]+=1;
			block->block_cells_[block->block_faces_[i]->face_2_cells_connectivity_[1]]->cell_2_cells_connectivity_[idx_cell_2_cells[block->block_faces_[i]->face_2_cells_connectivity_[1]]]=block->block_faces_[i]->face_2_cells_connectivity_[0];
			idx_cell_2_cells[block->block_faces_[i]->face_2_cells_connectivity_[1]]+=1;

		}

std::cout<<"Remplissage de l'array face_ids_in_wall"<<std::endl;
int temp_wall_face_count=0;
int* wall_face_count;
wall_face_count=&temp_wall_face_count;
int wall_face_id, wall_cell_id;
for(i=0;i < block->n_wall_faces_ ;i++)
{
	wall_cell_id=(block->block_wall_face_ids_[i]);
	wall_face_id=(block->block_cells_[wall_cell_id])->cell_2_faces_connectivity_[0];
	block ->addFaceIdInWall(wall_face_id,wall_face_count);
	//std::cout<<"TEST WALL FACE IDS in wall array: "<< block->block_wall_face_ids_[i]<<std::endl;
	//std::cout<<"TEST WALL face ID 1: "<< (block->block_faces_[(block->block_wall_face_ids_[i])])->face_id_<<std::endl;
	//std::cout<<"TEST WALL cell ID 1: "<< (block->block_faces_[(block->block_wall_face_ids_[i])])->face_2_cells_connectivity_[0]<<std::endl;
	//std::cout<<"TEST WALL cell ID 2: "<< (block->block_faces_[(block->block_wall_face_ids_[i])])->face_2_cells_connectivity_[1]<<std::endl;
}


std::cout<<"Remplissage de l'array face_ids_in_farfield"<<std::endl;
int temp_farfield_face_count=0;
int* farfield_face_count;
farfield_face_count=&temp_farfield_face_count;
int farfield_face_id, farfield_cell_id;
for(i=0;i < block->n_farfield_faces_ ;i++)
{
	farfield_cell_id=(block->block_farfield_face_ids_[i]);
	farfield_face_id=(block->block_cells_[farfield_cell_id])->cell_2_faces_connectivity_[0];
	block ->addFaceIdInFarfield(farfield_face_id,farfield_face_count);

}

std::cout<<"Remplissage de l'array face_ids_in_symmetry"<<std::endl;
int temp_symmetry_face_count=0;
int* symmetry_face_count;
symmetry_face_count=&temp_symmetry_face_count;
int symmetry_face_id, symmetry_cell_id;
for(i=0;i < block->n_symmetry_faces_ ;i++)
{
	symmetry_cell_id=(block->block_symmetry_face_ids_[i]);
	symmetry_face_id=(block->block_cells_[symmetry_cell_id])->cell_2_faces_connectivity_[0];
	block ->addFaceIdInSymmetry(symmetry_face_id,symmetry_face_count);

}

std::cout<<"Remplissage de l'array face_ids_in_connexion"<<std::endl;
int temp_connexion_face_count=0;
int* connexion_face_count;
connexion_face_count=&temp_connexion_face_count;
int connexion_face_id, connexion_cell_id;
for(i=0;i < block->n_connexion_faces_ ;i++)
{
	connexion_cell_id=(block->block_connexion_face_ids_[i]);
	connexion_face_id=(block->block_cells_[connexion_cell_id])->cell_2_faces_connectivity_[0];
	block ->addFaceIdInConnexionBlock(connexion_face_id,connexion_face_count);

}
//std::cout<<"TEEEEEEEST WALLLLLL FAAAAAAACE IIIIIIIIDS FIIIIIIIIIIIIIIIIINAL: "<< *wall_face_count<<std::endl;







	//VÉRIFICATION
	/*
	for(i=0;i <= block->n_all_cells_in_block_-1 ;i++)
	{
		std::cout << i <<" Nb faces "<< block->block_cells_[i]->n_faces_per_cell_<<" CELL2FACES "<< block->block_cells_[i]->cell_2_faces_connectivity_[0] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[1] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[2] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[3] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[4] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[5]  <<std::endl;
		//std::cout << i <<" Nb faces "<< block->block_cells_[i]->n_faces_per_cell_<<" CELL2CELLS "<< block->block_cells_[i]->cell_2_cells_connectivity_[0] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[1] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[2] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[3] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[4] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[5]  <<std::endl;

	}
	*/
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
