#ifdef EULER3D_SRC_AERODYNAMICPARAMETERS_CPP
#define EULER3D_SRC_AERODYNAMICPARAMETERS_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>

#include "AerodynamicParameters.h"

using namespace std;

AerodynamicParameters::AerodynamicParameters(Block* block, PostProcessing* postprocessing, Solver* solver, int iter_, int iteration_interval_, double cmac_, double mach_aircraft_, double aoa_, double gamma_)
{
  cout << "Starting Aerodynamic Parameters......................................" << endl;

  // Global value
  block_id_ = block-> block_id_;
  dynhead = 0.5*gamma_*mach_aircraft_*mach_aircraft_;

  // Calculate Mach numbers for each cell
  calculateMach(block, postprocessing, gamma_);

// Calculate pressure coefficient for each cell
  calculateCp(block, postprocessing);

  if(iter_ == iteration_interval_ || solver->stop_solver_flag_ == true)
  {
    int i, j, cell_0, cell_1;
    double nx,ny, nz, pp0, pp1, ppbc;

    // Initialize aerodynamic coefficients
    cl_ = 0.;
    cd_ = 0.;
    cm_ = 0.;
    cmx_ = 0.;
    cmy_ = 0.;
    cmz_ = 0.;

    for(i=0; i < nb_face_in_wall_; i++)
    {
      // Find wall face id
      wall_face_id_ = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell_0 = block->block_faces_[wall_face_id_]->face_2_cells_connectivity_[0];
      cell_1 = block->block_faces_[wall_face_id_]->face_2_cells_connectivity_[1];

      // Pressure value from cell 0 and 1
      pp0 = block->block_primitive_variables_->pp_[cell_0];
      pp1 = block->block_primitive_variables_->pp_[cell_1];

      // Mean pressure value
      ppbc = 0.5*(pp0 + pp1);

      // Face normals
      nx = block->block_faces_[wall_face_id_]->face_normals_[0];
      ny = block->block_faces_[wall_face_id_]->face_normals_[1];
      nz = block->block_faces_[wall_face_id_]->face_normals_[2];

    // Calculate Cl, Cd and Cm for the block
    calculateCl(ppbc, ny);
    calculateCd(ppbc, nx);
    calculateCmx(postprocessing);
    calculateCmy(postprocessing);
    calculateCmz(postprocessing);
    }

    cl_ = cl_/(dynhead*cmac_);
    cd_ = cd_/(dynhead*cmac_);

    calculateGlobalCl(postprocessing, aoa_);
    calculateGlobalCd(postprocessing, aoa_);
    calculateGlobalCm(postprocessing);
  }

  cout << "Ending Aerodynamic Parameters........................................" << endl;
}

AerodynamicParameters::~AerodynamicParameters()
{

}

void AerodynamicParameters::calculateMach(Block* block, PostProcessing* postprocessing, double gamma_)
{
  int i;
  double a,velocity;

  cout << "Execute calculateMach................................................" << endl;

  for(i=0; block->n_cells_in_block_; i++)
  {
    // Primitve variables
    pp_ = block->block_primitive_variables_->pp_[i];
    ro_ = block->block_primitive_variables_->ro_[i];
    uu_ = block->block_primitive_variables_->uu_[i];
    vv_ = block->block_primitive_variables_->vv_[i];
    ww_ = block->block_primitive_variables_->ww_[i];

    a = pow(gamma_*pp_/ro_, 0.5);

    // Calculate local velocity for each cell
    velocity = pow(pow(uu_,2)+pow(vv_,2)+pow(ww_,2), 0.5);

    // Claculate local mach number for each cell
    postprocessing->mach_[i] = velocity/a;

  }

}

void AerodynamicParameters::calculateCp(Block* block, PostProcessing* postprocessing)
{
  int i;

  cout << "Execute calculateCp.................................................." << endl;

  for(i=0; i < block->n_cells_in_block_ ; i++)
  {
    // Pressure value from cell i
    pp_ = block->block_primitive_variables_->pp_[i];

    // Save pressure coefficient in cp_ array
    postprocessing->cp_[i] = (pp_-1.)/dynhead;
  }
}

double AerodynamicParameters::calculateCl(double ppbc, double ny)
{
  cout << "Execute calculateCl.................................................." << endl;

  // Sum of lift coefficients
  cl_ += ppbc*ny;

  return cl_;

}

double AerodynamicParameters::calculateCd(double ppbc, double nx)
{
  cout << "Execute calculateCd.................................................." << endl;

  // Sum of drag coefficients
  cd_ += ppbc*nx;

  return cd_;

}

double AerodynamicParameters::calculateCmx(PostProcessing* postprocessing)
{
  cout << "Execute calculateCmx................................................." << endl;

  // Save cmx_ in array
  postprocessing->convergencedata_[block_id_][2] = cmx_;

  return cmx_;
}

double AerodynamicParameters::calculateCmy(PostProcessing* postprocessing)
{
  cout << "Execute calculateCmy................................................." << endl;

  // Save cmy_ in array
  postprocessing->convergencedata_[block_id_][3] = cmy_;

  return cmy_;
}

double AerodynamicParameters::calculateCmz(PostProcessing* postprocessing)
{
  cout << "Execute calculateCmz................................................." << endl;

  // Save clglobal_ in array
  postprocessing->convergencedata_[block_id_][4] = cmz_;

  return cmz_;
}

void AerodynamicParameters::calculateGlobalCl(PostProcessing* postprocessing, double aoa_)
{
  cout << "Execute calculateGlobalCl............................................" << endl;

  // Calculate clwind
  clglobal_ = cl_*cos(aoa_) - cd*sin(aoa_);

  // Save clglobal_ in array
  postprocessing->convergencedata_[block_id_][0] = clglobal;
}

void AerodynamicParameters::calculateGlobalCd(PostProcessing* postprocessing, double aoa_)
{
  cout << "Execute calculateGlobalCd............................................" << endl;

  cdglobal_ = cl_*sin(aoa_) + cd*cos(aoa_);

  // Save cdglobal_ in array
  postprocessing->convergencedata_[block_id_][1] = cdglobal;

}

void AerodynamicParameters::calculateGlobalCm(PostProcessing* postprocessing)
{
  cout << "Execute calculateGlobalCm............................................" << endl;

  // Save cmglobal_ in array
  postprocessing->convergencedata_[block_id_][5] = cmglobal;
}

#endif
