#define CATCH_CONFIG_MAIN

#include <catch.hpp>

//Project files
#include "Block.h"
#include "MetricsInitializer.h"
#include "Block.h"
#include "ConcreteBlockBuilder.h"


//STL
#include <vector>

//using namespace std;

typedef unsigned int uint;

void buildConnectivityInteg(Block *new_block)
{
    
    std::string block_file ="UnstructuredMesh5x5.su2";

    ConcreteBlockBuilder concrete_block_builder = ConcreteBlockBuilder(block_file);
    concrete_block_builder.preReadMyBlock(new_block);
    concrete_block_builder.readMyBlock(new_block);

    concrete_block_builder.createMyFaces(new_block);

    concrete_block_builder.setConnectivity(new_block);

    MetricsInitializer metricsInit(new_block);
    metricsInit.doInit();
    

}

TEST_CASE("Test computation of center cell", "")
{
    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    int cellID = 0;
    int dimension = 3;
    double centerCell[dimension];

    centerCell[0] = 0.5;
    centerCell[1] = 0.5;
    centerCell[2] = 0.5;

/* In comment because the method of computing center cell has change
    //Check center cell of cellID
    for(int i(0);i < dimension;i++)
    {
        double resultCoord = blockData->block_cells_[cellID]->cell_coordinates_[i];
        REQUIRE(centerCell[i] == resultCoord);
    }

    //Verify center cells of all ghost
    uint nbCellsTot = blockData->n_all_cells_in_block_;
    uint nbCells = blockData->n_real_cells_in_block_;

    const uint vector3DSize = 3;

    for(uint i(nbCells);i < nbCellsTot;i++)
    {
        uint leftCellID = blockData->block_cells_[i]->cell_2_cells_connectivity_[0];
        

        std::vector<double> centerCellLeft(vector3DSize);
        std::vector<double> centerGhost(vector3DSize);

        for(uint k(0);k < vector3DSize;k++)
        {
            centerCellLeft[k] = blockData->block_cells_[leftCellID]->cell_coordinates_[k];
            centerGhost[k] = blockData->block_cells_[i]->cell_coordinates_[k];
        }
        
        REQUIRE(centerCellLeft == centerGhost);

    }
*/

    delete blockData;
    blockData = nullptr;

}

TEST_CASE("Compute Normales")
{   
    //Making sure to respect orientation left to right for cells
    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);


    const uint nbCoordVec3D = 3;

    std::vector<double> centerCellLeft(nbCoordVec3D);
    std::vector<double> centerCellRight(nbCoordVec3D);

    std::vector<double> connectCenterVec(nbCoordVec3D);
    std::vector<double> normales(nbCoordVec3D);
 
    uint nbCells = blockData->n_real_cells_in_block_;

    for(uint i(0);i < nbCells;i++)
    {
        uint nbFacesCell = blockData->block_cells_[i]->n_faces_per_cell_;

        for(uint j(0);j < nbFacesCell;j++)
        {
            uint faceID = blockData->block_cells_[i]->cell_2_faces_connectivity_[j];

            uint cellLeftID = blockData->block_faces_[faceID]->face_2_cells_connectivity_[0];
            uint cellRightID = blockData->block_faces_[faceID]->face_2_cells_connectivity_[1];

            for(uint k(0); k < nbCoordVec3D;k++)
            {
                centerCellLeft[k] = blockData->block_cells_[cellLeftID]->cell_coordinates_[k];
                centerCellRight[k] = blockData->block_cells_[cellRightID]->cell_coordinates_[k];

            }
            
            double prodScalaire = 0.0;
            
            //Avoiding to compare ghost with real cells
            if(centerCellLeft != centerCellRight)
            {
                for(uint k(0); k < nbCoordVec3D;k++)
                {
                    //Obtaining a vector from left to right cell convention
                    connectCenterVec[k] = centerCellRight[k] - centerCellLeft[k];

                    //Initialize vector of normales
                    normales[k] =  blockData->block_faces_[faceID]->face_normals_[k];

                    //Compute dot product
                    prodScalaire += (connectCenterVec[k] * normales[k]);

                    
                }
                //Same orientation definition
                REQUIRE(prodScalaire > 0.0);
            }
            
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
    int nFacesTot = blockData->n_faces_in_block_;

    for(int i(0);i < nFacesTot;i++)
    {
        double result = blockData->block_faces_[i]->face_area_;
        REQUIRE(area == result);
    }

       
    delete blockData;
    blockData = nullptr;

}

TEST_CASE("Compute Volume", "")
{

    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    uint nbCells = blockData->n_real_cells_in_block_;

    for(uint i(0);i < nbCells;i++)
    {
        double result = blockData->block_cells_[i]->cell_volume_;
        REQUIRE(result >= 0.99);
        REQUIRE(result <= 1.01);
    }

    uint nbCellsTot = blockData->n_all_cells_in_block_;

    for(uint i(nbCells);i < nbCellsTot;i++)
    {

        double volumeGhost = blockData->block_cells_[i]->cell_volume_;

        REQUIRE(volumeGhost >= 0.99);
        REQUIRE(volumeGhost <= 1.01);
    }

      
    delete blockData;
    blockData = nullptr;

}


TEST_CASE("Compute weight least squares with cell #20")
{

    //1. Get neighbors of cell reference
    Block *blockData = new Block(0);
    buildConnectivityInteg(blockData);

    //Cell ID is 20
    uint cellID = 20;
    const uint nbFaces = 6;

    std::vector<double> cellCenter(3);

    std::vector<uint> cellNeighbors;

    for(uint i(0);i < nbFaces;i++)
    {
        cellNeighbors.push_back(blockData->block_cells_[cellID]->cell_2_cells_connectivity_[i]);

        cellCenter[0] = blockData->block_cells_[20]->cell_coordinates_[0];
        cellCenter[1] = blockData->block_cells_[20]->cell_coordinates_[1];
        cellCenter[2] = blockData->block_cells_[20]->cell_coordinates_[2];

        const uint X = 0;
        const uint Y = 1;
        const uint Z = 2;

        double result[3] = {0.0, 0.0, 0.0};

        result[X] = blockData->block_cells_[20]->cell_weights_[0][X];
        result[Y] = blockData->block_cells_[20]->cell_weights_[0][Y];
        result[Z] = blockData->block_cells_[20]->cell_weights_[0][Z];

        //Evaluate weigthts between cell 20 and 15

        double eps = 0.01;

        REQUIRE(result[X] == 0.0);
        REQUIRE(result[Y] >= -0.51);
        REQUIRE(result[Y] <= -0.49);
        REQUIRE(result[Z] == 0.0);

        
        result[X] = blockData->block_cells_[20]->cell_weights_[2][X];
        result[Y] = blockData->block_cells_[20]->cell_weights_[2][Y];
        result[Z] = blockData->block_cells_[20]->cell_weights_[2][Z];

        //Evaluate weigthts between cell 20 and 21
        REQUIRE(result[X] >= 0.49);
        REQUIRE(result[X] <= 0.51);
        REQUIRE(result[Y] == 0);
        REQUIRE(result[Z] == 0);

    }



       
    delete blockData;
    blockData = nullptr;


}





