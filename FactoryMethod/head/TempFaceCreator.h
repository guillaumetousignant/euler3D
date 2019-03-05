#ifndef FACTORYMETHOD_HEAD_TEMPFACECREATOR_H
#define FACTORYMETHOD_HEAD_TEMPFACECREATOR_H

#include "Face.h"
#include "Cell.h"

class TempFaceCreator
{
public:
	int* face_2_nodes_connectivity_local;
	int* n_nodes_per_face;

	TempFaceCreator();
	~TempFaceCreator();
	virtual int* createFace(Cell* cell);

	
};


#endif