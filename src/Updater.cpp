#ifndef SOLVERSKELETON_SRC_UPDATER_CPP
#define SOLVERSKELETON_SRC_UPDATER_CPP

#include "Block.h"
#include "Updater.h"


#include <iostream>
using namespace std;

void Updater::updateInternalBlock(Block* block)
{
	block->test_block_+=10;
	cout<<"\t\t\tExécution updateInternalBlock: "<<block->test_block_<<endl;
}

void Updater::updateBoundary(Block* block)
{
	block->test_block_+=20;
	cout<<"\t\t\tExécution updateBoundary: "<<block->test_block_<<endl;
}
void Updater::synchroniseUpdate(Block* block)
{

}



Updater::Updater()
{

}

Updater::~Updater()
{

}


#endif