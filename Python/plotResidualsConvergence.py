import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotResidualsConvergence(object):
    #Plot Cl vs Alpha graph
    def __init__(self , npIterations, npRoResiduals, npUuResiduals, npVvResiduals, npWwResiduals, npPpResiduals):
        print("plotResidualsConvergence........................................");
        self.Iterations_ = npIterations;
        self.RoResiduals_ = npRoResiduals;
        self.UuResiduals_ = npUuResiduals;
        self.VvResiduals_ = npVvResiduals;
        self.WwResiduals_ = npWwResiduals;
        self.PpResiduals_ = npPpResiduals;
        plt.figure()
        fig = plt.plot(self.Iterations_, self.RoResiduals_, label = 'Density Residuals');
        fig = plt.plot(self.Iterations_, self.UuResiduals_, label = 'Uu Residuals');
        fig = plt.plot(self.Iterations_, self.VvResiduals_, label = 'Vv Residuals');
        fig = plt.plot(self.Iterations_, self.WwResiduals_, label = 'Ww Residuals');
        fig = plt.plot(self.Iterations_, self.PpResiduals_, label = 'Pressure Residuals');
        plt.title('Residuals Convergence')
        plt.xlabel('Iterations');
        plt.ylabel('Residuals');
        plt.xlim(0);
        plt.legend();
        print("Print ResidualsConvergence.png..................................");
        plt.savefig('ResidualsConvergence.png');
        print("Print ResidualsConvergence.png..............................DONE");
        print("plotResidualsConvergence....................................DONE");
