#ifndef SOLVERSKELETON_HEAD_INITIALIZER_H
#define SOLVERSKELETON_HEAD_INITIALIZER_H


#include "Interface.h"
// #include "Solver.h"
#include "CompleteMesh.h"

#include <string>
using namespace std;

//class Interface;
//class Solver;

class Initializer
{
	public:


		Solver* initializeSolver(Interface* interface);
		CompleteMesh* InitializeMesh(Interface* interface);
		Initializer();
		~Initializer();




};


#endif
