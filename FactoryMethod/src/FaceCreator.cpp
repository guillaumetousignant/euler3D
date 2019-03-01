#ifndef FACTORYMETHOD_SRC_FACECREATOR_CPP
#define FACTORYMETHOD_SRC_FACECREATOR_CPP

#include "FaceCreator.h"

FaceCreator::FaceCreator()
{

}
FaceCreator::~FaceCreator()
{

}

Face* FaceCreator::createFace()
{
	Face* new_face;
	new_face = new Face;
	return new_face;
}

#endif