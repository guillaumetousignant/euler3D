import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotCmAlpha(object):
    #Plot Cm vs Alpha graph
    def __init__(self, npAngleOfAttack, npAerodynamicCmx, npAerodynamicCmy, npAerodynamicCmz):
        print("plotCmAlpha.....................................................");
        self.AngleOfAttack_ = npAngleOfAttack;
        self.AerodynamicCmx_ = npAerodynamicCmx;
        self.AerodynamicCmy_ = npAerodynamicCmy;
        self.AerodynamicCmz_ = npAerodynamicCmz;

        plt.figure()
        fig = plt.plot(self.AngleOfAttack_, self.AerodynamicCmx_, label = 'Cmx');
        fig = plt.plot(self.AngleOfAttack_, self.AerodynamicCmy_, label = 'Cmy');
        fig = plt.plot(self.AngleOfAttack_, self.AerodynamicCmz_, label = 'Cmz');

        plt.title('Moment Coefficients vs Angle of Attack')
        plt.xlabel('Angle of Attack (deg)');
        plt.ylabel('Moment Coefficients (Cm)');
        plt.legend();

        print("Save CmvsAlpha.png..............................................");
        plt.savefig('../Python/.png/CmvsAlpha.png');
        print("Save CmvsAlpha.png..........................................DONE");

        print("plotCmAlpha.................................................DONE");
