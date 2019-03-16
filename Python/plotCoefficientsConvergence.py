import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotCoefficientsConvergence(object):
    #Plot Cl vs Alpha graph
    def __init__(self , npIterations, npConvergenceCl, npConvergenceCd):
        print("plotCoefficientsConvergence.....................................");
        self.Iterations_ = npIterations;
        self.ConvergenceCl_ = npConvergenceCl;
        self.ConvergenceCd_ = npConvergenceCd;
        plt.figure()
        fig = plt.plot(self.Iterations_, self.ConvergenceCl_, label = 'Cl');
        fig = plt.plot(self.Iterations_, self.ConvergenceCd_, label = 'Cd');
        plt.title('Coefficients Convergence')
        plt.xlabel('Iterations');
        plt.ylabel('Coefficients');
        plt.legend();
        print("Print CoefficientsConvergence.png...............................");
        plt.savefig('CoefficientsConvergence.png');
        print("Print CoefficientsConvergence.png...........................DONE");
        print("plotCoefficientsConvergence.................................DONE");
