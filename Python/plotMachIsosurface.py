import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotMachIsosurface(object):
    def __init__(self, myFlowFile, Type):
        print("plotMachIsosurface..............................................");
        dataset = tecplot.data.load_tecplot(myFlowFile, read_data_option=2);
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
        if Type == 0: # EULER
            cont.variable = dataset.variable(9);
        elif Type == 1: # SU2
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

        # export image of wing
        print("Save MachIsosurface_wing.png....................................");
        tecplot.export.save_png('MachIsosurface_wing.png', 2000, supersample=3)
        print("Save MachIsosurface_wing.png................................DONE");
        print("plotMachIsosurface..........................................DONE");
