#ifndef SOLVERSKELETON_HEAD_UPDATER_H
#define SOLVERSKELETON_HEAD_UPDATER_H

#include "Block.h"


class Block;

class Updater
{
	public:

		
		void updateInternalBlock(Block* block);
		void updateBoundary(Block* block);
		void synchroniseUpdate(Block* block);


		Updater();
		~Updater();


};


#endif