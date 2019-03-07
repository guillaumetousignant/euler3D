#ifndef FACTORYMETHOD_HEAD_FACECREATOR_H
#define FACTORYMETHOD_HEAD_FACECREATOR_H

#include "Face.h"

class FaceCreator
{
public:
	FaceCreator();
	~FaceCreator();

	Face* createFace();
	
};

#endif