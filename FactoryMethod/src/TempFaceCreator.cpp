#ifndef FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP
#define FACTORYMETHOD_SRC_TEMPFACECREATOR_CPP

#include "TempFaceCreator.h"


TempFaceCreator::TempFaceCreator()
{

}
TempFaceCreator::~TempFaceCreator()
{

}

int* TempFaceCreator::createFace(Cell* cell)
{
	int* cell_2_nodes_connectivity = cell -> cell_2_nodes_connectivity_;
	int n_faces_per_cell = cell -> n_faces_per_cell_;
	int* face_2_nodes_connectivity_temp;

	// for(int i=0;i<n_faces_per_cell;i++)
	// {
	// 	face_2_nodes_connectivity_temp = new int[n_nodes_per_face[i]];
		

	// 	// new_face = buildFace(face_count_,n_nodes_per_face[i],face_creator);
	// 	for(int j=0;j<n_nodes_per_face[i];j++)
	// 	{
	// 		face_2_nodes_connectivity_temp[j] = cell_2_nodes_connectivity[face_2_nodes_connectivity_local[i][j]];
	// 		// face_count_+=1;
	// 	} 
	// }
}



#endif