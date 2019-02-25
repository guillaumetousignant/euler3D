#ifndef EULER3D_HEAD_POSTPROCESSING_H
#define EULER3D_HEAD_POSTPROCESSING_H

#include <string>
#include <vector>

#include "AerodynamicParameters.h"
#include "Convergence.h"
#include "OutputTecplot.h"

#include "Block.h"
#include "CompleteMesh.h"
#include "Solver.h"

class PostProcessing
{

public:

  PostProcessing(CompleteMesh* complete_mesh, int max_iter, double convergence_criterion, double cmac, double mach_aircraft, double aoa_deg, double gamma);
  ~PostProcessing();

  void process(Block* block, CompleteMesh* completemesh);



// Attributes
  int current_iter_;
  int max_iter_;
  int iteration_interval_;

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

  void initializePostProcessing(CompleteMesh* complete_mesh, double cmac, double mach_aircraft, double aoa_deg, double gamma);
  void computeFlowData(Block* block, CompleteMesh* complete_mesh);
  void checkStopSolver();
  void convergenceSum(CompleteMesh* complete_mesh);
  void convergenceSum0(CompleteMesh* complete_mesh`);
  void coefficientsSum(CompleteMesh* complete_mesh);
  void saveConvergence(Block* block, Convergence* convergence);
  void saveCoefficients(Block* block);

};

#endif
