#ifndef EULER3D_SRC_TESTMAIN_CPP
#define EULER3D_SRC_TESTMAIN_CPP

#include "PostProcessing.h"

#include <malloc.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char**argv)
{
  PostProcessing* postprocessing;
  Block* block;
  CompleteMesh* completemesh;
  Solver* solver;

  // Attributes
  bool stopsimulation = false;

  int max_iter = 1;

  double convergence_criterion = pow(10,-16);
  double cmac = 1.;
  double mach = 0.8;
  double aoa_rad = 0.20944;
  double gamma = 1.4;

  solver = new Solver();

  postprocessing = new PostProcessing(block, completemesh);

  for(int i=0; i < max_iter; i++)
  {
    postprocessing->process(block, completemesh, solver, stopsimulation, i, max_iter, convergence_criterion, cmac, mach, aoa_rad, gamma);
  }

}

#endif
