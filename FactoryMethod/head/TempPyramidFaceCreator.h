#ifndef FACTORYMETHOD_HEAD_TEMPPYRAMIDFACECREATOR_H
#define FACTORYMETHOD_HEAD_TEMPPYRAMIDFACECREATOR_H

#include "TempFaceCreator.h"

class TempPyramidFaceCreator:public TempFaceCreator
{
public:
	int face_2_nodes_connectivity_local[5][4] = {{0,3,2,1},{0,1,4,-1},{1,2,4,-1},{2,3,4,-1},{3,0,4,-1}};
	int n_nodes_per_face[5] = {4,3,3,3,3};

	int* createFace(Cell* cell);

};



#endif