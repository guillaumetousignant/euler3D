#ifndef FACTORYMETHOD_HEAD_TETRAHEDRALCELLCREATOR_H
#define FACTORYMETHOD_HEAD_TETRAHEDRALCELLCREATOR_H

#include "CellCreator.h"

class TetrahedralCellCreator:public CellCreator
{
public:

	Cell* createCell();

};



#endif