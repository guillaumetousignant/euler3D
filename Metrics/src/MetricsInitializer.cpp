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


void MetricsInitializer::doInit(BlockCommunicator* communicator)
{

    uint iNCells = blockData_->n_real_cells_in_block_;
    uint iNCellsTot = blockData_->n_all_cells_in_block_;
    uint iNFaces = blockData_->n_faces_in_block_;

    Cell** iCells = blockData_->block_cells_;
    Face** iFaces = blockData_->block_faces_;
    Node** iNodes = blockData_->block_nodes_;

    computeCenterCells(iNCells, iNCellsTot, iCells, iNodes);

    computeCenterFaces(iNFaces, iFaces, iNodes);

    computeNormalFaces(iNFaces, iFaces, iCells, iNodes);

    computeAreaFaces(iNFaces, iFaces);

    computeVolumeCells(iNCells, iNCellsTot, iCells, iFaces);

    computeInterpVect(iNCells, iNCellsTot,iNFaces, iCells, iFaces);

    computeCenterGhostCells(iNCells, iNCellsTot, iCells, iFaces);

    computeWLS(iNCells, iCells);

}


void MetricsInitializer::MetricsInitializer::computeCenterCells(uint iNCells, uint iNCellsTot, Cell** iCells, Node** iNodes)
{

    int const X = 0;
    int const Y = 1;
    int const Z = 2;

    for(uint i(0);i < iNCells;i++)
    {
        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;

        uint nbCell2Node = iCells[i]->n_nodes_per_cell_;

        for(uint j(0);j < nbCell2Node;j++)
        {
            //1. Get nodes coordinates of current cell
            int nodeID = iCells[i]->cell_2_nodes_connectivity_[j];

            //2. Get average of all nodes coordinates
            nodeCoord_x += iNodes[nodeID]->node_coordinates_[X];
            nodeCoord_y += iNodes[nodeID]->node_coordinates_[Y];
            nodeCoord_z += iNodes[nodeID]->node_coordinates_[Z];

        }

        //3. Output mapping
        iCells[i]->cell_coordinates_[X] = nodeCoord_x / nbCell2Node;
        iCells[i]->cell_coordinates_[Y] = nodeCoord_y / nbCell2Node;
        iCells[i]->cell_coordinates_[Z] = nodeCoord_z / nbCell2Node;
    }

    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;
        int const LEFT = 0;

        uint leftCellID = iCells[i]->cell_2_cells_connectivity_[LEFT];

        nodeCoord_x = iCells[leftCellID]->cell_coordinates_[X];
        nodeCoord_y = iCells[leftCellID]->cell_coordinates_[Y];
        nodeCoord_z = iCells[leftCellID]->cell_coordinates_[Z];

        iCells[i]->cell_coordinates_[X] = nodeCoord_x;
        iCells[i]->cell_coordinates_[Y] = nodeCoord_y;
        iCells[i]->cell_coordinates_[Z] = nodeCoord_z;
    }
}

void MetricsInitializer::computeCenterFaces(uint iNFaces, Face** iFaces, Node** iNodes)
{

    int const X = 0;
    int const Y = 1;
    int const Z = 2;

    for(uint i(0);i < iNFaces;i++)
    {

        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;

        uint nbFace2Nodes = iFaces[i]->n_nodes_per_face_;


        for(uint j(0);j < nbFace2Nodes;j++)
        {
            //1. Get coordinates of nodes on face.
            int nodeID = iFaces[i]->face_2_nodes_connectivity_[j];

            nodeCoord_x += iNodes[nodeID]->node_coordinates_[X];
            nodeCoord_y += iNodes[nodeID]->node_coordinates_[Y];
            nodeCoord_z += iNodes[nodeID]->node_coordinates_[Z];

        }

        //3. Output Mapping
        iFaces[i]->face_center_[X] = nodeCoord_x / nbFace2Nodes;
        iFaces[i]->face_center_[Y] = nodeCoord_y / nbFace2Nodes;
        iFaces[i]->face_center_[Z] = nodeCoord_z / nbFace2Nodes;

    }
}

void MetricsInitializer::computeNormalFaces2(uint iNFaces, Face** iFaces, Cell** iCells, Node** iNodes)
{

    const uint vec3DSize = 3;
    std::vector<double> centerLeftCell(vec3DSize);
    std::vector<double> faceCenter(vec3DSize);
    std::vector<double> centerConnecVec(vec3DSize);
    std::vector<double> centerFace(vec3DSize);

    const uint X = 0;
    const uint Y = 1;
    const uint Z = 2;

    for(uint i = 0; i < iNFaces;i++)
    {
        vector<vector<double>> nodeCoord(iFaces[i]->n_nodes_per_face_);

        for(int j = 0;j < iFaces[i]->n_nodes_per_face_;j++)
        {
            uint nodeID = iFaces[i]->face_2_nodes_connectivity_[j];

            double node_x = iNodes[nodeID]->node_coordinates_[X];
            double node_y = iNodes[nodeID]->node_coordinates_[Y];
            double node_z = iNodes[nodeID]->node_coordinates_[Z];

            nodeCoord[j] = std::vector<double>(3);
            // nodeCoord[j].push_back(3);

            nodeCoord[j][X] = node_x;
            nodeCoord[j][Y] = node_y;
            nodeCoord[j][Z] = node_z;

        }

        double s_x = 0.0;
        double s_y = 0.0;
        double s_z = 0.0;

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

        const uint nbNodesTriangle = 3;
        const uint nbNodesQuad = 4;

        if(iFaces[i]->n_nodes_per_face_ == nbNodesTriangle)
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
        else if(iFaces[i]->n_nodes_per_face_ == nbNodesQuad)
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

        //Adjust orientation of vector to obey left to right rule for cells
        uint leftCellID = iFaces[i]->face_2_cells_connectivity_[0];

        centerLeftCell[X] = iCells[leftCellID]->cell_coordinates_[X];
        centerLeftCell[Y] = iCells[leftCellID]->cell_coordinates_[Y];
        centerLeftCell[Z] = iCells[leftCellID]->cell_coordinates_[Z];

        uint faceID = i;
        centerFace[X] = iFaces[faceID]->face_center_[X];
        centerFace[Y] = iFaces[faceID]->face_center_[Y];
        centerFace[Z] = iFaces[faceID]->face_center_[Z];

        centerConnecVec[X] = centerFace[X] - centerLeftCell[X];
        centerConnecVec[Y] = centerFace[Y] - centerLeftCell[Y];
        centerConnecVec[Z] = centerFace[Z] - centerLeftCell[Z];

        double dotProduct = centerConnecVec[X]*s_x + centerConnecVec[Y]*s_y + centerConnecVec[Z]*s_z;


        if(dotProduct < 0)
        {
            s_x *= -1.0;
            s_y *= -1.0;
            s_z *= -1.0;
        }

        iFaces[i]->face_normals_[X] = s_x;
        iFaces[i]->face_normals_[Y] = s_y;
        iFaces[i]->face_normals_[Z] = s_z;

    }

}

void MetricsInitializer::computeNormalFaces(uint iNFaces, Face** iFaces, Cell** iCells, Node** iNodes)
{
    double centerLeftCell[3];
    double faceCenter[3];
    double centerConnecVec[3];
    double centerFace[3];

    double node_coord[12]; // Make bigger if we get faces with more than 4 corners

    double s_x;
    double s_y;
    double s_z;

    double dxyA, dxyB, dxyC;
    double dyzA, dyzB, dyzC;
    double dzxA, dzxB, dzxC;

    double dxA, dxB;
    double dyA, dyB;
    double dzA, dzB;

    double x1, x2, x3, x4;
    double y1, y2, y3, y4;
    double z1, z2, z3, z4;

    int nodeID;
    int leftCellID;
    double dotProduct;

    for(uint i = 0; i < iNFaces;i++)
    {
        for(int j = 0;j < iFaces[i]->n_nodes_per_face_;j++)
        {
            nodeID = iFaces[i]->face_2_nodes_connectivity_[j];

            node_coord[3*j] =     iNodes[nodeID]->node_coordinates_[0];
            node_coord[3*j + 1] = iNodes[nodeID]->node_coordinates_[1];
            node_coord[3*j + 2] = iNodes[nodeID]->node_coordinates_[2];

        }

        if(iFaces[i]->n_nodes_per_face_ == 3)
        {
            //Triangular face

                x1 = node_coord[0];
                x2 = node_coord[3];
                x3 = node_coord[6];

                y1 = node_coord[1];
                y2 = node_coord[4];
                y3 = node_coord[7];

                z1 = node_coord[2];
                z2 = node_coord[5];
                z3 = node_coord[8];

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
        else if(iFaces[i]->n_nodes_per_face_ == 4)
        {

            //Quadrilateral case

                x1 = node_coord[0];
                x2 = node_coord[3];
                x3 = node_coord[6];
                x4 = node_coord[9];

                y1 = node_coord[1];
                y2 = node_coord[4];
                y3 = node_coord[7];
                y4 = node_coord[10];

                z1 = node_coord[2];
                z2 = node_coord[5];
                z3 = node_coord[8];
                z4 = node_coord[11];

                dxA = x4 - x2;
                dxB = x3 - x1;
                dyA = y4 - y2;
                dyB = y3 - y1;
                dzA = z4 - z2;
                dzB = z3 - z1;

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

        //Adjust orientation of vector to obey left to right rule for cells
        leftCellID = iFaces[i]->face_2_cells_connectivity_[0];

        centerLeftCell[0] = iCells[leftCellID]->cell_coordinates_[0];
        centerLeftCell[1] = iCells[leftCellID]->cell_coordinates_[1];
        centerLeftCell[2] = iCells[leftCellID]->cell_coordinates_[2];

        centerFace[0] = iFaces[i]->face_center_[0];
        centerFace[1] = iFaces[i]->face_center_[1];
        centerFace[2] = iFaces[i]->face_center_[2];

        centerConnecVec[0] = centerFace[0] - centerLeftCell[0];
        centerConnecVec[1] = centerFace[1] - centerLeftCell[1];
        centerConnecVec[2] = centerFace[2] - centerLeftCell[2];

        dotProduct = centerConnecVec[0]*s_x + centerConnecVec[1]*s_y + centerConnecVec[2]*s_z;

        if(dotProduct < 0)
        {
            s_x *= -1.0;
            s_y *= -1.0;
            s_z *= -1.0;
        }

        iFaces[i]->face_normals_[0] = s_x;
        iFaces[i]->face_normals_[1] = s_y;
        iFaces[i]->face_normals_[2] = s_z;
    }
}

void MetricsInitializer::computeInterpVect(uint iNCells, uint iNCellsTot, uint iNFaces, Cell** iCells, Face** iFaces)
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

        centerFace[X] = iFaces[i]->face_center_[X];
        centerFace[Y] = iFaces[i]->face_center_[Y];
        centerFace[Z] = iFaces[i]->face_center_[Z];

        //Get center coordinates from neighbor's cells
        uint leftCellID = iFaces[i]->face_2_cells_connectivity_[LEFT];
        uint rightCellID = iFaces[i]->face_2_cells_connectivity_[RIGHT];

        double centerLeftCell[3];
        double centerRightCell[3];

        centerLeftCell[X] = iCells[leftCellID]->cell_coordinates_[0];
        centerLeftCell[Y] = iCells[leftCellID]->cell_coordinates_[1];
        centerLeftCell[Z] = iCells[leftCellID]->cell_coordinates_[2];

        centerRightCell[X] = iCells[rightCellID]->cell_coordinates_[0];
        centerRightCell[Y] = iCells[rightCellID]->cell_coordinates_[1];
        centerRightCell[Z] = iCells[rightCellID]->cell_coordinates_[2];

        double vecInterpLeft[3];

        vecInterpLeft[X] = centerFace[X] - centerLeftCell[X];
        vecInterpLeft[Y] = centerFace[Y] - centerLeftCell[Y];
        vecInterpLeft[Z] = centerFace[Z] - centerLeftCell[Z];

        double vecInterpRight[3];

        vecInterpRight[X] = centerFace[X] - centerRightCell[X];
        vecInterpRight[Y] = centerFace[Y] - centerRightCell[Y];
        vecInterpRight[Z] = centerFace[Z] - centerRightCell[Z];

        iFaces[i]->left_cell_r_vector_[X] = vecInterpLeft[X];
        iFaces[i]->left_cell_r_vector_[Y] = vecInterpLeft[Y];
        iFaces[i]->left_cell_r_vector_[Z] = vecInterpLeft[Z];

        iFaces[i]->right_cell_r_vector_[X] = vecInterpRight[X];
        iFaces[i]->right_cell_r_vector_[Y] = vecInterpRight[Y];
        iFaces[i]->right_cell_r_vector_[Z] = vecInterpRight[Z];

    }

    const uint FACE_GHOST = 0;


    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        uint faceID = iCells[i]->cell_2_faces_connectivity_[FACE_GHOST];

        //Get interpolant vector coordinates
        double r_x, r_y, r_z;

        r_x = iFaces[faceID]->left_cell_r_vector_[X];
        r_y = iFaces[faceID]->left_cell_r_vector_[Y];
        r_z = iFaces[faceID]->left_cell_r_vector_[Z];

        //Compute reflection vector.
        double r_ref_x, r_ref_y, r_ref_z;
        double n_x, n_y, n_z;
        double area;

        area = iFaces[faceID]->face_area_;
        n_x = iFaces[faceID]->face_normals_[X] / area;
        n_y = iFaces[faceID]->face_normals_[Y] / area;
        n_z = iFaces[faceID]->face_normals_[Z] / area;

        double prodScalaire = r_x*n_x + r_y*n_y + r_z*n_z;

        r_ref_x = r_x - 2*prodScalaire*n_x;
        r_ref_y = r_y - 2*prodScalaire*n_y;
        r_ref_z = r_z - 2*prodScalaire*n_z;

        iFaces[faceID]->right_cell_r_vector_[X] = r_ref_x;
        iFaces[faceID]->right_cell_r_vector_[Y] = r_ref_y;
        iFaces[faceID]->right_cell_r_vector_[Z] = r_ref_z;

    }


}


void MetricsInitializer::computeAreaFaces(uint iNFaces, Face** iFaces)
{
    for(uint i = 0;i < iNFaces;i++)
    {
        //Get coordinates of normales vector.
        double s_x = iFaces[i]->face_normals_[0];
        double s_y = iFaces[i]->face_normals_[1];
        double s_z = iFaces[i]->face_normals_[2];

        //Compute area;
        double area = sqrt(s_x*s_x + s_y*s_y + s_z*s_z);

        iFaces[i]->face_area_ = area;
        // Normalize normals

    }
}


void MetricsInitializer::computeVolumeCells(uint iNCells, uint iNCellsTot, Cell** iCells, Face** iFaces)
{
    const int X = 0;
    const int Y = 1;
    const int Z = 2;

    double volume = 0.0;
    const uint vector3DSize = 3;
    std::vector<double > connectVector(vector3DSize); // Vector from center of cell to center of face.

    for(uint i(0); i < iNCells; i++)
    {
        int nbFaceOfCell = iCells[i]->n_faces_per_cell_;

        for(int j(0); j < nbFaceOfCell;j++)
        {
            int faceID = iCells[i]->cell_2_faces_connectivity_[j];

            double cellCenter[3];

            cellCenter[X] = iFaces[faceID]->face_center_[0];
            cellCenter[Y] = iFaces[faceID]->face_center_[1];
            cellCenter[Z] = iFaces[faceID]->face_center_[2];

            double s_x, s_y, s_z;
            s_x = iFaces[faceID]->face_normals_[X];
            s_y = iFaces[faceID]->face_normals_[Y];
            s_z = iFaces[faceID]->face_normals_[Z];


            //Make sure that normal vector is pointing outward of the cell.
            double centerFaceCoord = 0.0;
            double centerCell = 0.0;

            for(uint k(0);k < vector3DSize;k++)
            {
                centerFaceCoord = blockData_->block_faces_[faceID]->face_center_[k];
                centerCell = blockData_->block_cells_[i]->cell_coordinates_[k];
                connectVector[k] = centerFaceCoord - centerCell;
            }

            //Dot product
            double dotProduct = 0.0;

            dotProduct = connectVector[0]*s_x + connectVector[1]*s_y + connectVector[2]*s_z;

            if(dotProduct < 0)
            {
                s_x *= -1.0;
                s_y *= -1.0;
                s_z *= -1.0;
            }

            volume += (cellCenter[X]*s_x + cellCenter[Y]*s_y + cellCenter[Z]*s_z)/3;

        }

        iCells[i]->cell_volume_ = volume;
        volume = 0.0;
    }

    const uint LEFT = 0;

    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        uint leftCellID = iCells[i]->cell_2_cells_connectivity_[LEFT];

        double volume = 0.0;
        volume = iCells[leftCellID]->cell_volume_;

        iCells[i]->cell_volume_ = volume;
    }

}

void MetricsInitializer::computeCenterGhostCells(uint iNCells, uint iNCellsTot, Cell** iCells, Face** iFaces)
{
    const uint FACE_GHOST = 0;

    const uint X = 0;
    const uint Y = 1;
    const uint Z = 2;

    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        uint faceID = iCells[i]->cell_2_faces_connectivity_[FACE_GHOST];

        // Get r vector coordinates
        // Left cell is always inside
        double r_x, r_y, r_z;

        r_x = iFaces[faceID]->left_cell_r_vector_[X];
        r_y = iFaces[faceID]->left_cell_r_vector_[Y];
        r_z = iFaces[faceID]->left_cell_r_vector_[Z];

        // Ghost Cell Center equals the real cell Center so


        iCells[i]->cell_coordinates_[0] += 2.0*r_x;
        iCells[i]->cell_coordinates_[1] += 2.0*r_y;
        iCells[i]->cell_coordinates_[2] += 2.0*r_z;



    }

}

void MetricsInitializer::computeWLS(uint iNCells, Cell** iCells)
{
    if( iNCells > 1)
    {
        const uint X = 0;
        const uint Y = 1;
        const uint Z = 2;

        for(uint i(0);i < iNCells;i++)
        {
            const uint nbCellsNeighbor = iCells[i]->n_faces_per_cell_;

            /*double dxij[nbCellsNeighbor];
            double dyij[nbCellsNeighbor];
            double dzij[nbCellsNeighbor];*/

            double* dxij = new double[iCells[i]->n_faces_per_cell_];
            double* dyij = new double[iCells[i]->n_faces_per_cell_];
            double* dzij = new double[iCells[i]->n_faces_per_cell_];

            for(uint j(0);j < nbCellsNeighbor;j++)
            {
                double centerCell[3] =  {0.0, 0.0,0.0};

                centerCell[X] = iCells[i]->cell_coordinates_[X];
                centerCell[Y] = iCells[i]->cell_coordinates_[Y];
                centerCell[Z] = iCells[i]->cell_coordinates_[Z];



                uint cellNeighborID = iCells[i]->cell_2_cells_connectivity_[j];
                double centerNeighborCell[3] = {0.0, 0.0,0.0};

                centerNeighborCell[X] = iCells[cellNeighborID]->cell_coordinates_[X];
                centerNeighborCell[Y] = iCells[cellNeighborID]->cell_coordinates_[Y];
                centerNeighborCell[Z] = iCells[cellNeighborID]->cell_coordinates_[Z];

                dxij[j] = centerNeighborCell[X] - centerCell[X];
                dyij[j] = centerNeighborCell[Y] - centerCell[Y];
                dzij[j] = centerNeighborCell[Z] - centerCell[Z];

            }

            double sumdxij2 = 0.0;
            double sumdxij_dot_dyij = 0.0;
            double sumdxij_dot_dzij = 0.0;
            double sumdyijSquare_minus_r12Square = 0.0;
            double sumdyijdzij_minus_r12r13 = 0.0;
            double sumdzijSquare_minus_r13Square_minusr23Square = 0.0;

            for(uint j(0);j < nbCellsNeighbor;j++)
            {
                sumdxij2 += dxij[j]*dxij[j];
                sumdxij_dot_dyij += dxij[j]*dyij[j];
                sumdxij_dot_dzij += dxij[j]*dzij[j];
            }

            double r11 = sqrt(sumdxij2);

            double r12 = (1/r11)*sumdxij_dot_dyij;

            double r13 = (1/r11)*sumdxij_dot_dzij;

            for(uint j(0);j < nbCellsNeighbor;j++)
            {
                sumdyijSquare_minus_r12Square += dyij[j]*dyij[j];
                sumdyijdzij_minus_r12r13 += dyij[j]*dzij[j];
            }

            double r22 = sqrt(sumdyijSquare_minus_r12Square - r12*r12);

            double r23 = (1/r22)*(sumdyijdzij_minus_r12r13- r12*r13);

            for(uint j(0);j < nbCellsNeighbor;j++)
            {
                sumdzijSquare_minus_r13Square_minusr23Square += dzij[j]*dzij[j] ;
            }

            double r33 = sqrt(sumdzijSquare_minus_r13Square_minusr23Square- (r13*r13 + r23*r23));

            double beta = (r12*r23 - r13*r22)/(r11*r22);

            const uint vector3DSize = 3;


            //Charles: Should be moved in DataStrutre when instanciating Cell Objects
            double **weightLeastSquared = new double*[nbCellsNeighbor];
            for(uint j (0); j < nbCellsNeighbor; j++)
            {
                weightLeastSquared[j] = new double[vector3DSize];
            }
            // **********************************************************************


            for(uint j(0);j < nbCellsNeighbor;j++)
            {

                double alpha3 = (1/(r33*r33))*(dzij[j] - (r23/r22)*dyij[j] + beta*dxij[j]);

                double alpha2 = (1/(r22*r22))*(dyij[j] - (r12/r11)*dxij[j]);

                double alpha1 = dxij[j] / (r11*r11);

                double weight1 = alpha1 - (r12/r11)*alpha2 + beta*alpha3;
                double weight2 = alpha2 - (r23/r22)*alpha3;
                double weight3 = alpha3;

               // cout<<"Cell idx: "<<i<<" "<<j<<" Weight: "<<weight1<<" "<<weight2<<" "<<weight3<<endl;


                weightLeastSquared[j][0] = weight1;
                weightLeastSquared[j][1] = weight2;
                weightLeastSquared[j][2] = weight3;

            }

            iCells[i]->cell_weights_=weightLeastSquared;

            delete [] dxij;
            delete [] dyij;
            delete [] dzij;

        }

    }


}
