#ifndef FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP
#define FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP

#include "TempFaceCreator.h"
#include <iostream>



TempFaceCreator::TempFaceCreator() /*: face_2_nodes_connectivity_local_(nullptr), n_nodes_per_face_(nullptr), n_faces_(0)*/
{

}
TempFaceCreator::~TempFaceCreator()
{
	// if (face_2_nodes_connectivity_local_!=nullptr)
	// {
	// 	for(int i=0;i<n_faces_;i++)
	// 	{
	// 		if(face_2_nodes_connectivity_local_[i]!=nullptr)
	// 		{
	// 			delete [] face_2_nodes_connectivity_local_[i];
	// 		}
	// 	}

	// 	delete [] face_2_nodes_connectivity_local_;
	// }

	// if (n_nodes_per_face_!=nullptr)
	// {
	// 	delete [] n_nodes_per_face_;
	// }

}

Face** TempFaceCreator::createFace(Cell* cell)
{
	int* cell_2_nodes_connectivity = cell -> cell_2_nodes_connectivity_;
	int n_faces_per_cell = cell -> n_faces_per_cell_;
	// int* face_2_nodes_connectivity_temp;
	Face* new_face;




	Face** return_face_array = new Face*[n_faces_per_cell];

	for(int i=0;i<n_faces_per_cell;i++)
	{
		// face_2_nodes_connectivity_temp = new int[n_nodes_per_face_[i]];
		return_face_array[i] = new Face;
		new_face = return_face_array[i];

		int n_nodes_per_face=n_nodes_per_face_[i];
		// int n_nodes_per_face = 8;

		new_face->face_2_nodes_connectivity_ = new int[n_nodes_per_face];
		new_face->n_nodes_per_face_ = n_nodes_per_face_[i];
		// new_face->n_nodes_per_face_ = n_nodes_per_face;
		
		for(int j=0;j<n_nodes_per_face_[i];j++)
		{

			// face_2_nodes_connectivity_temp[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local_[i][j]];
			new_face->face_2_nodes_connectivity_[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local_[i][j]];
			// face_count_+=1;

		} 
		// delete new_face;

	}

	return return_face_array;

	// for(int j=0;j<n_faces_per_cell;j++)
	// {
	// 	new_face = return_face_array[j];
	// 	delete[] new_face -> face_2_nodes_connectivity_;
	// 	delete[] new_face -> face_normals_;
	// 	delete[] new_face -> face_2_cells_connectivity_;
	// 	delete[] new_face -> right_cell_r_vector_;
	// 	delete[] new_face -> left_cell_r_vector_;

	// 	// delete new_face;
	// 	delete[] return_face_array[j];

	// }

	// delete[] return_face_array;
}



#endif