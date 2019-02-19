#ifndef EULER3D_SRC_OUTTECPLOT_CPP
#define EULER3D_SRC_OUTTECPLOT_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "OutputTecplot.h"

using namespace std;

OutputTecplot::OutputTecplot()
{
  cout << "Initialize OutTecplot................................................" << endl;

  cout << "Initialize OutTecplot............................................DONE" << endl;
}

OutputTecplot::~OutputTecplot()
{

}

void OutputTecplot::printFlowData(Block* block)
{
  int i;

  cout << "Starting printFlowData..............................................." << endl;

  //FlowData.open("FlowData.plt", ios::binary);
  FlowData.open("FlowData.dat");

    if (FlowData.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file FlowData.plt" << endl;
      //return;
    }

  #if 0
  FlowData << "TTILE = \"Vizualisation of the volumetric solution\""
  FlowData << "VARIABLES=\"X\",\"Y\",\"Z\",\"RO\",\"UU\",\"VV\",\"WW\",\"PP\",\"CP\",\"MACH\"" << endl;
  FlowData << "ZONE T=\"FLOW_FIELD\"" << endl;
  FlowData << "Nodes=" << block->n_nodes_in_block_ << ", " << "Elements=" << block->n_cells_in_block_ << ", " << "ZONETYPE=FEPOLYHEDRAL" << endl;
  FlowData << "DATAPACKING=BLOCK" << endl;
  FlowData << "VARLOCATION=([4,5,6,7,8,9,10]=CELLCENTERED)" << endl;

  // Print X coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    x_ = block->block_nodes_[i]->node_coordinates_[0];

    FlowData << x_ << endl;
  }

  // Print Y coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    y_ = block->block_nodes_[i]->node_coordinates_[1];

    FlowData << y_ << endl;
  }

  // Print Z coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    z_ = block->block_nodes_[i]->node_coordinates_[2];

    FlowData << z_ << endl;
  }

  // Print density for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    ro_ = block->block_primitive_variables_[i]->ro_[i];

    FlowData << ro_ << endl;
  }

  // Print UU velocity for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    uu_ = block->block_primitive_variables_[i]->uu_[i];

    FlowData << uu_ << endl;
  }

  // Print VV velocity for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    vv_ = block->block_primitive_variables_[i]->vv_[i];

    FlowData << vv_ << endl;
  }

  // Print WW velocity for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    ww_ = block->block_primitive_variables_[i]->ww_[i];

    FlowData << ww_ << endl;
  }

  // Print pressure for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    pp_ = block->block_primitive_variables_[i]->pp_[i];

    FlowData << pp_ << endl;
  }

  // Print pressure coefficient for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    FlowData << cp_[i] << endl;
  }

  // Print Mach number for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    FlowData << mach_[i] << endl;
  }

  for(i=0;i < block->n_cells_in_block_; i++)
  {
    switch(block->block_cells_[i]->cell_type_)
    {
      // Quadrilateral cell
      case 9:

        FlowData << block->block_cells_[i]->cell_2_nodes_connectivity_[0]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[1]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[2]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[3]+1 << endl;

      break;

      // Tetrahedral cell
      case 10:

        FlowData << block->block_cells_[i]->cell_2_nodes_connectivity_[0]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[1]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[2]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[3]+1 << endl;

      break;

      // Hexahedral cell
      case 12:

      break;

      // Prism cell
      case 13:

      break;

      // Pyramid cell
      case 14:

      break;
    }
  }
  #endif
  FlowData.close();

  cout << "Ending printFlowData..............................................." << endl;

}

void OutputTecplot::printSurfaceFlowData(Block* block)
{
  cout << "Starting printSurfaceFlowData........................................" << endl;

  //SurfaceFlowData.open("SurfaceFlowData.plt", ios::binary);
  SurfaceFlowData.open("SurfaceFlowData.dat");

    if (SurfaceFlowData.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file SurfaceFlowData.plt" << endl;
      //return;
    }

  SurfaceFlowData.close();

  cout << "Ending printSurfaceFlowData.........................................." << endl;
}

void OutputTecplot::printConvergence(Solver* solver, int iter)
{
  cout << "Starting printConvergence............................................" << endl;

  int i;
  double Cl, Cd, Cmx, Cmy, Cmz, ro_convergence, uu_convergence, vv_convergence, ww_convergence, pp_convergence;

  //Convergence.open("Convergence.plt", ios::binary);
  Convergence.open("Convergence.dat");

    if (Convergence.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file Convergence.plt" << endl;
      //return;
    }
  #if 0
  Cl = data_[0];
  Cd = data_[1];
  Cmx = data_[2];
  Cmy = data_[3];
  Cmz = data_[4];

  ro_convergence = data_[5];
  uu_convergence = data_[6];
  vv_convergence = data_[7];
  ww_convergence = data_[8];
  pp_convergence = data_[9];

  Convergence << "Iteration" << " " << "Cl" << " " << "Cd" << " " << "Cmx" << " " << "Cmy" << " " << "Cmz" << " " << "Density convergence" << " " << "Uu convergence" << " " << "Vv convergence" << " " << "Ww convergence" << " " << "DPressure convergence" << " " << endl;

  Convergence << iter << " " << Cl << " " << Cd << " " << Cmx << " " << Cmy << " " << Cmz << " " << ro_convergence << " " << uu_convergence << " " << vv_convergence << " " << ww_convergence << " " << pp_convergence << endl;

  if(solver->stop_solver_flag_==True)
  {
    Convergence.close();
  }
  #endif
  cout << "Ending printConvergence.............................................." << endl;
}

void OutputTecplot::printAerodynamicCoefficients(Block* block)
{
  cout << "Starting printAerodynamicCoefficients................................" << endl;

  //AerodynamicCoefficients.open("AerodynamicCoefficients.plt", ios::binary);
  AerodynamicCoefficients.open("AerodynamicCoefficients.dat");

    if (AerodynamicCoefficients.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file AerodynamicCoefficients.plt" << endl;
      //return;
    }
  #if 0
  Cl = data_[0];
  Cd = data_[1];
  Cmx = data_[2];
  Cmy = data_[3];
  Cmz = data_[4];

  AerodynamicCoefficients << "Angle of attack" << " " << "Cl" << " " << "Cd" << " " << "Cmx" << " " << "Cmy" << " " << "Cmz" << endl;

  AerodynamicCoefficients << aoa_deg << " " << Cl << " " << Cd << " " << Cmx << " " << Cmy << " " << Cmz << endl;

  if()
  {
    AerodynamicCoefficients.close();
  }
  #endif
  cout << "Ending printAerodynamicCoefficients.................................." << endl;
}

void OutputTecplot::printRestartFile(Block* block)
{
  cout << "Starting printRestartFile............................................" << endl;

  RestartFile.open("RestartFile.dat");

    if (RestartFile.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file RestartFile.dat" << endl;
      //return;
    }

    RestartFile.close();

  cout << "Ending printRestartFile.............................................." << endl;
}

void OutputTecplot::printData(Block* block, Solver* solver, int iter, int iteration_interval_, double aoa, double* data, double* cp, double* mach)
{
  cout << "Starting printData..................................................." << endl;
#if 0
  cp_ = cp;
  data_ = data;
  mach_ = mach;
#endif

  if(solver->stop_solver_flag_ == true)
  {
    aoa_deg_ = aoa*180/3.1416;

    printConvergence(solver, iter);
    printFlowData(block);
    printSurfaceFlowData(block);
    printAerodynamicCoefficients(block);
    printRestartFile(block);
  }
  else if(iter == iteration_interval_)
  {
    printConvergence(solver, iter);
  }

  cout << "Ending printData....................................................." << endl;

}

#endif
