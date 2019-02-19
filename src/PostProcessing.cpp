#ifndef EULER3D_SRC_POSTPROCESSING_CPP
#define EULER3D_SRC_POSTPROCESSING_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "PostProcessing.h"

using namespace std;

PostProcessing::PostProcessing(Block* block, CompleteMesh* completemesh)
{
  cout << "Starting PostProcessing.............................................." << endl;

  cp_ = 0;
  mach_ = 0;

  initializePostProcessing(block, completemesh);

  cout << "Ending PostProcessing................................................" << endl;
}

PostProcessing::~PostProcessing()
{
  if(cp_ != 0)
  {
    delete [] cp_;
  }

  if(data_ != 0)
  {
    delete [] data_;
  }

  if(mach_ != 0)
  {
    delete [] mach_;
  }

  for(int i=0; i < 11; i++)
  {
    delete [] convergencedata_[i];
  }

  delete [] convergencedata_;

  delete aerodynamicparameters;
  delete convergence;
  delete outputtecplot;
}

void PostProcessing::initializePostProcessing(Block* block, CompleteMesh* completemesh)
{
  int i;

  cout << "Starting initializePostProcessing...................................." << endl;


  iteration_interval_ = 0;
#if 0
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
#endif

  aerodynamicparameters = new AerodynamicParameters(block);
  convergence = new Convergence();
  outputtecplot = new OutputTecplot();

  cout << "Ending initializePostProcessing......................................" << endl;

}

void PostProcessing::checkStopSolver(Solver* solver,  bool stopsimulation, int iter, int max_iter, double convergence_criterion)
{
  cout << "Starting checkStopSolver............................................." << endl;
#if 0
  // Vefiry conditions and change the status of the simulation if one condition is true.
  if(iter == max_iter || stopsimulation == true || ro_convergence_ <= convergence_criterion || uu_convergence_ <= convergence_criterion || vv_convergence_ <= convergence_criterion || ww_convergence_ <= convergence_criterion || pp_convergence_ <= convergence_criterion)
  {
    solver->stop_solver_flag_ == true;
  }
#endif

  cout << "Ending checkStopSolver..............................................." << endl;

}

void PostProcessing::convergenceSum(CompleteMesh* completemesh)
{
  int i;

  cout << "Starting convergenceSum.............................................." << endl;
#if 0
    for(i=0; i<completemesh->n_blocks_ ; i++) // For each block
      {
        // Convergence data
        ro_convergence_ += convergencedata_[i][5];
        uu_convergence_ += convergencedata_[i][6];
        vv_convergence_ += convergencedata_[i][7];
        ww_convergence_ += convergencedata_[i][8];
        pp_convergence_ += convergencedata_[i][9];
      }
#endif
  cout << "Ending convergenceSum................................................" << endl;
}

void coefficientsSum(CompleteMesh* completemesh)
{
  int i;

  cout << "Starting coefficientsSum............................................." << endl;
#if 0
    for(i=0; i<completemesh->n_blocks_ ; i++) // For each block
      {
        // Aerodynamic data
        cl_geometry_ += convergencedata_[i][0];
        cd_geometry_ += convergencedata_[i][1];
        cmx_geometry_ += convergencedata_[i][2];
        cmy_geometry_ += convergencedata_[i][3];
        cmz_geometry_ += convergencedata_[i][4];
      }
#endif
  cout << "Ending coefficientsSum..............................................." << endl;
}

void PostProcessing::saveConvergence(Block* block, Convergence* convergence)
{
  cout << "Starting saveConvergence............................................." << endl;
#if 0
  int block_id;

  block_id = block-> block_id_;

  convergencedata[block_id][5] = convergence->getConvergence(0);
  convergencedata[block_id][6] = convergence->getConvergence(1);
  convergencedata[block_id][7] = convergence->getConvergence(2);
  convergencedata[block_id][8] = convergence->getConvergence(3);
  convergencedata[block_id][9] = convergence->getConvergence(4);
#endif
  cout << "Ending saveConvergence..............................................." << endl;
}

void PostProcessing::saveCoefficients(Block* block)
{
  cout << "Starting saveCoefficients............................................" << endl;
#if 0
  int block_id;

  block_id = block-> block_id_;

  convergencedata[block_id][0] = aerodynamicparameters->getCoefficients(0);
  convergencedata[block_id][1] = aerodynamicparameters->getCoefficients(1);
  convergencedata[block_id][2] = aerodynamicparameters->getCoefficients(2);
  convergencedata[block_id][3] = aerodynamicparameters->getCoefficients(3);
  convergencedata[block_id][4] = aerodynamicparameters->getCoefficients(4);
#endif
  cout << "Ending saveCoefficients.............................................." << endl;
}

void PostProcessing::saveCp(Block* block)
{
  int i;

  cout << "Starting saveCp......................................................" << endl;

  #if 0
  for(i=0; i < block->n_cells_in_block_ ; i++)
  {
    // Save pressure coefficient in cp_ array
    cp_[i] = aerodynamicparameters->getCp(i);
  }
  #endif

  cout << "Ending saveCp........................................................" << endl;
}

void PostProcessing::saveMach(Block* block)
{
  int i;

  cout << "Starting saveMach...................................................." << endl;

  #if 0
  for(i=0; i < block->n_cells_in_block_ ; i++)
  {
    // Save Mach numbers in mach_ array
    mach_[i] = aerodynamicparameters->getMach(i);
  }
  #endif

  cout << "Ending saveMach......................................................" << endl;
}

void PostProcessing::saveData()
{
  data_[0] = cl_geometry_;
  data_[1] = cd_geometry_;
  data_[2] = cmx_geometry_;
  data_[3] = cmy_geometry_;
  data_[4] = cmz_geometry_;
  data_[5] = ro_convergence_;
  data_[6] = uu_convergence_;
  data_[7] = vv_convergence_;
  data_[8] = ww_convergence_;
  data_[9] = pp_convergence_;
}

void PostProcessing::computeFlowData(Block* block, CompleteMesh* completemesh, Solver* solver, bool stopsimulation, int iter, int max_iter, double cmac, double mach, double aoa_rad, double gamma, double convergence_criterion)
{
  cout << "Starting computeFlowData............................................." << endl;

  //Calculate convergence for each residual for each block
  convergence->computeConvergence(block, iter);

  // Save convergence into convergencedata_
  saveConvergence(block, convergence);

  // Sum convergence for each block
  convergenceSum(completemesh);

  // Check simulation status
  checkStopSolver(solver, stopsimulation, iter, max_iter, convergence_criterion);

  //Calculate aerodynamic parameters for each block
  aerodynamicparameters->computeAerodynamic(block, solver, iter, iteration_interval_, cmac,  mach, aoa_rad, gamma);

  // Save pressure coefficients into an array
  saveCp(block);

  // Save Mach numbers into an array
  saveMach(block);

  if(iter == iteration_interval_ || solver->stop_solver_flag_ == true)
  {
    // Save convergence into convergencedata_
    saveCoefficients(block);

    // Sum aerodynamic parameters and convergence for each block
    coefficientsSum(completemesh);

    iteration_interval_ += 100;
  }

  cout << "Ending computeFlowData..............................................." << endl;

}

void PostProcessing::saveFlowData(Block* block, Solver* solver, int iter, double aoa_rad)
{
  cout << "Starting saveFlowData................................................" << endl;

  //Regroup data into an array
  saveData();

  // Call OutputTecplot to save data into binary files
  outputtecplot->printData(block, solver, iter, iteration_interval_, aoa_rad, data_, cp_, mach_);

  cout << "Ending saveFlowData.................................................." << endl;
}

void PostProcessing::process(Block* block, CompleteMesh* completemesh, Solver* solver, bool stopsimulation, int iter, int max_iter, double convergence_criterion, double cmac, double mach, double aoa_rad, double gamma)
{
  cout << "Starting process....................................................." << endl;

  // Compute flow data for each iteration
   computeFlowData(block, completemesh, solver, stopsimulation, iter, max_iter, cmac, mach, aoa_rad, gamma, convergence_criterion);

   // Save and print flow data into binary files
   saveFlowData(block, solver, iter, aoa_rad);

   cout << "Ending process......................................................" << endl;
}

#endif
