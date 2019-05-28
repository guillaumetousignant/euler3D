#!/usr/bin/python

import tecplot
import os
import numpy as np
import math
import string
import glob
from graphicsGenerator import graphicsGenerator
from tecplot.exception import *
from tecplot.constant import *

def postProcessingEuler():
    # Python directory to bin directory
    os.chdir("../bin");

    # Merge Files
    myFlowFiles_ = glob.glob("FlowData_Block*.dat");
    mySurfaceFiles_ = glob.glob("SurfaceFlowData_Block*.dat");

    if len(myFlowFiles_) != 0:
        print("Merging Flow Files..............................................")
        # Create new file
        myNewFileName_ = "FlowFile_AllBlocks";
        myNewFile_ = open(myNewFileName_ + ".dat", "w");

        for i in range(0,len(myFlowFiles_)):
            # Read Flow Files
            myFile_ = open(myFlowFiles_[i],"r");
            myLines_ = myFile_.readlines();
            myFile_.close();

            # Header
            myHeader_ = [];
            for j in range(0,6):
                myHeader_.append(myLines_[j].rstrip());

            # Data
            myDataset_ = tecplot.data.load_tecplot(myFlowFiles_[i], read_data_option=2);
            myX_ = myDataset_.variable(0).values(0).as_numpy_array();
            myY_ = myDataset_.variable(1).values(0).as_numpy_array();
            myZ_ = myDataset_.variable(2).values(0).as_numpy_array();
            myRo_ = myDataset_.variable(3).values(0).as_numpy_array();
            myUu_ = myDataset_.variable(4).values(0).as_numpy_array();
            myVv_ = myDataset_.variable(5).values(0).as_numpy_array();
            myWw_ = myDataset_.variable(6).values(0).as_numpy_array();
            myPp_ = myDataset_.variable(7).values(0).as_numpy_array();
            myCp_ = myDataset_.variable(8).values(0).as_numpy_array();
            myMach_ = myDataset_.variable(9).values(0).as_numpy_array();


            # Number of Elements
            string, string1, string2 = myHeader_[3].split(", ");
            string3, string4 = string1.split("=");
            myElements_ = int(string4);

            # Connectivity
            myConnectivity_ = [];
            for j in range(len(myLines_)-myElements_,len(myLines_)):
                myConnectivity_.append(myLines_[j].rstrip());

            # Write in new file
            if i == 0:
                myNewFile_.write(myHeader_[0] + "\n");
                myNewFile_.write(myHeader_[1] + "\n");
                myNewFile_.write(myHeader_[2] + "\n");
                myNewFile_.write(myHeader_[3] + "\n");
                myNewFile_.write(myHeader_[4] + "\n");
                myNewFile_.write(myHeader_[5] + "\n");
            else:
                myNewFile_.write(myHeader_[2] + "\n");
                myNewFile_.write(myHeader_[3] + "\n");
                myNewFile_.write(myHeader_[4] + "\n");
                myNewFile_.write(myHeader_[5] + "\n");

            for j in range(0,len(myX_)):
                myNewFile_.write(str(myX_[j]) + "\n");

            for j in range(0,len(myY_)):
                myNewFile_.write(str(myY_[j]) + "\n");

            for j in range(0,len(myZ_)):
                myNewFile_.write(str(myZ_[j]) + "\n");

            for j in range(0,len(myRo_)):
                myNewFile_.write(str(myRo_[j]) + "\n");

            for j in range(0,len(myUu_)):
                myNewFile_.write(str(myUu_[j]) + "\n");

            for j in range(0,len(myVv_)):
                myNewFile_.write(str(myVv_[j]) + "\n");

            for j in range(0,len(myWw_)):
                myNewFile_.write(str(myWw_[j]) + "\n");

            for j in range(0,len(myPp_)):
                myNewFile_.write(str(myPp_[j]) + "\n");

            for j in range(0,len(myCp_)):
                myNewFile_.write(str(myCp_[j]) + "\n");

            for j in range(0,len(myMach_)):
                myNewFile_.write(str(myMach_[j]) + "\n");

            for j in range(0,len(myConnectivity_)):
                myNewFile_.write(myConnectivity_[j] + "\n")

            if i == len(myFlowFiles_)-1:
                myNewFile_.close();

                # Load all data from all blocks
                myDataset_ = tecplot.data.load_tecplot(myNewFileName_ + ".dat", read_data_option=2);

                # Save in szl format
                tecplot.data.save_tecplot_szl(myNewFileName_ + ".szplt", dataset=myDataset_);

                # Delete .dat file
                print("Deleting FlowData_Block*.dat files..............................")
                os.remove( myNewFileName_ + ".dat");

                # Delete FlowDataBlock*.dat for each block
                for i in range(0,len(myFlowFiles_)):
                    os.remove(myFlowFiles_[i]);

                print("Deleting FlowData_Block*.dat files..........................DONE")
                print("Merging Flow Files..........................................DONE")


    if len(mySurfaceFiles_) != 0:
        print("Merging Surface Flow Files......................................")
        # Create new file
        myNewSurfaceFileName_ = "SurfaceFlowFile_AllBlocks";
        myNewFile_ = open(myNewSurfaceFileName_ + ".dat", "w");

        for i in range(0,len(mySurfaceFiles_)):
            # Read Surface Files
            myFile_ = open(mySurfaceFiles_[i],"r");
            myLines_ = myFile_.readlines();
            myFile_.close();

            # Header
            myHeader_ = [];
            for j in range(0,6):
                myHeader_.append(myLines_[j].rstrip());

            # Data
            myDataset_ = tecplot.data.load_tecplot(mySurfaceFiles_[i], read_data_option=2);
            myX_ = myDataset_.variable(0).values(0).as_numpy_array();
            myY_ = myDataset_.variable(1).values(0).as_numpy_array();
            myZ_ = myDataset_.variable(2).values(0).as_numpy_array();
            myRo_ = myDataset_.variable(3).values(0).as_numpy_array();
            myUu_ = myDataset_.variable(4).values(0).as_numpy_array();
            myVv_ = myDataset_.variable(5).values(0).as_numpy_array();
            myWw_ = myDataset_.variable(6).values(0).as_numpy_array();
            myPp_ = myDataset_.variable(7).values(0).as_numpy_array();
            myCp_ = myDataset_.variable(8).values(0).as_numpy_array();
            myMach_ = myDataset_.variable(9).values(0).as_numpy_array();

            # Number of Elements
            string, string1, string2 = myHeader_[3].split(", ");
            string3, string4 = string1.split("=");
            myElements_ = int(string4);

            # Connectivity
            myConnectivity_ = [];
            for j in range(len(myLines_)-myElements_,len(myLines_)):
                myConnectivity_.append(myLines_[j].rstrip());

            # Write in new file
            if i == 0:
                myNewFile_.write(myHeader_[0] + "\n");
                myNewFile_.write(myHeader_[1] + "\n");
                myNewFile_.write(myHeader_[2] + "\n");
                myNewFile_.write(myHeader_[3] + "\n");
                myNewFile_.write(myHeader_[4] + "\n");
                myNewFile_.write(myHeader_[5] + "\n");
            else:
                myNewFile_.write(myHeader_[2] + "\n");
                myNewFile_.write(myHeader_[3] + "\n");
                myNewFile_.write(myHeader_[4] + "\n");
                myNewFile_.write(myHeader_[5] + "\n");

            for j in range(0,len(myX_)):
                myNewFile_.write(str(myX_[j]) + "\n");

            for j in range(0,len(myY_)):
                myNewFile_.write(str(myY_[j]) + "\n");

            for j in range(0,len(myZ_)):
                myNewFile_.write(str(myZ_[j]) + "\n");

            for j in range(0,len(myRo_)):
                myNewFile_.write(str(myRo_[j]) + "\n");

            for j in range(0,len(myUu_)):
                myNewFile_.write(str(myUu_[j]) + "\n");

            for j in range(0,len(myVv_)):
                myNewFile_.write(str(myVv_[j]) + "\n");

            for j in range(0,len(myWw_)):
                myNewFile_.write(str(myWw_[j]) + "\n");

            for j in range(0,len(myPp_)):
                myNewFile_.write(str(myPp_[j]) + "\n");

            for j in range(0,len(myCp_)):
                myNewFile_.write(str(myCp_[j]) + "\n");

            for j in range(0,len(myMach_)):
                myNewFile_.write(str(myMach_[j]) + "\n");

            for j in range(0,len(myConnectivity_)):
                myNewFile_.write(myConnectivity_[j] + "\n")

            if i == len(mySurfaceFiles_)-1:
                myNewFile_.close();

                # Load all data from all blocks
                myDataset_ = tecplot.data.load_tecplot(myNewSurfaceFileName_ + ".dat", read_data_option=2);

                # Save in szl format
                tecplot.data.save_tecplot_szl(myNewSurfaceFileName_ + ".szplt", dataset=myDataset_);

                # Delete .dat file
                print("Deleting SurfaceFlowData_Block*.dat files.......................")
                os.remove(myNewSurfaceFileName_ + ".dat");

                # Delete SurfaceFlowDataBlock*.dat for each block
                for i in range(0,len(mySurfaceFiles_)):
                    os.remove(mySurfaceFiles_[i]);

                print("Deleting SurfaceFlowData_Block*.dat files...................DONE")
                print("Merging Surface Flow Files..................................DONE")


    if len(myFlowFiles_) >= 1 and len(mySurfaceFiles_) >= 1:
        # Euler Files
        myInterfaceFile_ = "output_interface";
        myFlowFile_ = myNewFileName_ + ".szplt";
        mySurfaceFlowFile_ = myNewSurfaceFileName_ + ".szplt";
        myConvergenceFile_ = "Convergence.dat";
        myAerodynamicFile_ = "AerodynamicCoefficients.dat";

    else:
        # also Euler Files
        myInterfaceFile_ = "output_interface";
        myFlowFile_ = "FlowFile_AllBlocks" + ".szplt";
        mySurfaceFlowFile_ = "SurfaceFlowFile_AllBlocks" + ".szplt";
        myConvergenceFile_ = "Convergence.dat";
        myAerodynamicFile_ = "AerodynamicCoefficients.dat";
        #SU2 Files
        #myInterfaceFile_ = "Interface_ONERAM6.txt";
        #myFlowFile_ = "flow_3.06.dat";
        #mySurfaceFlowFile_ = "surface_flow_3.06.dat";
        #myConvergenceFile_ = "history_3.06.dat";
        #myAerodynamicFile_ = "aerodynamic_file.dat";

    #Instantiate graphicsGenerator class
    graphicsgenerator_ = graphicsGenerator(myInterfaceFile_, myFlowFile_, mySurfaceFlowFile_, myConvergenceFile_, myAerodynamicFile_);

    #Generate graphs by user comnmands
    graphicsgenerator_.computeGraphics();

if __name__ == '__main__':
    postProcessingEuler()
