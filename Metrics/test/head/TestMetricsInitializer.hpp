#define CATCH_CONFIG_MAIN

#include <catch.hpp>

//Project files
#include "Block.h"
#include "MetricsInitializer.h"

using namespace std;


void buildConnectivity(Block *iBlock)
{   
    uint nbCells = 1;
    uint nbCellsTot = 6;
    uint nbFacesTot = 5;
    uint nbNodesTot = 5;

    iBlock->n_real_cells_in_block_ = nbCells;
    iBlock->n_all_cells_in_block_ = nbCellsTot;
    iBlock->n_faces_in_block_ = nbFacesTot;
    iBlock->n_nodes_in_block_ = nbNodesTot;

    iBlock->block_cells_ = new Cell*[nbCellsTot];
    iBlock->block_faces_ = new Face*[nbFacesTot];
    iBlock->block_nodes_ = new Node*[nbNodesTot];

    for(uint i(0);i < nbCellsTot;i++)
    {
        iBlock->block_cells_[i] = new Cell;
    }

    for(uint i(0);i < nbFacesTot;i++)
    {
        iBlock->block_faces_[i] = new Face;
    }

    for(uint i(0);i < nbNodesTot;i++)
    {
        iBlock->block_nodes_[i] = new Node;
    }



    iBlock->block_cells_[0]->n_faces_per_cell_ = nbFacesTot;
    iBlock->block_cells_[0]->n_nodes_per_cell_ = nbNodesTot;

    //Init nb of faces for each ghots cells
    for(uint i(1);i < nbCellsTot;i++)
    {
        iBlock->block_cells_[i]->n_faces_per_cell_ = 1;
    }

    //Init Cell block connectivity internal
    uint cell2cell_size = 1;
    iBlock->block_cells_[0]->cell_2_cells_connectivity_ = new int[cell2cell_size];
    iBlock->block_cells_[0]->cell_2_cells_connectivity_[0] = 0;

    iBlock->block_cells_[0]->cell_2_faces_connectivity_ = new int[nbFacesTot];
    iBlock->block_cells_[0]->cell_2_faces_connectivity_[0] = 0;
    iBlock->block_cells_[0]->cell_2_faces_connectivity_[1] = 1;
    iBlock->block_cells_[0]->cell_2_faces_connectivity_[2] = 2;
    iBlock->block_cells_[0]->cell_2_faces_connectivity_[3] = 3;
    iBlock->block_cells_[0]->cell_2_faces_connectivity_[4] = 4;

    iBlock->block_cells_[0]->cell_2_nodes_connectivity_ = new int[nbNodesTot];
    iBlock->block_cells_[0]->cell_2_nodes_connectivity_[0] = 0;
    iBlock->block_cells_[0]->cell_2_nodes_connectivity_[1] = 1;
    iBlock->block_cells_[0]->cell_2_nodes_connectivity_[2] = 2;
    iBlock->block_cells_[0]->cell_2_nodes_connectivity_[3] = 3;
    iBlock->block_cells_[0]->cell_2_nodes_connectivity_[4] = 4;

    //Init ghost connectivity
    uint nbCell2CellGhost = 1;
    uint nbFacesPerGhost = 1;

    for(uint i(1);i < nbCellsTot;i++)
    {
        iBlock->block_cells_[i]->cell_2_cells_connectivity_ = new int[nbCell2CellGhost];
        iBlock->block_cells_[i]->cell_2_cells_connectivity_[0] = 0;

        iBlock->block_cells_[i]->cell_2_faces_connectivity_ = new int[nbFacesPerGhost];
        iBlock->block_cells_[i]->cell_2_faces_connectivity_[0] = (i - 1);
    }

    //Setting nb of nodes for all faces

    const uint nbNodesTriangle = 3;
    const uint nbNodesSquare = 4;

    for(uint i(0);i < nbFacesTot - 1;i++)
        iBlock->block_faces_[i]->n_nodes_per_face_ = nbNodesTriangle; // Triangles

    iBlock->block_faces_[nbFacesTot - 1]->n_nodes_per_face_ = nbNodesSquare; //Square

    int face2cells_[nbFacesTot][2];
    face2cells_[0][0] = 0;
    face2cells_[0][1] = 1;

    face2cells_[1][0] = 0;
    face2cells_[1][1] = 2;

    face2cells_[2][0] = 0;
    face2cells_[2][1] = 3;

    face2cells_[3][0] = 0;
    face2cells_[3][1] = 4;
    
    face2cells_[4][0] = 0;
    face2cells_[4][1] = 5;

    for(uint i(0);i < nbFacesTot;i++)
    {
        iBlock->block_faces_[i]->face_2_cells_connectivity_ = new int[2];

        for(int j(0);j < 2;j++)
        {
            int value = face2cells_[i][j];
            iBlock->block_faces_[i]->face_2_cells_connectivity_[j] = value;
        }
    }
    
    //First face
    iBlock->block_faces_[0]->face_2_nodes_connectivity_ = new int[nbNodesTriangle];

    iBlock->block_faces_[0]->face_2_nodes_connectivity_[0] = 0;
    iBlock->block_faces_[0]->face_2_nodes_connectivity_[1] = 1;
    iBlock->block_faces_[0]->face_2_nodes_connectivity_[2] = 4;

    //Second face
    iBlock->block_faces_[1]->face_2_nodes_connectivity_ = new int[nbNodesTriangle];

    iBlock->block_faces_[1]->face_2_nodes_connectivity_[0] = 1;
    iBlock->block_faces_[1]->face_2_nodes_connectivity_[1] = 2;
    iBlock->block_faces_[1]->face_2_nodes_connectivity_[2] = 4;

    //Third face
    iBlock->block_faces_[2]->face_2_nodes_connectivity_ = new int[nbNodesTriangle];

    iBlock->block_faces_[2]->face_2_nodes_connectivity_[0] = 2;
    iBlock->block_faces_[2]->face_2_nodes_connectivity_[1] = 3;
    iBlock->block_faces_[2]->face_2_nodes_connectivity_[2] = 4;

    //Fourth face
    iBlock->block_faces_[3]->face_2_nodes_connectivity_ = new int[nbNodesTriangle];

    iBlock->block_faces_[3]->face_2_nodes_connectivity_[0] = 3;
    iBlock->block_faces_[3]->face_2_nodes_connectivity_[1] = 0;
    iBlock->block_faces_[3]->face_2_nodes_connectivity_[2] = 4;

    //Fifth face
    iBlock->block_faces_[4]->face_2_nodes_connectivity_ = new int[nbNodesSquare];

    iBlock->block_faces_[4]->face_2_nodes_connectivity_[0] = 0;
    iBlock->block_faces_[4]->face_2_nodes_connectivity_[1] = 3;
    iBlock->block_faces_[4]->face_2_nodes_connectivity_[2] = 2;
    iBlock->block_faces_[4]->face_2_nodes_connectivity_[3] = 1;
    
    
    int node2cells[1] = {0};

    for(int i(0);i < iBlock->n_nodes_in_block_;i++)
        iBlock->block_nodes_[i]->node_2_cells_connectivity_ = node2cells;

    iBlock->block_nodes_[0]->node_coordinates_[0] = 1.0;
    iBlock->block_nodes_[0]->node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[0]->node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[1]->node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[1]->node_coordinates_[1] = 1.0;
    iBlock->block_nodes_[1]->node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[2]->node_coordinates_[0] = -1.0;
    iBlock->block_nodes_[2]->node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[2]->node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[3]->node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[3]->node_coordinates_[1] = -1.0;
    iBlock->block_nodes_[3]->node_coordinates_[2] = 0.0;

    iBlock->block_nodes_[4]->node_coordinates_[0] = 0.0;
    iBlock->block_nodes_[4]->node_coordinates_[1] = 0.0;
    iBlock->block_nodes_[4]->node_coordinates_[2] = 2.0;

}

void tearDown(Block *iBlock)
{
 
    uint nbCellsTot = 6;
    uint nbFacesTot = 5;

    for(uint i(0);i < nbCellsTot;i++)
    { 
        delete [] iBlock->block_cells_[i]->cell_2_cells_connectivity_;
        delete [] iBlock->block_cells_[i]->cell_2_faces_connectivity_;
        
    }

    delete [] iBlock->block_cells_[0]->cell_2_nodes_connectivity_;

    for(uint i(0);i < nbFacesTot;i++)
    {
        delete [] iBlock->block_faces_[i]->face_2_cells_connectivity_;
        delete [] iBlock->block_faces_[i]->face_2_nodes_connectivity_;
    }


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

    double centerCoord[3] = {0.0,0.0,0.4};
    double resCenterCoord[3] = {0.0, 0.0, 0.0};

    //Test for internal cell and ghost cells
    for(int i(0);i < blockData->n_all_cells_in_block_;i++)
    {
        resCenterCoord[0] = blockData->block_cells_[i]->cell_coordinates_[0];
        resCenterCoord[1] = blockData->block_cells_[i]->cell_coordinates_[1];
        resCenterCoord[2] = blockData->block_cells_[i]->cell_coordinates_[2];

        REQUIRE(centerCoord[0] == resCenterCoord[0]);
        REQUIRE(centerCoord[1] == resCenterCoord[1]);
        REQUIRE(centerCoord[2] == resCenterCoord[2]);
    }
    

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;
}


TEST_CASE("TestComputeCenterFaces", "Prove that center of faces are correct")
{
    int blockId = 0;
    Block *blockData = new Block(blockId);

    buildConnectivity(blockData);

    MetricsInitializer *metricsInit = new MetricsInitializer(blockData);
    metricsInit->doInit();

    int const nbNodesTriangle = 3;
    int const nbNodesRect = 4;

    double centerFace1[nbNodesTriangle];
    double centerFace2[nbNodesTriangle];
    double centerFace3[nbNodesTriangle];
    double centerFace4[nbNodesTriangle];
    double centerFace5[nbNodesRect];

    double epsilon = 0.01;

    centerFace1[0] = 0.33;
    centerFace1[1] = 0.33;
    centerFace1[2] = 0.67;

    for(int i(0);i<nbNodesTriangle;i++)
    {
            REQUIRE(blockData->block_faces_[0]->face_center_[i] <= centerFace1[i] + epsilon);
            REQUIRE(blockData->block_faces_[0]->face_center_[i] >= centerFace1[i] - epsilon);
    }
        
    centerFace2[0] = -0.33;
    centerFace2[1] = 0.33;
    centerFace2[2] = 0.67;

    for(int i(0);i<nbNodesTriangle;i++)
    {
        REQUIRE(blockData->block_faces_[1]->face_center_[i] <= centerFace2[i] + epsilon);
        REQUIRE(blockData->block_faces_[1]->face_center_[i] >= centerFace2[i] - epsilon);
    }

    centerFace3[0] = -0.33;
    centerFace3[1] = -0.33;
    centerFace3[2] = 0.67;

    for(int i(0);i<nbNodesTriangle;i++)
    {
        REQUIRE(blockData->block_faces_[2]->face_center_[i] <= centerFace3[i] + epsilon);
        REQUIRE(blockData->block_faces_[2]->face_center_[i] >= centerFace3[i] - epsilon);
    }

    centerFace4[0] = 0.33;
    centerFace4[1] = -0.33;
    centerFace4[2] = 0.67;

    for(int i(0);i<nbNodesTriangle;i++)
    {
        REQUIRE(blockData->block_faces_[3]->face_center_[i] <= centerFace4[i] + epsilon);
        REQUIRE(blockData->block_faces_[3]->face_center_[i] >= centerFace4[i] - epsilon);
    }

    centerFace5[0] = 0.0;
    centerFace5[1] = 0.0;
    centerFace5[2] = 0.0;
    centerFace5[3] = 0.0;

    for(int i(0);i<nbNodesTriangle;i++)
    {
        REQUIRE(blockData->block_faces_[4]->face_center_[i] <= centerFace5[i] + epsilon);
        REQUIRE(blockData->block_faces_[4]->face_center_[i] >= centerFace5[i] - epsilon);
    }

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;
}


TEST_CASE( "TestComputeNormals", "Prove that normales of each faces are well defined" )
{
    
    int blockId = 0;
    Block *blockData = new Block(blockId);

    buildConnectivity(blockData);

    MetricsInitializer *metricsInit = new MetricsInitializer(blockData);
    metricsInit->doInit();

    int const nbCoordVect = 3;

    double normalFace1[nbCoordVect];
    double normalFace2[nbCoordVect];
    double normalFace3[nbCoordVect];
    double normalFace4[nbCoordVect];
    double normalFace5[nbCoordVect];

    double epsilon = 0.01;

    normalFace1[0] = 1.0;
    normalFace1[1] = 1.0;
    normalFace1[2] = 0.5;

    for(int i(0);i<nbCoordVect;i++)
    {
            REQUIRE(blockData->block_faces_[0]->face_normals_[i] <= normalFace1[i] + epsilon);
            REQUIRE(blockData->block_faces_[0]->face_normals_[i] >= normalFace1[i] - epsilon);
    }
        
    normalFace2[0] = -1.0;
    normalFace2[1] = 1.0;
    normalFace2[2] = 0.5;

    for(int i(0);i<nbCoordVect;i++)
    {
        REQUIRE(blockData->block_faces_[1]->face_normals_[i] <= normalFace2[i] + epsilon);
        REQUIRE(blockData->block_faces_[1]->face_normals_[i] >= normalFace2[i] - epsilon);
    }

    normalFace3[0] = -1.0;
    normalFace3[1] = -1.0;
    normalFace3[2] = 0.5;

    for(int i(0);i<nbCoordVect;i++)
    {
        REQUIRE(blockData->block_faces_[2]->face_normals_[i] <= normalFace3[i] + epsilon);
        REQUIRE(blockData->block_faces_[2]->face_normals_[i] >= normalFace3[i] - epsilon);
    }

    normalFace4[0] = 1.0;
    normalFace4[1] = -1.0;
    normalFace4[2] = 0.5;

    for(int i(0);i<nbCoordVect;i++)
    {
        REQUIRE(blockData->block_faces_[3]->face_normals_[i] <= normalFace4[i] + epsilon);
        REQUIRE(blockData->block_faces_[3]->face_normals_[i] >= normalFace4[i] - epsilon);
    }

    normalFace5[0] = 0.0;
    normalFace5[1] = 0.0;
    normalFace5[2] = 2.0;

    for(int i(0);i<nbCoordVect;i++)
    {
        REQUIRE(blockData->block_faces_[4]->face_normals_[i] <= normalFace5[i] + epsilon);
        REQUIRE(blockData->block_faces_[4]->face_normals_[i] >= normalFace5[i] - epsilon);
    }

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;
}

TEST_CASE("Test ComputeAreaFaces", "Testing if areas are well defined")
{
    int blockId = 0;
    Block *blockData = new Block(blockId);

    buildConnectivity(blockData);

    MetricsInitializer *metricsInit = new MetricsInitializer(blockData);
    metricsInit->doInit();

    int const nbFaces = 5;
    double area[nbFaces];
    
    area[0] = 1.5;
    area[1] = 1.5;
    area[2] = 1.5;
    area[3] = 1.5;
    area[4] = 2;

    for(int i(0);i < nbFaces;i++)
        REQUIRE(blockData->block_faces_[i]->face_area_ == area[i]);

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;

}

TEST_CASE("Test interpolation vector")
{
    int blockId = 0;
    Block *blockData = new Block(blockId);

    buildConnectivity(blockData);

    MetricsInitializer *metricsInit = new MetricsInitializer(blockData);
    metricsInit->doInit();

    double eps = 0.01;

    double vec_interp_left[3];

    vec_interp_left[0] = 0.33;
    vec_interp_left[1] = 0.33;
    vec_interp_left[2] = 0.27;

    double *result_left = blockData->block_faces_[0]->left_cell_r_vector_;

    for(int i(0);i < 3;i++)
    {
        REQUIRE(result_left[i] <= vec_interp_left[i] + eps);
        REQUIRE(result_left[i] >= vec_interp_left[i] - eps);
        
    }
        

    tearDown(blockData);

    delete blockData;
    blockData = nullptr;

    delete metricsInit;
    metricsInit = nullptr;

    result_left = nullptr;

}







