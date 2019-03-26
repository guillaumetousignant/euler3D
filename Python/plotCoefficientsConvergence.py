import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotCoefficientsConvergence(object):
    #Plot Cl vs Alpha graph
    def __init__(self , npIterations, npConvergenceCl, npConvergenceCd, npConverenceCmx, npConverenceCmy, npConverenceCmz):
        print("plotCoefficientsConvergence.....................................");
        self.Iterations_ = npIterations;
        self.ConvergenceCl_ = npConvergenceCl;
        self.ConvergenceCd_ = npConvergenceCd;
        self.ConvergenceCmx_ = npConverenceCmx;
        self.ConvergenceCmy_ = npConverenceCmy;
        self.ConvergenceCmz_ = npConverenceCmz;
        plt.figure()
        fig = plt.plot(self.Iterations_, self.ConvergenceCl_, label = 'Cl');
        fig = plt.plot(self.Iterations_, self.ConvergenceCd_, label = 'Cd');
        fig = plt.plot(self.Iterations_, self.ConvergenceCmx_, label = 'Cmx');
        fig = plt.plot(self.Iterations_, self.ConvergenceCmy_, label = 'Cmy');
        fig = plt.plot(self.Iterations_, self.ConvergenceCmz_, label = 'Cmz');
        plt.title('Coefficients Convergence')
        plt.xlabel('Iterations');
        plt.ylabel('Coefficients');
        plt.autoscale(enable=True, axis='y', tight=None)
        plt.legend();
        print("Save CoefficientsConvergence.png................................");
        plt.savefig('CoefficientsConvergence.png');
        print("Save CoefficientsConvergence.png............................DONE");
        print("plotCoefficientsConvergence.................................DONE");
