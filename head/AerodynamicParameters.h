#ifndef EULER3D_HEAD_AERODYNAMICPARAMETERS_H
#define EULER3D_HEAD_AERODYNAMICPARAMETERS_H

#include <string>
#include <vector>


#include "Block.h"
#include "Solver.h"

class AerodynamicParameters
{

public:

  AerodynamicParameters(Block* block);
  ~AerodynamicParameters();

void computeAerodynamic(Block* block, Solver* solver, int iter, int iteration_interval_, double cmac, double mach_aircraft, double aoa, double gamma);

double getCoefficients(int i);
double getCp(int i);
double getMach(int i);

private:

// Attributes
int block_id_;
int wall_face_id_;

double dynhead;
double cl_;
double cd_;
double cmx_;
double cmy_;
double cmz_;
double clglobal_;
double cdglobal_;
double pp_;
double ro_;
double uu_;
double vv_;
double ww_;
double nx_;
double ny_;
double nz_;
double force_;
double fx_;
double fy_;
double fz_;
double area_;
double cell_x_coordinate_;
double cell_y_coordinate_;
double cell_z_coordinate_;


double* coefficients_;
double* cp_;
double* mach_;

  // Methods
double calculateCl();
double calculateCd();

void calculateCmx();
void calculateCmy();
void calculateCmz();
void calculateForce(double cpbc);
void calculateMach(Block* block, double gamma);
void calculateCp(Block* block);
void calculateGlobalCl(double aoa);
void calculateGlobalCd(double aoa);
void checkClDriver();

};

#endif
