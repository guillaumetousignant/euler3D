#!/usr/bin/python

import tecplot
import numpy as np
import math
import string
from graphicsGenerator import graphicsGenerator
from tecplot.exception import *
from tecplot.constant import *

# Euler Files
myInterfaceFile_ = "Interface_output.txt";
myFlowFile_ = "FlowData.dat";
mySurfaceFlowFile_ = "SurfaceFlowData.dat";
myConvergenceFile_ = "Convergence.dat";
myAerodynamicFile_ = "aerodynamic_file.dat";

# SU2 Files
#myInterfaceFile_ = "Interface_output.txt";
#myFlowFile_ = "flow_3.06.dat";
#mySurfaceFlowFile_ = "surface_flow_3.06.dat";
#myConvergenceFile_ = "history_3.06.dat";
#myAerodynamicFile_ = "aerodynamic_file.dat";

#Instantiate graphicsGenerator class
graphicsgenerator_ = graphicsGenerator(myInterfaceFile_, myFlowFile_, mySurfaceFlowFile_, myConvergenceFile_, myAerodynamicFile_);

#Generate graphs by user comnmands
graphicsgenerator_.computeGraphics();
