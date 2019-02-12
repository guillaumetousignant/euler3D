#ifdef EULER3D_SRC_POSTPROCESSING_CPP
#define EULER3D_SRC_POSTPROCESSING_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>

#include "PostProcessing.h"

using namespace std;

PostProcessing::PostProcessing(Block* block, Solver* solver, bool stopsimulation_, int iter_, int max_iter_, double convergence_criterion, double cmac_, double mach_, double aoa_rad_, double gamma_)
{
  cout << "Starting post-processing............................................." << endl;

  PostProcessing* postprocessing;

  if(iter_ == 0)
  {
    initializePostProcessing(block);
  }

 // Compute flow data for each iteration
  computeFlowData(block, solver, iter_, cmac_, mach_, aoa_rad_, gamma_);

  // Save and print flow data into binary files
  saveFlowData(block, solver);

  cout << "Ending post-processing..............................................." << endl;

}

PostProcessing::~PostProcessing()
{

}

void PostProcessing::initializePostProcessing(Block* block)
{
  iteration_interval_ = 0;


}

void PostProcessing::checkStopSolver(Solver* solver,  bool stopsimulation_, int iter_, int max_iter_, double convergence_criterion)
{
  // Vefiry conditions and change the status of the simulation if one condition is true.
  if(iter_ == max_iter_ || stopsimulation_ == true || ro_convergence <= convergence_criterion || uu_convergence <= convergence_criterion || vv_convergence <= convergence_criterion || ww_convergence <= convergence_criterion || pp_convergence <= convergence_criterion)
  {
    solver->stop_solver_flag_ == true;
  }
}

void PostProcessing::convergenceSum()
{
  int i;

    for(i=0; i<nblock ; i++) // For each block
      {
        // Convergence data
        ro_convergence_ += convergencedata_[i][6];
        uu_convergence_ += convergencedata_[i][7];
        vv_convergence_ += convergencedata_[i][8];
        ww_convergence_ += convergencedata_[i][9];
        pp_convergence_ += convergencedata_[i][10];
      }
}

void coefficientsSum()
{
  int i;

    for(i=0; i<nblock ; i++) // For each block
      {
        // Aerodynamic data
        cl_geometry_ += convergencedata_[i][0];
        cd_geometry_ += convergencedata_[i][1];
        cmx_geometry_ += convergencedata_[i][2];
        cmy_geometry_ += convergencedata_[i][3];
        cmz_geometry_ += convergencedata_[i][4];
        cm_geometry_ += convergencedata_[i][5];
      }
}

void PostProcessing::computeFlowData(Block* block, Solver* solver, int iter_, double cmac_, double mach_, double aoa_rad_, double gamma_)
{
  //Calculate convergence for each residual for each block
  convergence = new Convergence(block, postprocessing, iter_);

  // Sum convergence for each block
  convergenceSum();

  // Check simulation status
  checkStopSolver(solver, stopsimulation_, iter_, max_iter_, convergence_criterion);

  //Calculate aerodynamic parameters for each block
  aerodynamicparameters = new AerodynamicParemeters(block, postprocessing, solver, iter_, iteration_interval_, cmac_, mach_, aoa_rad_, gamma_);

  if(iter_ == iteration_interval_ || solver->stop_solver_flag_ == true)
  {
    // Sum aerodynamic parameters and convergence for each block
      coeffcientsSum();

      iteration_interval_ += 100;
  }
}

void PostProcessing::saveFlowData(Block* block, Solver* solver, int iter_)
{
  // Call OutputTecplot to save data into binary files
  outputtecplot = new OutputTecplot(block, postprocessing, solver, iter_);
}

#endif
