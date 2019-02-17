/**
 * @file MetricsInitializer.h
 * @author Patrick Deschambault
 * @brief 
 * @version 0.1
 * @date 2019-02-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef DEF_METRICSINITIALIZER_H
#define DEF_METRICSINITIALIZER_H

//Project files.
#include "Block.h"

//Standard library
#include <iostream>
#include <vector>
#include <math.h>


typedef unsigned int uint;

class MetricsInitializer : public Initializer
{

    public:

        /**
         * @brief Construct a new Metrics Initializer object
         * 
         * @param iBlock 
         */
        MetricsInitializer(Block* iBlock);
        
        /**
         * @brief Destroy the Metrics Initializer object
         * 
         */
        ~MetricsInitializer();

        /**
         * @brief This method is the entry point defined by the Initializer's inherited class
         * 
         */
        virtual void doInit();
    
    protected:
        /**
         * @brief 
         * This method allows to compute the center coordinates of every internal or ghost cells.
         * 
         * @param iNCells: Number of internal cells.
         * @param iNCellsTot: Number of internal and ghost cells.
         * @param iCells: Array of Cell objects to represent internal cells.
         * @param iWalls: Array of Cell objects to represent ghost cell of type wall.
         * @param iFarF: Array of Cell objects to represent ghost cell of type farfield.
         * @param iSynchs: Array of Cell objects to represent ghost cell of type synchs.
         * @param iNodes: Array of Node objects to represent the properties of nodes.
         */
        void computeCenterCells(uint iNCells, uint iNCellsTot, Cell* iCells, Cell* iWalls, Cell* iFarF, Cell* iSynchs, Node* iNodes);

        /**
         * @brief 
         * 
         * @param iNFaces : Total number of faces.
         * @param iFaces: Array containing objects of type Faces.
         * @param iNodes: Array containing objects of type Nodes.
         */
        void computeCenterFaces(uint iNFaces, Face* iFaces, Node* iNodes);

        /**
         * @brief 
         * 
         * @param iNCells 
         * @param iNCellsTot 
         * @param iNFaces 
         * @param iCells 
         * @param iWalls 
         * @param iFarF 
         * @param iSynchs 
         * @param iFaces 
         */
        void computeInterpVect(uint iNCells, uint iNCellsTot, uint iNFaces, Cell* iCells, Cell* iWalls, Cell* iFarF, Cell* iSynchs, Face* iFaces);

        /**
         * @brief 
         * 
         * @param iNFaces 
         * @param iFaces 
         */
        void computeAreaFaces(uint iNFaces, Face* iFaces);

        /**
         * @brief 
         * 
         * @param iNFaces 
         * @param iFaces 
         * @param iNodes 
         */
        void computeNormalFaces(uint iNFaces, Face* iFaces, Node* iNodes);

        /**
         * @brief 
         * 
         * @param iNCells 
         * @param iNCellsTot 
         * @param iCells 
         * @param iWalls 
         * @param iFarF 
         * @param iSynchs 
         * @param iFaces 
         */
        void computeVolumeCells(uint iNCells, uint iNCellsTot, Cell* iCells, Cell* iWalls, Cell* iFarF, Cell* iSynchs, Face* iFaces);

        /**
         * @brief 
         * 
         * @param iNCells: 
         * @param iCells 
         */
        void computeWLS(uint iNCells, Cell* iCells);

    private:

        Block* blockData_;

};


#endif

