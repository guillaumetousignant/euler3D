import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotSurfaceMachContour(object):
    def __init__(self, mySurfaceFlowFile, Type):
        print("plotMachContour.................................................");
        dataset = tecplot.data.load_tecplot(mySurfaceFlowFile, read_data_option=2);

        frame = tecplot.active_frame();
        plot = frame.plot(PlotType.Cartesian3D)
        plot.activate()
        plot.show_contour = True;

        if Type == 0: # EULER
            plot.contour(0).variable = dataset.variable(9);
        elif Type == 1: # SU2
            plot.contour(0).variable = dataset.variable(11);

        plot.view.width = 1.62571;
        plot.view.alpha = 0;
        plot.view.theta = 240;
        plot.view.psi = 60;
        plot.view.position = (6.9746, 4.3061, 4.26909);

        # Save layout for Tecplot
        print("Save MachContour_fullbody.lay...................................");
        tecplot.save_layout('.lay/MachContour_fullbody.lay');
        print("Save MachContour_fullbody.lay...............................DONE");

        # export image of full body
        print("Save MachContour_fullbody.png...................................");
        tecplot.export.save_png('.png/MachContour_fullbody.png', 2000, supersample=3);
        print("Save MachContour_fullbody.png...............................DONE");

        plot = frame.plot(PlotType.Cartesian2D)
        plot.activate()
        plot.show_contour = True;

        if Type == 0: # EULER
            plot.contour(0).variable = dataset.variable(9);
        elif Type == 1: # SU2
            plot.contour(0).variable = dataset.variable(11);

        plot.axes.x_axis.show = False;
        plot.axes.y_axis.show = False;

        # Save layout for Tecplot
        print("Save MachContour_wing.lay.......................................");
        tecplot.save_layout('.lay/MachContour_wing.lay');
        print("Save MachContour_wing.lay...................................DONE");

        # export image of wing
        print("Save MachContour_wing.png.......................................");
        tecplot.export.save_png('.png/MachContour_wing.png', 2000, supersample=3);
        print("Save MachContour_wing.png...................................DONE");

        print("plotMachContour.............................................DONE");
