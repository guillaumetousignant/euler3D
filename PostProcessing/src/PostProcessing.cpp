#ifndef EULER3D_SRC_POSTPROCESSING_CPP
#define EULER3D_SRC_POSTPROCESSING_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/stat.h>

#include "PostProcessing.h"
#include "BlockCommunicator.h"

using namespace std;


PostProcessing::PostProcessing(int n_blocks, int max_iter, double convergence_criterion, double cmac, double mach_aircraft, double aoa_deg, double gamma)
{
  //cout << "Initialize PostProcessing............................................" << endl;

  stop_file_name_="STOP";
  current_iter_=0;
  max_iter_=max_iter;
  iteration_interval_=1;

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

  //cout << "Initialize PostProcessing........................................DONE" << endl;
}

PostProcessing::~PostProcessing()
{
  delete aerodynamic_parameters_;
  delete convergence_;
  delete output_tecplot_;
}


// ENLEVER D�PENDANCE SOLVER
void PostProcessing::checkStopSolver()
{
  //cout << "Starting checkStopSolver............................................." << endl;
#if 0
  // Vefiry conditions and change the status of the simulation if one condition is true.
  if(current_iter_+1 == max_iter_ || ro_convergence_ <= convergence_criterion_ || uu_convergence_ <= convergence_criterion || vv_convergence_ <= convergence_criterion || ww_convergence_ <= convergence_criterion || pp_convergence_ <= convergence_criterion)
  {
    stop_solver_= true;
  }
#endif



  // Check if STOP file exists
  struct stat buffer;
  bool file_exist_flag=(stat (stop_file_name_.c_str(), &buffer) == 0);

  // EN ATTENDANT
  if((current_iter_+1 == max_iter_)|| (ro_convergence_ <= convergence_criterion_)||(file_exist_flag))
  {
    stop_solver_= true;
  }
  //cout << "Ending checkStopSolver..............................................." << endl;

}

void PostProcessing::convergenceSum0()
{

  // EN ATTENDANT
  //cout << "Starting convergenceSum.............................................." << endl;

  ro_rms0_mesh_=ro_rms_mesh_;
  uu_rms0_mesh_=uu_rms_mesh_;
  vv_rms0_mesh_=vv_rms_mesh_;
  ww_rms0_mesh_=ww_rms_mesh_;
  pp_rms0_mesh_=pp_rms_mesh_;

  //cout << "Ending convergenceSum................................................" << endl;
}

void PostProcessing::convergenceSum(CompleteMesh* complete_mesh)
{

  // EN ATTENDANT
  int i;

  //cout << "Starting convergenceSum.............................................." << endl;

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

  //cout << "Ending convergenceSum................................................" << endl;
}

void PostProcessing::coefficientsSum(CompleteMesh* complete_mesh)
{
  // EN ATTENDANT
  int i;

  //cout << "Starting coefficientsSum............................................." << endl;

    // MPI
    cl_geometry_mesh_=0.0;
    cd_geometry_mesh_=0.0;
    cmx_geometry_mesh_=0.0;
    cmy_geometry_mesh_=0.0;
    cmz_geometry_mesh_=0.0;

    for(i=0; i<complete_mesh->n_blocks_ ; i++) // For each block
      {
        // Aerodynamic data
        cl_geometry_mesh_ += cl_geometry_blocks_[i];
        cd_geometry_mesh_ += cd_geometry_blocks_[i];
        cmx_geometry_mesh_ += cmx_geometry_blocks_[i];
        cmy_geometry_mesh_ += cmy_geometry_blocks_[i];
        cmz_geometry_mesh_ += cmz_geometry_blocks_[i];
      }

  //cout << "Ending coefficientsSum..............................................." << endl;
}



void PostProcessing::saveConvergence(Block* block)
{
  //cout << "Starting saveConvergence............................................." << endl;

  int block_id;

  block_id = block-> block_id_;

  ro_rms_blocks_[block_id] = convergence_->rms_ro_block_;
  uu_rms_blocks_[block_id] = convergence_->rms_uu_block_;
  vv_rms_blocks_[block_id] = convergence_->rms_vv_block_;
  ww_rms_blocks_[block_id] = convergence_->rms_ww_block_;
  pp_rms_blocks_[block_id] = convergence_->rms_pp_block_;


  //cout << "Ending saveConvergence..............................................." << endl;
}



void PostProcessing::saveCoefficients(Block* block)
{
  //cout << "Starting saveCoefficients............................................" << endl;

  int block_id;

  block_id = block-> block_id_;

  cl_geometry_blocks_[block_id] = aerodynamic_parameters_->cl_global_;
  cd_geometry_blocks_[block_id] = aerodynamic_parameters_->cd_global_;
  cmx_geometry_blocks_[block_id] = aerodynamic_parameters_->cmx_;
  cmy_geometry_blocks_[block_id] = aerodynamic_parameters_->cmy_;
  cmz_geometry_blocks_[block_id] = aerodynamic_parameters_->cmz_;


  //cout << "Ending saveCoefficients.............................................." << endl;
}




void PostProcessing::computeFlowData(Block* block)
{
  //cout << "Starting computeFlowData............................................." << endl;

  if (current_iter_%iteration_interval_==0||current_iter_+1==max_iter_)
  {
    //Calculate convergence for each residual for each block
    convergence_->computeConvergence(block);
    // Save convergence into convergencedata_
    saveConvergence(block);

    //Calculate aerodynamic parameters for each block
    aerodynamic_parameters_->computeAerodynamic(block);
    // Save convergence into convergencedata_
    saveCoefficients(block);
  }

  //cout << "Ending computeFlowData..............................................." << endl;

}


void PostProcessing::process(CompleteMesh* complete_mesh, BlockCommunicator* communicator)
{

  //cout << "Starting process....................................................." << endl;
  if (current_iter_%iteration_interval_==0||current_iter_+1==max_iter_)
  {

    int i;
    int n_blocks_in_process;
    int* my_blocks;
    Block** all_blocks;
    Block* current_block;
    int n_blocks = complete_mesh->n_blocks_;

    std::cout << n_blocks << '\n';

    n_blocks_in_process=complete_mesh->n_blocks_in_process_;
    my_blocks=complete_mesh->my_blocks_;
    all_blocks=complete_mesh->all_blocks_;

    // Sum aerodynamic parameters and convergence for each block
    // Sum convergence for each block
    std::cout << "test 1" << '\n';
    communicator->getGlobal(complete_mesh, this);
    std::cout << "test 2" << '\n';

    ro_rms_mesh_ = sqrt(ro_rms_mesh_);
    uu_rms_mesh_ = sqrt(uu_rms_mesh_);
    vv_rms_mesh_ = sqrt(vv_rms_mesh_);
    ww_rms_mesh_ = sqrt(ww_rms_mesh_);
    pp_rms_mesh_ = sqrt(pp_rms_mesh_);

    if (current_iter_==0)
    {
      convergenceSum0();
    }

    if (current_iter_==1)
    {
      convergenceSum0();
    }


    ro_convergence_=log10(ro_rms_mesh_)-log10(ro_rms0_mesh_);
    uu_convergence_=log10(uu_rms_mesh_)-log10(uu_rms0_mesh_);
    vv_convergence_=log10(vv_rms_mesh_)-log10(vv_rms0_mesh_);
    ww_convergence_=log10(ww_rms_mesh_)-log10(ww_rms0_mesh_);
    pp_convergence_=log10(pp_rms_mesh_)-log10(pp_rms0_mesh_);


    checkStopSolver();
    if (stop_solver_==true)
    {
      communicator->sync();
      if (communicator->process_id_ == 0){
        cout<<"STOP ACTIVATED"<<endl;
        remove( stop_file_name_.c_str() );
      }
    }

    // EN ATTENDANT
    if (communicator->process_id_ == 0){
      cout<<"Iter: "<<current_iter_<<" Convergence Ro: "<<ro_convergence_<<" cl: "<<cl_geometry_mesh_<<" cd: "<<cd_geometry_mesh_<<endl;
    }

    // Save and print flow data into binary files

    // Pour le complete mesh seulement
    if (communicator->process_id_ == 0){
      output_tecplot_->printConvergence(current_iter_, cl_geometry_mesh_, cd_geometry_mesh_, cmx_geometry_mesh_, cmy_geometry_mesh_, cmz_geometry_mesh_, ro_convergence_, uu_convergence_, vv_convergence_, ww_convergence_, pp_convergence_,n_blocks);
    }

    if (stop_solver_==true)
    {
      if (communicator->process_id_ == 0){
        cout << "Writing Solution......................................................" << endl;
      }
      // Pour chaque block
      // SINON ON PEUT FAIRE PAR EXEMPLE printFlowData(complete_mesh), pis c'est le printFlowData qui gère la patente
      for (i=0;i<n_blocks_in_process;i++)
      {
        /// ATTENTION NE GÈRE PAS LES NOMS DES BLOCKS DIFFÉRENTS PRESENTEMENT
        current_block=all_blocks[my_blocks[i]];
        output_tecplot_->printFlowData(current_block);
        output_tecplot_->printSurfaceFlowData(current_block);
        output_tecplot_->printRestartFile(current_block);//PARTIE QUI FAIT JUSTE CALCULER LES CL ET CONVERGENCE PARTIELLE
      }

      // Pour le complete mesh seulement
      if (communicator->process_id_ == 0){
        output_tecplot_->printAerodynamicCoefficients(cl_geometry_mesh_, cd_geometry_mesh_, cmx_geometry_mesh_, cmy_geometry_mesh_, cmz_geometry_mesh_,n_blocks);
      }
      if (communicator->process_id_ == 0){
        cout << "========================END OF PROGRAM========================" << endl;
      }
      //exit(0);
    }

  }

  current_iter_++;



  //cout << "Ending process......................................................" << endl;
}



#endif
