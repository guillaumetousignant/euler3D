import tecplot
import numpy as np
import math
import string
from tecplot.exception import *
from tecplot.constant import *

class plotMachIsosurface(object):
    def __init__(self, myFlowFile):
        print("plotMachIsosurface..............................................");
        dataset = tecplot.data.load_tecplot(myFlowFile, read_data_option=2);
        frame = tecplot.active_frame();
        plot = frame.plot();

        # Set Isosurface to match Contour Levels of the first group.
        iso = plot.isosurface(0)
        iso.isosurface_selection = IsoSurfaceSelection.AllContourLevels
        cont = plot.contour(0)
        iso.definition_contour_group = cont
        cont.colormap_name = 'Magma'

        # Setup definition Isosurface layers
        cont.variable = dataset.variable(12)
        cont.levels.reset_levels( [0.95,1.,1.1,1.4]);

        # Turn on Translucency
        iso.effects.use_translucency = True
        iso.effects.surface_translucency = 80

        # Turn on Isosurfaces
        plot.show_isosurfaces = True
        iso.show = True

        cont.legend.show = False

        plot.view.width = 42.3549
        plot.view.alpha = -10
        plot.view.theta = 169.95
        plot.view.psi = 33.34
        plot.view.position = (6.8157, 175.436, 257.337)

        # export image of wing
        print("Print MachIsosurface_wing.png...................................");
        tecplot.export.save_png('MachIsosurface_wing.png', 2000, supersample=3)
        print("Print MachIsosurface_wing.png...............................DONE");
        print("plotMachIsosurface..........................................DONE");
