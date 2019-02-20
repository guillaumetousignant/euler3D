#ifndef EULER3D_SRC_BLOCK_CPP
#define EULER3D_SRC_BLOCK_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Block.h"

using namespace std;

Block::Block()
{
  n_cells_in_block_ = 20;
}

Block::~Block()
{

}

#endif
