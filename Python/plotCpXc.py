import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotCpXc(object):
    def __init__(self, mySurfaceFlowFile, Axis, XCoordinate, YCoordinate, ZCoordinate):
        print("plotCpXc........................................................");

        self.normal_x_ = 0;
        self.normal_y_ = 0;
        self.normal_z_ = 0;

        # Pre-processing
        # Axis
        if Axis == 1:
            self.normal_x_ = 1;
        elif Axis == 2:
            self.normal_y_ = 1;
        elif Axis == 3:
            self.normal_z_ = 1;

        #Coordinates
        origin_x = XCoordinate;
        origin_y = YCoordinate;
        origin_z = ZCoordinate;

        #Processing
        # Graphic
        dataset = tecplot.data.load_tecplot(mySurfaceFlowFile, read_data_option=2);

        frame = tecplot.active_frame()
        frame.plot_type = PlotType.Cartesian3D

        # Extract slice using user commands
        extracted_slice = tecplot.data.extract.extract_slice(
            origin=(origin_x, origin_y, origin_z),
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
        cp_linemap = plot.add_linemap(
            zone=extracted_slice,
            x=dataset.variable(0),
            y=dataset.variable(11))

        # Set graph parameters
        cp_linemap.line.color = tecplot.constant.Color.Blue
        cp_linemap.line.line_thickness = 0.8
        cp_linemap.y_axis.reverse = True
        plot.view.fit()

        # export image of pressure coefficient as a function of x
        print("Print CpXc_wing.png.............................................");
        tecplot.export.save_png('CpXc_wing.png', 2000, supersample=3)
        print("Print CpXc_wing.png.........................................DONE");
        print("plotCpXc....................................................DONE");
