#ifndef EULER3D_SRC_POSTPROCESSING_CPP
#define EULER3D_SRC_POSTPROCESSING_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "PostProcessing.h"

using namespace std;

PostProcessing::PostProcessing(int n_blocks, int max_iter, double convergence_criterion, double cmac, double mach_aircraft, double aoa_deg, double gamma)
{
  cout << "Initialize PostProcessing............................................DONE" << endl;

  current_iter_=0;
  max_iter_=max_iter;
  iteration_interval_=10;

  convergence_criterion_=convergence_criterion;
  stop_solver_=false;

  ro_rms_blocks_ = new double[n_blocks];
  uu_rms_blocks_ = new double[n_blocks];
  vv_rms_blocks_ = new double[n_blocks];
  ww_rms_blocks_ = new double[n_blocks];
  pp_rms_blocks_ = new double[n_blocks];


  cl_geometry_blocks_ = new double[n_blocks];
  cd_geometry_blocks_ = new double[n_blocks];
  cmx_geometry_blocks_ = new double[n_blocks];
  cmy_geometry_blocks_ = new double[n_blocks];
  cmz_geometry_blocks_ = new double[n_blocks];



  aerodynamic_parameters_ = new AerodynamicParameters(cmac, mach_aircraft, aoa_deg, gamma);
  convergence_ = new Convergence();
  output_tecplot_ = new OutputTecplot(mach_aircraft, aoa_deg, gamma);

  cout << "Initialize PostProcessing............................................DONE" << endl;
}

PostProcessing::~PostProcessing()
{
  delete aerodynamic_parameters_;
  delete convergence_;
  delete output_tecplot_;
}


// ENLEVER DÉPENDANCE SOLVER
void PostProcessing::checkStopSolver()
{
  cout << "Starting checkStopSolver............................................." << endl;
#if 0
  // Vefiry conditions and change the status of the simulation if one condition is true.
  if(current_iter_+1 == max_iter_ || ro_convergence_ <= convergence_criterion_ || uu_convergence_ <= convergence_criterion || vv_convergence_ <= convergence_criterion || ww_convergence_ <= convergence_criterion || pp_convergence_ <= convergence_criterion)
  {
    stop_solver_= true;
  }
#endif
  // EN ATTENDANT
  if(current_iter_+1 == max_iter_)
  {
    stop_solver_= true;
  }
  cout << "Ending checkStopSolver..............................................." << endl;

}

void PostProcessing::convergenceSum0(CompleteMesh* complete_mesh)
{
  int i;

  cout << "Starting convergenceSum.............................................." << endl;
#if 0
    // MPI 
    ro_rms0_mesh_=0.0;
    uu_rms0_mesh_=0.0;
    vv_rms0_mesh_=0.0;
    ww_rms0_mesh_=0.0;
    pp_rms0_mesh_=0.0;

    for(i=0; i<complete_mesh->n_blocks_ ; i++) // For each block
      {
        // Convergence data
        ro_rms0_mesh_ += ro_rms_blocks_[i];
        uu_rms0_mesh_ += uu_rms_blocks_[i];
        vv_rms0_mesh_ += vv_rms_blocks_[i];
        ww_rms0_mesh_ += ww_rms_blocks_[i];
        pp_rms0_mesh_ += pp_rms_blocks_[i];
      }
#endif
  cout << "Ending convergenceSum................................................" << endl;
}

void PostProcessing::convergenceSum(CompleteMesh* complete_mesh)
{
  int i;

  cout << "Starting convergenceSum.............................................." << endl;
#if 0
    // MPI 
    ro_rms_mesh_=0.0;
    uu_rms_mesh_=0.0;
    vv_rms_mesh_=0.0;
    ww_rms_mesh_=0.0;
    pp_rms_mesh_=0.0;

    for(i=0; i<complete_mesh->n_blocks_ ; i++) // For each block
      {
        // Convergence data
        ro_rms_mesh_ += ro_rms_blocks_[i];
        uu_rms_mesh_ += uu_rms_blocks_[i];
        vv_rms_mesh_ += vv_rms_blocks_[i];
        ww_rms_mesh_ += ww_rms_blocks_[i];
        pp_rms_mesh_ += pp_rms_blocks_[i];
      }
#endif
  cout << "Ending convergenceSum................................................" << endl;
}

void PostProcessing::coefficientsSum(CompleteMesh* complete_mesh)
{
  int i;

  cout << "Starting coefficientsSum............................................." << endl;
#if 0
    // MPI 
    cl_geometry_mesh_=0.0;
    cd_geometry_mesh_=0.0;
    cmx_geometry_mesh_=0.0;
    cmy_geometry_mesh_=0.0;
    cmz_geometry_mesh_=0.0;

    for(i=0; i<completemesh->n_blocks_ ; i++) // For each block
      {
        // Aerodynamic data
        cl_geometry_mesh_ += cl_geometry_blocks_[i];
        cd_geometry_mesh_ += cd_geometry_blocks_[i];
        cmx_geometry_mesh_ += cmx_geometry_blocks_[i];
        cmy_geometry_mesh_ += cmy_geometry_blocks_[i];
        cmz_geometry_mesh_ += cmz_geometry_blocks_[i];
      }
#endif
  cout << "Ending coefficientsSum..............................................." << endl;
}



void PostProcessing::saveConvergence(Block* block)
{
  cout << "Starting saveConvergence............................................." << endl;
#if 0
  int block_id;

  block_id = block-> block_id_;

  ro_rms_blocks_[block_id] = convergence_->rms_ro_block_;
  uu_rms_blocks_[block_id] = convergence_->rms_uu_block_;
  vv_rms_blocks_[block_id] = convergence_->rms_vv_block_;
  ww_rms_blocks_[block_id] = convergence_->rms_ww_block_;
  pp_rms_blocks_[block_id] = convergence_->rms_pp_block_;

#endif
  cout << "Ending saveConvergence..............................................." << endl;
}



void PostProcessing::saveCoefficients(Block* block)
{
  cout << "Starting saveCoefficients............................................" << endl;
#if 0
  int block_id;

  block_id = block-> block_id_;

  cl_geometry_blocks_[block_id][0] = aerodynamic_parameters_->cl_global_;
  cd_geometry_blocks_[block_id][0] = aerodynamic_parameters_->cd_global_;
  cmx_geometry_blocks_[block_id][0] = aerodynamic_parameters_->cmx_;
  cmy_geometry_blocks_[block_id][0] = aerodynamic_parameters_->cmy_;
  cmz_geometry_blocks_[block_id][0] = aerodynamic_parameters_->cmz_;

#endif
  cout << "Ending saveCoefficients.............................................." << endl;
}




void PostProcessing::computeFlowData(Block* block, CompleteMesh* complete_mesh)
{
  cout << "Starting computeFlowData............................................." << endl;

  //Calculate convergence for each residual for each block
  convergence_->computeConvergence(block);
  // Save convergence into convergencedata_
  saveConvergence(block);

  //Calculate aerodynamic parameters for each block
  aerodynamic_parameters_->computeAerodynamic(block);
  // Save convergence into convergencedata_
  saveCoefficients(block);


  // MPI SYNCHRONISATION POINT
  // Sum aerodynamic parameters and convergence for each block
  coefficientsSum(complete_mesh);
  // Sum convergence for each block
  convergenceSum(complete_mesh);
  if (current_iter_==0)
  {
    convergenceSum0(complete_mesh);
  }

  
  ro_convergence_=log10(ro_rms_mesh_)-log10(ro_rms0_mesh_);
  uu_convergence_=log10(uu_rms_mesh_)-log10(uu_rms0_mesh_);
  vv_convergence_=log10(vv_rms_mesh_)-log10(vv_rms0_mesh_);
  ww_convergence_=log10(ww_rms_mesh_)-log10(ww_rms0_mesh_);
  pp_convergence_=log10(pp_rms_mesh_)-log10(pp_rms0_mesh_);


  // FIN SYNCHRONISATION
  


  cout << "Ending computeFlowData..............................................." << endl;

}


void PostProcessing::process(Block* block, CompleteMesh* complete_mesh)
{
  cout << "Starting process....................................................." << endl;

  if (current_iter_%iteration_interval_==0||current_iter_+1==max_iter_)
  {
    // Compute flow data
    computeFlowData(block, complete_mesh);
    // Check simulation status
    checkStopSolver();
    if (stop_solver_==true)
    {
      cout<<"STOP ACTIVATED"<<endl;
    }
   

    // Save and print flow data into binary files
    output_tecplot_->printConvergence(current_iter_, cl_geometry_mesh_, cd_geometry_mesh_, cmx_geometry_mesh_, cmy_geometry_mesh_, cmz_geometry_mesh_, ro_convergence_, uu_convergence_, vv_convergence_, ww_convergence_, pp_convergence_);
  
    if (stop_solver_==true)
    {
      cout << "Writing Solution......................................................" << endl;
      output_tecplot_->printFlowData(block);
      output_tecplot_->printSurfaceFlowData(block);
      output_tecplot_->printAerodynamicCoefficients(cl_geometry_mesh_, cd_geometry_mesh_, cmx_geometry_mesh_, cmy_geometry_mesh_, cmz_geometry_mesh_);
      output_tecplot_->printRestartFile(block);
      cout << "Exiting program......................................................" << endl;
      exit(0);
    }

   
  }

  current_iter_++;

  cout << "Ending process......................................................" << endl;
}

#endif
