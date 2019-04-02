import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotSlicesCp(object):
    def __init__(self, mySurfaceFlowFile, Type, Axis, firstCoordinate, lastCoordinate, numberOfSlices):
        print("plotSlicesCp....................................................");
        # Put input into attributes
        self.mySurfaceFlowFile_ = mySurfaceFlowFile;
        self.type_ = Type;
        self.axis_ = Axis;
        self.firstCoordinate_ = firstCoordinate;
        self.lastCoordinate_ = lastCoordinate;
        self.numberOfSlices_ = numberOfSlices;

        # Initialize attributes
        self.normalX_ = 0;
        self.normalY_ = 0;
        self.normalZ_ = 0;

        # Initialize vectors
        self.originX_ = [];
        self.originY_ = [];
        self.originZ_ = [];

        # PRE-PROCESSING
        # Axis
        if self.axis_ == 1:
            self.normalX_ = 1;
        elif self.axis_ == 2:
            self.normalY_ = 1;
        elif self.axis_ == 3:
            self.normalZ_ = 1;

        # Slices
        self.interval_ = (self.lastCoordinate_-self.firstCoordinate_)/(self.numberOfSlices_-1);

        self.slice_ = self.firstCoordinate_;

        for i in range(0,self.numberOfSlices_):
            if self.axis_ == 1:

                self.originX_.append(self.slice_);
                self.originY_.append(0);
                self.originZ_.append(0);

                self.slice_ += self.interval_;

            elif self.axis_ == 2:

                self.originX_.append(0);
                self.originY_.append(self.slice_);
                self.originZ_.append(0);

                self.slice_ += self.interval_;

            elif self.axis_ == 3:

                self.originX_.append(0);
                self.originY_.append(0);
                self.originZ_.append(self.slice_);

                self.slice_ += self.interval_;

        #PROCESSING
        # Graphics

        if self.type_ == 0: #EULER
            dataset = tecplot.data.load_tecplot_szl(self.mySurfaceFlowFile_, read_data_option=2);
        elif self.type_ == 1: #SU2
            dataset = tecplot.data.load_tecplot(self.mySurfaceFlowFile_, read_data_option=2);

        # Extract slice using user commands
        for i in range(0, self.numberOfSlices_):
            frame = tecplot.active_frame()
            frame.plot_type = PlotType.Cartesian3D

            extracted_slice = tecplot.data.extract.extract_slice(
                origin=(self.originX_[i], self.originY_[i], self.originZ_[i]),
                normal=(self.normalX_, self.normalY_, self.normalZ_),
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
            graphName = "SliceCp_{:.2f}_{:.2f}_{:.2f}.png".format(self.originX_[i], self.originY_[i], self.originZ_[i]);
            print("Save {}.................................".format(graphName));
            tecplot.export.save_png('.png/'+ graphName, 2000, supersample=3)
            print("Save {}.............................DONE".format(graphName));

        print("plotSlicesCp................................................DONE");
