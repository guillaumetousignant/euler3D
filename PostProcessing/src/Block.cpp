#ifndef SOLVERSKELETON_SRC_BLOCK_CPP
#define SOLVERSKELETON_SRC_BLOCK_CPP

#include "Block.h"

#include <iostream>
using namespace std;

Block::Block(int test_block)
{
	test_block_=test_block;
	n_cells_in_block_ = 20;
  	nb_face_in_wall_=10;
}


Block::~Block()
{

}


#endif
