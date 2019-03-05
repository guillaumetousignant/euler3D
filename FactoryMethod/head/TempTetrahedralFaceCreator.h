#ifndef FACTORYMETHOD_HEAD_TEMPTETRAHEDRALFACECREATOR_H
#define FACTORYMETHOD_HEAD_TEMPTETRAHEDRALFACECREATOR_H

#include "TempFaceCreator.h"

class TempTetrahedralFaceCreator:public TempFaceCreator
{
public:
	int face_2_nodes_connectivity_local[4][3] = {{0,2,1},{0,1,3},{1,2,3},{2,0,3}};
	int n_nodes_per_face[4] = {3,3,3,3};

	int* createFace(Cell* cell);

};



#endif