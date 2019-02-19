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

  convergence_ = new double[5];

  cout << "Initialize Convergence...........................................DONE" << endl;
}

Convergence::~Convergence()
{
  if(convergence_ != 0)
  {
    delete [] convergence_;
  }
}

void Convergence::calculateRoRms(Block* block, int iter)
{
  cout << "Starting calculateRoRms.............................................." << endl;

  int i;

  #if 0
  for (i=0; i<block->n_cell_in_block_; i++)
	{
		res_ro_ = block->block_primitive_variables_->res_ro_[i];

		rms_ro_ += res_ro_*res_ro_;
	}

	rms_ro_ = (1./block->n_cell_in_block_)*pow(rms_ro_, 0.5);

  if (iter == 0)
  {
    rms0_ro_ = rms_ro_;
  }

  convergence_[0] = log10(rms_ro_)-log10(rms0_ro_);
  #endif

  cout << "Ending calculateRoRms................................................" << endl;

}

void Convergence::calculateUuRms(Block* block, int iter)
{
  cout << "Starting calculateUuRms.............................................." << endl;

  int i;
  #if 0
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_uu_ = block->block_primitive_variables_->res_uu_[i];

    rms_uu_ += res_uu_*res_uu_;
  }

  rms_uu_ = (1./block->n_cell_in_block_)*_pow(rms_uu_, 0.5);

  if (iter == 0)
  {
    rms0_uu_ = rms_uu_;
  }

  convergence_[1] = log10(rms_uu_)-log10(rms0_uu_);
  #endif
  cout << "Ending calculateUuRms................................................" << endl;

}

void Convergence::calculateVvRms(Block* block, int iter)
{
  cout << "Starting calculateVvRms.............................................." << endl;
  #if 0
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_vv_ = block->block_primitive_variables_->res_vv_[i];

    rms_vv_ += res_vv_*res_vv_;
  }

  rms_vv_ = (1./block->n_cell_in_block_)*pow(rms_vv_, 0.5);

  if (iter == 0)
  {
    rms0_vv_ = rms_vv_;
  }

  convergence_[2]= log10(rms_vv_)-log10(rms0_vv_);
  #endif
  cout << "Ending calculateVvRms................................................" << endl;

}

void Convergence::calculateWwRms(Block* block, int iter)
{
  cout << "Starting calculateWwRms.............................................." << endl;
  #if 0
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_ww_ = block->block_primitive_variables_->res_ww_[i];

    rms_ww_ += res_ww_*res_ww_;
  }

  rms_ww_ = (1./block->n_cell_in_block_)*pow(rms_ww_, 0.5);

  if (iter == 0)
  {
    rms0_ww_ = rms_ww_;
  }

  convergence_[3]= log10(rms_ww_)-log10(rms0_ww_);
  #endif
  cout << "Ending calculateWwRms................................................" << endl;
}

void Convergence::calculatePpRms(Block* block, int iter)
{
  cout << "Starting calculatePpRms.............................................." << endl;
  #if 0
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_pp_ = block->block_primitive_variables_->res_pp_[i];

    rms_pp_ += res_pp_*res_pp_;
  }

  rms_pp_ = (1./block->n_cell_in_block_)*pow(rms_pp_, 0.5);

  if (iter == 0)
  {
    rms0_pp_ = rms_pp_;
  }

  convergence[4]= log10(rms_pp_)-log10(rms0_pp_);
  #endif
  cout << "Ending calculatePpRms................................................" << endl;

}

void Convergence::computeConvergence(Block* block, int iter)
{
  #if 0
  block_id = block->block_id_;
  #endif

  calculateRoRms(block, iter);
  calculateUuRms(block, iter);
  calculateVvRms(block, iter);
  calculateWwRms(block, iter);
  calculatePpRms(block, iter);
}

double Convergence::getConvergence(int i)
{
  return convergence_[i];
}

#endif
