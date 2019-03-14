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

typedef unsigned int uint;

void buildConnectivityInteg(Block *new_block)
{
    
    string block_file ="UnstructuredMesh5x5.su2";

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
    //Making sure to respect orientation left to right for cells


    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    uint cellRefID = 0;
    uint cellNeighborID;

    std::vector<double> centerCellNeighbor(3);

    std::vector<double> centerCellRef;
    centerCellRef.push_back(blockData->block_cells_[cellRefID]->cell_coordinates_[0]);
    centerCellRef.push_back(blockData->block_cells_[cellRefID]->cell_coordinates_[1]);
    centerCellRef.push_back(blockData->block_cells_[cellRefID]->cell_coordinates_[2]);

    std::vector<double> connectCenterVec(3);

    uint nbCells = blockData->n_real_cells_in_block_;


    for(uint i(0);i < nbCells;i++)
    {
        uint nbFacesCell = blockData->block_cells_[i]->n_faces_per_cell_;

        for(uint j(0);j < nbFacesCell;j++)
        {
            uint faceID = blockData->block_cells_[i]->cell_2_faces_connectivity_[j];

            uint cellLeftID = blockData->block_faces_[faceID]->face_2_cells_connectivity_[0];
            uint cellRightID = blockData->block_faces_[faceID]->face_2_cells_connectivity_[1];

            

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

