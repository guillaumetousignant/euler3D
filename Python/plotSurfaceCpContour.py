import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotSurfaceCpContour(object):
    def __init__(self, mySurfaceFlowFile, Type):
        print("plotCpContour...................................................");

        self.mySurfaceFlowFile_ = mySurfaceFlowFile;
        self.type_ = Type;

        if self.type_ == 0: #EULER
            dataset = tecplot.data.load_tecplot_szl(self.mySurfaceFlowFile_, read_data_option=2);
        elif self.type_ == 1: #SU2
            dataset = tecplot.data.load_tecplot(self.mySurfaceFlowFile_, read_data_option=2);

        frame = tecplot.active_frame();
        plot = frame.plot(PlotType.Cartesian3D)
        plot.activate()
        plot.show_contour = True;
        plot.use_lighting_effect = False;

        if self.type_ == 0: #EULER
            plot.contour(0).variable = dataset.variable(8);
        elif self.type_ == 1: #SU2
            plot.contour(0).variable = dataset.variable(10);

        # Set Rainbow
        plot.contour(0).colormap_name = 'Small Rainbow';

        # Set View
        plot.view.width = 1.91291;
        plot.view.alpha = -47.73;
        plot.view.theta = 137.32;
        plot.view.psi = 136.51;
        plot.view.position = (-6.57402, 7.48889, -10.3657);

        # Save layout for Tecplot
        print("Save CpContour_fullbody.lay.....................................");
        tecplot.save_layout('../Python/lay/CpContour_fullbody.lay');
        print("Save CpContour_fullbody.lay.................................DONE");

        # export image of full body
        print("Save CpContour_fullbody.png.....................................");
        tecplot.export.save_png('../Python/png/CpContour_fullbody.png', 2000, supersample=3);
        print("Save CpContour_fullbody.png.................................DONE");

        plot = frame.plot(PlotType.Cartesian2D)
        plot.activate()
        plot.show_contour = True;

        if self.type_ == 0: #EULER
            plot.contour(0).variable = dataset.variable(8);
        elif self.type_ == 1: #SU2
            plot.contour(0).variable = dataset.variable(10);

        plot.axes.x_axis.show = False;
        plot.axes.y_axis.show = False;

        # Save layout for Tecplot
        print("Save CpContour_wing.lay.........................................");
        tecplot.save_layout('../Python/lay/CpContour_wing.lay');
        print("Save CpContour_wing.lay.....................................DONE");

        # export image of wing
        print("Save CpContour_wing.png.........................................");
        tecplot.export.save_png('../Python/png/CpContour_wing.png', 2000, supersample=3);
        print("Save CpContour_wing.png.....................................DONE");

        print("plotCpContour...............................................DONE");
