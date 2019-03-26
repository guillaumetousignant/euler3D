#ifndef METIS_HEAD_RECONSTRUCTFACES_H
#define METIS_HEAD_RECONSTRUCTFACES_H

#include <iostream>     // std::cout
#include <algorithm>    // std::set_intersection, std::sort
#include <vector> 

class ReconstructFaces
{
public:
	int n_blocks_;
	int** block_array_4_comparaison_;
	ReconstructFaces();
	~ReconstructFaces();
	
};