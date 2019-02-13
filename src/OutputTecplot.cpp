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

}

void OutputTecplot::printSurfaceFlowData(Block* block, PostProcessing* postprocessing)
{
  FlowData.open("FlowData.plt", ios::binary);

    if (FlowData.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file FlowData.plt" << endl;
      //return;
    }

  FlowData << "TTILE = \"Vizualisation of the surfacic solution\""
  FlowData << "VARIABLES=\"X\",\"Y\",\"Z\",\"RO\",\"UU\",\"VV\",\"WW\",\"PP\",\"CP\",\"MACH\"" << endl;
  FlowData << "ZONE T=\"FLOW_FIELD\"" << endl;
  FlowData << "Nodes=" << block->n_nodes_in_block_ << ", " << "Elements=" << block->n_cells_in_block_ << ", " << "ZONETYPE=FEQUADRILATERAL" << endl;
  FlowData << "DATAPACKING=BLOCK" << endl;
  FlowData << "VARLOCATION=([1,2,3,4,5,6,7,8,9,10]=CELLCENTERED)" << endl;

}

void OutputTecplot::printConvergence(Block* block, PostProcessing* postprocessing)
{

}

void OutputTecplot::printAerodynamicCoefficients(Block* block, PostProcessing* postprocessing)
{

}

void OutputTecplot::RestartFile(Block* block, PostProcessing* postprocessing)
{

}

#endif
