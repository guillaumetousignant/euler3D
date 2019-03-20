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
        plot.contour(0).variable = dataset.variable(10);
        plot.view.width = 1.62571;
        plot.view.alpha = 0;
        plot.view.theta = 240;
        plot.view.psi = 60;
        plot.view.position = (6.9746, 4.3061, 4.26909);

        # export image of full body
        print("Print CpContour_fullbody.png....................................");
        tecplot.export.save_png('CpContour_fullbody.png', 2000, supersample=3);
        print("Print CpContour_fullbody.png................................DONE");

        plot = frame.plot(PlotType.Cartesian2D)
        plot.activate()
        plot.show_contour = True;
        plot.contour(0).variable = dataset.variable(10);
        plot.axes.x_axis.show = False;
        plot.axes.y_axis.show = False;


        # export image of wing
        print("Save CpContour_wing.png.........................................");
        tecplot.export.save_png('CpContour_wing.png', 2000, supersample=3);
        print("Save CpContour_wing.png.....................................DONE");

        print("plotCpContour...............................................DONE");
