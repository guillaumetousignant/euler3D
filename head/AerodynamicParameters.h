#ifdef EULER3D_HEAD_AERODYNAMICPARAMETERS_H
#define EULER3D_HEAD_AERODYNAMICPARAMETERS_H

#include <string>
#include <vector>

class AerodynamicParameters
{

public:

  AerodynamicParameters(Block* block, PostProcessing* postprocessing, Solver* solver, int iter, int iteration_interval_, double cmac, double mach_aircraft, double aoa, double gamma);
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
void calculateMach(Block* block, PostProcessing* postprocessing, double gamma);
void calculateCp(Block* block, PostProcessing* postprocessing);
void calculateGlobalCl(PostProcessing* postprocessing, double aoa);
void calculateGlobalCd(PostProcessing* postprocessing, double aoa);
void calculateGlobalCm(PostProcessing* postprocessing);
void checkClDriver();

}

#endif
