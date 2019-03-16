#ifndef FACTORYMETHOD_HEAD_GHOSTCELLCREATOR_H
#define FACTORYMETHOD_HEAD_GHOSTCELLCREATOR_H

#include "CellCreator.h"

class GhostCellCreator:public CellCreator
{
public:

	Cell* createCell();

};



#endif