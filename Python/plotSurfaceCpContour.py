import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotSurfaceCpContour(object):
    def __init__(self, mySurfaceFlowFile):
        print("plotCpContour...................................................");
        dataset = tecplot.data.load_tecplot(mySurfaceFlowFile, read_data_option=2);

        frame = tecplot.active_frame();
        plot = frame.plot(PlotType.Cartesian3D)
        plot.activate()
        plot.show_contour = True;
        plot.contour(0).variable = dataset.variable(11);
        plot.view.width = 68.1536;
        plot.view.alpha = -0.19;
        plot.view.theta = 143.99;
        plot.view.psi = 59.88;
        plot.view.position = (-168.527, 271.68, 195.667);

        # export image of full body
        print("Print CpContour_fullbody.png....................................");
        tecplot.export.save_png('CpContour_fullbody.png', 2000, supersample=3);
        print("Print CpContour_fullbody.png................................DONE");

        plot.view.width = 31.9838;
        plot.view.alpha = 0;
        plot.view.theta = 0;
        plot.view.psi = 0;
        plot.view.position = (39.1623, 16.5128, 383.577);

        # export image of wing
        print("Print CpContour_wing.png........................................");
        tecplot.export.save_png('CpContour_wing.png', 2000, supersample=3);
        print("Print CpContour_wing.png....................................DONE");

        print("plotCpContour...............................................DONE");
