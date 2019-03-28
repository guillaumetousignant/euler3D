#include "MetisMesh.h"

#include <iostream>
#include <fstream>
#include <metis.h>
#include <string>

using namespace std;

/*==============HELENE=================*/
int* MetisMesh::getnNodes_()
{
  return nNodes_;
}
/*=====================================*/

int findNodeIndex(std::vector<int> &list, int node2find)
{
    int count(list.size());

    for (int i = 0; i < count; i++)
    {
        if (node2find == list[i])
        {
<<<<<<< HEAD

=======
>>>>>>> origin/metis_isa
            return i + 1;
        }
    }

    list.push_back(node2find);
    return list.size();
}

MetisMesh::MetisMesh()
    : nElements_(nullptr), nNodes_(nullptr), elementType_(nullptr), local2GlobalElements_(nullptr),
     nTotalNode_(0), nBlock_(0), x_(nullptr), y_(nullptr), z_(nullptr), connectivity_(nullptr), connectivity_node_(nullptr)


{
    std::cout << "constructing MetisMesh..." << endl;
}

MetisMesh::~MetisMesh()
{
    std::cout << "destructing MetisMesh..." << endl;

    if (nElements_ != nullptr)
        delete[] nElements_;
    if (nNodes_ != nullptr)
        delete[] nNodes_;

    nElements_ = nullptr;
    nNodes_ = nullptr;
<<<<<<< HEAD

=======

    cout << "destructor ok 1" << endl;
>>>>>>> origin/metis_isa
    for (int blockI = 0; blockI < nBlock_; blockI++)
    {
        if (x_[blockI] != nullptr)
            delete[] x_[blockI];
        if (y_[blockI] != nullptr)
            delete[] y_[blockI];
        if (z_[blockI] != nullptr)
            delete[] z_[blockI];
<<<<<<< HEAD

        if (elementType_[blockI] != nullptr)
            delete[] elementType_[blockI];
        if (elementNbrNodes_[blockI] != nullptr)
            delete[] elementNbrNodes_[blockI];

        delete local2GlobalElements_;
=======
        if (local2GlobalElements_[blockI] != nullptr)
            delete[] local2GlobalElements_[blockI];
         /* if (elementType_[blockI] != nullptr)
            delete[] elementType_[blockI];
        if (elementNbrNodes_[blockI] != nullptr)
            delete[] elementNbrNodes_[blockI]; */


>>>>>>> origin/metis_isa


        if (connectivity_[blockI] != nullptr)
            delete[] connectivity_[blockI];


        connectivity_[blockI] = nullptr;
<<<<<<< HEAD

        /*==============HELENE=================*/
        if (connectivity_node_[blockI] != nullptr)
            delete[] connectivity_node_[blockI];


        connectivity_node_[blockI] = nullptr;
        /*=====================================*/

=======

>>>>>>> origin/metis_isa
    }

    cout << "destructor ok 2" << endl;

    if (x_ != nullptr)
        delete[] x_;
    if (y_ != nullptr)
        delete[] y_;
    if (z_ != nullptr)
        delete[] z_;

    if (elementType_ != nullptr)
        delete[] elementType_;
     if (elementNbrNodes_ != nullptr)
        delete[] elementNbrNodes_;

    cout << "destructor ok 3" << endl;
    if (local2GlobalElements_ != nullptr)
        delete[] local2GlobalElements_;
    cout << "destructor ok 3.25" << endl;

    if (connectivity_ != nullptr)
        delete[] connectivity_;
<<<<<<< HEAD
    /*==============HELENE=================*/
    if (connectivity_node_ != nullptr)
        delete[] connectivity_node_;
    /*=====================================*/



=======
    cout << "destructor ok 3.5" << endl;
>>>>>>> origin/metis_isa
    x_ = nullptr;
    y_ = nullptr;
    z_ = nullptr;

    local2GlobalElements_ = nullptr;
    elementType_ = nullptr;
    elementNbrNodes_ = nullptr;
    connectivity_ = nullptr;

    /*==============HELENE=================*/
    connectivity_node_ = nullptr;
    /*=====================================*/


    cout << "destructor ok 4" << endl;
    cout << "destruct succeed" << endl;
}

void MetisMesh::Init(int nBlock, int *nElements, int *nNodes)

{
    std::cout << "starting Init..." << endl;
    nBlock_ = nBlock;
    nElements_ = new int[nBlock];
    nNodes_ = new int[nBlock];

    elementType_ = new int *[nBlock];
    elementNbrNodes_ = new int *[nBlock];


    x_ = new double *[nBlock];
    y_ = new double *[nBlock];
    z_ = new double *[nBlock];

    connectivity_ = new std::vector<int> *[nBlock];
    connectivity_node_ = new std::vector<int> *[nBlock];



    for (int i = 0; i < nBlock; i++)
    {
        nElements_[i] = nElements[i];
        nNodes_[i] = nNodes[i];
        x_[i] = new double[nNodes[i]];
        y_[i] = new double[nNodes[i]];
        z_[i] = new double[nNodes[i]];
       /*  elementType_[i] = new int [nElements[i]];
        elementNbrNodes_[i] = new int [nElements[i]]; */

        connectivity_[i] = new std::vector<int>[nElements_[i]];
        connectivity_node_[i] = new std::vector<int>[nNodes_[i]];

    }

    // Only want to initialize after partitioning
    if (nBlock != 1) {
        local2GlobalElements_ = new int *[nBlock];

        for (int i = 0; i < nBlock; i++) {
            local2GlobalElements_[i] = new int [nElements[i]];
        }
        std::cout << "Initialisation done global" << endl;
    }


}

// Initialize static int attribute nDimensions_
int MetisMesh::nDimensions_ = 0;

void MetisMesh::ReadSingleBlockMesh(std::string fileName)
{

    ifstream myfile(fileName);
    string line;

    if (myfile.is_open())
    {
        std::cout << "Reading...................... " << fileName << endl;

        int nNodes(0);
        int nElements(0);
        int nBoundaries(0);
        int nDimensions(0);
        int nBlock(1);
        char str_temp[100];

        // ------- Prepass 1 : -------- //
        getline(myfile, line);

        // Stocke le nombre de dimensions du maillage dans une variable statique
        sscanf(line.c_str(), "NDIME=%d", &nDimensions);
        std::cout << "Nombre de dimensions = " << nDimensions << endl;
        nDimensions_ = nDimensions;
        getline(myfile, line);

        // Stocke le nombre d'éléments du maillage
        sscanf(line.c_str(), "NELEM=%d", &nElements);
        std::cout << "Nombre d'elements= " << nElements << endl;

        for (int i = 0; i < nElements + 1; i++)
        {
            getline(myfile, line);
        }
        cout << line << endl;
        // Stocke le nombre de noeuds du maillage
        sscanf(line.c_str(), "NPOIN=%d", &nNodes);
        std::cout << "Nombre de noeuds= " << nNodes << endl;

        for (int i = 0; i < nNodes + 1; i++)
        {
            getline(myfile, line);
        }





        // Stocke le nombre de conditions frontieres
        sscanf(line.c_str(), "NMARK=%d", &nBoundaries);
        std::cout << "Nombre de conditions frontières= " << nBoundaries << endl;

        // Création d'un object MetisBoundary pour stocker les variables
        metisBoundary_ = new MetisBoundary(nBoundaries);


        for (int i = 0; i < nBoundaries; i++) {


            getline(myfile, line);
            // Finding the first equal sign in the string
            // This is because we want only its right side MARKER_TAG= AIRFOIL
            size_t pos_equal_sign = line.find('=');
            // The string tag is whatever is at the right of the equal sign.
            string str_tag = line.substr(pos_equal_sign+1);
            // The following is the equivalent to a left trim (strip)
            while (str_tag[0] == ' ')
            {
                str_tag = str_tag.substr(1);
            }

            metisBoundary_->boundaryNames_[i] = str_tag;

            std::cout << "le nom de la frontiere " << i+1 << " est : " << str_tag << endl;


            getline(myfile, line);

            int boundaryNelements = 0;

            sscanf(line.c_str(), "MARKER_ELEMS= %d", &boundaryNelements);

            // Objets a deleter
            int* elementTypeBoundary = new int[boundaryNelements];
            metisBoundary_->boundaryNelements_[i] = boundaryNelements;
            metisBoundary_->boundaryElementNbrNodes_[i] = new int[boundaryNelements];
            metisBoundary_->boundaryElementType_[i] = new int[boundaryNelements];

            for (int j = 0; j < boundaryNelements; j++) {

                getline(myfile, line);
                sscanf(line.c_str(), "%d %s", &elementTypeBoundary[j], str_temp);

                metisBoundary_->boundaryElementType_[i][j] = elementTypeBoundary[j];
                metisBoundary_->boundaryElementNbrNodes_[i][j] = NumberOfNodes(elementTypeBoundary[j]);
            }
        }

        // Fonctions d'initialisation :
        Init(nBlock, &nElements, &nNodes);
        metisBoundary_->InitBoundary(metisBoundary_->boundaryNelements_, nBoundaries);

        // Prepass 2 : retour au debut du fichier
        myfile.seekg(0, myfile.beg);

        getline(myfile, line);
        getline(myfile, line);
        getline(myfile, line);

        // Enregistrement du premier entier elementType
        nTotalNode_ = 0;
        elementType_ = new int[nElements];
        elementNbrNodes_ = new int[nElements];

        for (int i = 0; i < nElements; i++)
        {
            sscanf(line.c_str(), "%d %s", &elementType_[i], str_temp);
            elementNbrNodes_[i] = NumberOfNodes(elementType_[i]);
            nTotalNode_ += elementNbrNodes_[i];
            getline(myfile, line);

        }

        cout << "nTotalNode_ = " << nTotalNode_ << endl;
        cout << "nNodes = " << nNodes << endl;

        if (nDimensions == 3)
        {
            for (int nodeI = 0; nodeI < nNodes; nodeI++)
            {
                myfile >> x_[0][nodeI] >> y_[0][nodeI] >> z_[0][nodeI];
                getline(myfile, line);
            }

        }
        else
        {
            for (int nodeI = 0; nodeI < nNodes; nodeI++)
            {
                myfile >> x_[0][nodeI] >> y_[0][nodeI];
                getline(myfile, line);
                z_[0][nodeI] = 0.0;
            }
        }

        cout << "Noeuds enregistres " << endl;
        getline(myfile, line);
        getline(myfile, line);
        getline(myfile, line);

        int node;
        int temp;

        for (int i = 0; i < nBoundaries; i ++) {

            for (int j = 0; j < metisBoundary_->boundaryNelements_[i]; j++) {
                myfile >> temp;
                for (int k = 0; k < metisBoundary_->boundaryElementNbrNodes_[i][j]; k++)
                {

                    myfile >> node;
                    //getline(myfile, line);
                    metisBoundary_->boundaryConnectivity_[i][j].push_back(node);
                }

                getline(myfile, line);
            }

           // cout << "last " << metisBoundary_->boundaryConnectivity_[6][1833][2] << endl;
            if (i != nBoundaries - 1)
            {
                getline(myfile, line);
                getline(myfile, line);
            }
        }

        cout << "Frontieres enregistrees " << endl;


        // getline and tokenize node in boundaries
        myfile.seekg(0, myfile.beg);
        myfile.seekg(0, myfile.beg);
        //debut du fichier remplacer par une recher mot cle ^
        getline(myfile, line);
        getline(myfile, line);


        for (int i = 0; i < nElements; i++)
        {
            myfile >> temp;

            for (int numberOfNodes = 0; numberOfNodes < elementNbrNodes_[i]; numberOfNodes++)
            {

                int node;
                myfile >> node;
                connectivity_[0][i].push_back(node);
                /*==============HELENE=================*/
                connectivity_node_[0][node].push_back(i);
                /*=====================================*/
            }

            getline(myfile, line);
        }

        myfile.close();
        std::cout << "closing... " << fileName << endl;

    }
    else
        std::cout << "could not open " << fileName << endl;

}


void MetisMesh::WriteMesh(std::string fileName)
{
    FILE *fid = fopen(fileName.c_str(), "w");
    std::cout << "file open... " << fileName << endl;
/*
    for (int i = 0; i < nBoundaries_; i++) {
        cout << "allo" << endl;

        for (int j = 0; j < metisBoundaries_[i]->boundaryConnectivity_[0].size(); i++) {
            //std::cout << "coutcout" << metisBoundaries_[0]->boundaryConnectivity_[0][i] << endl;
        }
    } */
     //for (int i = 0; i < 60; i++) {
        //std::cout << "ElementType" <<  " " << elementType_[582571] << endl;
        //std::cout << "Element" <<  " " << elementNbrNodes_[582571] << endl;
        //std::cout << "local2GlobalElements_[blockI][elementI] " << local2GlobalElements_[1][291377] << endl;

   /*  for (int i = 0; i < 60; i++) {

        cout << "Connectivity" << i;

        for (int j = 0; j < 4; j++) {
            cout << " " << connectivity_[1][i][j];
        }
        cout << endl;
    }   */

    for (int blockI = 0; blockI < nBlock_; blockI++)
    {

        int nNodes = nNodes_[blockI];
        int nElements = nElements_[blockI];

        fprintf(fid, "Block= %d\n", blockI + 1);
        fprintf(fid, "NDIME= %d\n", nDimensions_);
        fprintf(fid, "NELEM= %d\n", nElements);


        //cout << "local2GlobalElements_[0][0]" <<  local2GlobalElements_[blockI][0] << endl;
        //cout << "elementNbrNodes_[0][elementI] " << elementNbrNodes_[0][local2GlobalElements_[blockI][nElements]] << endl;
        //for (int i = 0; i < 4)
        //cout <<
        //cout << blockI << " NELEM= " << nElements << endl;


        for (int elementI = 0; elementI < nElements; elementI++)
        {

            int elementGlobal = local2GlobalElements_[blockI][elementI];

            //cout << "element local du block" << blockI << " element" << elementI <<  " = " << elementGlobal << endl;
            fprintf(fid, "%d ", elementType_[elementGlobal]);
            //cout << "elementType_[elementGlobal] " << elementType_[elementGlobal] << endl;
            //cout << "elementNbrNodes_[elementGlobal] " << elementNbrNodes_[elementGlobal] << endl;


           for (int j = 0; j < elementNbrNodes_[elementGlobal]; j++)
            {
                fprintf(fid, "%d ", connectivity_[blockI][elementI][j]);
            }

            fprintf(fid, "\n");
        }

        cout << "access connectivity elements block " << blockI << endl;
        fprintf(fid, "NPOIN= %d\n", nNodes);
        for (int nodeI = 0; nodeI < nNodes; nodeI++)
        {
            fprintf(fid, "%.12e %.12e %.12e\n", x_[blockI][nodeI], y_[blockI][nodeI], z_[blockI][nodeI]);
        }
        cout << "access nodes block " << blockI << endl;
    }

    fclose(fid);
    std::cout << fileName << "output file closed ..." << endl;
}

int MetisMesh::NumberOfNodes(int elementType)
{

    int numberOfNodes(0);

    // Line
    if (elementType == 3)
    {

        numberOfNodes = 2;
    }

    // Triangle
    else if (elementType == 5)
    {

        numberOfNodes = 3;
    }

    // Quadrlateral
    else if (elementType == 9)
    {

        numberOfNodes = 4;
    }

    // Tetrahedral
    else if (elementType == 10)
    {

        numberOfNodes = 4;
    }

    // Hexahedral
    else if (elementType == 12)
    {

        numberOfNodes = 8;
    }

    // Wedge
    else if (elementType == 13)
    {

        numberOfNodes = 6;
    }

    // Pyramid
    else if (elementType == 14)
    {

        numberOfNodes = 5;
    }

    return numberOfNodes;
}

MetisMesh* MetisMesh::Partition(int nPart)
{
    std::cout << "fonction Partition start " << endl;

    if (nBlock_ > 1)
    {
        throw std::runtime_error("Cannot partition a multiblock mesh!");
    }

    // Vecteurs d'entrée pour Metis
    int eptr[nElements_[0] + 1];
    int *eind = new int[nTotalNode_];

    // Converting connectivity into METIS data structure See Metis reference doc
    eptr[0] = 0;
    int count = 0;
    int count1 = 0;

    for (int i = 0; i < nElements_[0]; i++)
    {

        count += elementNbrNodes_[i];
        eptr[i+1] = count; // i + 1, car eptr[0] doit commencer a 0
    }


    for (int i = 0; i < nElements_[0]; i++)
    {
        for (int j = 0; j < elementNbrNodes_[i]; j++)
        {
            eind[count1] = connectivity_[0][i][j];
            count1++;

        }
    }

    std::cout << "fin connectivite Metis" << endl;

    int ncommon(3);
    int objval;
    int epart[nElements_[0]];
    int npart[nNodes_[0]];

    int success = METIS_PartMeshDual(&nElements_[0], &nNodes_[0], &eptr[0], eind, NULL, NULL,
                                     &ncommon, &nPart, NULL, NULL, &objval,
                                     &epart[0], &npart[0]);

    std::cout << "Partition Success: " << success << std::endl;

    std::vector<int> elementsPerBlock[nPart];
    std::vector<int> elementNbrNodesPerBlock[nPart];
    std::vector<int> nodesPerBlock[nPart];


    for (int i = 0; i < nElements_[0]; i++)
    {

        int blockId = epart[i];
        elementsPerBlock[blockId].push_back(i);
        elementNbrNodesPerBlock[blockId].push_back(elementNbrNodes_[0][i]);
    }

    /*==============HELENE=================*/
    std::vector<int> nodesPerBlock[nPart];
    for (int i = 0; i < nNodes_[0]; i++)
    {
        int blockId = npart[i];
        nodesPerBlock[blockId].push_back(i);
        elementNbrNodesPerBlock[blockId].push_back(elementNbrNodes_[i]);
    }
    /*=====================================*/

   /*   for (int i = 0; i < 15; i++)
    {
        int blockId = npart[i];
        nodesPerBlock[blockId].push_back(i);
    } */

    int newNelements[nPart];

    for (int blockI = 0; blockI < nPart; blockI++) {
        newNelements[blockI] = elementsPerBlock[blockI].size();
    }

    cout << "Partition and new vector" << endl;

    std::vector<int> addedNode[nPart];
    std::vector<int> **newConnectivity;
    newConnectivity = new std::vector<int> *[nPart];
    cout << "nPart = " << nPart << endl;
    for (int blockI = 0; blockI < nPart; blockI++)
    {
        newConnectivity[blockI] = new std::vector<int>[newNelements[blockI]];
        cout << "building newConnectivity " << blockI << endl;
        cout << newNelements[blockI] << endl;

        for (int i = 0; i < newNelements[blockI]; i++)
        {

            for (int j = 0; j < elementNbrNodesPerBlock[blockI][i]; j++)
            {
                int elementIblockI = elementsPerBlock[blockI][i];
                int n1 = connectivity_[0][elementIblockI][j];
                int newN1 = findNodeIndex(addedNode[blockI], n1);
                newConnectivity[blockI][i].push_back(newN1);

            }
        }

    }
    cout << "new connectivity done" << endl;
    int newNnodes[nPart];

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        newNnodes[blockI] = addedNode[blockI].size();
    }

    // Creation dune nouvelle instance de Metis Mesh
    MetisMesh *newMesh = new MetisMesh();
    newMesh->Init(nPart, newNelements, newNnodes);

    newMesh->SetConnectivity(newConnectivity);

    std::cout << "newMesh ok" << endl;

    for (int blockI = 0; blockI < nPart; blockI++) {
        newNelements[blockI] = elementsPerBlock[blockI].size();

        for (int i = 0; i < newNelements[blockI]; i++) {
            newMesh->local2GlobalElements_[blockI][i] = elementsPerBlock[blockI][i];

        }
    }

    for (int blockI = 0; blockI < nPart; blockI++)
    {

        int size = addedNode[blockI].size();

        for (int i = 0; i < size; i++)
        {
            int nodeId = addedNode[blockI][i];
            newMesh->x_[blockI][i] = x_[0][nodeId];
            newMesh->y_[blockI][i] = y_[0][nodeId];
            newMesh->z_[blockI][i] = z_[0][nodeId];
        }
    }

    cout << "addedNode ok" << endl;

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        if (newConnectivity[blockI] != nullptr)
            delete[] newConnectivity[blockI];
        newConnectivity[blockI] = nullptr;
    }

    if (newConnectivity != nullptr)
        delete[] newConnectivity;
    newConnectivity = nullptr;

    if (eind != nullptr)
        delete[] eind;
    eind = nullptr;

    std::cout << "newMesh returned" << endl;

    // TODO: Check if newMesh should (like in this case), have a pointer to local2global or create its own structure.
    // Pas le choix de copier les attributs dans le newMesh car cest sur lui que l<on call la fonction WriteMesh
    newMesh->elementType_ = elementType_;
    local2GlobalElements_ = newMesh->local2GlobalElements_;
    newMesh->elementNbrNodes_ = elementNbrNodes_;

  /*
    for (int i = 0; i < 60; i++) {
        //cout << "ElementType" << i << " " << elementType_[i] << endl;
        //cout << "Element" << i << " " << elementNbrNodes_[i] << endl;
        cout << "ConnectivityEnBas" << i;

        for (int j = 0; j < 4; j++) {
            cout << " " << newMesh->connectivity_[1][i][j];
        }
        cout << endl;
    }   */

    return newMesh;

}
/*

Mesh* Mesh::Partition(int nPart)
{
    if (nBlock_ > 1)
    {
        throw std::runtime_error("Cannot partition a multiblock mesh!");
    }

    int eptr[nElements_[0] + 1];
    int eind[nElements_[0] * 3];

    // Converting conncectivity into METIS data structure See Metis reference doc
    eptr[0] = 0;
    int count = 0;

    for (int i = 1; i < nElements_[0]+1; i++)
    {
        count += 3;
        eptr[i] = count;
    }

    for (int i = 0; i < nElements_[0]; i++)
    {
        eind[i*3]   = connectivity_[0][i][0]-1;
        eind[i*3+1] = connectivity_[0][i][1]-1;
        eind[i*3+2] = connectivity_[0][i][2]-1;
    }

    int ncommon(2);
    int objval;

    int epart[nElements_[0]];
    int npart[nNodes_[0]];

    int success = METIS_PartMeshDual(&nElements_[0], &nNodes_[0], &eptr[0], &eind[0], NULL, NULL,
                                     &ncommon, &nPart, NULL, NULL, &objval,
                                     &epart[0], &npart[0]);

    std::cout << "Partition Success: " << success << std::endl;

    std::vector<int> elementsPerBlock[nPart];
    std::vector<int> nodesPerBlock[nPart];

    for (int i = 0; i < nElements_[0]; i++)
    {
        int blockId = epart[i];
        elementsPerBlock[blockId].push_back(i);
    }

    for (int i = 0; i < nNodes_[0]; i++)
    {
        int blockId = npart[i];
        nodesPerBlock[blockId].push_back(i);
    }

    int newNelements[nPart];

    for (int blockI = 0; blockI < nPart; blockI++)
        newNelements[blockI] = elementsPerBlock[blockI].size();

    std::vector<int> addedNode[nPart];
    std::vector<int>** newConnectivity;

    newConnectivity = new std::vector<int>*[nPart];

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        newConnectivity[blockI] = new std::vector<int>[newNelements[blockI]];

        for (int i = 0; i < newNelements[blockI]; i++)
        {
            int n1 = connectivity_[0][elementsPerBlock[blockI][i]][0];
            int n2 = connectivity_[0][elementsPerBlock[blockI][i]][1];
            int n3 = connectivity_[0][elementsPerBlock[blockI][i]][2];

            int newN1 = findNodeIndex(addedNode[blockI], n1);
            int newN2 = findNodeIndex(addedNode[blockI], n2);
            int newN3 = findNodeIndex(addedNode[blockI], n3);

            newConnectivity[blockI][i].push_back(newN1);
            newConnectivity[blockI][i].push_back(newN2);
            newConnectivity[blockI][i].push_back(newN3);
        }
    }

    int newNnodes[nPart];

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        newNnodes[blockI] = addedNode[blockI].size();
    }

    Mesh* newMesh = new Mesh();
    newMesh->Init(nPart, newNelements, newNnodes);
    newMesh->SetConnectivity(newConnectivity);

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        int size(addedNode[blockI].size());
        for (int i = 0; i < size; i++)
        {
            int nodeId = addedNode[blockI][i]-1;

            newMesh->x_[blockI][i] = x_[0][nodeId];
            newMesh->y_[blockI][i] = y_[0][nodeId];
            newMesh->z_[blockI][i] = z_[0][nodeId];
        }
    }

    for (int blockI = 0; blockI < nPart; blockI++)
    {
        if (newConnectivity[blockI] != nullptr) delete [] newConnectivity[blockI];
        newConnectivity[blockI] = nullptr;
    }

    if (newConnectivity != nullptr) delete [] newConnectivity;
    newConnectivity = nullptr;

    return newMesh;
}*/

void MetisMesh::SetConnectivity(std::vector<int> **connectivity)
{
    std::cout << "set connectivity function called" << endl;
    for (int blockI = 0; blockI < nBlock_; blockI++)
        for (int elementI = 0; elementI < nElements_[blockI]; elementI++)
            connectivity_[blockI][elementI] = connectivity[blockI][elementI];
}

vector<vector<int>>* MetisMesh::ReturnFaces(int blockI, int element)
{
    // Faces in vtk format for hexaedron
    int** faces = new int*[6];

    int hexaedronFaces[6][4] = {{1,0,3,2}, {1,2,6,5}, {2,3,7,6}, {3,0,4,7}, {0,1,5,4}, {4,5,6,7}};
    for (int i = 0; i < 6; i++) {

        int *face = hexaedronFaces[i];
        faces[i] = new int[4];
        for (int j = 0; j < 4; j++) {
            faces[i][j] = connectivity_[blockI][element][face[j]];
            cout << faces[i][j] << " ";
        }
        cout << endl;





    }
}
