#ifdef EULER3D_C++_H_OUTTECPLOT_H
#define EULER3D_C++_H_OUTTEPLOT_H

#include <string>
#include <vector>

class OutTeplot
{

public:

  OutTeplot(Block* block, PostProcessing* postprocessing, Solver* solver, int iter_, int iteration_interval_);
  ~OutTeplot();

private:

// Attributes

double cp_;
double mach_;
double aoa_deg_;
double cl_aircraft_;
double cd_aircraft_;
double cmx_aircraft_;
double cmy_aircraft_;
double cmz_aircraft_;
double cm_aircraft_;
double convergence_;
double ro_;
double uu_;
double vv_;
double ww_;
double pp_;
double x_;
double y_;
double z_;

std::ofstream FlowData;
std::ofstream SurfaceFlowData;
std::ofstream Convergence;
std::ofstream AerodynamicCoefficients;
std:: ofstream RestartFile;

  // Methods

void printFlowData(Block* block, PostProcessing* postprocessing);
void printSurfaceFlowData(Block* block, PostProcessing* postprocessing);
void printConvergence(Block* block, PostProcessing* postprocessing);
void printAerodynamicCoefficients(Block* block, PostProcessing* postprocessing);
void printRestartFile(Block* block, PostProcessing* postprocessing);

}

#endif
