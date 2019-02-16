#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    cout << "This is the main" << endl;
    
    // Finalize the MPI environment.
    MPI_Finalize();
}
