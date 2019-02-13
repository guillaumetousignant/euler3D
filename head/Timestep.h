#ifndef SOLVERSKELETON_HEAD_TIMESTEP_H
#define SOLVERSKELETON_HEAD_TIMESTEP_H

#include "Block.h"

#include <string>
using namespace std;


class Timestep
{
	public:
		double cfl_;
		double gamma_;

		void computeSpectralRadius(Block* block);
		void computeTimestep(Block* block);

		Timestep(double cfl, double gamma);

		~Timestep();




};


#endif
