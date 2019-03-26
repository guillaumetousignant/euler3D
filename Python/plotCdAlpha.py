import numpy as np
import math
import string
import matplotlib
import matplotlib.pyplot as plt

class plotCdAlpha(object):
    #Plot Cd vs Alpha graph
    def __init__(self, npAngleOfAttack, npAerodynamicCd):
        print("plotCdAlpha.....................................................");
        self.AngleOfAttack_ = npAngleOfAttack;
        self.AerodynamicCd_ = npAerodynamicCd;
        plt.figure()
        fig = plt.plot(self.AngleOfAttack_, self.AerodynamicCd_);

        # Plot parameters
        plt.title('Drag Coefficient vs Angle of Attack')
        plt.xlabel('Angle of Attack (deg)');
        plt.ylabel('Drag Coefficient (Cd)');

        print("Save CdvsAlpha.png..............................................");
        plt.savefig('.png/CdvsAlpha.png');
        print("Save CdvsAlpha.png..........................................DONE");

        print("plotCdAlpha.................................................DONE");
