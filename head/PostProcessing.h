#ifdef EULER3D_HEAD_POSTPROCESSING_H
#define EULER3D_HEAD_POSTPROCESSING_H

#include <string>
#include <vector>

class PostProcessing
{

public:

  PostProcessing(Block* block, Solver* solver, bool stopsimulation_, int iter_, int max_iter_, double convergence_criterion, double cmac_, double mach_, double aoa_rad, double gamma_);
  ~PostProcessing();

  void process(Block* block, Solver* solver, bool stopsimulation, int iter, int max_iter, double convergence_criterion, double cmac, double mach, double aoa_rad, double gamma);

private:

// Attributes

  int iteration_interval_;

  double cl_geometry_;
  double cd_geometry_;
  double cmx_geometry_;
  double cmy_geometry_;
  double cmz_geometry_;
  double cm_geometry_;
  double ro_convergence_;
  double uu_convergence_;
  double vv_convergence_;
  double ww_convergence_;
  double pp_convergence_;

  double* cp_;
  double* mach_;

  double** convergencedata_;

  // Methods

  void initializePostProcessing(Block* block);
  void computeFlowData(Block* block, Solver* solver, bool stopsimulation, int iter_, int max_iter_, double cmac_, double mach_, double aoa_rad_, double gamma_);
  void checkStopSolver(Solver* solver, bool stopsimulation_, int iter_, int max_iter_, double convergence_criterion);
  void saveFlowData(Block* block, Solver* solver);
  void convergenceSum();
  void coefficientsSum();

}

#endif
