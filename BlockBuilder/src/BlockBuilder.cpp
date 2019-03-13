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
#include <math.h>

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
	int i,j,k,w,idx,node_0,node_1,node_2,n_cells_linked;
	int *idx_node,*idx_cell_2_faces,*idx_cell_2_cells; 
	double THETA[10],THETA_TEMP,VECTX[10],VECTY[10],VECTZ[10],norm1,norm2,cos_TEMP,PROJ_1[3],PROJ_2[3],face_center[3];
	int face2nodes_TEMP;

	
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


	//VÉRIFICATION
	/*	
	for(i=0;i <= block->n_all_cells_in_block_-1 ;i++)
	{
		std::cout << i <<" Nb faces "<< block->block_cells_[i]->n_faces_per_cell_<<" CELL2FACES "<< block->block_cells_[i]->cell_2_faces_connectivity_[0] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[1] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[2] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[3] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[4] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[5]  <<std::endl;
		//std::cout << i <<" Nb faces "<< block->block_cells_[i]->n_faces_per_cell_<<" CELL2CELLS "<< block->block_cells_[i]->cell_2_cells_connectivity_[0] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[1] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[2] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[3] <<" " << block->block_cells_[i]->cell_2_cells_connectivity_[4] <<" " << block->block_cells_[i]->cell_2_faces_connectivity_[5]  <<std::endl;

	}
	*/

		
std::cout<<"DÉBUT CENTRE CELLS"<<std::endl;

std::cout<<"DÉBUT face2nodes CCW"<<std::endl;

for(i=0;i <= block->n_faces_in_block_-1 ;i++)
{
	face_center[0]=0;
	face_center[1]=0;
	face_center[2]=0;
	/*
	block->block_faces_[i]->face_center_[0]=0;
	block->block_faces_[i]->face_center_[1]=0;
	block->block_faces_[i]->face_center_[2]=0;
	*/
	for(j=0;j <= block->block_faces_[i]->n_nodes_per_face_-1;j++)
	{

		face_center[0]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0];
		face_center[1]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[1];
		face_center[2]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[2];
		/*
		block->block_faces_[i]->face_center_[0]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0];
		block->block_faces_[i]->face_center_[1]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0];
		block->block_faces_[i]->face_center_[2]+=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0];
		*/

	}
	face_center[0]=face_center[0]/block->block_faces_[i]->n_nodes_per_face_;
	face_center[1]=face_center[1]/block->block_faces_[i]->n_nodes_per_face_;
	face_center[2]=face_center[2]/block->block_faces_[i]->n_nodes_per_face_;

	VECTX[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[0]-face_center[0];
	VECTY[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[1]-face_center[1];
	VECTZ[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[2]-face_center[2];	
	/*
	block->block_faces_[i]->face_center_[0]=block->block_faces_[i]->face_center_[0]/block->block_faces_[i]->n_nodes_per_face_;
	block->block_faces_[i]->face_center_[1]=block->block_faces_[i]->face_center_[1]/block->block_faces_[i]->n_nodes_per_face_;
	block->block_faces_[i]->face_center_[2]=block->block_faces_[i]->face_center_[2]/block->block_faces_[i]->n_nodes_per_face_;

	VECTX[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[0]-block->block_faces_[i]->face_center_[0];
	VECTY[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[1]-block->block_faces_[i]->face_center_[1];
	VECTZ[0]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[0]]->node_coordinates_[2]-block->block_faces_[i]->face_center_[2];
	*/
	norm1=sqrt(VECTX[0]*VECTX[0]+VECTY[0]*VECTY[0]+VECTZ[0]*VECTZ[0]);

	THETA[0]=0;
	
	for(j=1;j <= block->block_faces_[i]->n_nodes_per_face_-1;j++)
	{
		VECTX[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0]-face_center[0];
		VECTY[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[1]-face_center[1];
		VECTZ[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[2]-face_center[2];
		/*
		VECTX[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[0]-block->block_faces_[i]->face_center_[0];
		VECTY[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[1]-block->block_faces_[i]->face_center_[1];
		VECTZ[j]=block->block_nodes_[block->block_faces_[i]->face_2_nodes_connectivity_[j]]->node_coordinates_[2]-block->block_faces_[i]->face_center_[2];
		*/

		norm2=sqrt(VECTX[j]*VECTX[j]+VECTY[j]*VECTY[j]+VECTZ[j]*VECTZ[j]);


		cos_TEMP=(VECTX[0]*VECTX[j]+VECTY[0]*VECTY[j]+VECTZ[0]*VECTZ[j])/(norm1*norm2);

		PROJ_1[0]=((norm2*cos_TEMP)/norm1)*VECTX[0];
		PROJ_1[1]=((norm2*cos_TEMP)/norm1)*VECTY[1];
		PROJ_1[2]=((norm2*cos_TEMP)/norm1)*VECTZ[2];

		PROJ_2[0]=VECTX[j]-PROJ_1[0];
		PROJ_2[1]=VECTY[j]-PROJ_1[1];
		PROJ_2[2]=VECTZ[j]-PROJ_1[2];

		if(cos_TEMP)
		THETA[j]=atan2(sqrt(PROJ_2[0]*PROJ_2[0]+PROJ_2[1]*PROJ_2[1]+PROJ_2[2]*PROJ_2[2]),sqrt(PROJ_1[0]*PROJ_1[0]+PROJ_1[1]*PROJ_1[1]+PROJ_1[2]*PROJ_1[2]));

		face2nodes_TEMP=block->block_faces_[i]->face_2_nodes_connectivity_[j];
		THETA_TEMP=THETA[j];

		
	if(i==3)
	{
		std::cout<<cos_TEMP<<" VECT "<<VECTX[0]<<" "<<VECTY[0]<<" "<<VECTZ[0]<<" VECTj "<<VECTX[j]<<" "<<VECTY[j]<<" "<<VECTZ[j]<<" norm1 "<<norm1<<" norm2 "<<norm2<< std::endl;
		std::cout<<cos_TEMP<<" "<<sqrt(PROJ_1[0]*PROJ_1[0]+PROJ_1[1]*PROJ_1[1]+PROJ_1[2]*PROJ_1[2])<<" "<<sqrt(PROJ_2[0]*PROJ_2[0]+PROJ_2[1]*PROJ_2[1]+PROJ_2[2]*PROJ_2[2])<<" "<<THETA[j] <<std::endl;
	}


		for(k=0;k<j;k++)
		{
			if(THETA[j]<THETA[k])
			{
				for(w=j;w>k;w--)
				{
					block->block_faces_[i]->face_2_nodes_connectivity_[w]=block->block_faces_[i]->face_2_nodes_connectivity_[w-1];
					THETA[w]=THETA[w-1];
				}
				block->block_faces_[i]->face_2_nodes_connectivity_[k]=face2nodes_TEMP;
				break;
			}
		}
	}

	if(i==3)
	{
		std::cout<<THETA[0] <<" "<<THETA[1] <<" "<<THETA[2] <<" "<<THETA[3] <<" "<<std::endl;
	}

}


	//VÉRIFICATION
	/*
	for(i=0;i <= block->n_faces_in_block_-1 ;i++)
	{
		std::cout << i << " "<< block->block_faces_[i]->face_2_nodes_connectivity_[0] << " "<< block->block_faces_[i]->face_2_nodes_connectivity_[1] << " "<< block->block_faces_[i]->face_2_nodes_connectivity_[2] << " "<< block->block_faces_[i]->face_2_nodes_connectivity_[3]<<std::endl;
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