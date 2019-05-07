import tecplot
import os
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotCpXc(object):
    def __init__(self, mySurfaceFlowFile, Type, Axis, XCoordinate, YCoordinate, ZCoordinate):
        print("plotCpXc........................................................");
        # Put input into attributes
        self.mySurfaceFlowFile_ = mySurfaceFlowFile;
        self.type_ = Type;
        self.axis_ = Axis;

        self.normal_x_ = 0;
        self.normal_y_ = 0;
        self.normal_z_ = 0;

        # Pre-processing
        # Axis
        if self.axis_ == 1:
            self.normal_x_ = 1;
        elif self.axis_ == 2:
            self.normal_y_ = 1;
        elif self.axis_ == 3:
            self.normal_z_ = 1;

        #Coordinates
        self.origin_x = XCoordinate;
        self.origin_y = YCoordinate;
        self.origin_z = ZCoordinate;

        #Processing
        # Graphic

        if self.type_ == 0: #EULER
            dataset = tecplot.data.load_tecplot_szl(self.mySurfaceFlowFile_, read_data_option=2);
        elif self.type_ == 1: #SU2
            dataset = tecplot.data.load_tecplot(self.mySurfaceFlowFile_, read_data_option=2);

        frame = tecplot.active_frame()
        frame.plot_type = PlotType.Cartesian3D

        # Extract slice using user commands
        extracted_slice = tecplot.data.extract.extract_slice(
            origin=(self.origin_x, self.origin_y, self.origin_z),
            normal=(self.normal_x_, self.normal_y_, self.normal_z_),
            source=SliceSource.SurfaceZones,
            dataset=dataset)

        # Get x from slice
        slice_x = extracted_slice.values(0);
        x = slice_x.as_numpy_array();

        # Normalize x with aerodynamic chord
        xc = (x-x.min())/(x.max()-x.min());
        slice_x[:] = xc;

        # switch plot type in current frame, clear plot
        plot = frame.plot(PlotType.XYLine)
        plot.activate()
        plot.delete_linemaps()

        # Create Cp vs x/c 2D plot
        if self.type_ == 0: #EULER
            cp_linemap = plot.add_linemap(
                zone=extracted_slice,
                x=dataset.variable(0),
                y=dataset.variable(8))
        elif self.type_ == 1: #SU2
            cp_linemap = plot.add_linemap(
                zone=extracted_slice,
                x=dataset.variable(0),
                y=dataset.variable(10))


        # Set graph parameters
        cp_linemap.line.color = tecplot.constant.Color.Blue;
        cp_linemap.line.line_thickness = 0.8;
        cp_linemap.y_axis.reverse = True;
        plot.axes.x_axis(0).title.title_mode = AxisTitleMode.UseText;
        plot.axes.x_axis(0).title.text = 'x/c';
        plot.view.fit();

        # export image of pressure coefficient as a function of x
        graphName = "CpXc_{:.2f}_{:.2f}_{:.2f}.png".format(self.origin_x, self.origin_y, self.origin_z);
        print("Save {}....................................".format(graphName));
        tecplot.export.save_png('../Python/png/'+graphName, 2000, supersample=3)
        print("Save {}................................DONE".format(graphName));
        print("plotCpXc....................................................DONE");
