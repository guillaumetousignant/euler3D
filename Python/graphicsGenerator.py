import tecplot
import numpy as np
import math
import string
from plotClAlpha import plotClAlpha
from plotCdAlpha import plotCdAlpha
from plotCmAlpha import plotCmAlpha
from plotCoefficientsConvergence import plotCoefficientsConvergence
from plotResidualsConvergence import plotResidualsConvergence
from plotCpXc import plotCpXc
from plotSurfaceCpContour import plotSurfaceCpContour
from plotSurfaceMachContour import plotSurfaceMachContour
from plotMachIsosurface import plotMachIsosurface
from tecplot.exception import *
from tecplot.constant import *

class graphicsGenerator(object):
    #Initialize booleans
    def __init__(self, myInterfaceFile, myFlowFile, mySurfaceFlowFile, myConvergenceFile, myAerodynamicFile):
        print("Initialize graphicsGenerator....................................")
        #Indicators
        self.ClAlpha_Indicator_ = False;
        self.CdAlpha_Indicator_ = False;
        self.CmAlpha_Indicator_ = False;
        self.CoefficientsConvergence_Indicator_ = False;
        self.ResidualsConvergence_Indicator_ = False;
        self.SlicesCp_Indicator_ = False;
        self.CpXc_Indicator_ = False;
        self.SurfaceCpContour_Indicator_ = False;
        self.SurfaceMachContour_Indicator_ = False;
        self.MachIsosurface_Indicator_ = True ;
        #Files
        self.myInterfaceFile_ = myInterfaceFile;
        self.myFlowFile_ = myFlowFile;
        self.mySurfaceFlowFile_ = mySurfaceFlowFile;
        self.myConvergenceFile_ = myConvergenceFile;
        self.myAerodynamicFile_ = myAerodynamicFile;
        #Attributes
        self.Axis_ = "x";
        self.XCoordinate_ = 0.;
        self.YCoordinate_ = 0.;
        self.ZCoordinate_ = 0.;
        print("Initialize graphicsGenerator................................DONE")

    #Read interface file to execute user commands
    def readInterfaceFile(self, myInterfaceFile):
        print("readInterfaceFile...............................................")
        InterfaceFile = open(myInterfaceFile, "r");
        userCommands = InterfaceFile.readlines();
        InterfaceFile.close();
        print("readInterfaceFile...........................................DONE")
        return userCommands;

    #Change a string to a boolean
    def str2bool(self, text):
        if text == "1":
            return True;
        elif text == "0":
            return False;

    #Initialize user command's booleans
    def Interface2Booleans(self, userCommands):
        findLine = userCommands.index("OUTPUT (0-no 1-yes)\n");
        #Remove \n from strings
        string = userCommands[findLine+2].rstrip();
        string1 = userCommands[findLine+4].rstrip();
        string2 = userCommands[findLine+6].rstrip();
        string3 = userCommands[findLine+8].rstrip();
        string4 = userCommands[findLine+10].rstrip();
        #Put values into attributes
        ClAlpha, CdAlpha, CmAlpha = userCommands[findLine+2].split(" ");
        CoefficientsConvergence, ResidualsConvergence = userCommands[findLine+4].split(" ");
        CpXc, SurfaceMachContour, SurfaceCpContour, MachIsosurface = userCommands[findLine+6].split(" ");
        SliceCp = userCommands[findLine+8].split(" ");
        Axis, XCoordinate, YCoordinate, ZCoordinate = userCommands[findLine+10].split(" ");

        if Axis == "x":
            self.Axis_ = 1;
        elif Axis == "y":
            self.Axis_ = 2;
        elif Axis == "y":
            self.Axis_ = 3;

        # String to float
        self.XCoordinate_ = float(XCoordinate);
        self.YCoordinate_ = float(YCoordinate);
        self.ZCoordinate_ = float(ZCoordinate);

        #String to Boolean
        self.ClAlpha_Indicator_ = self.str2bool(ClAlpha);
        self.CdAlpha_Indicator_ = self.str2bool(CdAlpha);
        self.CmAlpha_Indicator_ = self.str2bool(CmAlpha);
        self.CoefficientsConvergence_Indicator_ = self.str2bool(CoefficientsConvergence);
        self.ResidualsConvergence_Indicator_ = self.str2bool(ResidualsConvergence);
        self.SlicesCp_Indicator_ = self.str2bool(SliceCp);
        self.CpXc_Indicator_ = self.str2bool(CpXc);
        self.SurfaceCpContour_Indicator_ = self.str2bool(SurfaceCpContour);
        self.SurfaceMachContour_Indicator_ = self.str2bool(SurfaceMachContour);
        self.MachIsosurface_Indicator_ = self.str2bool(MachIsosurface);

    #Load data from binary file
    def loadData(self, myFile):
        myDataset = tecplot.data.load_tecplot(myFile, read_data_option=2);
        return myDataset;

    #Save angle of attack into a numpy array
    def getAngleOfAttack(self, myDataset):
        AngleOfAttack = myDataset.variable(0).values(0).as_numpy_array();
        return AngleOfAttack;

    #Save lift coefficients into a numpy array
    def getCl(self, myDataset):
        Cl = myDataset.variable(1).values(0).as_numpy_array();
        return Cl;

    #Save drag coefficients into a numpy array
    def getCd(self, myDataset):
        Cd = myDataset.variable(2).values(0).as_numpy_array();
        return Cd;

    #Save moment coefficients into a numpy array
    def getCm(self, myDataset):
        Cmx = myDataset.variable(3).values(0).as_numpy_array();
        Cmy = myDataset.variable(4).values(0).as_numpy_array();
        Cmz = myDataset.variable(5).values(0).as_numpy_array();
        return Cmx, Cmy, Cmz;

    def getIterations(self, MyDataset):
        Iterations = myDataset.variable(0).values(0).as_numpy_array();
        return Iterations;

    #Save residuals into a numpy array
    def getResiduals(self, myDataset):
        RoResiduals = myDataset.variable(6).values(0).as_numpy_array();
        UuResiduals = myDataset.variable(7).values(0).as_numpy_array();
        VvResiduals = myDataset.variable(8).values(0).as_numpy_array();
        WwResiduals = myDataset.variable(9).values(0).as_numpy_array();
        PpResiduals = myDataset.variable(10).values(0).as_numpy_array();
        return RoResiduals, UuResiduals, VvResiduals, WwResiduals, PpResiduals;

    #Convergence file processing
    def processingConvergenceFile(self, myConvergenceFile):
        print("processingConvergenceFile.......................................")
        #Load convergence dataset
        self.convergenceDataset = self.loadData(myConvergenceFile);
        #Save data into numpy arrays
        npIterations = self.getIterations(self.convergenceDataset);
        npConvergenceCl = self.getCl(self.convergenceDataset);
        npConvergenceCd = self.getCd(self.convergenceDataset);
        npConvergenceCmx, npConvergenceCmy, npConvergenceCmz = self.getCm(self.convergenceDataset);
        npRoResiduals, npUuResiduals, npVvResiduals, npWwResiduals, npPpResiduals = self.getResiduals(self.convergenceDataset);
        print("processingConvergenceFile...................................DONE")
        return npIterations, npConvergenceCl, npConvergenceCd, npConvergenceCmx, npConvergenceCmy, npConvergenceCmz, npRoResiduals, npUuResiduals, npVvResiduals, npWwResiduals, npPpResiduals;

    #Aerodynamic file processing
    def processingAerodynamicFile(self, myAerodynamicFile):
        print("processingAerodynamicFile.......................................")
        #Load aerodynamic dataset
        self.aerodynamicDataset = self.loadData(myAerodynamicFile);
        #Save data into numpy arrays
        npAngleOfAttack = self.getAngleOfAttack(self.aerodynamicDataset);
        npAerodynamicCl = self.getCl(self.aerodynamicDataset);
        npAerodynamicCd = self.getCd(self.aerodynamicDataset);
        npAerodynamicCmx, npAerodynamicCmy, npAerodynamicCmz = self.getCm(self.aerodynamicDataset);
        print("processingAerodynamicFile...................................DONE")
        return npAngleOfAttack, npAerodynamicCl, npAerodynamicCd, npAerodynamicCmx, npAerodynamicCmy, npAerodynamicCmz;

    # Main
    def computeGraphics(self):
        print("computeGraphics.................................................")
        userCommands_ = self.readInterfaceFile(self.myInterfaceFile_)
        self.Interface2Booleans(userCommands_);

        # Processing files
        if self.CoefficientsConvergence_Indicator_ or self.ResidualsConvergence_Indicator_:
            npIterations_, npConvergenceCl_, npConvergenceCd_, npConvergenceCmx_, npConvergenceCmy_, npConvergenceCmz_, npRoResiduals_, npUuResiduals_, npVvResiduals_, npWwResiduals_, npPpResiduals_ = self.processingConvergenceFile(self.myConvergenceFile_);

        if self.ClAlpha_Indicator_ or self.CdAlpha_Indicator_ or self.CmAlpha_Indicator_:
            npAngleOfAttack_, npAerodynamicCl_, npAerodynamicCd_, npAerodynamicCmx_, npAerodynamicCmy_, npAerodynamicCmz_ = self.processingAerodynamicFile(self.myAerodynamicFile_);

        # Execute post processing classes by user commands
        if self.ClAlpha_Indicator_:
            plotclaplha_ = plotClAlpha(npAngleOfAttack_, npAerodynamicCl_);

        if self.CdAlpha_Indicator_:
            plotcdaplha_ = plotCdAlpha(npAngleOfAttack_, npAerodynamicCd_);

        if self.CmAlpha_Indicator_:
            plotcmaplha_ = plotCmAlpha(npAngleOfAttack_, npAerodynamicCmx_, npAerodynamicCmy_, npAerodynamicCmz_);

        if self.CoefficientsConvergence_Indicator_:
            #plotcoefficientsconvergence_ = plotCoefficientsConvergence(npIterations_, npConvergenceCl_, npConvergenceCd_);
            print()

        if self.ResidualsConvergence_Indicator_:
            #plotresidualsconvergence_ = plotResidualsConvergence(npIterations_, npRoResiduals_, npUuResiduals_, npVvResiduals_, npWwResiduals_, npPpResiduals_);
            print()

        if self.SlicesCp_Indicator_:
            #plotslicescp_ = plotSlicesCp();
            print()

        if self.CpXc_Indicator_:
            plotcpxc_ = plotCpXc(self.mySurfaceFlowFile_, self.Axis_, float(self.XCoordinate_), float(self.YCoordinate_), float(self.ZCoordinate_));

        if self.SurfaceCpContour_Indicator_:
            plotsurfacecpcontour_ = plotSurfaceCpContour(self.mySurfaceFlowFile_);

        if self.SurfaceMachContour_Indicator_:
            plotsurfacemachcontour_ = plotSurfaceMachContour(self.mySurfaceFlowFile_);

        if self.MachIsosurface_Indicator_:
            plotmachisosurface_ = plotMachIsosurface(self.myFlowFile_);
        print("computeGraphics.............................................DONE")
