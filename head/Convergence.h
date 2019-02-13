#ifdef EULER3D_HEAD_CONVERGENCE_H
#define EULER3D_HEAD_CONVERGENCE_H

#include <string>
#include <vector>

class Convergence
{

public:

  Convergence(Block* block, PostProcessing* postprocessing, int iter);
  ~Convergence();

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

  // Method

void calculateRoRms(Block* block, PostProcessing* postprocessing, int iter);
void calculateUuRms(Block* block, PostProcessing* postprocessing, int iter);
void calculateVvRms(Block* block, PostProcessing* postprocessing, int iter);
void calculateWwRms(Block* block, PostProcessing* postprocessing, int iter);
void calculatePpRms(Block* block, PostProcessing* postprocessing, int iter);

}

#endif
