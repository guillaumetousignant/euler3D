#ifndef EULER3D_SRC_AERODYNAMICPARAMETERS_CPP
#define EULER3D_SRC_AERODYNAMICPARAMETERS_CPP

#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

#include "AerodynamicParameters.h"

using namespace std;

AerodynamicParameters::AerodynamicParameters(double cmac, double mach_aircraft, double aoa_deg, double gamma)
{
  cout << "Initialize AerodynamicParameters....................................." << endl;

  #if 0
  gamma_=gamma;
  cmac_=cmac;
  mach_aircraft_=mach_aircraft;
  aoa_rad_=aoa_deg*atan(1)*4/180;

  stop_solver_flag_=false;


  #endif

  cout << "Initialize AerodynamicParameters.................................DONE" << endl;
}

AerodynamicParameters::~AerodynamicParameters()
{

}



void AerodynamicParameters::calculateForce(double cpbc, double area, double nx, double ny, double nz)
{
  cout << "Starting calculateForce.............................................." << endl;

  #if 0
  force_ = cpbc*area;
  fx_ = -force_*nx;
  fy_ = -force_*ny;
  fz_ = -force_*nz;
  #endif

  cout << "Ending calculateForce................................................" << endl;
}

void AerodynamicParameters::calculateCl()
{
  cout << "Starting calculateCl................................................." << endl;

  #if 0
  // Sum of lift coefficients
  cl_ += fy_;

  #endif

  cout << "Ending calculateCl..................................................." << endl;
}

void AerodynamicParameters::calculateCd()
{
  cout << "Starting calculateCd................................................." << endl;

  #if 0
  // Sum of drag coefficients
  cd_ += fx_;

  #endif

  cout << "Ending calculateCd..................................................." << endl;
}

void AerodynamicParameters::calculateCmx(double cell_y_coordinate, double cell_z_coordinate)
{
  cout << "Starting calculateCmx................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to x axis
  cmx_ += cell_y_coordinate*fz_ - cell_z_coordinate*fy_;

  #endif

  cout << "Ending calculateCmx.................................................." << endl;
}

void AerodynamicParameters::calculateCmy(double cell_x_coordinate, double cell_z_coordinate)
{
  cout << "Starting calculateCmy................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to y axis
  cmy_ += cell_z_coordinate*fx_ - cell_x_coordinate*fz_;


  #endif

  cout << "Ending calculateCmy.................................................." << endl;
}

void AerodynamicParameters::calculateCmz(double cell_x_coordinate, double cell_y_coordinate)
{
  cout << "Starting calculateCmz................................................" << endl;

  #if 0
  // Calculate moment coefficient compared to z axis
  cmz_ += cell_x_coordinate*fy_ - cell_y_coordinate*fx_;


  #endif

  cout << "Ending calculateCmz.................................................." << endl;
}

void AerodynamicParameters::calculateGlobalCl()
{
  cout << "Starting calculateGlobalCl..........................................." << endl;

  #if 0
  // Calculate clwind
  cl_global_ = cl_*cos(aoa_rad_) - cd*sin(aoa_rad_);

  #endif

  cout << "Ending calculateGlobalCl............................................." << endl;
}

void AerodynamicParameters::calculateGlobalCd()
{
  cout << "Starting calculateGlobalCd..........................................." << endl;

  #if 0
  cd_global_ = cl_*sin(aoa_rad_) + cd*cos(aoa_rad_);

  #endif

  cout << "Ending calculateGlobalCd............................................" << endl;

}


/* NON
void AerodynamicParameters::checkClDriver()
{
  cout << "Starting checkClDriver..............................................." << endl;


  #if 0
  if(clglobal_ < cldriver_)
  {

  }
  else
  {
    // NON ÇA NE MARCHE PAS COMME ÇA
    stop_solver_flag_ == true;
  }
  #endif

  cout << "Ending checkClDriver................................................." << endl;
}
*/

void AerodynamicParameters::computeAerodynamic(Block* block)
{
  #if 0
  double dyn_head;
  dyn_head = 0.5*gamma_*mach_aircraft_*mach_aircraft_;

  #endif

  int i, j, cell_0, cell_1, wall_face_id;
  double cell_x_coordinate, cell_y_coordinate, cell_z_coordinate;
  double pp0, pp1, ppbc, cpbc;
  double nx, ny, nz, area;

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
    wall_face_id = block->block_wall_face_ids_[i];

    // Find wall cells associate with the wall face i
    cell_0 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
    cell_1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

    // cell_0 coordinates
    cell_x_coordinate = block->block_cells_[cell_0]->cell_coordinates_[0];
    cell_y_coordinate = block->block_cells_[cell_0]->cell_coordinates_[1];
    cell_z_coordinate = block->block_cells_[cell_0]->cell_coordinates_[2];

    // Pressure value from cell 0 and 1
    pp0 = block->block_primitive_variables_->pp_[cell_0];
    pp1 = block->block_primitive_variables_->pp_[cell_1];

    // Mean pressure value
    ppbc = 0.5*(pp0 + pp1);

    // Pressure coefficient for each wall cell
    cpbc = (ppbc-1.)/dyn_head;

    // Face normals
    nx = block->block_faces_[wall_face_id]->face_normals_[0];
    ny = block->block_faces_[wall_face_id]->face_normals_[1];
    nz = block->block_faces_[wall_face_id]->face_normals_[2];

    // Face aera
    area = block->block_faces_[wall_face_id]->face_area_;
    #endif

    cpbc = 1.; // EN ATTENDANT
    area=1.;
    nx=1.;
    ny=1.;
    nz=1.;
    cell_x_coordinate=1.;
    cell_y_coordinate=1.;
    cell_z_coordinate=1.;

    // Calculate force and force components for each wall cell
    calculateForce(cpbc, area, nx, ny, nz);

    // Calculate Cl, Cd and Cm for the block
    calculateCl();
    calculateCd();
    calculateCmx(cell_y_coordinate, cell_z_coordinate);
    calculateCmy(cell_x_coordinate, cell_z_coordinate);
    calculateCmz(cell_x_coordinate, cell_y_coordinate);
  }

  #if 0
  cl_ = cl_/(dyn_head*cmac);
  cd_ = cd_/(dyn_head*cmac);
  #endif

  calculateGlobalCl();
  calculateGlobalCd();

  // NON checkClDriver();

}

#endif
