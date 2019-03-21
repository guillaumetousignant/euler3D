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


  gamma_=gamma;
  cmac_=cmac;
  mach_aircraft_=mach_aircraft;
  aoa_rad_=aoa_deg*4.*atan(1.)/180;

  cout << "Initialize AerodynamicParameters.................................DONE" << endl;
}

AerodynamicParameters::~AerodynamicParameters()
{

}



void AerodynamicParameters::calculateForce(double cpbc, double area, double nx, double ny, double nz)
{
  //cout << "Starting calculateForce.............................................." << endl;

  force_ = cpbc;
  fx_ = force_*nx;
  fy_ = force_*ny;
  fz_ = force_*nz;


  //cout << "Ending calculateForce................................................" << endl;
}

void AerodynamicParameters::calculateCl()
{
  //cout << "Starting calculateCl................................................." << endl;


  // Sum of lift coefficients
  cl_ += fy_;



  //cout << "Ending calculateCl..................................................." << endl;
}

void AerodynamicParameters::calculateCd()
{
  //cout << "Starting calculateCd................................................." << endl;


  // Sum of drag coefficients
  cd_ += fx_;



  //cout << "Ending calculateCd..................................................." << endl;
}

void AerodynamicParameters::calculateCmx(double face_y_coordinate, double face_z_coordinate)
{
  //cout << "Starting calculateCmx................................................" << endl;


  // Calculate moment coefficient compared to x axis
  cmx_ += face_y_coordinate*fz_ - face_z_coordinate*fy_;



  //cout << "Ending calculateCmx.................................................." << endl;
}

void AerodynamicParameters::calculateCmy(double face_x_coordinate, double face_z_coordinate)
{
  //cout << "Starting calculateCmy................................................" << endl;


  // Calculate moment coefficient compared to y axis
  cmy_ += face_z_coordinate*fx_ - face_x_coordinate*fz_;




  //cout << "Ending calculateCmy.................................................." << endl;
}

void AerodynamicParameters::calculateCmz(double face_x_coordinate, double face_y_coordinate)
{
  //cout << "Starting calculateCmz................................................" << endl;


  // Calculate moment coefficient compared to z axis
  cmz_ += face_x_coordinate*fy_ - face_y_coordinate*fx_;




  //cout << "Ending calculateCmz.................................................." << endl;
}

void AerodynamicParameters::calculateGlobalCl()
{
  //cout << "Starting calculateGlobalCl..........................................." << endl;


  // Calculate clwind
  cl_global_ = cl_*cos(aoa_rad_) - cd_*sin(aoa_rad_);



  //cout << "Ending calculateGlobalCl............................................." << endl;
}

void AerodynamicParameters::calculateGlobalCd()
{
  //cout << "Starting calculateGlobalCd..........................................." << endl;


  cd_global_ = cl_*sin(aoa_rad_) + cd_*cos(aoa_rad_);



  //cout << "Ending calculateGlobalCd............................................" << endl;

}


/* À IMPLÉMENTER
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

  double dyn_head;
  dyn_head = 0.5*gamma_*mach_aircraft_*mach_aircraft_;


  int i, cell_0, cell_1, wall_face_id;
  double face_x_coordinate, face_y_coordinate, face_z_coordinate;
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


  for(i=0; i < block->n_wall_faces_; i++)
  {

    // Find wall face id
    wall_face_id = block->block_wall_face_ids_[i];

    // Find wall cells associate with the wall face i
    cell_0 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
    cell_1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

    // Wall faces coordinates
    face_x_coordinate = block->block_faces_[wall_face_id]->face_center_[0];
    face_y_coordinate = block->block_faces_[wall_face_id]->face_center_[1];
    face_z_coordinate = block->block_faces_[wall_face_id]->face_center_[2];

    // Pressure value from cell 0 and 1
    pp0 = block->block_primitive_variables_->pp_[cell_0];
    pp1 = block->block_primitive_variables_->pp_[cell_1];

    // Mean pressure value
    ppbc = 0.5*(pp0 + pp1);

    // Pressure coefficient for each wall cell
    cpbc = (ppbc-1.)/(dyn_head*cmac_);

    // Face normals
    // non-normalized
    nx = block->block_faces_[wall_face_id]->face_normals_[0];
    ny = block->block_faces_[wall_face_id]->face_normals_[1];
    nz = block->block_faces_[wall_face_id]->face_normals_[2];

    // Face aera
    area = block->block_faces_[wall_face_id]->face_area_;

    // Calculate force and force components for each wall cell
    calculateForce(cpbc, area, nx, ny, nz);

    // Calculate Cl, Cd and Cm for the block
    calculateCl();
    calculateCd();
    calculateCmx(face_y_coordinate, face_z_coordinate);
    calculateCmy(face_x_coordinate, face_z_coordinate);
    calculateCmz(face_x_coordinate, face_y_coordinate);
  }

  calculateGlobalCl();
  calculateGlobalCd();

  // NON checkClDriver();

}

#endif
