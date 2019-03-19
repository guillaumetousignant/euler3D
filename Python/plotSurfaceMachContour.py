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
        plot.contour(0).variable = dataset.variable(11);
        plot.view.width = 1.62571;
        plot.view.alpha = 0;
        plot.view.theta = 240;
        plot.view.psi = 60;
        plot.view.position = (6.9746, 4.3061, 4.26909);

        # export image of full body
        print("Print MachContour_fullbody.png..................................");
        tecplot.export.save_png('MachContour_fullbody.png', 2000, supersample=3);
        print("Print MachContour_fullbody.png..............................DONE");

        plot = frame.plot(PlotType.Cartesian2D)
        plot.activate()
        plot.show_contour = True;
        plot.contour(0).variable = dataset.variable(11);
        plot.axes.x_axis.show = False;
        plot.axes.y_axis.show = False;

        # export image of wing
        print("Print MachContour_wing.png......................................");
        tecplot.export.save_png('MachContour_wing.png', 2000, supersample=3);
        print("Print MachContour_wing.png..................................DONE");

        print("plotMachContour.............................................DONE");
