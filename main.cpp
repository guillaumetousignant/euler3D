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
  PostProcessing* post_processing;
  Block* block;
  CompleteMesh* complete_mesh;
  Solver* solver;

  block= new Block();
  complete_mesh= new CompleteMesh();

  // Attributes
 
  int max_iter = 25;

  double convergence_criterion = pow(10,-16);
  double cmac = 1.;
  double mach_aircraft = 0.8;
  double aoa_deg = 0.20944;
  double gamma = 1.4;

  solver = new Solver();

  
  post_processing = new PostProcessing(complete_mesh, max_iter, convergence_criterion, cmac, mach_aircraft, aoa_deg, gamma);

  for(int i=0; i < max_iter; i++)
  {
    cout << i << endl;
    post_processing->process(block, complete_mesh);
  }
}

#endif
