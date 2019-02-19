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

void computeConvergence(Block* block, int iter);

double getConvergence(int i);

private:

// Attributes
int block_id_;

double rms_ro_;
double rms0_ro_;
double rms_uu_;
double rms0_uu_;
double rms_vv_;
double rms0_vv_;
double rms_ww_;
double rms0_ww_;
double rms_pp_;
double rms0_pp_;
double res_ro_;
double res_uu_;
double res_vv_;
double res_ww_;
double res_pp_;

double* convergence_;

  // Method

void calculateRoRms(Block* block, int iter);
void calculateUuRms(Block* block, int iter);
void calculateVvRms(Block* block, int iter);
void calculateWwRms(Block* block, int iter);
void calculatePpRms(Block* block, int iter);

};

#endif
