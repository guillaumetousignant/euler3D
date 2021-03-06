#ifndef DATASTRUCTURE_SRC_COMPLETEMESH_CPP
#define DATASTRUCTURE_SRC_COMPLETEMESH_CPP

#include "CompleteMesh.h"
#include "Block.h"
#include "BlockBuilder.h"
#include "ConcreteBlockBuilder.h"
#include "MetricsInitializer.h"
#include "Interface.h"
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

string CompleteMesh::getBlockFileName(int block_id)
{
	string line_in_file;
	ifstream topology_file(topology_file_name_);
	string block_file_name;

	if (topology_file.is_open())
	{
		topology_file.ignore(256, '\n');
		for(int i=0;i<block_id;i++)
		{
			//Skip n_blocks_
			getline(topology_file, line_in_file);
		}
		// Reading NBlocks
		topology_file >> block_file_name;
		//block_file_name="../"+block_file_name; // why
		if (block_id == 0){
		cout<<"Block File Name is: "<<block_file_name<<endl;
		}
		topology_file.close();
	}
	else
	{
		cout << "Opening File'" << topology_file_name_ << "' Failure..."<<endl;
		/*std::ofstream outfile ("STOP");
		outfile.close();*/
		exit(42);
	}
	
	return block_file_name;
}


void CompleteMesh::InitializeMyBlocks(Interface* interface, BlockCommunicator* communicator)
{
	//std::string block_id_string;
	//std::string block_file;
	//Block* new_block;
	//int block_id;

	// #pragma omp parallel for num_threads(8) // DECOMMENTER POUR AVOIR OPENMP
	for(int i=0;i<n_blocks_in_process_;i++)
	{

		std::string block_file_name;
		int block_id = my_blocks_[i];
		block_file_name=getBlockFileName(block_id);

		if (communicator->process_id_ == 0){
		cout << "Initialize block number: "<<block_id<<endl;
		}
		
		ConcreteBlockBuilder block_builder=ConcreteBlockBuilder(block_file_name, topology_file_name_);
		Block* new_block = all_blocks_[block_id];

		//std::cout<<new_block -> block_id_<<std::endl;

		block_builder.preReadMyBlock(new_block);
		block_builder.readMyBlock(new_block, communicator);

		block_builder.createMyFaces(new_block);

		block_builder.setConnectivity(new_block);

		// cout<<"Cellules\n";
		/*Cell* test_cell;
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
		}*/

		// test_cell = new_block ->block_cells_[12];
		// cout<<test_cell->cell_2_nodes_connectivity_[1]<<endl;
		// cout<<"Noeuds\n";
		/*Node* test_node;
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
		*/

		if (communicator->process_id_ == 0){
		cout << "In MetricsInitializer........." << endl;
		}
		MetricsInitializer metricsInit(new_block);
		metricsInit.doInit();

		if (communicator->process_id_ == 0){
		cout << "In calculateFreeVariables........." << endl;
		}
		new_block->block_primitive_variables_->calculateFreeVariables(interface->gamma_interface_, interface->aoa_deg_interface_, interface->mach_aircraft_interface_);

		if (communicator->process_id_ == 0){
		cout << "In initializeFlowField........." << endl;
		}
		new_block->block_primitive_variables_->initializeFlowField(new_block->n_all_cells_in_block_);

		if (communicator->process_id_ == 0){
		cout << "In Solver........." << endl;
		}
	}


	for(int block_id=0;block_id<n_blocks_;block_id++)
	{

		
		std::ifstream myfile(topology_file_name_);
		char str_temp[200];
		std::string line;
		int i,j,k;
		int n_blocks,block_idx,n_boundaries,n_elems,block_origin_temp,elem_id_destination_temp,count_connexions;


		//cout<<"Début Set Topology............ "<<endl;

		if (myfile.is_open())
		{
				// Find current block
			getline(myfile, line);
			sscanf (line.c_str(), "%s %d",str_temp,&n_blocks);
			//cout<<"N blocks: "<<n_blocks<<endl;

				// Skip block file names
			for(i=0;i<n_blocks;i++)
			{
				myfile.ignore(256, '\n');
					//cout<<"Ignore Line"<<endl;
			}


			for(i=0;i<n_blocks;i++)
			{
					// Get block idx
				getline(myfile, line);
				sscanf (line.c_str(), "%s %d",str_temp,&block_idx);
					//cout<<"Block idx read: "<<block_idx<<endl;
					// Current block found
				if(block_idx==block_id) 
				{
					//cout<<"Block Found: "<<block_idx<<endl;
					
					// Read Count Connexions
					getline(myfile, line);
					sscanf (line.c_str(), "%s %d",str_temp,&count_connexions);

					getline(myfile, line);
					sscanf (line.c_str(), "%s %d",str_temp,&n_boundaries);

					//cout<<"Number of boundaries: "<<n_boundaries<<endl;
						// Create Connexion object for n_boundaries
					for(j=0;j<n_boundaries;j++)
					{

						ConnexionCellIds *block_connexion_boundary_cell_ids = new ConnexionCellIds();

						getline(myfile, line);
						sscanf (line.c_str(), "%s %d",str_temp,&block_origin_temp); 
						//cout<<"Source block: "<<block_origin_temp<<endl;
						getline(myfile, line);
						sscanf (line.c_str(), "%s %d",str_temp,&n_elems); 
						//cout<<"Number of elements: "<<n_elems<<endl;



						block_connexion_boundary_cell_ids->block_destination_=block_id;
						block_connexion_boundary_cell_ids->block_origin_=block_origin_temp;
						block_connexion_boundary_cell_ids->n_cell_in_boundary_=n_elems;
						block_connexion_boundary_cell_ids->cell_ids_in_boundary_other_block_=new int[n_elems]();
						block_connexion_boundary_cell_ids->cell_ids_in_boundary_=new int[n_elems]();
						block_connexion_boundary_cell_ids->owner_block_=nullptr;


						for(k=0;k<n_elems;k++)
						{
							getline(myfile, line);
							sscanf (line.c_str(), "%d",&elem_id_destination_temp); 

							block_connexion_boundary_cell_ids->cell_ids_in_boundary_[k]=count_connexions;
							count_connexions+=1;

							block_connexion_boundary_cell_ids->cell_ids_in_boundary_other_block_[k]=elem_id_destination_temp;

						}

						block_connexion_boundary_cell_ids->cell_count_= &count_connexions;

						communicator->addCellIdInConnexion(block_connexion_boundary_cell_ids);


					}

				}
					// Current block not found
				else
				{
						// Skip block

						// Skip Count Connexions
					getline(myfile, line);
					sscanf (line.c_str(), "%s %d",str_temp,&count_connexions);
					
					getline(myfile, line);
					sscanf (line.c_str(), "%s %d",str_temp,&n_boundaries);

					

					for(j=0;j<n_boundaries;j++)
					{

						getline(myfile, line);
						sscanf (line.c_str(), "%s %d",str_temp,&block_origin_temp); 
						getline(myfile, line);
						sscanf (line.c_str(), "%s %d",str_temp,&n_elems); 

						for(k=0;k<n_elems;k++)
						{
							getline(myfile, line);
							sscanf (line.c_str(), "%s %d",str_temp,&elem_id_destination_temp); 
						}
					}
				}
			}
		}
		myfile.close();		
	}
}

#endif
