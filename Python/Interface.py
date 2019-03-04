import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class MainWindow():
    def __init__(self, master): # Initialize the object
        master.title("GRAPHICAL USER INTERFACE")
        
        # TABS CREATION FOR THE MAIN WINDOW
        tabControl = ttk.Notebook(master)
        tabControl.grid(row=0, column=0, columnspan=10, sticky='NESW')

        tab1 = ttk.Frame(tabControl)
        tabControl.add(tab1, text="1. Input")

        tab2 = ttk.Frame(tabControl)
        tabControl.add(tab2, text="2. Solver")

        tab3 = ttk.Frame(tabControl)
        tabControl.add(tab3, text="3. Output")

        # SECTION 1. INPUT
        # SECTION 1.1 GEOMETRY AND MESH
        title_section_1_1 = ttk.LabelFrame(tab1, text="1.1 Geometry and mesh")
        title_section_1_1.grid(row=0, column=0, columnspan=10)

        text_section_1_1 = ttk.Label(title_section_1_1, text="Please select the desired mesh or geometry: ")
        text_section_1_1.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        import_mesh = Button(title_section_1_1, text="Import mesh", command=self.importMesh)
        import_mesh.grid(row=1, column=1, sticky=NSEW)

        import_geometry = Button(title_section_1_1, text="Import geometry", command=self.importGeometry)
        import_geometry.grid(row=1, column=3, sticky=NSEW)

        generate_geometry = Button(title_section_1_1, text="Generate geometry", command=self.generateGeometry)
        generate_geometry.grid(row=1, column=5, sticky=NSEW)

        show_resulting_mesh = Button(title_section_1_1, text="Show resulting mesh", command=self.showResultingMesh)
        show_resulting_mesh.grid(row=2, column=3, sticky=NSEW)

        # SECTION 1.2 INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(tab1, text="1.2 Input parameters")
        title_section_1_2.grid(row=1, column=0, columnspan=10)

        text_section_1_2 = ttk.Label(title_section_1_2, text="Please specify the required input values: ")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        ttk.Label(title_section_1_2, text="cfl", borderwidth=2, relief="groove").grid(row=1, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=1, column=1)

        ttk.Label(title_section_1_2, text="gamma", borderwidth=2, relief="groove").grid(row=2, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=2, column=1)

        ttk.Label(title_section_1_2, text="mach", borderwidth=2, relief="groove").grid(row=3, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=3, column=1)

        ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove").grid(row=1, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=1, column=3)

        ttk.Label(title_section_1_2, text="Angle of\nattack (deg)", borderwidth=2, relief="groove").grid(row=2, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=2, column=3)

        ttk.Label(title_section_1_2, text="Number of\nstages (RK)", borderwidth=2, relief="groove").grid(row=3, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=18).grid(row=3, column=3)

        # SECTION 2. SOLVER
        # SECTION 2.1 CONVERGENCE CRITERIA
        title_section_2_1 = ttk.LabelFrame(tab2, text="2.1 Convergence criteria")
        title_section_2_1.grid(row=0, column=0, columnspan=10)

        text_section_2_1 = ttk.Label(title_section_2_1, text="Please specify the required convergence criteria: ")
        text_section_2_1.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        ttk.Label(title_section_2_1, text="Max number\nof itterations", borderwidth=2, relief="groove").grid(row=1, column=1, sticky=NSEW)
        ttk.Entry(title_section_2_1, width=18).grid(row=1, column=2)

        ttk.Label(title_section_2_1, text="Convergence\ncriterion", borderwidth=2, relief="groove").grid(row=2, column=1, sticky=NSEW)
        ttk.Entry(title_section_2_1, width=18).grid(row=2, column=2)

        # SECTION 2.2 SCHEME SELECTION
        title_section_2_2 = ttk.LabelFrame(tab2, text="2.2 Scheme Selection")
        title_section_2_2.grid(row=1, column=0, columnspan=10)

        text_section_2_2 = ttk.Label(title_section_2_2, text="Please select the required flux scheme: ")
        text_section_2_2.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        flux_scheme = ttk.Button(title_section_2_2, text="Select\nflux scheme", command=self.selectFluxScheme)
        flux_scheme.grid(row=1, column=1)

        # SECTION 2.3 SOLVER OPTIONS
        title_section_2_3 = ttk.LabelFrame(tab2, text="2.3 Solver options")
        title_section_2_3.grid(row=2, column=0, columnspan=10)

        text_section_2_3 = ttk.Label(title_section_2_3, text="Please select a code option: ")
        text_section_2_3.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        # SECTION 3 OUTPUT
        text_section_3 = ttk.Label(tab3, text="Please specify what type of graphe(s) you would like to display: ")
        text_section_3.grid(row=0, column=0)

    # SECTION 1 METHODS
    def importMesh(self):
        self.mesh_window = Tk()
        self.mesh_window.title("Mesh importation")
        ttk.Label(self.mesh_window, text="Import the desired mesh: ").grid(row=0, column=0)
        ttk.Button(self.mesh_window, text="Select a file", command=self.meshFileDialog).grid(row=1, column=2)
        ttk.Button(self.mesh_window, text="Ok", command=self.mesh_window.destroy).grid(row=2, column=1)
        ttk.Button(self.mesh_window, text="Cancel", command=self.mesh_window.destroy).grid(row=2, column=2)

    def meshFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label = ttk.Label(self.mesh_window, text="")
        self.label.grid(row=1, column=1)
        self.label.configure(text=self.filename)

    def importGeometry(self):
        self.geometry_window = Tk()
        self.geometry_window.title("Geometry importation")
        ttk.Label(self.geometry_window, text="Import the desired geometry: ").grid(row=0, column=0)
        ttk.Button(self.geometry_window, text="Select a file", command=self.geometryFileDialog).grid(row=1, column=2)
        ttk.Button(self.geometry_window, text="Ok", command=self.geometry_window.destroy).grid(row=2, column=1)
        ttk.Button(self.geometry_window, text="Cancel", command=self.geometry_window.destroy).grid(row=2, column=2)

    def geometryFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label = ttk.Label(self.geometry_window, text="")
        self.label.grid(row=1, column=1)
        self.label.configure(text=self.filename)

    def generateGeometry(self):
        messagebox.askokcancel('Geometry Generation', 'Specify the needed information for geometry generation:')

    def showResultingMesh(self):
        messagebox.showinfo('Resulting Mesh')
    
    # SECTION 2 METHODS
    def selectFluxScheme(self):
        self.flux_scheme_window = Tk()
        self.flux_scheme_window.title("Scheme selection")
        ttk.Label(self.flux_scheme_window, text="Please select the desired scheme: ").grid(row=0, column=0)
        ttk.Button(self.flux_scheme_window, text="Ok", command=self.flux_scheme_window.destroy).grid(row=2, column=1)
        ttk.Button(self.flux_scheme_window, text="Cancel", command=self.flux_scheme_window.destroy).grid(row=2, column=2)


root = Tk()
main_window = MainWindow(root)
root.mainloop() #Mainloop allows you to be display the window continuously until you close it