import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotSurfaceMachContour(object):
    def __init__(self, mySurfaceFlowFile):
        print("plotMachContour.................................................");
        dataset = tecplot.data.load_tecplot(mySurfaceFlowFile, read_data_option=2);

        frame = tecplot.active_frame();
        plot = frame.plot(PlotType.Cartesian3D)
        plot.activate()
        plot.show_contour = True;
        plot.contour(0).variable = dataset.variable(12);
        plot.view.width = 70.6166;
        plot.view.alpha = -10;
        plot.view.theta = 169.95;
        plot.view.psi = 33.34;
        plot.view.position = (1.06189, 170.465, 259.896);

        # export image of full body
        print("Print MachContour_fullbody.png..................................");
        tecplot.export.save_png('MachContour_fullbody.png', 2000, supersample=3);
        print("Print MachContour_fullbody.png..............................DONE");

        plot.view.width = 42.3549;
        plot.view.alpha = -10;
        plot.view.theta = 169.95;
        plot.view.psi = 33.34;
        plot.view.position = (6.8157, 175.436, 257.337);

        # export image of wing
        print("Print MachContour_wing.png......................................");
        tecplot.export.save_png('MachContour_wing.png', 2000, supersample=3);
        print("Print MachContour_wing.png..................................DONE");

        print("plotMachContour.............................................DONE");
