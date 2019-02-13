#ifdef EULER3D_HEAD_AERODYNAMICPARAMETERS_H
#define EULER3D_HEAD_AERODYNAMICPARAMETERS_H

#include <string>
#include <vector>

class AerodynamicParameters
{

public:

  AerodynamicParameters(Block* block, PostProcessing* postprocessing, Solver* solver, int iter_, int iteration_interval_, double cmac_, double mach_aircraft_, double aoa_, double gamma_);
  ~AerodynamicParameters();

private:

// Attributes
int block_id_;
int wall_face_id_;

double dynhead;
double cl_;
double cd_;
double cmx_;
double cmy_;
double cmz_;
double clglobal_;
double cdglobal_;
double cmglobal_;
double pp_;
double ro_;
double uu_;
double vv_;
double ww_;

  // Methods

double calculateCl(double ppbc, double ny);
double calculateCd(double ppbc, double nx);
double calculateCm(PostProcessing* postprocessing);
double calculateCmx(PostProcessing* postprocessing);
double calculateCmy(PostProcessing* postprocessing);
double calculateCmz(PostProcessing* postprocessing);
void calculateMach(Block* block, PostProcessing* postprocessing, double gamma_);
void calculateCp(Block* block, PostProcessing* postprocessing);
void calculateGlobalCl(PostProcessing* postprocessing, double aoa_);
void calculateGlobalCd(PostProcessing* postprocessing, double aoa_);
void calculateGlobalCm(PostProcessing* postprocessing);
void checkClDriver();

}

#endif
