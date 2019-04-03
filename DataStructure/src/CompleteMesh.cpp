#ifndef DATASTRUCTURE_SRC_COMPLETEMESH_CPP
#define DATASTRUCTURE_SRC_COMPLETEMESH_CPP

#include "CompleteMesh.h"
#include "Block.h"
#include "BlockBuilder.h"
#include "ConcreteBlockBuilder.h"
#include <string>
#include <iostream>
using namespace std;


CompleteMesh::CompleteMesh(int n_blocks, int n_blocks_in_process, int* my_blocks) : n_blocks_(0), n_blocks_in_process_(0), my_blocks_(nullptr), all_blocks_(nullptr)

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

string CompleteMesh::preReadTopology(Block* block)
{
std::ifstream myfile(Topology);
char str_temp[200];
std::string block_file_;
int n_blocks

if (myfile.is_open())
{
	getline(myfile, line);
  scanf (line.c_str(), "%s %d",str_temp,n_blocks);

  for(i=0;i<n_blocks;i++)
   {
   	if(i==block->block_id_)
   	{
   		getline(myfile, line);
   		scanf (line.c_str(), "%s",str_temp);
   		block_file_=str_temp;
   		return block_file_;
      break;
   	}
   	else
   	{
   		getline(myfile, line);
   	}   
}
myfile.close();
}
else if (myfile.fail())
{
cerr << "fail opening topology file " << meshFileName << endl;
}


}

void CompleteMesh::readTopology(Block* block, int& count)
{
std::ifstream myfile(Topology);
char str_temp[200];
std::string line;
int i,j,k;
int n_blocks,n_connexions,n_boundaries,n_elems,block_destination_temp,elem_id_destination_temp;

if (myfile.is_open())
{
  getline(myfile, line);
  scanf (line.c_str(), "%s %d",str_temp,n_blocks);

  for(i=0;i<n_blocks;i++)
   {
      getline(myfile, line);
   }

   for(i=0;i<n_blocks;i++)
   {

    if(i==block->block_id_)
    {
      getline(myfile, line);
      scanf (line.c_str(), "%s %d",str_temp,n_boundaries);

      for(j=0;j<n_boundaries;j++)
      {

        int** block_connexion_boundary_cell_ids_ = new ConnexionCellIds*;

        getline(myfile, line);
        scanf (line.c_str(), "%s %d",str_temp,block_destination_temp); 
        getline(myfile, line);
        scanf (line.c_str(), "%s %d",str_temp,n_elems); 
        

        count=0;
        block_connexion_boundary_cell_ids_[j]->block_origin_=i;
        block_connexion_boundary_cell_ids_[j]->block_destination_=block_destination_temp;
        block_connexion_boundary_cell_ids_[j]->n_cell_in_boundary_=n_elems;
        block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_other_block_=new int[n_elems]();
        block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_=new int[n_elems]();
        block_connexion_boundary_cell_ids_[j]->owner_block_=block;
        block_connexion_boundary_cell_ids_[j]->cell_count_= new int;
        *((block->block_connexion_boundary_cell_ids_[j])->cell_count_)=0;

        for(k=0;k<n_elems;k++)
        {
          getline(myfile, line);
          scanf (line.c_str(), "%s %d",str_temp,elem_id_destination_temp); 

          block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_[k]=count;
          count=+1;
          *(block->block_connexion_boundary_cell_ids_[j]->cell_count_)+=1;

          block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_other_block_=elem_id_destination_temp;

        }

        BlockCommunicator::addCellIdInConnexion(block_connexion_boundary_cell_ids_);
      
      }

    }
    else
    {
 getline(myfile, line);
      scanf (line.c_str(), "%s %d",str_temp,n_boundaries);

      for(j=0;j<n_boundaries;j++)
      {

        int** block_connexion_boundary_cell_ids_ = new ConnexionCellIds*;

        getline(myfile, line);
        scanf (line.c_str(), "%s %d",str_temp,block_destination_temp); 
        getline(myfile, line);
        scanf (line.c_str(), "%s %d",str_temp,n_elems); 
        

        count=0;
        block_connexion_boundary_cell_ids_[j]->block_origin_=i;
        block_connexion_boundary_cell_ids_[j]->block_destination_=block_destination_temp;
        block_connexion_boundary_cell_ids_[j]->n_cell_in_boundary_=n_elems;
        block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_other_block_=new int[n_elems]();
        block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_=new int[n_elems]();
        block_connexion_boundary_cell_ids_[j]->owner_block_=block;
        block_connexion_boundary_cell_ids_[j]->cell_count_= new int;
        *((block->block_connexion_boundary_cell_ids_[j])->cell_count_)=0;

        for(k=0;k<n_elems;k++)
        {
          getline(myfile, line);
          scanf (line.c_str(), "%s %d",str_temp,elem_id_destination_temp); 

          block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_[k]= nullptr;
          *(block->block_connexion_boundary_cell_ids_[j]->cell_count_)+=1;

          block_connexion_boundary_cell_ids_[j]->cell_ids_in_boundary_other_block_=elem_id_destination_temp;


        }

        BlockCommunicator::addCellIdInConnexion(block_connexion_boundary_cell_ids_);
    }


  }
myfile.close();
}
else if (myfile.fail())
{
cerr << "fail opening topology file " << meshFileName << endl;
}


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

#endif
