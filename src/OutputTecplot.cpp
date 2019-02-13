#ifdef EULER3D_SRC_OUTTECPLOT_CPP
#define EULER3D_SRC_OUTTECPLOT_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "OutputTecplot.h"

using namespace std;

OutputTecplot::OutputTecplot(Block* block, PostProcessing* postprocessing, Solver* solver, int iter_, int iteration_interval_)
{
  if(iter_ == iteration_interval_)
  {
    printConvergence();
  }
  else if(solver->stop_solver_flag_ == true)
  {
    printConvergence();
    Convergence.close();

    printFlowData();
    printSurfaceFlowData();
    printAerodynamicCoefficients();
    printRestartFile();
  }

}

OutputTecplot::~OutputTecplot()
{

}

void OutputTecplot::printFlowData(Block* block, PostProcessing* postprocessing)
{
  int i;

  FlowData.open("FlowData.plt", ios::binary);

    if (FlowData.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file FlowData.plt" << endl;
      //return;
    }

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
    cp_ = postprocessing->cp_[i];

    FlowData << cp_ << endl;
  }

  // Print Mach number for each cell
  for(i=0; i < block->n_cells_in_block_; i++)
  {
    mach_ = postprocessing->mach_[i];

    FlowData << mach_ << endl;
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

  FlowData.close();

}

void OutputTecplot::printSurfaceFlowData(Block* block, PostProcessing* postprocessing)
{
  SurfaceFlowData.open("SurfaceFlowData.plt", ios::binary);

    if (SurfaceFlowData.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file SurfaceFlowData.plt" << endl;
      //return;
    }

  SurfaceFlowData.close();
}

void OutputTecplot::printConvergence(Block* block, PostProcessing* postprocessing)
{
  Convergence.open("Convergence.plt", ios::binary);

    if (Convergence.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file Convergence.plt" << endl;
      //return;
    }
}

void OutputTecplot::printAerodynamicCoefficients(Block* block, PostProcessing* postprocessing)
{
  AerodynamicCoefficients.open("AerodynamicCoefficients.plt", ios::binary);

    if (AerodynamicCoefficients.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file AerodynamicCoefficients.plt" << endl;
      //return;
    }
}

void OutputTecplot::RestartFile(Block* block, PostProcessing* postprocessing)
{
  RestartFile.open("RestartFile.dat");

    if (RestartFile.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file RestartFile.dat" << endl;
      //return;
    }

    RestartFile.close();
}

#endif
