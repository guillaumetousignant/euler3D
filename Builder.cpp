/**
*Auteur: LAURENT PATRY BEAUDOIN
*DATE MODIFICATIONS: 2019-02-13
*
*
*
*/



#ifndef Builder_CPP
#define Builder_CPP

#include "Builder.h"

#include <malloc.h>
#include <stdio.h>
#include <string>

#include <iostream>
#include <fstream>

using namespace std;

Builder::Builder(std::string meshFileName, double _rofree, double _uufree, double _vvfree, double _ppfree)
{

}


Builder::~Builder()
{

}

/**
*Brief: Read .su2 file and initialize cells,nodes,faces,etc.
*/
void Builder::readMyBlocks()
{

}

/**
*Brief: build cell
*/
void Builder::buildCell(int cell_type)
{

}

/**
*Brief: build node
*/
void Builder::buildNode()
{

}

/**
*Brief: build face
*/
void Builder::buildFace(int face_type)
{

}

/**
*Brief: Complete connectivity not given by .su2 file
*/

/** attributs à ajouter
DANS BLOCK
*nb_nodes_per_cell_* 
*nb_cells_per_node_* 
*nb_nodes_per_face_*
DANS CELL
*cell_type_
*/
void Builder::setConnectivity()
{
	int i,j,k,w,idx,node_0,node_1,node_2,n_cells_linked;
	int *idx_node,*idx_cell_2_faces,*idx_cell_2_cells; 
	
	//node_2_cells_connectivity_
		
		idx_node=allocate_1d_array_int(int my_block->n_nodes_in_block_, "idx_node")
		
		for(i=0;i < my_block->n_nodes_in_block_-1 ;i++)
		{
			my_block->block_nodes_[i]->node_2_cells_connectivity_=allocate_1d_array_int(int my_block->block_nodes_[i]->n_cells_per_node_, string "node_2_cells_connectivity_");
			idx_node[i]=0;
		}

		for(i=0;i < my_Block->n_cells_in_block_-1 ;i++)
		{
			{
			for(j=0,j < my_block->block_cells_[i]->n_nodes_per_cell_-1 ;i++)
				idx=my_block->block_cells_[i]->cell_2_nodes_connectivity_[j];
				my_block->block_nodes_[idx]->node_2_cells_connectivity_[idx_node[idx]]=i;
				idx_node[idx]+=1;
			}

		}

	//face_2_cells_connectivity_
/*
		VERSION 1 : PAS BONNE

		for(i=0;i < my_block->n_faces_in_block_-1 ;i++)
		{
			my_block->block_faces_[i]->face_2_cells_connectivity_=allocate_1d_array_int(int 2, "face_2_cells_connectivity_");
		
			node_0=my_block->block_faces_[i]->face_2_nodes_connectivity_[0];
			
			
			for(j=1;j < my_block->block_faces_[i]->n_nodes_per_face_-1 ;j++)
			{	
				n_cells_linked=0;
				node_1=my_block->block_faces_[i]->face_2_nodes_connectivity_[j];

				for(k=0;k < my_block->block_nodes_[node_0]->n_cells_per_node-1 ;k++)
				{	

					for(w=0;w < my_block->block_nodes_[node_1]->n_cells_per_node-1 ; w++)
					{
						if(my_block->block_nodes[node_0]->node_2_cells_connectivity_[k]=my_block->block_nodes[node_1]->node_2_cells_connectivity_[w])
						{
							n_cells_linked+=1;
						}
	
					}

				}	

				if(n_cells_linked==2)
				{
					j=my_block->block_faces_[i]->n_nodes_per_face_;
				}			

			}	

			idx=0;

			for(k=0;k < my_block->block_nodes[node_0]->n_cells_per_node-1 ;k++)
				{	

					for(w=0;w < my_block->block_nodes[node_1]->n_cells_per_node-1 ; w++)
					{
						if(my_block->block_nodes[node_0]->node_2_cells_connectivity_[k]=my_block->block_nodes[node_1]->node_2_cells_connectivity_[w])
						{
							my_block->block_faces[i]->face_2_cells[idx]=my_block->block_nodes[node_0]->node_2_cells_connectivity_[k];
							idx+=1;
						}

					}

				}	

		}
*/

// VERSION 2 (verification de 3 points pareil)

		for(i=0;i < my_block->n_faces_in_block_-1 ;i++)
		{
			my_block->block_faces_[i]->face_2_cells_connectivity_=allocate_1d_array_int(int 2, "face_2_cells_connectivity_");
		
			idx=0;
			node_0=my_block->block_faces_[i]->face_2_nodes_connectivity_[0];
			node_1=my_block->block_faces_[i]->face_2_nodes_connectivity_[1];
			node_2=my_block->block_faces_[i]->face_2_nodes_connectivity_[2];
			
			for(j=0,j<my_block->block_nodes[node_0]->n_cells_per_node_-1,j++)
			{
				n_cells_linked=0;
				
				for(k=0,k<my_block->block_cells[my_block->block_nodes[node_0]->node_2_cells_connectivity_[j]]->n_nodes_per_cell_-1,k++)
				{
						if( (my_block->block_cells[my_block->block_nodes[node_0]->node_2_cells_connectivity_[j]]->cell_2_nodes_connectivity_[k]==node_1) || (my_block->block_cells[my_block->block_nodes[node_0]->node_2_cells_connectivity_[j]]->cell_2_nodes_connectivity_[k]==node_2) )
						{
							n_cells_linked+=1;
						}
				}

				if(n_cells_linked==2)
				{
					my_block->block_faces_[i]->face_2_cells_connectivity_[idx]=my_block->block_nodes[node_0]->node_2_cells_connectivity_[j];
					idx+=1;
					if(idx==2)
					{
						break;
					}
				}




			}


		}



	//cell_2_faces_connectivity_ & cell_2_cells_connectivity_
		idx_cell_2_faces=allocate_1d_array_int(int my_block->n_cells_in_block_, "idx_cell_2_faces")
		idx_cell_2_cells=allocate_1d_array_int(int my_block->n_cells_in_block_, "idx_cell_2_cells")

		for(i=0;i < my_block->n_cells_in_block_-1 ;i++)
		{
			idx_cell_2_faces[i]=0;
			idx_cell_2_cells[i]=0;

			switch (my_block->block_cells_[i]->cell_type_) 

		 	{
			  case 10: //tetrahedral
			  my_block->block_cells->cell_2_faces_connectivity_=allocate_1d_array_int(int 4, "cell_2_faces_connectivity_");
			  my_block->block_cells->cell_2_cells_connectivity_=allocate_1d_array_int(int 4, "cell_2_cells_connectivity_");
			  
			    break;
			  case 12: //hexahedral
			  my_block->block_cells->cell_2_faces_connectivity_=allocate_1d_array_int(int 6, "cell_2_faces_connectivity_");
			  my_block->block_cells->cell_2_cells_connectivity_=allocate_1d_array_int(int 6, "cell_2_cells_connectivity_");
			    break;
			  case 13: //prism
			  my_block->block_cells->cell_2_faces_connectivity_=allocate_1d_array_int(int 2+((my_block->block_cells_[i]->n_nodes_per_cell_)/2), "cell_2_faces_connectivity_");
			  my_block->block_cells->cell_2_cells_connectivity_=allocate_1d_array_int(int 2+((my_block->block_cells_[i]->n_nodes_per_cell_)/2), "cell_2_cells_connectivity_");
			    break;	    
			  case 14: //pyramid
			  my_block->block_cells->cell_2_faces_connectivity_=allocate_1d_array_int(int my_block->block_cells_[i]->n_nodes_per_cell_, "cell_2_faces_connectivity_");
			  my_block->block_cells->cell_2_cells_connectivity_=allocate_1d_array_int(int my_block->block_cells_[i]->n_nodes_per_cell_, "cell_2_cells_connectivity_");
			    break;

			}
			
		}


		for(i=0;i < my_block->n_faces_in_block_-1 ;i++)
		{
			my_block->block_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]->cell_2_faces_connectivity_[idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]]=i;
			idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]+=1;

			my_block->block_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]->cell_2_faces_connectivity_[idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]]=i;
			idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]+=1;


			my_block->block_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]->cell_2_cells_connectivity_[idx_cell_2_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]]=my_block->block_faces_[i]->face_2_cells_connectivity_[1];
			my_block->block_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]->cell_2_cells_connectivity_[idx_cell_2_cells[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]]=my_block->block_faces_[i]->face_2_cells_connectivity_[0];
			idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[0]]+=1;
			idx_cell_2_faces[my_block->block_faces_[i]->face_2_cells_connectivity_[1]]+=1;

		}





}

int* Builder::allocate_1d_array_int(int nbpt, string str)
{
  int i;
  int *tmp;  
  
 // cout << "allocate_1d_array of size " << nbpt << " for " << str << endl;
  tmp=(int *)malloc(nbpt*sizeof(int));
  if(tmp==NULL)
  {
	  // TODO throw exception
	  cerr << str << "can not be allocated" << endl;
	  return NULL;
  }

  for (i=0;i<nbpt;i++) tmp[i]=0.0;
  
  return tmp;
}