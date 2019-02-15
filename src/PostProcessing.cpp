#ifdef EULER3D_SRC_POSTPROCESSING_CPP
#define EULER3D_SRC_POSTPROCESSING_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>

#include "PostProcessing.h"

using namespace std;

PostProcessing::PostProcessing(Block* block, CompleteMesh* completemesh)
{
  cout << "Starting initializePostProcessing...................................." << endl;

  cp_ = 0;
  mach_ = 0;

  initializePostProcessing(block, completemesh);

  cout << "Ending initializePostProcessing......................................" << endl;
}

PostProcessing::~PostProcessing()
{
  if(cp_ != 0)
  {
    delete [] cp_;
  }

  if(mach_ != 0)
  {
    delete [] mach_;
  }

  for(i=0; i < 11; i++)
  {
    delete [] convergencedata_[i];
  }

  delete [] convergencedata_;
}

void PostProcessing::initializePostProcessing(Block* block, CompleteMesh* completemesh)
{
  int i;

  iteration_interval_ = 0;

  // Initialize vector cp_
  cp_ = new double[block->n_cell_in_block_];

  // Initialize vector mach_
  mach_ = new double[block->n_cell_in_block_];

  // Initialize array convergencedata_
  convergencedata_ = new double[completemesh->n_blocks_]

  for(i=0; i < 10; i++)
  {
    convergencedata_[i] = new double[10];
  }

}

void PostProcessing::checkStopSolver(Solver* solver,  bool stopsimulation, int iter, int max_iter, double convergence_criterion)
{
  // Vefiry conditions and change the status of the simulation if one condition is true.
  if(iter == max_iter || stopsimulation == true || ro_convergence_ <= convergence_criterion || uu_convergence_ <= convergence_criterion || vv_convergence_ <= convergence_criterion || ww_convergence_ <= convergence_criterion || pp_convergence_ <= convergence_criterion)
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

void PostProcessing::computeFlowData(Block* block, Solver* solver, bool stopsimulation, int iter, int max_iter, double cmac, double mach, double aoa_rad, double gamma)
{
  cout << "Starting computeFlowData............................................." << endl;

  //Calculate convergence for each residual for each block
  convergence = new Convergence(block, postprocessing, iter);

  // Sum convergence for each block
  convergenceSum();

  // Check simulation status
  checkStopSolver(solver, stopsimulation, iter, max_iter, convergence_criterion);

  //Calculate aerodynamic parameters for each block
  aerodynamicparameters = new AerodynamicParemeters(block, this, solver, iter, iteration_interval_, cmac, mach, aoa_rad, gamma);

  if(iter == iteration_interval_ || solver->stop_solver_flag_ == true)
  {
    // Sum aerodynamic parameters and convergence for each block
      coeffcientsSum();

      iteration_interval_ += 100;
  }

  cout << "Ending computeFlowData..............................................." << endl;

}

void PostProcessing::saveFlowData(Block* block, Solver* solver, int iter)
{
  cout << "Starting saveFlowData................................................" << endl;

  // Call OutputTecplot to save data into binary files
  outputtecplot = new OutputTecplot(block, this, solver, iter, iteration_interval_);

  cout << "Ending saveFlowData.................................................." << endl;
}

void PostProcessing::process(Block* block, Solver* solver, bool stopsimulation, int iter, int max_iter, double convergence_criterion, double cmac, double mach, double aoa_rad, double gamma)
{
  cout << "Starting process....................................................." << endl;

  // Compute flow data for each iteration
   computeFlowData(block, solver, stopsimulation, iter, max_iter, cmac, mach, aoa_rad, gamma);

   // Save and print flow data into binary files
   saveFlowData(block, solver);

   cout << "Ending process......................................................" << endl;
}

#endif
