#ifndef EULER3D_SRC_OUTTECPLOT_CPP
#define EULER3D_SRC_OUTTECPLOT_CPP

#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "OutputTecplot.h"

using namespace std;

OutputTecplot::OutputTecplot(double mach_aircraft, double aoa_deg, double gamma)
{
  cout << "Initialize OutTecplot................................................" << endl;
  mach_aircraft_=mach_aircraft;
  aoa_deg_=aoa_deg;
  gamma_=gamma;
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


  FlowData << "TTILE = \"Vizualisation of the volumetric solution\""<<endl;
  FlowData << "VARIABLES=\"X\",\"Y\",\"Z\",\"RO\",\"UU\",\"VV\",\"WW\",\"PP\",\"CP\",\"MACH\"" << endl;
  FlowData << "ZONE T=\"FLOW_FIELD\"" << endl;
  FlowData << "Nodes=" << block->n_nodes_in_block_ << ", " << "Elements=" << block->n_real_cells_in_block_ << ", " << "ZONETYPE=FEBRICK" << endl;
  FlowData << "DATAPACKING=BLOCK" << endl;
  FlowData << "VARLOCATION=([4,5,6,7,8,9,10]=CELLCENTERED)" << endl;

  double x_node;
  // Print X coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    x_node = block->block_nodes_[i]->node_coordinates_[0];

    FlowData << x_node << endl;
  }

  double y_node;
  // Print Y coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    y_node = block->block_nodes_[i]->node_coordinates_[1];

    FlowData << y_node << endl;
  }

  double z_node;
  // Print Z coordinate for each node
  for(i=0; i < block->n_nodes_in_block_; i++)
  {
    z_node = block->block_nodes_[i]->node_coordinates_[2];

    FlowData << z_node << endl;
  }

  double ro_cell;
  // Print density for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    ro_cell = block->block_primitive_variables_->ro_[i];

    FlowData << ro_cell << endl;
  }

  double uu_cell;
  // Print UU velocity for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    uu_cell = block->block_primitive_variables_->uu_[i];

    FlowData << uu_cell << endl;
  }

  double vv_cell;
  // Print VV velocity for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    vv_cell = block->block_primitive_variables_->vv_[i];

    FlowData << vv_cell << endl;
  }

  double ww_cell;
  // Print WW velocity for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    ww_cell = block->block_primitive_variables_->ww_[i];

    FlowData << ww_cell << endl;
  }

  double pp_cell;
  // Print pressure for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    pp_cell = block->block_primitive_variables_->pp_[i];

    FlowData << pp_cell << endl;
  }


  double dyn_head;
  double cp_cell;
  // Print pressure coefficient for each cell
  dyn_head = 0.5*gamma_*mach_aircraft_*mach_aircraft_;
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    // Pressure value from cell i
    pp_cell = block->block_primitive_variables_->pp_[i];


    // Save pressure coefficient in cp_ array
    cp_cell = (pp_cell-1.)/dyn_head;
    FlowData << cp_cell << endl;
  }

  double a_cell;
  double velocity_cell;
  double mach_cell;
  // Print Mach number for each cell
  for(i=0; i < block->n_real_cells_in_block_; i++)
  {
    // Primitve variables
    pp_cell = block->block_primitive_variables_->pp_[i];
    ro_cell = block->block_primitive_variables_->ro_[i];
    uu_cell = block->block_primitive_variables_->uu_[i];
    vv_cell = block->block_primitive_variables_->vv_[i];
    ww_cell = block->block_primitive_variables_->ww_[i];

    a_cell = pow(gamma_*pp_cell/ro_cell, 0.5);

    // Calculate local velocity for each cell
    velocity_cell = pow(pow(uu_cell,2)+pow(vv_cell,2)+pow(ww_cell,2), 0.5);

    // Claculate local mach number for each cell
    mach_cell = velocity_cell/a_cell;

    FlowData << mach_cell << endl;
  }


  int j;
  for(i=0;i < block->n_real_cells_in_block_; i++)
  {
    for(j=0;j<block->block_cells_[i]->n_nodes_per_cell_;j++)
    {
      FlowData << block->block_cells_[i]->cell_2_nodes_connectivity_[j]+1 << " ";
    }
    FlowData<<endl;
    /*

        FlowData << block->block_cells_[i]->cell_2_nodes_connectivity_[0]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[1]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[2]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[3]+1 << endl;



        FlowData << block->block_cells_[i]->cell_2_nodes_connectivity_[0]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[1]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[2]+1 << " " << block->block_cells_[i]->cell_2_nodes_connectivity_[3]+1 << endl;
    */
  }

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

    SurfaceFlowData << "TTILE = \"Vizualisation of the surface solution\""<<endl;
    SurfaceFlowData << "VARIABLES=\"X\",\"Y\",\"Z\",\"RO\",\"UU\",\"VV\",\"WW\",\"PP\",\"CP\",\"MACH\"" << endl;
    SurfaceFlowData << "ZONE T=\"FLOW_FIELD\"" << endl;
    SurfaceFlowData << "Nodes=" << block->n_wall_faces_*4 << ", " << "Elements=" << block->n_wall_faces_<< ", " << "ZONETYPE=FEQUADRILATERAL" << endl;
    SurfaceFlowData << "DATAPACKING=BLOCK" << endl;
    SurfaceFlowData << "VARLOCATION=([4,5,6,7,8,9,10]=CELLCENTERED)" << endl;

    int i;
    int j;
    int node;
    int wall_face_id;
    double x_node;

    // Print X coordinate for each node
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      for(j=0; j < block->block_faces_[wall_face_id]->n_nodes_per_face_; j++)
      {
        node = block->block_faces_[wall_face_id]->face_2_nodes_connectivity_[j];

        x_node = block->block_nodes_[node]->node_coordinates_[0];

        SurfaceFlowData << x_node << endl;
      }
    }

    double y_node;
    // Print Y coordinate for each node
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      for(j=0; j < block->block_faces_[wall_face_id]->n_nodes_per_face_; j++)
      {
        node = block->block_faces_[wall_face_id]->face_2_nodes_connectivity_[j];

        y_node = block->block_nodes_[node]->node_coordinates_[1];

        SurfaceFlowData << y_node << endl;
      }
    }

    double z_node;
    // Print Z coordinate for each node
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      for(j=0; j <  block->block_faces_[wall_face_id]->n_nodes_per_face_; j++)
      {
        node = block->block_faces_[wall_face_id]->face_2_nodes_connectivity_[j];

        z_node = block->block_nodes_[node]->node_coordinates_[2];

        SurfaceFlowData << z_node << endl;
      }
    }

    int cell;
    int cell1;
    double ro_face;
    // Print density for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      ro_face = (block->block_primitive_variables_->ro_[cell] + block->block_primitive_variables_->ro_[cell1])*0.5;

      SurfaceFlowData << ro_face << endl;
    }

    double uu_face;
    // Print UU velocity for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      uu_face = (block->block_primitive_variables_->uu_[cell] + block->block_primitive_variables_->uu_[cell1])*0.5;

      SurfaceFlowData << uu_face << endl;
    }

    double vv_face;
    // Print VV velocity for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      vv_face = (block->block_primitive_variables_->vv_[cell] + block->block_primitive_variables_->vv_[cell1])*0.5;

      SurfaceFlowData << vv_face << endl;
    }

    double ww_face;
    // Print WW velocity for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      ww_face = (block->block_primitive_variables_->ww_[cell] + block->block_primitive_variables_->ww_[cell1])*0.5;

      SurfaceFlowData << ww_face << endl;
    }

    double pp_face;
    // Print pressure for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      pp_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->pp_[cell1])*0.5;

      SurfaceFlowData << pp_face << endl;
    }


    double dyn_head;
    double cp_face;
    double pp_face1;
    // Print pressure coefficient for each face
    dyn_head = 0.5*gamma_*mach_aircraft_*mach_aircraft_;
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      // Pressure value from cell i
      pp_face = block->block_primitive_variables_->pp_[cell];
      pp_face1 = block->block_primitive_variables_->pp_[cell1];


      // Save pressure coefficient in cp_ array
      cp_face = ((pp_face + pp_face1)*0.5-1.)/dyn_head;
      SurfaceFlowData << cp_face << endl;
    }

    double a_face;
    double velocity_face;
    double mach_face;
    // Print Mach number for each face
    for(i=0; i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      // Find wall cells associate with the wall face i
      cell = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[0];
      cell1 = block->block_faces_[wall_face_id]->face_2_cells_connectivity_[1];

      // Primitve variables
      pp_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->pp_[cell1])*0.5;
      ro_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->ro_[cell1])*0.5;
      uu_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->uu_[cell1])*0.5;
      vv_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->vv_[cell1])*0.5;
      ww_face = (block->block_primitive_variables_->pp_[cell] + block->block_primitive_variables_->ww_[cell1])*0.5;

      a_face = pow(gamma_*pp_face/ro_face, 0.5);

      // Calculate local velocity for each face
      velocity_face = pow(pow(uu_face,2)+pow(vv_face,2)+pow(ww_face,2), 0.5);

      // Claculate local mach number for each cell
      mach_face = velocity_face/a_face;

      SurfaceFlowData << mach_face << endl;
    }

    for(i=0;i < block->n_wall_faces_; i++)
    {
      // Find wall face id
      wall_face_id = block->block_wall_face_ids_[i];

      for(j=0; j < block->block_faces_[wall_face_id]->n_nodes_per_face_; j++)
      {
        node = block->block_faces_[wall_face_id]->face_2_nodes_connectivity_[j];

        if(j == block->block_faces_[wall_face_id]->n_nodes_per_face_ -1)
        {
          SurfaceFlowData << node + 1 << endl;
        }
        else
        {
          SurfaceFlowData << node + 1 << " ";
        }
      }
    }

  SurfaceFlowData.close();

  cout << "Ending printSurfaceFlowData.........................................." << endl;
}

void OutputTecplot::printConvergence(int iter, double cl, double cd, double cmx, double cmy, double cmz, double ro_convergence, double uu_convergence, double vv_convergence, double ww_convergence, double pp_convergence)
{
  //cout << "Starting printConvergence............................................" << endl;

  //Convergence.open("Convergence.plt", ios::binary);
  if(iter == 0)
  {
    Convergence.open("Convergence.dat");
  }
  else
  {
    Convergence.open("Convergence.dat", std::ios_base::app);
  }


    if (Convergence.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file Convergence.plt" << endl;
      //return;
    }

  if (iter==0)
  {
    Convergence << "Iteration" << " " << "Cl" << " " << "Cd" << " " << "Cmx" << " " << "Cmy" << " " << "Cmz" << " " << "Density_Convergence" << " " << "Uu_Convergence" << " " << "Vv_Convergence" << " " << "Ww_Convergence" << " " << "Pressure_Convergence" << " " << endl;
  }

  Convergence << iter << " " << cl << " " << cd << " " << cmx << " " << cmy << " " << cmz << " " << ro_convergence << " " << uu_convergence << " " << vv_convergence << " " << ww_convergence << " " << pp_convergence << endl;

  Convergence.close();

  //cout << "Ending printConvergence.............................................." << endl;
}

void OutputTecplot::printAerodynamicCoefficients(double cl, double cd, double cmx, double cmy, double cmz)
{
  cout << "Starting printAerodynamicCoefficients................................" << endl;

  //AerodynamicCoefficients.open("AerodynamicCoefficients.plt", ios::binary);
  AerodynamicCoefficients.open("AerodynamicCoefficients.dat");

    if (AerodynamicCoefficients.fail())
    {
      // TODO throw exception
      cerr << "Fail opening file AerodynamicCoefficients.dat" << endl;
      //return;
    }



  AerodynamicCoefficients << "Angle of attack" << " " << "Cl" << " " << "Cd" << " " << "Cmx" << " " << "Cmy" << " " << "Cmz" << endl;

  AerodynamicCoefficients << aoa_deg_ << " " << cl << " " << cd << " " << cmx << " " << cmy << " " << cmz << endl;


  AerodynamicCoefficients.close();

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



#endif
