#ifdef EULER3D_SRC_AERODYNAMICPARAMETERS_CPP
#define EULER3D_SRC_AERODYNAMICPARAMETERS_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>

#include "AerodynamicParameters.h"

using namespace std;

AerodynamicParameters::AerodynamicParameters(Block* block, PostProcessing* postprocessing, Solver* solver, int iter, int iteration_interval_, double cmac, double mach_aircraft, double aoa, double gamma)
{
  cout << "Starting Aerodynamic Parameters......................................" << endl;

  // Global value
  block_id_ = block-> block_id_;
  dynhead = 0.5*gamma*mach_aircraft*mach_aircraft;

  // Calculate Mach numbers for each cell
  calculateMach(block, postprocessing, gamma);

// Calculate pressure coefficient for each cell
  calculateCp(block, postprocessing);

  if(iter == iteration_interval_ || solver->stop_solver_flag_ == true)
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

    for(i=0; i < block->nb_face_in_wall_; i++)
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

    cl_ = cl_/(dynhead*cmac);
    cd_ = cd_/(dynhead*cmac);

    calculateGlobalCl(postprocessing, aoa);
    calculateGlobalCd(postprocessing, aoa);
    calculateGlobalCm(postprocessing);

    checkClDriver();
  }

  cout << "Ending Aerodynamic Parameters........................................" << endl;
}

AerodynamicParameters::~AerodynamicParameters()
{

}

void AerodynamicParameters::calculateMach(Block* block, PostProcessing* postprocessing, double gamma)
{
  int i;
  double a,velocity;

  cout << "Starting calculateMach..............................................." << endl;

  for(i=0; block->n_cells_in_block_; i++)
  {
    // Primitve variables
    pp_ = block->block_primitive_variables_->pp_[i];
    ro_ = block->block_primitive_variables_->ro_[i];
    uu_ = block->block_primitive_variables_->uu_[i];
    vv_ = block->block_primitive_variables_->vv_[i];
    ww_ = block->block_primitive_variables_->ww_[i];

    a = pow(gamma*pp_/ro_, 0.5);

    // Calculate local velocity for each cell
    velocity = pow(pow(uu_,2)+pow(vv_,2)+pow(ww_,2), 0.5);

    // Claculate local mach number for each cell
    postprocessing->mach_[i] = velocity/a;
  }

  cout << "Ending calculateMach................................................." << endl;
}

void AerodynamicParameters::calculateCp(Block* block, PostProcessing* postprocessing)
{
  int i;

  cout << "Starting calculateCp................................................." << endl;

  for(i=0; i < block->n_cells_in_block_ ; i++)
  {
    // Pressure value from cell i
    pp_ = block->block_primitive_variables_->pp_[i];

    // Save pressure coefficient in cp_ array
    postprocessing->cp_[i] = (pp_-1.)/dynhead;
  }

  cout << "Ending calculateCp..................................................." << endl;
}

double AerodynamicParameters::calculateCl(double ppbc, double ny)
{
  cout << "Starting calculateCl................................................." << endl;

  // Sum of lift coefficients
  cl_ += ppbc*ny;

  return cl_;

  cout << "Ending calculateCl..................................................." << endl;
}

double AerodynamicParameters::calculateCd(double ppbc, double nx)
{
  cout << "Starting calculateCd................................................." << endl;

  // Sum of drag coefficients
  cd_ += ppbc*nx;

  return cd_;

  cout << "Ending calculateCd..................................................." << endl;
}

double AerodynamicParameters::calculateCmx(PostProcessing* postprocessing)
{
  cout << "Starting calculateCmx................................................" << endl;

  // Save cmx_ in array
  postprocessing->convergencedata_[block_id_][2] = cmx_;

  return cmx_;

  cout << "Ending calculateCmx.................................................." << endl;
}

double AerodynamicParameters::calculateCmy(PostProcessing* postprocessing)
{
  cout << "Starting calculateCmy................................................" << endl;

  // Save cmy_ in array
  postprocessing->convergencedata_[block_id_][3] = cmy_;

  return cmy_;

  cout << "Ending calculateCmy.................................................." << endl;
}

double AerodynamicParameters::calculateCmz(PostProcessing* postprocessing)
{
  cout << "Starting calculateCmz................................................" << endl;

  // Save clglobal_ in array
  postprocessing->convergencedata_[block_id_][4] = cmz_;

  return cmz_;

  cout << "Ending calculateCmz.................................................." << endl;
}

void AerodynamicParameters::calculateGlobalCl(PostProcessing* postprocessing, double aoa)
{
  cout << "Starting calculateGlobalCl..........................................." << endl;

  // Calculate clwind
  clglobal_ = cl_*cos(aoa) - cd*sin(aoa);

  // Save clglobal_ in array
  postprocessing->convergencedata_[block_id_][0] = clglobal_;

  cout << "Ending calculateGlobalCl............................................" << endl;
}

void AerodynamicParameters::calculateGlobalCd(PostProcessing* postprocessing, double aoa)
{
  cout << "Starting calculateGlobalCd..........................................." << endl;

  cdglobal_ = cl_*sin(aoa) + cd*cos(aoa);

  // Save cdglobal_ in array
  postprocessing->convergencedata_[block_id_][1] = cdglobal_;

  cout << "Ending calculateGlobalCd............................................" << endl;

}

void AerodynamicParameters::calculateGlobalCm(PostProcessing* postprocessing)
{
  cout << "Starting calculateGlobalCm..........................................." << endl;

  // Save cmglobal_ in array
  postprocessing->convergencedata_[block_id_][5] = cmglobal_;

  cout << "Ending calculateGlobalCm............................................" << endl;
}

void AerodynamicParameters::checkClDriver()
{
  cout << "Starting checkClDriver..............................................." << endl;

  if(clglobal_ < cldriver_)
  {

  }
  else
  {
    solver->stop_solver_flag_ == true;
  }

  cout << "Ending checkClDriver................................................." << endl;
}

#endif
