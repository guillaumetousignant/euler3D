#ifndef EULER3D_SRC_CONVERGENCE_CPP
#define EULER3D_SRC_CONVERGENCE_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Convergence.h"

using namespace std;

Convergence::Convergence()
{
  cout << "Initialize Convergence..............................................." << endl;


  cout << "Initialize Convergence...........................................DONE" << endl;
}

Convergence::~Convergence()
{
 
}

void Convergence::calculateRoRms(Block* block)
{
  cout << "Starting calculateRoRms.............................................." << endl;

  int i;

  #if 0
  rms_ro_block_=0.0;
  for (i=0; i<block->n_cell_in_block_; i++)
	{
		res_ro_block_ = block->block_primitive_variables_->res_ro_[i];

		rms_ro_block_ += res_ro*res_ro;
	}

	rms_ro_block_ = (1./block->n_cell_in_block_)*pow(rms_ro_block_, 0.5);

  #endif

  cout << "Ending calculateRoRms................................................" << endl;

}

void Convergence::calculateUuRms(Block* block)
{
  cout << "Starting calculateUuRms.............................................." << endl;

  int i;
  #if 0
  rms_uu_block_=0.0;
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_uu = block->block_primitive_variables_->res_uu_[i];

    rms_uu_block_ += res_uu*res_uu;
  }

  rms_uu_block_ = (1./block->n_cell_in_block_)*_pow(rms_uu_block_, 0.5);

  #endif
  cout << "Ending calculateUuRms................................................" << endl;

}

void Convergence::calculateVvRms(Block* block)
{
  cout << "Starting calculateVvRms.............................................." << endl;
  #if 0
  rms_vv_block_=0.0;
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_vv = block->block_primitive_variables_->res_vv_[i];

    rms_vv_block_ += res_vv*res_vv;
  }

  rms_vv_block_ = (1./block->n_cell_in_block_)*pow(rms_vv_block_, 0.5);

  #endif
  cout << "Ending calculateVvRms................................................" << endl;

}

void Convergence::calculateWwRms(Block* block)
{
  cout << "Starting calculateWwRms.............................................." << endl;
  #if 0
  rms_ww_block_=0.0;
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_ww = block->block_primitive_variables_->res_ww_[i];

    rms_ww_block_ += res_ww*res_ww;
  }

  rms_ww_block_ = (1./block->n_cell_in_block_)*pow(rms_ww_block_, 0.5);

  #endif
  cout << "Ending calculateWwRms................................................" << endl;
}

void Convergence::calculatePpRms(Block* block)
{
  cout << "Starting calculatePpRms.............................................." << endl;
  #if 0
  rms_pp_block_=0.0;
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_pp = block->block_primitive_variables_->res_pp_[i];

    rms_pp_block_ += res_pp*res_pp;
  }

  rms_pp_block_ = (1./block->n_cell_in_block_)*pow(rms_pp_block_, 0.5);

  #endif
  cout << "Ending calculatePpRms................................................" << endl;

}

void Convergence::computeConvergence(Block* block)
{
  calculateRoRms(block);
  calculateUuRms(block);
  calculateVvRms(block);
  calculateWwRms(block);
  calculatePpRms(block);
}



#endif
