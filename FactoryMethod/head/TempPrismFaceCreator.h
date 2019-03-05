#ifndef FACTORYMETHOD_HEAD_TEMPPRISMFACECREATOR_H
#define FACTORYMETHOD_HEAD_TEMPPRISMFACECREATOR_H

#include "TempFaceCreator.h"

class TempPrismFaceCreator:public TempFaceCreator
{
public:
	int face_2_nodes_connectivity_local[6][4] = {{0,3,2,1},{1,2,6,5},{2,3,7,6},{3,0,4,7},{0,1,5,4},{4,5,8,7}};
	int n_nodes_per_face[6] = {4,4,4,4,4,4};

	int* createFace(Cell* cell);

};



#endif