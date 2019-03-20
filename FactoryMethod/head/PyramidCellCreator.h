#ifndef FACTORYMETHOD_HEAD_PYRAMIDCELLCREATOR_H
#define FACTORYMETHOD_HEAD_PYRAMIDCELLCREATOR_H

#include "CellCreator.h"

class PyramidCellCreator:public CellCreator
{
public:

	Cell* createCell();

};



#endif