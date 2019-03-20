#ifndef EULER3D_HEAD_AERODYNAMICPARAMETERS_H
#define EULER3D_HEAD_AERODYNAMICPARAMETERS_H

#include <string>
#include <vector>


#include "Block.h"
#include "Solver.h"

class AerodynamicParameters
{

public:

  AerodynamicParameters(double cmac, double mach_aircraft, double aoa_deg, double gamma);
  ~AerodynamicParameters();

void computeAerodynamic(Block* block);



double cmac_;
double mach_aircraft_;
double aoa_rad_;

double gamma_;

double cl_;
double cd_;
double cmx_;
double cmy_;
double cmz_;
double cl_global_;
double cd_global_;

double force_;
double fx_;
double fy_;
double fz_;




  // Methods
void calculateCl();
void calculateCd();

void calculateCmx(double face_y_coordinate, double face_z_coordinate);
void calculateCmy(double face_x_coordinate, double face_z_coordinate);
void calculateCmz(double face_x_coordinate, double face_y_coordinate);
void calculateForce(double cpbc, double area, double nx, double ny, double nz);
void calculateGlobalCl();
void calculateGlobalCd();
// À compléter void checkClDriver();

};

#endif
