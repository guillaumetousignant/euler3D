#ifndef EULER3D_HEAD_OUTPUTTECPLOT_H
#define EULER3D_HEAD_OUTPUTTECPLOT_H

#include <string>
#include <vector>
#include <fstream>

#include "Block.h"
#include "Solver.h"

class OutputTecplot
{

public:

  OutputTecplot(double mach_aircraft, double aoa_deg, double gamma);
  ~OutputTecplot();

// Attributes


double mach_aircraft_;
double aoa_deg_;
double gamma_;

// oh my god that's it wow, that can't work
//std::ofstream FlowData;
//std::ofstream SurfaceFlowData;
//std::ofstream Convergence;
//std::ofstream AerodynamicCoefficients;
//std::ofstream RestartFile;

  // Methods

void printFlowData(Block* block);
void printSurfaceFlowData(Block* block);
void printConvergence(int iter, double cl, double cd, double cmx, double cmy, double cmz, double ro_convergence, double uu_convergence, double vv_convergence, double ww_convergence, double pp_convergence);
void printAerodynamicCoefficients(double cl, double cd, double cmx, double cmy, double cmz);
void printRestartFile(Block* block);

};

#endif
