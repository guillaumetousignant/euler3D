#ifndef SOLVERSKELETON_HEAD_INITIALIZER_H
#define SOLVERSKELETON_HEAD_INITIALIZER_H


#include "Interface.h"
#include "Solver.h"

#include <string>
using namespace std;

//class Interface;
//class Solver;

class Initializer
{
	public:
		

		Solver* initializeSolver(Interface* interface);


		Initializer();
		
		~Initializer();




};


#endif