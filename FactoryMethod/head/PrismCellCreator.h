#ifndef FACTORYMETHOD_HEAD_PRISMCELLCREATOR_H
#define FACTORYMETHOD_HEAD_PRISMCELLCREATOR_H

#include "CellCreator.h"

class PrismCellCreator:public CellCreator
{
public:

	Cell* createCell();

};



#endif