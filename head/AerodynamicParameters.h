#ifndef EULER3D_HEAD_AERODYNAMICPARAMETERS_H
#define EULER3D_HEAD_AERODYNAMICPARAMETERS_H

#include <string>
#include <vector>


#include "Block.h"
#include "Solver.h"

class AerodynamicParameters
{

public:

  AerodynamicParameters(Block* block, double mach_aircraft, double gamma);
  ~AerodynamicParameters();

void computeAerodynamic(Block* block, Solver* solver, int iter, int iteration_interval_, double cmac, double mach_aircraft, double aoa, double gamma);

double getCoefficients(int i);
double getCp(int i);
double getMach(int i);

private:

// Attributes
// NON int block_id_;
// NON int wall_face_id_;

double dynhead_;
double mach_aircraft_;

double gamma_;

double cl_;
double cd_;
double cmx_;
double cmy_;
double cmz_;
double clglobal_;
double cdglobal_;
// NON double pp_;
// NON double ro_;
// NON double uu_;
// NON double vv_;
// NON double ww_;
// NON double nx_;
// NON double ny_;
// NON double nz_;
double force_;
double fx_;
double fy_;
double fz_;
// NON double area_;

// NON double* coefficients_;
double* cp_;
double* mach_;

  // Methods
double calculateCl();
double calculateCd();
double calculateCmx();
double calculateCmy();
double calculateCmz();

void calculateForce(double cpbc);
void calculateMach(Block* block);
void calculateCp(Block* block);
void calculateGlobalCl(double aoa);
void calculateGlobalCd(double aoa);
void checkClDriver();

};

#endif
