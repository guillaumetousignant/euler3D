#include "metisMesh.h"
#include <iostream>
#include <mpi.h>
#include <metis.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    cout << "This is the main" << endl;
    
    // Finalize the MPI environment.
    MPI_Finalize();

    /*if (argc != 4)
	{
		std::cout << "Usage: ./metis <single block mesh file> <Number of partitions> <Output mesh file name>\n";
		return 0;
	}*/

    //Metis' routine

    //Input arguments
	std::string meshFile = argv[1];
	//int nPart = atoi(argv[2]);
	//std::string outputMeshFile = argv[3];


	MetisMesh reader;
	reader.ReadSingleBlockMesh(meshFile);
    
    
	//MetisMesh* newMesh = reader.Partition(nPart);

	//newMesh->WriteMesh(outputMeshFile);
}
