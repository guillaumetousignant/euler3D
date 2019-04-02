import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotMachIsosurface(object):
    def __init__(self, myFlowFile, Type):
        print("plotMachIsosurface..............................................");

        self.myFlowFile_ = myFlowFile;
        self.type_ = Type;

        if self.type_ == 0: #EULER
            dataset = tecplot.data.load_tecplot_szl(self.myFlowFile_, read_data_option=2);
        elif self.type_ == 1: #SU2
            dataset = tecplot.data.load_tecplot(self.myFlowFile_, read_data_option=2);

        frame = tecplot.active_frame();
        plot = frame.plot();

        # Set Isosurface to match Contour Levels of the first group.
        iso = plot.isosurface(0);

        # Turn on Shade
        iso.shade.show = True

        iso.isosurface_selection = IsoSurfaceSelection.AllContourLevels;
        cont = plot.contour(0);
        iso.definition_contour_group = cont;
        cont.colormap_name = 'Magma';

        # Setup definition Isosurface layers
        if self.type_ == 0: # EULER
            cont.variable = dataset.variable(9);
        elif self.type_ == 1: # SU2
            cont.variable = dataset.variable(11);

        cont.levels.reset_levels( [0.95,1.,1.1,1.4]);

        # Turn on Translucency
        iso.effects.use_translucency = True;
        iso.effects.surface_translucency = 80;

        # Turn on Isosurfaces
        plot.show_isosurfaces = True;
        iso.show = True;

        cont.legend.show = False

        plot.view.width = 2.058;
        plot.view.alpha = 0;
        plot.view.theta = 159.61;
        plot.view.psi = 52.79;
        plot.view.position = (-1.91333,6.93022,5.17559);

        # Save layout for Tecplot
        print("Save MachIsosurface_wing.lay....................................");
        tecplot.save_layout('.lay/MachIsosurface_wing.lay');
        print("Save MachIsosurface_wing.lay................................DONE");

        # export image of wing
        print("Save MachIsosurface_wing.png....................................");
        tecplot.export.save_png('.png/MachIsosurface_wing.png', 2000, supersample=3)
        print("Save MachIsosurface_wing.png................................DONE");

        print("plotMachIsosurface..........................................DONE");
