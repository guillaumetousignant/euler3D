#ifndef EULER3D_HEAD_CONVERGENCE_H
#define EULER3D_HEAD_CONVERGENCE_H

#include <string>
#include <vector>

#include "Block.h"

class Convergence
{

public:

  Convergence();
  ~Convergence();

void computeConvergence(Block* block);




// Attributes


double rms_ro_block_;
double rms_uu_block_;
double rms_vv_block_;
double rms_ww_block_;
double rms_pp_block_;

  // Method

void calculateRoRms(Block* block);
void calculateUuRms(Block* block);
void calculateVvRms(Block* block);
void calculateWwRms(Block* block);
void calculatePpRms(Block* block);

};

#endif
