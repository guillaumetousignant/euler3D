#ifndef FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP
#define FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP

#include "TempFaceCreator.h"
#include <iostream>



TempFaceCreator::TempFaceCreator()
{

}
TempFaceCreator::~TempFaceCreator()
{

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

		new_face->face_2_nodes_connectivity_ = new int[n_nodes_per_face_[i]];
		new_face->n_nodes_per_face_ = n_nodes_per_face_[i];
		// new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
		for(int j=0;j<n_nodes_per_face_[i];j++)
		{

			// face_2_nodes_connectivity_temp[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local_[i][j]];
			new_face->face_2_nodes_connectivity_[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local_[i][j]];
			// face_count_+=1;

		} 
	}

	return return_face_array;
}



#endif