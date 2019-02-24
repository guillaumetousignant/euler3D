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
    
    Cell* iCells = blockData_->block_cells_;
    Face* iFaces = blockData_->block_faces_;
    Node* iNodes = blockData_->block_nodes_;

    computeCenterCells(iNCells, iNCellsTot, iCells, iNodes);
    
    computeCenterFaces(iNFaces, iFaces, iNodes);

    computeNormalFaces(iNFaces, iFaces, iNodes);

    computeAreaFaces(iNFaces, iFaces);

    computeVolumeCells(iNCells, iNCellsTot, iCells, iFaces);

    computeInterpVect(iNCells, iNCellsTot,iNFaces, iCells, iFaces);
    
    //computeWLS();


   iCells = nullptr;
   iFaces = nullptr;
   iNodes = nullptr;

}


void MetricsInitializer::MetricsInitializer::computeCenterCells(uint iNCells, uint iNCellsTot, Cell* iCells, Node* iNodes)
{

    int const X = 0;
    int const Y = 1;
    int const Z = 2;

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
            nodeCoord_x += iNodes[nodeID].node_coordinates_[X];
            nodeCoord_y += iNodes[nodeID].node_coordinates_[Y];
            nodeCoord_z += iNodes[nodeID].node_coordinates_[Z];

        }

        //3. Output mapping
        iCells[i].cell_coordinates_[0] = nodeCoord_x / nbCell2Node;
        iCells[i].cell_coordinates_[1] = nodeCoord_y / nbCell2Node;
        iCells[i].cell_coordinates_[2] = nodeCoord_z / nbCell2Node;
    }

    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;
        int const LEFT = 0;

        uint leftCellID = iCells[i].cell_2_cells_connectivity_[LEFT];

        nodeCoord_x = iCells[leftCellID].cell_coordinates_[X];
        nodeCoord_y = iCells[leftCellID].cell_coordinates_[Y];
        nodeCoord_z = iCells[leftCellID].cell_coordinates_[Z];

        iCells[i].cell_coordinates_[0] = nodeCoord_x;
        iCells[i].cell_coordinates_[1] = nodeCoord_y;
        iCells[i].cell_coordinates_[2] = nodeCoord_z;
    }
}

void MetricsInitializer::computeCenterFaces(uint iNFaces, Face* iFaces, Node* iNodes)
{
    
    for(uint i(0);i < iNFaces;i++)
    {

        double nodeCoord_x = 0.0;
        double nodeCoord_y = 0.0;
        double nodeCoord_z = 0.0;

        uint nbFace2Nodes = iFaces[i].face_2_nodes_connectivity_size_;


        for(uint j(0);j < nbFace2Nodes;j++)
        {
            //1. Get coordinates of nodes on face.
            int nodeID = iFaces[i].face_2_nodes_connectivity_[j];

            nodeCoord_x += iNodes[nodeID].node_coordinates_[0];
            nodeCoord_y += iNodes[nodeID].node_coordinates_[1];
            nodeCoord_z += iNodes[nodeID].node_coordinates_[2];
            
        }

        //3. Output Mapping
        iFaces[i].face_center_[0] = nodeCoord_x / nbFace2Nodes;
        iFaces[i].face_center_[1] = nodeCoord_y / nbFace2Nodes;
        iFaces[i].face_center_[2] = nodeCoord_z / nbFace2Nodes;

    }
}


void MetricsInitializer::computeNormalFaces(uint iNFaces, Face* iFaces, Node* iNodes)
{
    for(uint i = 0; i < iNFaces;i++)
    {
        vector<vector<double>> nodeCoord(iFaces[i].face_2_nodes_connectivity_size_);

        for(int j = 0;j < iFaces[i].face_2_nodes_connectivity_size_;j++)
        {
            uint nodeID = iFaces[i].face_2_nodes_connectivity_[j];

            double node_x = iNodes[nodeID].node_coordinates_[0];
            double node_y = iNodes[nodeID].node_coordinates_[1];
            double node_z = iNodes[nodeID].node_coordinates_[2];

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

        if(iFaces[i].face_2_nodes_connectivity_size_ == 3)   
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
        else if(iFaces[i].face_2_nodes_connectivity_size_ == 4)
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

        iFaces[i].face_normals_[0] = s_x;
        iFaces[i].face_normals_[1] = s_y;
        iFaces[i].face_normals_[2] = s_z;

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

        centerFace[X] = iFaces[i].face_center_[0];
        centerFace[Y] = iFaces[i].face_center_[1];
        centerFace[Z] = iFaces[i].face_center_[2];

        //Get center coordinates from neighbor's cells
        uint leftCellID = iFaces[i].face_2_cells_connectivity_[LEFT];
        uint rightCellID = iFaces[i].face_2_cells_connectivity_[RIGHT];

        double centerLeftCell[3];
        double centerRightCell[3];

        centerLeftCell[X] = iCells[leftCellID].cell_coordinates_[0];
        centerLeftCell[Y] = iCells[leftCellID].cell_coordinates_[1];
        centerLeftCell[Z] = iCells[leftCellID].cell_coordinates_[2];

        centerRightCell[X] = iCells[rightCellID].cell_coordinates_[0];
        centerRightCell[Y] = iCells[rightCellID].cell_coordinates_[1];
        centerRightCell[Z] = iCells[rightCellID].cell_coordinates_[2];

        double vecInterpLeft[3];

        vecInterpLeft[X] = centerFace[X] - centerLeftCell[X];
        vecInterpLeft[Y] = centerFace[Y] - centerLeftCell[Y];
        vecInterpLeft[Z] = centerFace[Z] - centerLeftCell[Z];

        double vecInterpRight[3];

        vecInterpRight[X] = centerFace[X] - centerRightCell[X];
        vecInterpRight[Y] = centerFace[Y] - centerRightCell[Y];
        vecInterpRight[Z] = centerFace[Z] - centerRightCell[Z];

        iFaces[i].left_cell_r_vector_[X] = vecInterpLeft[X];
        iFaces[i].left_cell_r_vector_[Y] = vecInterpLeft[Y];
        iFaces[i].left_cell_r_vector_[Z] = vecInterpLeft[Z];

        iFaces[i].right_cell_r_vector_[X] = vecInterpRight[X];
        iFaces[i].right_cell_r_vector_[Y] = vecInterpRight[Y];
        iFaces[i].right_cell_r_vector_[Z] = vecInterpRight[Z];

    }

    const uint FACE_GHOST = 0;


    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        uint faceID = iCells[i].cell_2_faces_connectivity_[FACE_GHOST];

        //Get interpolant vector coordinates
        double r_x, r_y, r_z;

        r_x = iFaces[faceID].left_cell_r_vector_[X];
        r_y = iFaces[faceID].left_cell_r_vector_[Y];
        r_z = iFaces[faceID].left_cell_r_vector_[Z];

        //Compute reflection vector.
        double r_ref_x, r_ref_y, r_ref_z;
        double n_x, n_y, n_z;
        double area;

        area = iFaces[faceID].face_area_;
        n_x = iFaces[faceID].face_normals_[X] / area;
        n_y = iFaces[faceID].face_normals_[Y] / area;
        n_z = iFaces[faceID].face_normals_[Z] / area;

        double prodScalaire = r_x*n_x + r_y*n_y + r_z*n_z;

        r_ref_x = r_x - 2*prodScalaire*n_x;
        r_ref_y = r_y - 2*prodScalaire*n_y;
        r_ref_z = r_z - 2*prodScalaire*n_z;

        iFaces[faceID].right_cell_r_vector_[X] = r_ref_x;
        iFaces[faceID].right_cell_r_vector_[Y] = r_ref_y;
        iFaces[faceID].right_cell_r_vector_[Z] = r_ref_z;

    }


}


void MetricsInitializer::computeAreaFaces(uint iNFaces, Face* iFaces)
{
    for(uint i = 0;i < iNFaces;i++)
    {
        //Get coordinates of normales vector.
        double s_x = iFaces[i].face_normals_[0];
        double s_y = iFaces[i].face_normals_[1];
        double s_z = iFaces[i].face_normals_[2];

        //Compute area;
        double area = sqrt(s_x*s_x + s_y*s_y + s_z*s_z);

        iFaces[i].face_area_ = area;
    }
}   

  
void MetricsInitializer::computeVolumeCells(uint iNCells, uint iNCellsTot, Cell* iCells, Face* iFaces)
{
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    
    for(uint i(0); i < iNCells; i++)
    {
        int nbFaceOfCell = iCells[i].cell_2_faces_connectivity_size_;
        double volume = 0;

        for(int j(0); j < nbFaceOfCell;j++)
        {
            int faceID = iCells[i].cell_2_faces_connectivity_[j];

            double cellCenter[3];

            cellCenter[X] = iFaces[faceID].face_center_[0];
            cellCenter[Y] = iFaces[faceID].face_center_[1];
            cellCenter[Z] = iFaces[faceID].face_center_[2];

            double s_x, s_y, s_z;
            s_x = iFaces[faceID].face_normals_[X];
            s_y = iFaces[faceID].face_normals_[Y];
            s_z = iFaces[faceID].face_normals_[Z];

            volume += (cellCenter[X]*s_x + cellCenter[Y]*s_y + cellCenter[Z]*s_z)/3;
            
        }   

        iCells[i].cell_volume_ = volume;
    }

    const uint LEFT = 0;

    for(uint i(iNCells);i < iNCellsTot;i++)
    {
        uint leftCellID = iCells[i].cell_2_cells_connectivity_[LEFT];

        double volume = 0.0;
        volume = iCells[leftCellID].cell_volume_;

        iCells[i].cell_volume_ = volume;
    }

}
    
void MetricsInitializer::computeWLS(uint iNCells, Cell* iCells)
{

    const uint X = 0;
    const uint Y = 1;
    const uint Z = 2;

    for(uint i(0);i < iNCells;i++)
    {
        const uint nbCellsNeighbor = iCells[i].cell_2_cells_connectivity_size_;

        double dxij[nbCellsNeighbor];
        double dyij[nbCellsNeighbor];
        double dzij[nbCellsNeighbor];

        for(uint j(0);j < nbCellsNeighbor;j++)
        {
            double centerCell[3] =  {0.0, 0.0,0.0};

            centerCell[X] = iCells[i].cell_coordinates_[X];
            centerCell[Y] = iCells[i].cell_coordinates_[Y];
            centerCell[Z] = iCells[i].cell_coordinates_[Z];

            uint cellNeighborID = iCells[i].cell_2_cells_connectivity_[j];
            double centerNeighborCell[3] = {0.0, 0.0,0.0};

            centerNeighborCell[X] = iCells[cellNeighborID].cell_coordinates_[X];
            centerNeighborCell[Y] = iCells[cellNeighborID].cell_coordinates_[Y];
            centerNeighborCell[Z] = iCells[cellNeighborID].cell_coordinates_[Z];

            dxij[j] = centerNeighborCell[X] - centerCell[X];
            dyij[j] = centerNeighborCell[Y] - centerCell[Y];
            dzij[j] = centerNeighborCell[Z] - centerCell[Z];

        }

        double sumdxij2 = 0.0;
        double sumdxij_dot_dyij = 0.0;
        double sumdxij_dot_dzij = 0.0;
        double sumdyijSquare_minus_r12Square = 0.0;
        double sumdyijdzij_minus_r12r13;
        double sumdzijSquare_minus_r13Square_minusr23Square = 0.0;

        for(int j(0);j < nbCellsNeighbor;j++)
        {
            sumdxij2 += dxij[j]*dxij[j];
            sumdxij_dot_dyij += dxij[j]*dyij[j];
            sumdxij_dot_dzij += dxij[j]*dzij[j];
        }

        double r11 = sqrt(sumdxij2);

        double r12 = (1/r11)*sumdxij_dot_dyij;

        double r13 = (1/r11)*sumdxij_dot_dzij;

        for(int j(0);j < nbCellsNeighbor;j++)
        {
            sumdyijSquare_minus_r12Square += dyij[j]*dyij[j] - r12*r12;
            sumdyijdzij_minus_r12r13 += dyij[j]*dzij[j] - r12*r13;
        }

        double r22 = sqrt(sumdyijSquare_minus_r12Square);

        double r23 = (1/r22)*sumdyijdzij_minus_r12r13;

        for(int j(0);j < nbCellsNeighbor;j++)
        {
            sumdzijSquare_minus_r13Square_minusr23Square += dzij[j]*dzij[j] - (r13*r13 + r23*r23);
        }
        
        double r33 = sqrt(sumdzijSquare_minus_r13Square_minusr23Square);    

        double beta = (r12*r23 - r13*r22)/(r11*r22);

        double **weights = new double*[nbCellsNeighbor];;
        
        for(uint j(0);j < nbCellsNeighbor;j++)
        {
            weights[j] = new double[3];

            double alpha3 = (1/(r33*r33))*(dzij[j] - (r33/r22)*dyij[j] + beta*dxij[j]);

            double alpha2 = (1/(r22*r22))*(dyij[j] - (r12/r11)*dxij[j]);

            double alpha1 = dxij[j] / (r11*r11);

            weights[j][0] = alpha1 - (r12/r11)*alpha2 + beta*alpha3;
            weights[j][1] = alpha2 - (r23/r22)*alpha3;
            weights[j][2] = alpha3;

        }

        //Deallocation
        for(uint j(0);j < nbCellsNeighbor;j++)
        {
            delete [] weights[j];
        }
        delete [] weights;
        weights = nullptr;
        
    }


}
