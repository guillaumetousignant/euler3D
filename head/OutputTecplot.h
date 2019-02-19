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

  OutputTecplot();
  ~OutputTecplot();

void printData(Block* block, Solver* solver, int iter, int iteration_interval_, double aoa, double* data, double* cp, double* mach);

private:

// Attributes

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

double* cp_;
double* data_;
double* mach_;

std::ofstream FlowData;
std::ofstream SurfaceFlowData;
std::ofstream Convergence;
std::ofstream AerodynamicCoefficients;
std::ofstream RestartFile;

  // Methods

void printFlowData(Block* block);
void printSurfaceFlowData(Block* block);
void printConvergence(Solver* solver, int iter);
void printAerodynamicCoefficients(Block* block);
void printRestartFile(Block* block);

};

#endif
