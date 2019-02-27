import tkinter
from tkinter import *
from tkinter import ttk
# from tkinter import messagebox


class Root(Tk):
    def __init__(self):
        super(Root, self).__init__()
        self.title("GRAPHICAL USER INTERFACE")
        self.minsize(640, 400)

        # TABS CREATION FOR THE MAIN WINDOW
        tabControl = ttk.Notebook(self)

        tab1 = ttk.Frame(tabControl)
        tabControl.add(tab1, text="1. Input")

        tab2 = ttk.Frame(tabControl)
        tabControl.add(tab2, text = "2. Solver")

        tab3 = ttk.Frame(tabControl)
        tabControl.add(tab3, text = "3. Output")

        tabControl.pack(expan = 1, fill = "both")




# ##################### 1. INPUT #####################
# # SECTION 1.1: GEOMETRY AND MESH
# title_section_1_1 = LabelFrame(tab1, text="1.1 Geometry and mesh", padx=20, pady=20)
# title_section_1_1.pack(fill="both", expand="yes")

# text_section_1_1 = Label(title_section_1_1, text="Please select the desired mesh or geometry:")
# text_section_1_1.pack()

# # Aller chercher les fonctions des classes mesh et geometry??
# def importMesh():
#     messagebox.askokcancel('Mesh Importation', 'Import the desired mesh:')
# Button(title_section_1_1, text='Import mesh', command=importMesh).pack(side=LEFT)

# def importGeometry():
#     messagebox.askokcancel('Geometry Importation', 'Import the desired geometry:')
# Button(title_section_1_1, text='Import geometry', command=importGeometry).pack(side=TOP)

# def generateGeometry():
#     messagebox.askokcancel('Geometry Generation', 'Specify the needed information for geometry generation:')
# Button(title_section_1_1, text='Generate geometry', command=generateGeometry).pack(side=RIGHT)

# # SECTION 1.2: INPUT PARAMETERS
# title_section_1_2 = LabelFrame(tab1, text="1.2 Input parameters", padx=20, pady=20)
# title_section_1_2.pack(fill="both", expand="yes")

# text_section_1_2 = Label(title_section_1_2, text="Please specify the required input values:")
# text_section_1_2.pack()

# ##################### 2. SOLVER #####################
# # SECTION 2.1: CONVERGENCE CRITERIAS
# title_section_2_1 = LabelFrame(tab2, text="2.1 Convergence criterias", padx=20, pady=20)
# title_section_2_1.pack(fill="both", expand="yes")

# text_section_2_1 = Label(title_section_2_1, text="Please specify the required convergence criterias:")
# text_section_2_1.pack()

# # SECTION 2.2: SCHEME SELECTION
# title_section_2_2 = LabelFrame(tab2, text="2.2 Scheme Selection", padx=20, pady=20)
# title_section_2_2.pack(fill="both", expand="yes")

# text_section_2_2 = Label(title_section_2_2, text="Please select the desired flux scheme:")
# text_section_2_2.pack()

# # SECTION 2.3: SOLVER OPTIONS
# title_section_2_3 = LabelFrame(tab2, text="2.3 Solver Options", padx=20, pady=20)
# title_section_2_3.pack(fill="both", expand="yes")

# text_section_2_3 = Label(title_section_2_3, text="Please select other code options:")
# text_section_2_3.pack()

# ##################### 3. OUTPUT #####################
# text_section_3 = Label(tab3, text="Please specify the graphs that you would like to display:")
# text_section_3.pack()

# DISPLAYING OF THE MAIN WINDOW
# main_window1.mainloop()

root = Root()
root.mainloop()