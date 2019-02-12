#ifdef EULER3D_C++_CPP_CONVERGENCE_CPP
#define EULER3D_C++_CPP_CONVERGENCE_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>

#include "Convergence.h"

using namespace std;

Convergence::Convergence(Block* block, PostProcessing* postprocessing, int iter_)
{
  block_id = block->block_id_;

  calculateRoRms(block, postprocessing, iter_);
  calculateUuRms(block, postprocessing, iter_);
  calculateVvRms(block, postprocessing, iter_);
  calculateWwRms(block, postprocessing, iter_);
  calculatePpRms(block, postprocessing, iter_);

}

Convergence::~Convergence()
{

}

void Convergence::calculateRoRms(Block* block, PostProcessing* postprocessing, int iter_)
{
  int i;

  for (i=0; i<block->n_cell_in_block_; i++)
	{
		res_ro_ = block->primitivevariables->res_ro_[i];

		rms_ro_ += res_ro_*res_ro_;
	}

	rms_ro_ = (1./block->n_cell_in_block_)*pow(rms_ro_, 0.5);

  if (iter_ == 0)
  {
    rms0_ro_ = rms_ro_;
  }

  postprocessing->convergencedata_[block_id][6] = log10(rms_ro_)-log10(rms0_ro_);

}

void Convergence::calculateUuRms(Block* block, PostProcessing* postprocessing, int iter_)
{
  int i;

  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_uu_ = block->primitivevariables->res_uu_[i];

    rms_uu_ += res_uu_*res_uu_;
  }

  rms_uu_ = (1./block->n_cell_in_block_)*_pow(rms_uu_, 0.5);

  if (iter_ == 0)
  {
    rms0_uu_ = rms_uu_;
  }

  postprocessing->convergencedata_[block_id][7] = log10(rms_uu_)-log10(rms0_uu_);

}

void Convergence::calculateVvRms(Block* block, PostProcessing* postprocessing, int iter_)
{
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_vv_ = block->primitivevariables->res_vv_[i];

    rms_vv_ += res_vv_*res_vv_;
  }

  rms_vv_ = (1./block->n_cell_in_block_)*pow(rms_vv_, 0.5);

  if (iter_ == 0)
  {
    rms0_vv_ = rms_vv_;
  }

  postprocessing->convergencedata_[block_id][8]= log10(rms_vv_)-log10(rms0_vv_);

}

void Convergence::calculateWwRms(Block* block, PostProcessing* postprocessing, int iter_)
{
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_ww_ = block->primitivevariables->res_ww_[i];

    rms_ww_ += res_ww_*res_ww_;
  }

  rms_ww_ = (1./block->n_cell_in_block_)*pow(rms_ww_, 0.5);

  if (iter_ == 0)
  {
    rms0_ww_ = rms_ww_;
  }

  postprocessing->convergencedata_[block_id][8]= log10(rms_ww_)-log10(rms0_ww_);
}

void Convergence::calculatePpRms(Block* block, PostProcessing* postprocessing, int iter_)
{
  for (i=0; i<block->n_cell_in_block_; i++)
  {
    res_pp_ = block->primitivevariables->res_pp_[i];

    rms_pp_ += res_pp_*res_pp_;
  }

  rms_pp_ = (1./block->n_cell_in_block_)*pow(rms_pp_, 0.5);

  if (iter_ == 0)
  {
    rms0_pp_ = rms_pp_;
  }

  postprocessing->convergencedata_[block_id][8]= log10(rms_pp_)-log10(rms0_pp_);

}

#endif
