#ifndef SOLVERSKELETON_HEAD_SFD_H
#define SOLVERSKELETON_HEAD_SFD_H

#include "Block.h"
#include "Timestep.h"
#include <iostream>
#include <string>
#include <math.h>
class SelectiveFrequencyDamper
{
  public:
    double khi_;
    double delta_;


    SelectiveFrequencyDamper(double khi, double delta);
    ~SelectiveFrequencyDamper();
    void calculateDampedVariables(Block* block);
};

#endif
