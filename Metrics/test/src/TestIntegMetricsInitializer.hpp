#define CATCH_CONFIG_MAIN

#include <catch.hpp>

//Project files
#include "Block.h"
#include "Metrics/src/MetricsInitializer.h"
#include "Block.h"
#include "ConcreteBlockBuilder.h"


//STL
#include <vector>

using namespace std;



void buildConnectivityInteg(Block *new_block)
{
    
    string block_file ="../UnstructuredMesh5x5.su2";

    ConcreteBlockBuilder concrete_block_builder = ConcreteBlockBuilder(block_file);
    concrete_block_builder.preReadMyBlock(new_block);
    concrete_block_builder.readMyBlock(new_block);

    concrete_block_builder.createMyFaces(new_block);

    concrete_block_builder.setConnectivity(new_block);

    MetricsInitializer metricsInit(new_block);
    metricsInit.doInit();
    

}

TEST_CASE("Test computation of center cell (ID = 0)", "")
{
    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    int cellID = 0;
    int dimension = 3;
    double centerCell[dimension];

    centerCell[0] = 0.5;
    centerCell[1] = 0.5;
    centerCell[2] = 0.5;

    for(int i(0);i < dimension;i++)
    {
        double resultCoord = blockData->block_cells_[cellID]->cell_coordinates_[i];
        REQUIRE(centerCell[i] == resultCoord);
    }


    delete blockData;
    blockData = nullptr;

}

TEST_CASE("Compute Normales (cellID = 0)")
{

    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    const int nbFaceCube = 6;
    const int nbCoordVec3D = 3;

    std::vector<std::vector<double>> vectorPerFace;
    vectorPerFace.resize(nbFaceCube);
    
    for(int i(0);i < vectorPerFace.size();i++)
    {
        vectorPerFace[i].resize(nbCoordVec3D);
    }

    vectorPerFace[0] = {0., 0., -1.};
    vectorPerFace[1] = {1., 0., 0.};
    vectorPerFace[2] = {0., 1., 0.};
    vectorPerFace[3] = {-1., 0., 0.};
    vectorPerFace[4] = {0., -1., 0.};
    vectorPerFace[5] = {0., 0., 1.};

    std::vector<int> faceID;
    
    for(int i(0);i < nbFaceCube;i++)
    {
        faceID.push_back(blockData->block_cells_[0]->cell_2_faces_connectivity_[i]);
    }
    
    for(int i(0);i < nbFaceCube;i++)
    {
        int actualFace = faceID[i];
        
        for(int j(0);j < vectorPerFace[i].size();j++)
        {
            double result = blockData->block_faces_[actualFace]->face_normals_[j] * -1; // Problem of Face2Node here CCW vs CW.
            REQUIRE(vectorPerFace[i][j] == result);
        }
    }

    delete blockData;
    blockData = nullptr;

}

TEST_CASE("Compute areas", "")
{

    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    double area = 1.0;
    int nbFacesCube = 6;
    std::vector<int> faceID;

    for(int i(0);i < nbFacesCube;i++)
    {
        faceID.push_back(blockData->block_cells_[0]->cell_2_faces_connectivity_[i]);
    }

    for(int i(0);i < nbFacesCube;i++)
    {
        int actualFace = faceID[i];

        double result = blockData->block_faces_[actualFace]->face_area_;

        REQUIRE(area == result);

    }

}

TEST_CASE("Compute Volume", "")
{

    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    double volume = 1.0;
    double result = blockData->block_cells_[0]->cell_volume_;

    REQUIRE(volume == result);

}

