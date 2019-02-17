#define CATCH_CONFIG_MAIN

#include <catch.hpp>

//Project files
#include "Block.h"


void buildConnectivity(Block *iBlock)
{
    iBlock->n_real_cells_in_block_ = 1;
    iBlock->n_all_cells_in_block_ = 1;
    iBlock->nb_faces_in_block_ = 5;
    iBlock->nb_nodes_in_block_ = 5;

    iBlock->block_cells_ = new Cell[iBlock->n_real_cells_in_block_];
    iBlock->block_faces_ = new Face[iBlock->nb_faces_in_block_];
    iBlock->block_nodes_ = new Node[iBlock->nb_nodes_in_block_];

    iBlock->block_cells_[0].cell_2_cells_connectivity_size_ = 1;
    iBlock->block_cells_[0].cell_2_faces_connectivity_size_ = 5;
    iBlock->block_cells_[0].cell_2_faces_connectivity_size_ = 5;

    //Init Cells block connectivity
    int cell2cells[1] = {0};
    int cell2faces[5] = {0,1,2,3,4};
    int cell2nodes[5] = {0,1,2,3,4};

    iBlock->block_cells_[0].cell_2_cells_connectivity_ = cell2cells;
    iBlock->block_cells_[0].cell_2_faces_connectivity_ = cell2faces;
    iBlock->block_cells_[0].cell_2_nodes_connectivity_ = cell2nodes;

    //Init Faces block connectivity
    for(int i(0);i < iBlock->nb_faces_in_block_;i++)
        iBlock->block_faces_[i].face_2_cells_connectivity_size_ = 1;

    for(int i(0);i < iBlock->nb_faces_in_block_ - 1;i++)
        iBlock->block_faces_[i].face_2_nodes_connectivity_size_ = 3; // Triangles

    iBlock->block_faces_[iBlock->nb_faces_in_block_ - 1].face_2_nodes_connectivity_size_ = 4; //Square

    int face2cells[1] = {0};

    for(int i(0);i < iBlock->nb_faces_in_block_;i++)
        iBlock->block_faces_[0].face_2_cells_connectivity_ = face2cells;

    int face2node_0[3] = {0,1,4};
    int face2node_1[3] = {1,2,4};
    int face2node_2[3] = {2,3,4};
    int face2node_3[3] = {3,0,4};
    int face2node_4[4] = {0,3,2,1};

    iBlock->block_faces_[0].face_2_nodes_connectivity_ = face2node_0;
    iBlock->block_faces_[1].face_2_nodes_connectivity_ = face2node_1;
    iBlock->block_faces_[2].face_2_nodes_connectivity_ = face2node_2;
    iBlock->block_faces_[3].face_2_nodes_connectivity_ = face2node_3;
    iBlock->block_faces_[4].face_2_nodes_connectivity_ = face2node_4;

    int node2cells[1] = {0};

    for(int i(0);i < iBlock->nb_nodes_in_block_;i++)
        iBlock->block_nodes_[i].node_2_cells_connectivity_ = node2cells;

    iBlock->block_nodes_[0].node_coordinates_[0] = 1.0;
    iBlock->block_nodes_[0].node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[0].node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[1].node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[1].node_coordinates_[1] = 1.0;
    iBlock->block_nodes_[1].node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[2].node_coordinates_[0] = -1.0;
    iBlock->block_nodes_[2].node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[2].node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[3].node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[3].node_coordinates_[1] = -1.0;
    iBlock->block_nodes_[3].node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[4].node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[4].node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[4].node_coordinates_[2] = 2.0;

    for(int i(0);i < iBlock->nb_faces_in_block_;i++)
    {
        
    }


}

void tearDown(Block *iBlock)
{
    delete [] iBlock->block_cells_;
    delete [] iBlock->block_faces_;
    delete [] iBlock->block_nodes_;
}

TEST_CASE( "TestComputeCenterCells", "Prove that center cells are well defined" )
{
    
    int blockId = 0;
    Block *blockData = new Block(blockId);

    buildConnectivity(blockData);

    MetricsInitializer *metricsInit = new MetricsInitializer(blockData);
    metricsInit->doInit();

    double centerCoord[3] = {0.0,0.3,0.4};

    REQUIRE(centerCoord == blockData->block_cells_[0].cell_coordinates_);

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;
}
