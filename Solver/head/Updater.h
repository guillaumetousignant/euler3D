#ifndef SOLVERSKELETON_HEAD_UPDATER_H
#define SOLVERSKELETON_HEAD_UPDATER_H

#include "Block.h"
#include <vector>


class Block;

class Updater
{
	public:

		double gamma_;
		int current_stage_;
		std::vector<double> alpha_rk_;
		
		void updateInternalBlock(Block* block);
		void updateBoundary(Block* block);
		void synchroniseUpdate(Block* block);


		Updater(double gamma, std::vector<double> alpha_rk);
		~Updater();


};


#endif