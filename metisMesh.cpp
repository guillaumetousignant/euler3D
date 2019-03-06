#include "metisMesh.h"
#include <iostream>
#include <fstream>
#include <metis.h>
#include <string>

using namespace std;


int findNodeIndex(std::vector<int>& list, int node2find)
{
    int count(list.size());

    for (int i = 0; i < count; i++)
    {
        if (node2find == list[i])
        {
            return i+1;
        }
    }

    list.push_back(node2find);

    return list.size();
}

MetisMesh::MetisMesh()
: nElements_(nullptr), nNodes_(nullptr), nBlock_(0), x_(nullptr), y_(nullptr), z_(nullptr), connectivity_(nullptr)
{

}

MetisMesh::~MetisMesh()
{
    if (nElements_ != nullptr) delete [] nElements_;
    if (nNodes_ != nullptr) delete [] nNodes_;
    if (elementType_ != nullptr) delete [] elementType_;
    if (nTotalNode_ != nullptr) delete nTotalNode_;

    nElements_ = nullptr;
    nNodes_ = nullptr;
    elementType_ = nullptr;
    nTotalNode_ = nullptr;

    for (int blockI = 0; blockI < nBlock_; blockI++)
    {
        if (x_[blockI] != nullptr) delete [] x_[blockI];
        if (y_[blockI] != nullptr) delete [] y_[blockI];
        if (z_[blockI] != nullptr) delete [] z_[blockI];

        if (connectivity_[blockI] != nullptr) delete [] connectivity_[blockI];
        connectivity_[blockI] = nullptr;
    }

    if (x_ != nullptr) delete [] x_;
    if (y_ != nullptr) delete [] y_;
    if (z_ != nullptr) delete [] z_;
    

    if (connectivity_ != nullptr) delete [] connectivity_;

    x_ = nullptr;
    y_ = nullptr;
    z_ = nullptr;


    connectivity_ = nullptr;
}

void MetisMesh::Init(int nBlock, int* nElements, int* nNodes)
{
    nBlock_ = nBlock; 
    nElements_ = new int[nBlock];
    nNodes_ = new int[nBlock];
    elementType_ = new int[*nElements];
    nTotalNode_ = new int[1];

    x_ = new double*[nBlock]; 
    y_ = new double*[nBlock];
    z_ = new double*[nBlock];  

    connectivity_ = new std::vector<int>*[nBlock];

    for (int i = 0; i < nBlock; i++)
    {
        nElements_[i] = nElements[i];
        nNodes_[i] = nNodes[i];
        x_[i] = new double[nNodes[i]];
        y_[i] = new double[nNodes[i]];
        z_[i] = new double[nNodes[i]];

        connectivity_[i] = new std::vector<int>[nElements_[i]];
    }
    cout << "Initialisation done" << endl;
}

void MetisMesh::ReadSingleBlockMesh(std::string fileName)
{

ifstream myfile(fileName);
string line;

if (myfile.is_open()) {

    cout << "Reading : " << fileName << endl;
    int nNodes(0);
    int nElements(0);
    int nDimensions(0);
    int nBlock(1);
    char str_temp[100];

    // Prepass 1 :
    getline (myfile, line);
    sscanf(line.c_str(), "NDIME=%d", &nDimensions);
    cout << "Nb de dimensions = " << nDimensions << endl;

    getline (myfile, line);
    sscanf(line.c_str(), "NELEM=%d", &nElements);
    cout << "Nb d'elements= " << nElements << endl;   
    
        for (int i = 0; i < nElements + 1; i++) {
        getline (myfile,line);   
        } 

    sscanf(line.c_str(), "NPOIN=%d", &nNodes);
    cout << "Nb de noeuds= " << nNodes << endl;  

    // Fonction d'initialisation :
    Init(nBlock, &nElements, &nNodes);

    // Prepass 2 :
    myfile.seekg(0, myfile.beg); 
    getline(myfile,line);
    cout << "ligne debut : " << line << endl;

    getline(myfile,line);
    getline(myfile,line);
    
    *nTotalNode_ = 0;
    for (int i = 0; i < nElements; i++) {
         
        sscanf(line.c_str(), "%d %s", &elementType_[i], str_temp); 
        elementType_[i] = NumberOfNodes(elementType_[i]);
        *nTotalNode_ += elementType_[i];
        getline(myfile, line); 
    
    }

    cout << elementType_[0] << " " << elementType_[nElements-1] << " " << elementType_[2345] << endl;
    cout << line << endl;
    cout << line << endl;

    if (nDimensions == 3) {
        for (int nodeI = 0; nodeI < nNodes; nodeI++) { 
            myfile >> x_[0][nodeI] >> y_[0][nodeI] >> z_[0][nodeI];         
        }
    }

    else {
       for (int nodeI = 0; nodeI < nNodes; nodeI++)
        {
            myfile >> x_[0][nodeI] >> y_[0][nodeI];
            z_[0][nodeI] = 0.0;      
        } 
    }
     
    myfile.seekg(0, myfile.beg); 
    getline(myfile,line);
    cout << "ligne 1 : " << line << endl;
    getline(myfile,line);
    cout << "ligne 2 : " << line << endl;

    int temp;

    for (int elementI = 0; elementI < nElements; elementI ++) {
        myfile >> temp;

        for (int numberOfNodes = 0; numberOfNodes < elementType_[elementI]; numberOfNodes ++) {
        
        int node;
        myfile >> node; 
        connectivity_[0][elementI].push_back(node);    
        }
    }

    myfile.close(); 
    }
}

/*void MetisMesh::ReadSingleBlockMesh(std::string fileName)
{
    std::ifstream myfile(fileName);
    std::string line;

    for (int i = 0; i < 7; i++)
        getline(myfile, line);

    int nNodes(0);
    int nElements(0);
    int nBlock(1);

    char ZONETYPE[128];

    sscanf(line.c_str()," Nodes=%d, Elements=%d, ZONETYPE=%s", &nNodes, &nElements, ZONETYPE);

    Init(nBlock, &nElements, &nNodes);

    getline(myfile, line);
    getline(myfile, line);

    for (int nodeI = 0; nodeI < nNodes; nodeI++)
    {
        myfile >> x_[0][nodeI] >> y_[0][nodeI] >> z_[0][nodeI];
    }

    for (int elementI = 0; elementI < nElements; elementI++)
    {
        int n1, n2, n3;
        myfile >> n1 >> n2 >> n3;
        connectivity_[0][elementI].push_back(n1);
        connectivity_[0][elementI].push_back(n2);
        connectivity_[0][elementI].push_back(n3);
    }

    myfile.close();
}
*/

void MetisMesh::WriteMesh(std::string fileName)
{
    FILE* fid = fopen(fileName.c_str(), "w");

    fprintf(fid, "VARIABLES=\"X\",\"Y\"\n");

    for (int blockI = 0; blockI < nBlock_; blockI++)
    {
        int nNodes = nNodes_[blockI];
        int nElements = nElements_[blockI];

        fprintf(fid, "ZONE T=\"Element\"\nNodes=%d, Elements=%d, ZONETYPE=FETriangle\nDATAPACKING=POINT\n", nNodes, nElements);

        for (int nodeI = 0; nodeI < nNodes; nodeI++)
        {
            fprintf(fid, "%.12e %.12e\n", x_[blockI][nodeI], y_[blockI][nodeI]);
        }

        for (int elementI = 0; elementI < nElements; elementI++)
        {
            fprintf(fid, "%d %d %d\n", connectivity_[blockI][elementI][0], connectivity_[blockI][elementI][1], connectivity_[blockI][elementI][2]);
        }
    }

    fclose(fid);
}
/* void MetisMesh::WriteMesh(std::string fileName)
{
    FILE* fid = fopen(fileName.c_str(), "w");

    fprintf(fid, "VARIABLES=\"X\",\"Y\"\n");

    for (int blockI = 0; blockI < nBlock_; blockI++)
    {
        int nNodes = nNodes_[blockI];
        int nElements = nElements_[blockI];

        fprintf(fid, "ZONE T=\"Element\"\nNodes=%d, Elements=%d, ZONETYPE=FETriangle\nDATAPACKING=POINT\n", nNodes, nElements);

        for (int nodeI = 0; nodeI < nNodes; nodeI++)
        {
            fprintf(fid, "%.12e %.12e\n", x_[blockI][nodeI], y_[blockI][nodeI]);
        }

        for (int elementI = 0; elementI < nElements; elementI++)
        {
            fprintf(fid, "%d %d %d\n", connectivity_[blockI][elementI][0], connectivity_[blockI][elementI][1], connectivity_[blockI][elementI][2]);
        }
    }

    fclose(fid);
} */

int MetisMesh::NumberOfNodes(int elementType) {

int numberOfNodes(0);

    // Line
    if (elementType == 3) {

       numberOfNodes = 2; 
    }

    // Triangle
    else if (elementType == 5) {

       numberOfNodes = 3; 
    }

    // Quadrlateral
    else if (elementType == 9) {

       numberOfNodes = 4; 
    }

    // Tetrahedral 
    else if (elementType == 10) {

       numberOfNodes = 4; 
    }
   
    // Hexahedral 
    else if (elementType == 12) {

       numberOfNodes = 8; 
    }
    
    // Wedge
    else if (elementType == 13) {

       numberOfNodes = 6; 
    }

    // Pyramid
    else if (elementType == 14) {

       numberOfNodes = 5; 
    }

   
    return numberOfNodes;
}



MetisMesh* MetisMesh::Partition(int nPart)
{
    if (nBlock_ > 1)
    {
        throw std::runtime_error("Cannot partition a multiblock mesh!");
    }


// alloc memoire
    int eptr[nElements_[0] + 1];
    int eind[*nTotalNode_];
    cout << "fin alloc memoire" << endl;

    // Converting conncectivity into METIS data structure See Metis reference doc
    eptr[0] = 0;
    int count = 0;

    for (int i = 1; i < nElements_[0]+1; i++)
    {
        count += connectivity_[0][i].size();
        eptr[i] = count;
    }
    cout << "count is : " << count << endl;
    cout << "fin conversion" << endl;
    cout << "element 0 : " << nElements_[0] << endl;
    
    int count1 = 0;
    for (int i = 0; i < nElements_[0]; i++)
    {
        for (int j = 0; j < elementType_[i]; j++) {
        
        eind[count1] = connectivity_[0][i][j]; 
        count1++;
        }
    }

    cout << *nTotalNode_ << endl;
    cout << eind[*nTotalNode_ -1] << endl;
    
    cout << "fin connectivite" << endl;

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

    MetisMesh* newMesh = new MetisMesh();
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


void MetisMesh::SetConnectivity(std::vector<int>** connectivity)
{
    for (int blockI = 0; blockI < nBlock_; blockI++)
        for (int elementI = 0; elementI < nElements_[blockI]; elementI++)
            connectivity_[blockI][elementI] = connectivity[blockI][elementI];
}
