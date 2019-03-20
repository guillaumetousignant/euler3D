import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotClAlpha(object):
    #Plot Cl vs Alpha graph
    def __init__(self, npAngleOfAttack, npAerodynamicCl):
        print("plotClAlpha.....................................................");
        self.AngleOfAttack_ = npAngleOfAttack;
        self.AerodynamicCl_ = npAerodynamicCl;
        plt.figure()
        fig = plt.plot(self.AngleOfAttack_, self.AerodynamicCl_);
        plt.title('Lift Coefficient vs Angle of Attack')
        plt.xlabel('Angle of Attack (deg)');
        plt.ylabel('Lift Coefficient (Cl)');
        print("Save ClvsAlpha.png..............................................");
        plt.savefig('ClvsAlpha.png');
        print("Save ClvsAlpha.png..........................................DONE");
        print("plotClAlpha.................................................DONE");
