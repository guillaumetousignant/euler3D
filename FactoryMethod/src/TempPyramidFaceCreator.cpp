#ifndef FACTORYMETHOD_SRC_TEMPPYRAMIDFACECREATOR_CPP
#define FACTORYMETHOD_SRC_TEMPPYRAMIDFACECREATOR_CPP

#include "TempPyramidFaceCreator.h"


// Face* TempPyramidFaceCreator::createFace(Cell* cell)
// {
// 	Face* new_face;
// 	new_face = new Face;

// 	// new_face -> n_nodes_per_face_ = n_nodes_per_face;
// 	// new_face ->face_2_nodes_connectivity_= new int[n_nodes_per_face];


// 	return new_face;

// } 

// int* TempPyramidFaceCreator::createFace(Cell* cell)
// {
// 	int* cell_2_nodes_connectivity = cell -> cell_2_nodes_connectivity_;
// 	int n_faces_per_cell = cell -> n_faces_per_cell_;
// 	int* face_2_nodes_connectivity_temp;

// 	for(int i=0;i<n_faces_per_cell;i++)
// 	{
// 		face_2_nodes_connectivity_temp = new int[n_nodes_per_face[i]];
		

// 		// new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
// 		for(int j=0;j<n_nodes_per_face[i];j++)
// 		{
// 			face_2_nodes_connectivity_temp[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local[i][j]];
// 			// face_count_+=1;
// 		} 
// 	}
// }

TempPyramidFaceCreator::TempPyramidFaceCreator()
{

	int face_2_nodes_connectivity_local_temp[5][4] = {{0,3,2,1},{0,1,4,-1},{1,2,4,-1},{2,3,4,-1},{3,0,4,-1}};
	int n_nodes_per_face_temp[5] = {4,3,3,3,3};

	face_2_nodes_connectivity_local_ = new int*[5]; 
	n_nodes_per_face_ = new int[5];

	for(int i=0;i<5;i++)
	{
		face_2_nodes_connectivity_local_[i] = new int[4];
		n_nodes_per_face_[i] = n_nodes_per_face_temp[i];
		for(int j=0;j<4;j++)
		{
			face_2_nodes_connectivity_local_[i][j] = face_2_nodes_connectivity_local_temp[i][j];
		}
	}

}

#endif