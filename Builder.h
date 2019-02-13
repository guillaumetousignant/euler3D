#ifndef Builder_H
#define Builder_H

#include "nsconstants.h"
#include <string>
#include <vector>

class MESH
{
public:
	Builder();
	~Builder();


void readMyBlocks()
void buildCell(int cell_type)
void buildNode()
void buildFace(int face_type)
void setConnectivity()


int *allocate_1d_array_int(int nbpt, std::string str);

private:






};

#endif