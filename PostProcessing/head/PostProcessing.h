#ifndef EULER3D_HEAD_POSTPROCESSING_H
#define EULER3D_HEAD_POSTPROCESSING_H

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <sys/stat.h>

#include "AerodynamicParameters.h"
#include "Convergence.h"
#include "OutputTecplot.h"

#include "Block.h"
#include "CompleteMesh.h"
#include "Solver.h"

class AerodynamicParameters;
class Convergence;
class OutputTecplot;
class BlockCommunicator;

class PostProcessing
{

public:

  PostProcessing(int n_blocks, int max_iter, double convergence_criterion, double cmac, double mach_aircraft, double aoa_deg, double gamma);
  ~PostProcessing();

  void process(CompleteMesh* complete_mesh, BlockCommunicator* communicator);



// Attributes
  int current_iter_;
  int max_iter_;
  int iteration_interval_;

  std::string stop_file_name_;

  double convergence_criterion_;
  bool stop_solver_;

  double cl_geometry_mesh_;
  double cd_geometry_mesh_;
  double cmx_geometry_mesh_;
  double cmy_geometry_mesh_;
  double cmz_geometry_mesh_;

  double *cl_geometry_blocks_;
  double *cd_geometry_blocks_;
  double *cmx_geometry_blocks_;
  double *cmy_geometry_blocks_;
  double *cmz_geometry_blocks_;

  double ro_rms_mesh_;
  double uu_rms_mesh_;
  double vv_rms_mesh_;
  double ww_rms_mesh_;
  double pp_rms_mesh_;

  double* ro_rms_blocks_;
  double* uu_rms_blocks_;
  double* vv_rms_blocks_;
  double* ww_rms_blocks_;
  double* pp_rms_blocks_;

  double ro_rms0_mesh_;
  double uu_rms0_mesh_;
  double vv_rms0_mesh_;
  double ww_rms0_mesh_;
  double pp_rms0_mesh_;

  double ro_convergence_;
  double uu_convergence_;
  double vv_convergence_;
  double ww_convergence_;
  double pp_convergence_;


  AerodynamicParameters* aerodynamic_parameters_;
  Convergence* convergence_;
  OutputTecplot* output_tecplot_;

  // Methods

  void computeFlowData(Block* block);
  void checkStopSolver();
  void convergenceSum(CompleteMesh* complete_mesh);
  void convergenceSum0();
  void coefficientsSum(CompleteMesh* complete_mesh);
  void saveConvergence(Block* block);
  void saveCoefficients(Block* block);


  

};

#endif
