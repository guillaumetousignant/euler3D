#ifndef FACTORYMETHOD_HEAD_FACECREATOR_H
#define FACTORYMETHOD_HEAD_FACECREATOR_H

#include "Face.h"
#include "Cell.h"


class FaceCreator
{
public:
	FaceCreator();
	~FaceCreator();

	virtual Face* createFace() = 0;
	
};

#endif