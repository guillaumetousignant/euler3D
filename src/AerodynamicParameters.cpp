#ifndef EULER3D_SRC_AERODYNAMICPARAMETERS_DAVE_CPP
#define EULER3D_SRC_AERODYNAMICPARAMETERS_DAVE_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "AerodynamicParameters.h"

using namespace std;

AerodynamicParameters::AerodynamicParameters(Block* block)
{
  cout << "Initialize AerodynamicParameters....................................." << endl;

  #if 0
  mach_ = new double[block->n_cells_in_block_];
  cp_ = new double[block->n_cells_in_block_];
  coefficients_ = new double[5];
  #endif

  cout << "Initialize AerodynamicParameters.................................DONE" << endl;
}

AerodynamicParameters::~AerodynamicParameters()
{
  if(coefficients_ != 0)
  {
    delete [] coefficients_;
  }

  if(cp_ != 0)
  {
    delete [] coefficients_;
  }

  if(mach_ != 0)
  {
    delete [] mach_;
  }
}

void AerodynamicParameters::calculateMach(Block* block, double gamma)
{
  int i;
  double a,velocity;

  cout << "Starting calculateMach..............................................." << endl;

  #if 0
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
    mach_[i] = velocity/a;
  }
  #endif

  cout << "Ending calculateMach................................................." << endl;
}

void AerodynamicParameters::calculateCp(int i)
{
  cout << "Starting calculateCp................................................." << endl;

  #if 0

    // Save wall pressure coefficient in cp_ array
    cp_[i] = (ppbc-1.)/dynhead;

  #endif

  cout << "Ending calculateCp..................................................." << endl;
}

void AerodynamicParameters::calculateForce(double ppbc)
{
  cout << "Starting calculateForce.............................................." << endl;

  #if 0
  force_ = (ppbc-1.)/dynhead*area_;
  fx_ = -force_*nx_;
  fy_ = -force_*ny_;
  fz_ = -force_*nz_;
  #endif

  cout << "Ending calculateForce................................................" << endl;
}

double AerodynamicParameters::calculateCl()
{
  cout << "Starting calculateCl................................................." << endl;

  #if 0
  // Sum of lift coefficients
  cl_ += fy_;

  return cl_;
  #endif

  cout << "Ending calculateCl..................................................." << endl;
}

double AerodynamicParameters::calculateCd()
{
  cout << "Starting calculateCd................................................." << endl;

  #if 0
  // Sum of drag coefficients
  cd_ += fx_;

  return cd_;
  #endif

  cout << "Ending calculateCd..................................................." << endl;
}

void AerodynamicParameters::calculateCmx()
{
  cout << "Starting calculateCmx................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to x axis
  cmx_ += face_y_coordinate_*fz_ - face_z_coordinate_*fy_;

  // Save cmx_ in array
  coefficients_[2] = cmx_;
  #endif

  cout << "Ending calculateCmx.................................................." << endl;
}

void AerodynamicParameters::calculateCmy()
{
  cout << "Starting calculateCmy................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to y axis
  cmy_ += face_z_coordinate_*fx_ - face_x_coordinate_*fz_;

  // Save cmy_ in array
  coefficients_[3] = cmy_;
  #endif

  cout << "Ending calculateCmy.................................................." << endl;
}

void AerodynamicParameters::calculateCmz()
{
  cout << "Starting calculateCmz................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to z axis
  cmz_ += face_x_coordinate_*fy_ - face_y_coordinate_*fx_;

  // Save clglobal_ in array
  coefficients_[4] = cmz_;
  #endif

  cout << "Ending calculateCmz.................................................." << endl;
}

void AerodynamicParameters::calculateGlobalCl(double aoa)
{
  cout << "Starting calculateGlobalCl..........................................." << endl;

  #if 0
  // Calculate clwind
  clglobal_ = cl_*cos(aoa) - cd*sin(aoa);

  // Save clglobal_ in array
  coefficients_[0] = clglobal_;
  #endif

  cout << "Ending calculateGlobalCl............................................." << endl;
}

void AerodynamicParameters::calculateGlobalCd(double aoa)
{
  cout << "Starting calculateGlobalCd..........................................." << endl;

  #if 0
  cdglobal_ = cl_*sin(aoa) + cd*cos(aoa);

  // Save cdglobal_ in array
  coefficients_[1] = cdglobal_;
  #endif

  cout << "Ending calculateGlobalCd............................................" << endl;

}

void AerodynamicParameters::checkClDriver()
{
  cout << "Starting checkClDriver..............................................." << endl;

  #if 0
  if(clglobal_ < cldriver_)
  {

  }
  else
  {
    solver->stop_solver_flag_ == true;
  }
  #endif

  cout << "Ending checkClDriver................................................." << endl;
}

void AerodynamicParameters::computeAerodynamic(Block* block, Solver* solver, int iter, int iteration_interval_, double cmac, double mach_aircraft, double aoa, double gamma)
{
    int i, j, cell_0, cell_1;
    double pp0, pp1, ppbc, cpbc;

    #if 0
    // Global value
    block_id_ = block-> block_id_;
    dynhead = 0.5*gamma*mach_aircraft*mach_aircraft;
    #endif

    // Initialize forces
    force_ = 0.;
    fx_ = 0.;
    fy_ = 0.;
    fz_ = 0.;

    // Initialize aerodynamic coefficients
    cl_ = 0.;
    cd_ = 0.;
    cmx_ = 0.;
    cmy_ = 0.;
    cmz_ = 0.;

    for(i=0; i < block->nb_face_in_wall_; i++)
    {
      #if 0
      // Find wall face id
      wall_face_id_ = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell_0 = block->block_faces_[wall_face_id_]->face_2_cells_connectivity_[0];
      cell_1 = block->block_faces_[wall_face_id_]->face_2_cells_connectivity_[1];

      // Face coordinates
      Face_x_coordinate_ = block->block_faces_[wall_face_id_]->face_center_[0];
      Face_y_coordinate_ = block->block_faces_[wall_face_id_]->face_center_[1];
      Face_z_coordinate_ = block->block_faces_[wall_face_id_]->face_center_[2];

      // Pressure value from cell 0 and 1
      pp0 = block->block_primitive_variables_->pp_[cell_0];
      pp1 = block->block_primitive_variables_->pp_[cell_1];

      // Mean pressure value
      ppbc = 0.5*(pp0 + pp1);

      // Face normals
      nx_ = block->block_faces_[wall_face_id_]->face_normals_[0];
      ny_ = block->block_faces_[wall_face_id_]->face_normals_[1];
      nz_ = block->block_faces_[wall_face_id_]->face_normals_[2];

      // Face aera
      area_ = block->block_faces_[wall_face_id_]->face_area_;
      #endif

      // Calculate force and force components for each wall cell
      calculateForce(ppbc);

      // Calculate Cl, Cd and Cm for the block
      calculateCl();
      calculateCd();
      calculateCmx();
      calculateCmy();
      calculateCmz();

    #if 0
    cl_ = cl_/(dynhead*cmac);
    cd_ = cd_/(dynhead*cmac);
    #endif

    calculateGlobalCl(aoa);
    calculateGlobalCd(aoa);

    if(solver->stop_solver_flag_ == true)
    {
      // Calculate Mach numbers for each cell
      calculateMach(block, gamma);

      // Calculate pressure coefficient for each cell
      calculateCp(i);
    }

  }
      checkClDriver();
}

double AerodynamicParameters::getCoefficients(int i)
{
  return coefficients_[i];
}

double AerodynamicParameters::getCp(int i)
{
  return cp_[i];
}

double AerodynamicParameters::getMach(int i)
{
  return mach_[i];
}

#endif
