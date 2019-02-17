/**
 * @file MetricsInitializer.cpp
 * @author your name (Patrick Deschambault)
 * @brief 
 * @version 0.1
 * @date 2019-02-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "MetricsInitializer.h"

using namespace std;

MetricsInitializer::MetricsInitializer(Block *iBlock)
{
    blockData_ = iBlock;
}

MetricsInitializer::~MetricsInitializer()
{
    //Nothing.
}


void MetricsInitializer::doInit()
{

    uint iNCells = blockData_->n_real_cells_in_block_;
    uint iNCellsTot = blockData_->n_all_cells_in_block_;
    uint iNFaces = blockData_->nb_faces_in_block_;

    //uint iNCellsFarf = blockData_->nb_farfields_in_block_;
    //uint iNCellsWall = blockData_->nb_walls_in_block_;
    //uint iNCellsSynchs = blockData_->nb_synchs_in_block_;

    Cell* iCells = blockData_->block_cells_;
    Face* iFaces = blockData_->block_faces_;
    Node* iNodes = blockData_->block_nodes_;
    
    //Cell* iWalls = blockData_->walls_in_block_;
    //Cell* iSynchs = blockData_->synchs_in_block_;
    //Cell* iFarF = blockData_->farfields_in_block_;

    computeCenterCells(iNCells, iNCellsTot, iCells, iNodes);
    
    //computeCenterFaces(iNFaces, iFaces, iNodes);

    //computeNormalFaces(iNFaces, iFaces, iNodes);

    //computeAreaFaces(iNFaces, iFaces);

    //computeVolumeCells(iNCells, iNCellsTot, iCells, iFaces);

    //computeInterpVect(iNCells, iNCellsTot,iNFaces, iCells, iFaces);
    
    //computeWLS();


   iCells = nullptr;
   iFaces = nullptr;
   iNodes = nullptr;
   //iWalls = nullptr;
   //iSynchs = nullptr;
   //iFarF = nullptr;

}


void MetricsInitializer::MetricsInitializer::computeCenterCells(uint iNCells, uint iNCellsTot, Cell* iCells, Node* iNodes)
{
    for(uint i(0);i < iNCells;i++)
    {
        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;

        uint nbCell2Node = iCells[i].cell_2_nodes_connectivity_size_;
        
        for(uint j(0);j < nbCell2Node;j++)
        {
            //1. Get nodes coordinates of current cell
            int nodeID = iCells[i].cell_2_nodes_connectivity_[j];

            //2. Get average of all nodes coordinates
            nodeCoord_x += iNodes[nodeID].node_coordinates_[0];
            nodeCoord_y += iNodes[nodeID].node_coordinates_[1];
            nodeCoord_z += iNodes[nodeID].node_coordinates_[2];

        }

        //3. Output mapping
        iCells[i].cell_coordinates_[0] = nodeCoord_x / nbCell2Node;
        iCells[i].cell_coordinates_[1] = nodeCoord_y / nbCell2Node;
        iCells[i].cell_coordinates_[2] = nodeCoord_z / nbCell2Node;

    }
}
/*
void MetricsInitializer::computeCenterFaces(uint iNFaces, Face* iFaces, Node* iNodes)
{
    
    for(uint i(0);i < iNFaces;i++)
    {

        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;

        uint nbFace2Nodes = iFaces[i].nb_face2nodes_;


        for(uint j(0);j < nbFace2Nodes;j++)
        {
            //1. Get coordinates of nodes on face.
            int nodeID = iFaces[i].face2nodes_[j];

            nodeCoord_x += iNodes[nodeID].x_node_;
            nodeCoord_y += iNodes[nodeID].y_node_;
            nodeCoord_z += iNodes[nodeID].z_node_;
            
        }

        //3. Output Mapping
        iFaces[i].x_face_ = nodeCoord_x / nbFace2Nodes;
        iFaces[i].y_face_ = nodeCoord_y / nbFace2Nodes;
        iFaces[i].z_face_ = nodeCoord_z / nbFace2Nodes;

    }
}

void MetricsInitializer::computeNormalFaces(uint iNFaces, Face* iFaces, Node* iNodes)
{
    for(uint i = 0; i < iNFaces;i++)
    {
        vector<vector<double>> nodeCoord(iFaces[i].nb_face2nodes_);

        for(int j = 0;j < iFaces[i].nb_face2nodes_;j++)
        {
            uint nodeID = iFaces[i].face2nodes_[j];

            double node_x = iNodes[nodeID].x_node_;
            double node_y = iNodes[nodeID].y_node_;
            double node_z = iNodes[nodeID].z_node_;

            nodeCoord[j].push_back(3);

            nodeCoord[j][0] = node_x;
            nodeCoord[j][1] = node_y;
            nodeCoord[j][2] = node_z;

        }

        double s_x = 0.0;
        double s_y = 0.0;
        double s_z = 0.0;

        const uint X = 0;
        const uint Y = 1;
        const uint Z = 2;

        double dxyA, dxyB, dxyC;
        double dyzA, dyzB, dyzC;
        double dzxA, dzxB, dzxC;

        double dxA, dxB;
        double dyA, dyB;
        double dzA, dzB;

        double x1, x2, x3;
        double y1, y2, y3;
        double z1, z2, z3;
        
        double x5,x6,x7,x8;
        double y5,y6,y7,y8;
        double z5,z6,z7,z8;

        if(iFaces[i].nb_face2nodes_ == 3)   
        {
            //Triangular face
            
                x1 = nodeCoord[0][X];
                x2 = nodeCoord[1][X];
                x3 = nodeCoord[2][X];

                y1 = nodeCoord[0][Y];
                y2 = nodeCoord[1][Y];
                y3 = nodeCoord[2][Y];

                z1 = nodeCoord[0][Z];
                z2 = nodeCoord[1][Z];
                z3 = nodeCoord[2][Z];

                dxyA = (x1 - x2)*(y1 + y2);
                dxyB = (x2 - x3)*(y2 + y3);
                dxyC = (x3 - x1)*(y3 + y1);

                dyzA = (y1 - y2)*(z1 + z2);
                dyzB = (y2 - y3)*(z2 + z3);
                dyzC = (y3 - y1)*(z3 + z1);

                dzxA = (z1 - z2)*(x1 + x2);
                dzxB = (z2 - z3)*(x2 + x3);
                dzxC = (z3 - z1)*(x3 + x1);

                s_x = 0.5*(dyzA + dyzB + dyzC);
                s_y = 0.5*(dzxA + dzxB + dzxC);
                s_z = 0.5*(dxyA + dxyB + dxyC);

        }   
        else if(iFaces[i].nb_face2nodes_ == 4)
        {

            //Quadrilateral case
            
                x5 = nodeCoord[0][X];
                x6 = nodeCoord[1][X];
                x7 = nodeCoord[2][X];
                x8 = nodeCoord[3][X];

                y5 = nodeCoord[0][Y];
                y6 = nodeCoord[1][Y];
                y7 = nodeCoord[2][Y];
                y8 = nodeCoord[3][Y];

                z5 = nodeCoord[0][Z];
                z6 = nodeCoord[1][Z];
                z7 = nodeCoord[2][Z];
                z8 = nodeCoord[3][Z];

                dxA = x8 - x6;
                dxB = x7 - x5;
                dyA = y8 - y6;
                dyB = y7 - y5;
                dzA = z8 - z6;
                dzB = z7 - z5;

                s_x = 0.5*(dyA*dzB - dzA*dyB);
                s_y = 0.5*(dzA*dxB - dxA*dzB);
                s_z = 0.5*(dxA*dyB - dyA*dxB);

        }
        else
        {
            s_x = 0.0;
            s_y = 0.0;
            s_z = 0.0; 
        }

        iFaces[i].n_vector_[0] = s_x;
        iFaces[i].n_vector_[1] = s_y;
        iFaces[i].n_vector_[2] = s_z;

    }

}

void MetricsInitializer::computeInterpVect(uint iNCells, uint iNCellsTot, uint iNFaces, Cell* iCells, Face* iFaces)
{
    const uint X = 0;
    const uint Y = 1;
    const uint Z = 2;

    const uint LEFT = 0;
    const uint RIGHT = 1;
    
    for(uint i(0);i < iNFaces;i++)
    {
        //Get center of face
        double centerFace[3];

        centerFace[X] = iFaces[i].x_face_;
        centerFace[Y] = iFaces[i].y_face_;
        centerFace[Z] = iFaces[i].z_face_;

        //Get center coordinates from neighbor's cells
        uint leftCellID = iFaces[i].face2cells_[LEFT];
        uint rightCellID = iFaces[i].face2cells_[RIGHT];

        double centerLeftCell[3];
        double centerRightCell[3];

        centerLeftCell[X] = iCells[leftCellID].x_cell_;
        centerLeftCell[Y] = iCells[leftCellID].y_cell_;
        centerLeftCell[Z] = iCells[leftCellID].z_cell_;

        centerRightCell[X] = iCells[rightCellID].x_cell_;
        centerRightCell[Y] = iCells[rightCellID].y_cell_;
        centerRightCell[Z] = iCells[rightCellID].z_cell_;

        double vecInterpLeft[3];

        vecInterpLeft[X] = centerFace[X] - centerLeftCell[X];
        vecInterpLeft[Y] = centerFace[Y] - centerLeftCell[Y];
        vecInterpLeft[Z] = centerFace[Z] - centerLeftCell[Z];

        double vecInterpRight[3];

        vecInterpRight[X] = centerFace[X] - centerRightCell[X];
        vecInterpRight[Y] = centerFace[Y] - centerRightCell[Y];
        vecInterpRight[Z] = centerFace[Z] - centerRightCell[Z];

        iFaces[i].r_vector_left_[X] = vecInterpLeft[X];
        iFaces[i].r_vector_left_[Y] = vecInterpLeft[Y];
        iFaces[i].r_vector_left_[Z] = vecInterpLeft[Z];

        iFaces[i].r_vector_right_[X] = vecInterpRight[X];
        iFaces[i].r_vector_right_[Y] = vecInterpRight[Y];
        iFaces[i].r_vector_right_[Z] = vecInterpRight[Z];

    }

}
    
void MetricsInitializer::computeAreaFaces(uint iNFaces, Face* iFaces)
{
    for(uint i = 0;i < iNFaces;i++)
    {
        //Get coordinates of normales vector.
        double s_x = iFaces[i].n_vector_[0];
        double s_y = iFaces[i].n_vector_[1];
        double s_z = iFaces[i].n_vector_[2];

        //Compute area;
        double area = sqrt(s_x*s_x + s_y*s_y + s_z*s_z);

        iFaces[i].area_face_ = area;
    }
}   

    
void MetricsInitializer::computeVolumeCells(uint iNCells, uint iNCellsTot, Cell* iCells, Face* iFaces)
{
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    
    for(uint i(0); i < iNCells; i++)
    {
        int nbFaceOfCell = iCells[i].nb_cell2faces_;
        double volume = 0;

        for(int j(0); j < nbFaceOfCell;j++)
        {
            int faceID = iCells[i].cell2faces_[j];

            double cellCenter[3];

            cellCenter[X] = iFaces[faceID].x_face_;
            cellCenter[Y] = iFaces[faceID].y_face_;
            cellCenter[Z] = iFaces[faceID].z_face_;

            double s_x, s_y, s_z;
            s_x = iFaces[faceID].n_vector_[X];
            s_y = iFaces[faceID].n_vector_[Y];
            s_z = iFaces[faceID].n_vector_[Z];

            volume += (cellCenter[X]*s_x + cellCenter[Y]*s_y + cellCenter[Z]*s_z)/3;
            
        }   

        iCells[i].volume_cell_ = volume;
    }


}
    
void MetricsInitializer::computeWLS(uint iNCells, Cell* iCells)
{
    
}
*/