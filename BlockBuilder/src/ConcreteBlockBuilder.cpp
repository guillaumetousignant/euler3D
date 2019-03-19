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
			else if (cell_type_temp == "12") //prism
			{
				faces_sum_for_each_cell+=6;
			}
		}



		getline(myfile, line);
		getline(myfile, line);
		sscanf (line.c_str(), "%s %d",str_temp,&n_boundaries);
		block->n_real_boundaries_in_block_=n_boundaries;


		for(int boundary=0;boundary<n_boundaries;boundary++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,boundary_type_temp);
			boundary_type = boundary_type_temp;

			getline(myfile, line);
			sscanf (line.c_str(), "%s %d",str_temp,&n_elements_in_boundary);

			if(boundary_type=="FARFIELD" /*|| boundary_type == "WALL" || boundary_type == "CONNEXION"*/)
			{
				faces_sum_in_boundaries+=n_elements_in_boundary;
				//std::cout<<"on a une boundary farfield"<<std::endl;
			}


			if(boundary_type=="WALL")
			{
				//std::cout<<"on a une boundary wall"<<std::endl;
				faces_sum_in_boundaries+=n_elements_in_boundary;
			}


			if(boundary_type=="CONNECTION")
			{
				//std::cout<<"on a une boundary connection"<<std::endl;
				faces_sum_in_boundaries+=n_elements_in_boundary;
				block->n_real_boundaries_in_block_=(block->n_real_boundaries_in_block_)-1;
			}

			n_ghost_cells +=n_elements_in_boundary;

			for(int element_in_boundary = 0;element_in_boundary<n_elements_in_boundary;element_in_boundary++)
			{
				getline(myfile, line);
			}
		}
		n_boundaries=block->n_real_boundaries_in_block_;
		block ->block_boundary_cell_ids_ = new BoundaryCellIds* [n_boundaries];

		n_all_cells = n_real_cells + n_ghost_cells;
		block->block_cells_ = new Cell*[n_all_cells];

		block->n_ghost_cells_in_block_ = n_ghost_cells;
		block->n_all_cells_in_block_ = n_all_cells;

		n_faces = faces_sum_for_each_cell-(faces_sum_for_each_cell - faces_sum_in_boundaries)/2.;
		block->block_faces_ = new Face*[n_faces];
		block->n_faces_in_block_ = n_faces;
		// block->n_faces_in_block_ = 750;

		std::cout<<"---------------------------------  "<< block->n_faces_in_block_<<std::endl;

		std::cout<<n_faces<<std::endl;
		
		PrimitiveVariables* prim= new PrimitiveVariables(block->n_all_cells_in_block_);
		block->block_primitive_variables_=prim;
		
		TimeVariables* tim= new TimeVariables(block->n_all_cells_in_block_);
		block->block_time_variables_=tim;
		
		InterpolationVariables* inpvar= new InterpolationVariables(block->n_all_cells_in_block_);
		block->block_interpolation_variables_=inpvar;

		std::cout<<n_faces<<std::endl;



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
	//int n_ghost_cells;
	int cell_id = 0;
	int real_boundary_id;
	std::string cell_type_temp;
	std::string ghost_cell_type_temp;
	std::string cell_2_nodes_connectivity_temp;
	std::string ghost_cell_2_nodes_connectivity_temp;
	char boundary_type_temp[50];

	//WallCellIds *wall_boundary_temp;
	//FarfieldCellIds *farfield_boundary_temp;
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

			new_node -> block_id_ = block_id;

			// block->block_nodes_[node_id] = new Node;

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
		real_boundary_id=0;
		//block->n_real_boundaries_in_block_=n_boundaries;
		//std::cout<<"test bound: "<< n_boundaries<<std::endl;
		//block ->block_boundary_cell_ids_ = new BoundaryCellIds* [n_boundaries];


		for(int boundary_id = 0; boundary_id < n_boundaries; boundary_id++)
		{
			getline(myfile, line);
			sscanf (line.c_str(), "%s %s",str_temp,boundary_type_temp);
			std::string boundary_type_temp_str(boundary_type_temp);
			getline(myfile, line);
			sscanf (line.c_str(), "%s %i",str_temp,&n_ghost_cells_temp);

				if (boundary_type_temp_str=="WALL") // wall
				{
					//std::cout<<"on a un wall"<< std::endl;
					block->block_boundary_cell_ids_[real_boundary_id]= new WallCellIds;

					(block->block_boundary_cell_ids_[real_boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
					(block->block_boundary_cell_ids_[real_boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
					(block->block_boundary_cell_ids_[real_boundary_id])->cell_count_= new int;
					*((block->block_boundary_cell_ids_[real_boundary_id])->cell_count_)=0;
					(block->block_boundary_cell_ids_[real_boundary_id])->owner_block_=block;
					real_boundary_id=real_boundary_id+1;


				}
				else if (boundary_type_temp_str == "FARFIELD") //farfield
				{
					//std::cout<<"on a un farfield"<< std::endl;
					block->block_boundary_cell_ids_[real_boundary_id]= new FarfieldCellIds;
					
					(block->block_boundary_cell_ids_[real_boundary_id])->n_cell_in_boundary_=n_ghost_cells_temp;
					(block->block_boundary_cell_ids_[real_boundary_id])->cell_ids_in_boundary_=new int[n_ghost_cells_temp];
					(block->block_boundary_cell_ids_[real_boundary_id])->cell_count_= new int;
					*((block->block_boundary_cell_ids_[real_boundary_id])->cell_count_)=0;
					(block->block_boundary_cell_ids_[real_boundary_id])->owner_block_=block;
					real_boundary_id=real_boundary_id+1;

				}
				else if (boundary_type_temp_str == "CONNECTION") //Connection inter-bloc
				{
					//block->n_real_boundaries_in_block_=(block->n_real_boundaries_in_block_)-1;

				}


			//std::cout<<"test type bound: "<< boundary_type_temp <<std::endl;
			//std::cout<<"test nbcell in bound: "<< n_ghost_cells_temp <<std::endl;
			//std::cout<<"test la ou on est: "<< cell_id <<std::endl;
			int cond=n_ghost_cells_temp+cell_id;
			//std::cout<<"limite boucle test: "<< cond <<std::endl;
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
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[real_boundary_id-1]);
					//block ->addFaceIdInWall(int face_id, int face_count)

				}
				else if (boundary_type_temp_str == "FARFIELD") //farfield
				{
					//std::cout<<"on a un farfield"<< std::endl;
					block ->addCellIdInBoundary(cell_id,block->block_boundary_cell_ids_[real_boundary_id-1]);

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

	TempFaceCreator temp_face_creators[3];

	FaceCreator* real_face_creator = new FaceCreator();
	Cell* cell;
	Face* face;
	Face* face_already_in_block;

	

	temp_face_creators[0] = tetrahedral_face_creator;
	temp_face_creators[1] = pyramid_face_creator;
	temp_face_creators[2] = prism_face_creator;

	int* temp_nodes=nullptr;
	int n_possible_combinaisons=0;
	int** possible_combinaisons=nullptr;

	int possible_combinaisons_4_quad[24][4] = 
				{
				{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
				{2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},
				{3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
				{4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1}
				};
	int possible_combinaisons_4_triangle[6][3] = 
				{
				{1,2,3},{1,3,2},
				{2,1,3},{2,3,1},
				{3,1,2},{3,2,1}
				};

	
	

	std::cout<< "================================ "<< block->n_real_cells_in_block_<<std::endl;
	for(int i=0; i<block->n_real_cells_in_block_;i++)
	{
		Face** temp_face_array;


		cell = block -> block_cells_[i];
		// cout<<"====================================Cell_id = "<<cell->cell_id_<<endl;

		// temp_face_array = new Face*[cell->n_faces_per_cell_];

		temp_face_array = temp_face_creators[cell->creator_key_].createFace(cell);

		for(int j=0;j<cell->n_faces_per_cell_;j++)
		{

			face =  temp_face_array[j];
			if(face->n_nodes_per_face_==4)
			{
				temp_nodes = new int[4];

				temp_nodes[0] = face -> face_2_nodes_connectivity_[0];
				temp_nodes[1] = face -> face_2_nodes_connectivity_[1];
				temp_nodes[2] = face -> face_2_nodes_connectivity_[2];
				temp_nodes[3] = face -> face_2_nodes_connectivity_[3];
				n_possible_combinaisons = 24;

				possible_combinaisons = new int*[n_possible_combinaisons];

				for(int k=0;k<n_possible_combinaisons;k++)
				{
					possible_combinaisons[k] = new int[face->n_nodes_per_face_];
					for(int l=0;l<face->n_nodes_per_face_;l++)
					{
						possible_combinaisons[k][l]=possible_combinaisons_4_quad[k][l];
					}
				}
				
				
			}
			else if(face->n_nodes_per_face_==3)
			{
				temp_nodes = new int[3];

				temp_nodes[0] = face -> face_2_nodes_connectivity_[0];
				temp_nodes[1] = face -> face_2_nodes_connectivity_[1];
				temp_nodes[2] = face -> face_2_nodes_connectivity_[2];
				
				n_possible_combinaisons = 6;

				possible_combinaisons = new int*[n_possible_combinaisons];

				for(int k=0;k<n_possible_combinaisons;k++)
				{
					possible_combinaisons[k] = new int[face->n_nodes_per_face_];
					for(int l=0;l<face->n_nodes_per_face_;l++)
					{
						possible_combinaisons[k][l]=possible_combinaisons_4_triangle[k][l];
					}
				}
				
				
			}

			
			// std::cout << "\n Press return to continue \n" ;
    		// std::cin.ignore();

			// std::cout<<"nodes to check\n";
			// std::cout<<temp_nodes[0]<<"\t"<<temp_nodes[1]<<"\t"<<temp_nodes[2]<<"\t"<<std::endl;

			// double modulo_product=1.;
			// double modulo_sum = 0.;

			bool flag=true;

			// std::cout<<"face_already_in_block\n";


			for(int face_in_block=0;face_in_block<face_count_;face_in_block++)
			{
				face_already_in_block = block->block_faces_[face_in_block];


				// cout<<face_already_in_block->face_2_nodes_connectivity_[0]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[1]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[2]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[3]<<endl;

				if(face_already_in_block->n_nodes_per_face_==face->n_nodes_per_face_)
				{
					// std::cout<<temp_nodes[0]<<"\t"<<temp_nodes[1]<<"\t"<<temp_nodes[2]<<"\t"<<temp_nodes[3]<<"\t"<<std::endl;

					for(int combinaison=0;combinaison<n_possible_combinaisons;combinaison++)
					{
						int* local_combinaison=possible_combinaisons[combinaison];



						int node_count =0;

						// std::cout<<"New combinaison\n";



						for(int nodes_2_check=0;nodes_2_check<face_already_in_block->n_nodes_per_face_;nodes_2_check++)
						{
							int local_node_in_combinaison = local_combinaison[nodes_2_check]-1;



							// std::cout<<"Node = "<<temp_nodes[nodes_2_check]<<"\t Node 2 check = "<<face_already_in_block->face_2_nodes_connectivity_[local_node_in_combinaison]<<std::endl;
							if(temp_nodes[nodes_2_check]==face_already_in_block->face_2_nodes_connectivity_[local_node_in_combinaison])
							{
								// std::cout<<node_count<<endl;
								node_count+=1;
							}
							
						}

						if(node_count==face->n_nodes_per_face_)
						{
							// std::cout<<"===================================Yeeeeeee\n";

							flag = false;
							break ;

						}
						// else
						// {
						// 	flag = true;
						// }
					}	
				}
				// cout<<face_already_in_block->face_2_nodes_connectivity_[0]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[1]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[2]<<"\t"<<face_already_in_block->face_2_nodes_connectivity_[3]<<endl;
				// modulo_sum = (temp_nodes[0]+1)%(face_already_in_block->face_2_nodes_connectivity_[0]+1)+(temp_nodes[1]+1)%(face_already_in_block->face_2_nodes_connectivity_[1]+1)+(temp_nodes[2]+1)%(face_already_in_block->face_2_nodes_connectivity_[2]+1);
				
				
				// modulo_product*=modulo_sum;

			}
			// if(modulo_product!=0.)
			if(flag)
			{
				// std::cout<<"New face created\n";
				Face* new_face;
				new_face = buildFace(face_count_, face->n_nodes_per_face_,real_face_creator);
				new_face -> block_id_ = block->block_id_;
				// std::cout<<"====================================== facecount"<< face_count_<<std::endl;


				for(int node_in_face=0;node_in_face<face->n_nodes_per_face_;node_in_face++)
				{
					new_face->face_2_nodes_connectivity_[node_in_face]=face->face_2_nodes_connectivity_[node_in_face];
				}
				// cout<<"Face_id = "<<new_face->face_id_<<endl;
				// cout<<new_face->face_2_nodes_connectivity_[0]<<"\t"<<new_face->face_2_nodes_connectivity_[1]<<"\t"<<new_face->face_2_nodes_connectivity_[2]<<"\t"<<new_face->face_2_nodes_connectivity_[3]<<endl;

				block->addFace(new_face);
				face_count_+=1;

			}

			// if(temp_nodes)
			// {
			// 	delete [] temp_nodes;
			// }

			// for(int k=0;k<n_possible_combinaisons;k++)
			// {
			// 	if(possible_combinaisons[k])
			// 	{
			// 		delete [] possible_combinaisons[k];
			// 	}
			// }

			// if(possible_combinaisons)
			// {
			// 	delete [] possible_combinaisons;
			// }
		}

		// for(int j=0;j<cell->n_faces_per_cell_;j++)
		// {
		// 	Face* new_face = temp_face_array[j];
		// 	delete[] new_face -> face_2_nodes_connectivity_;
		// 	delete[] new_face -> face_normals_;
		// 	delete[] new_face -> face_2_cells_connectivity_;
		// 	delete[] new_face -> right_cell_r_vector_;
		// 	delete[] new_face -> left_cell_r_vector_;

		// 	// delete new_face;
		// 	delete[] temp_face_array[j];

		// }

		// for(int j=0;j<cell->n_faces_per_cell_;j++)
		// {
		// 	delete temp_face_array[j];
		// }

		// delete [] temp_face_array;

	}
	delete [] temp_nodes;
	delete real_face_creator;

}

#endif
















