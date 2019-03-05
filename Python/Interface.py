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
        title_section_1_1 = LabelFrame(tab1, text="1.1 Geometry and mesh", labelanchor=N, height=195, width=385)
        title_section_1_1.grid(row=0, column=0)
        title_section_1_1.grid_propagate(False)

        text_section_1_1 = ttk.Label(title_section_1_1, text="\nPlease select the desired mesh or geometry:\n")
        text_section_1_1.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        import_mesh = ttk.Button(title_section_1_1, text="Import mesh", command=self.importMesh)
        import_mesh.grid(row=1, column=1, sticky=NSEW)

        import_geometry = ttk.Button(title_section_1_1, text="Import geometry", command=self.importGeometry)
        import_geometry.grid(row=1, column=3, sticky=NSEW)

        generate_geometry = ttk.Button(title_section_1_1, text="Generate geometry", command=self.generateGeometry)
        generate_geometry.grid(row=1, column=5, sticky=NSEW)

        show_resulting_mesh = ttk.Button(title_section_1_1, text="Show resulting mesh", command=self.showResultingMesh)
        show_resulting_mesh.grid(row=2, column=3, sticky=NSEW)

        # SECTION 1.2 INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(tab1, text="1.2 Input parameters", labelanchor=N, height=195, width=385)
        title_section_1_2.grid(row=1, column=0)
        title_section_1_2.grid_propagate(False)

        text_section_1_2 = ttk.Label(title_section_1_2, text="\nPlease specify the required input values:\n")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        ttk.Label(title_section_1_2, text="cfl", borderwidth=2, relief="groove", anchor=CENTER).grid(row=1, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=1, column=1)

        ttk.Label(title_section_1_2, text="gamma", borderwidth=2, relief="groove", anchor=CENTER).grid(row=2, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=2, column=1)

        ttk.Label(title_section_1_2, text="mach", borderwidth=2, relief="groove", anchor=CENTER).grid(row=3, column=0, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=3, column=1)

        ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove", anchor=CENTER).grid(row=1, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=1, column=3)

        ttk.Label(title_section_1_2, text="Angle of attack (deg)", borderwidth=2, relief="groove", anchor=CENTER).grid(row=2, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=2, column=3)

        ttk.Label(title_section_1_2, text="Number of stages (RK)", borderwidth=2, relief="groove", anchor=CENTER).grid(row=3, column=2, sticky=NSEW)
        ttk.Entry(title_section_1_2, width=10).grid(row=3, column=3)

        # SECTION 2. SOLVER
        # SECTION 2.1 CONVERGENCE CRITERIA
        title_section_2_1 = ttk.LabelFrame(tab2, text="2.1 Convergence criteria", labelanchor=N, height=130, width=385)
        title_section_2_1.grid(row=0, column=0, columnspan=10)
        title_section_2_1.grid_propagate(False)

        text_section_2_1 = ttk.Label(title_section_2_1, text="\nPlease specify the required convergence criteria:\n")
        text_section_2_1.grid(row=0, column=0, columnspan=10, sticky=NSEW)

        ttk.Label(title_section_2_1, text="Max number of itterations", borderwidth=2, relief="groove", anchor=CENTER).grid(row=1, column=1, sticky=NSEW)
        ttk.Entry(title_section_2_1, width=18).grid(row=1, column=2)

        ttk.Label(title_section_2_1, text="Convergence criterion", borderwidth=2, relief="groove", anchor=CENTER).grid(row=2, column=1, sticky=NSEW)
        ttk.Entry(title_section_2_1, width=18).grid(row=2, column=2)

        # SECTION 2.2 SCHEME SELECTION
        title_section_2_2 = ttk.LabelFrame(tab2, text="2.2 Scheme Selection", labelanchor=N, height=130, width=385)
        title_section_2_2.grid(row=1, column=0)
        title_section_2_2.grid_propagate(False)

        text_section_2_2 = ttk.Label(title_section_2_2, text="\nPlease select the required flux scheme:\n")
        text_section_2_2.grid(row=0, column=0, columnspan=3, sticky=NSEW)

        flux_scheme = ttk.Button(title_section_2_2, text="Select flux scheme", command=self.selectFluxScheme)
        flux_scheme.grid(row=1, column=2, sticky=N)

        # SECTION 2.3 SOLVER OPTIONS
        title_section_2_3 = ttk.LabelFrame(tab2, text="2.3 Solver options", labelanchor=N, height=130, width=385)
        title_section_2_3.grid(row=2, column=0)
        title_section_2_3.grid_propagate(False)

        text_section_2_3 = ttk.Label(title_section_2_3, text="\nPlease select a code option:\n")
        text_section_2_3.grid(row=0, column=0, columnspan=3, sticky=NSEW)

        solver_option_1 = Radiobutton(title_section_2_3, text="Build the code", value=1, relief="groove", width=23, anchor=W)
        solver_option_1.grid(row=1, column=1, columnspan=2)

        solver_option_2 = Radiobutton(title_section_2_3, text="Execute the code", value=2, relief="groove", width=23, anchor=W)
        solver_option_2.grid(row=2, column=1, columnspan=2)

        solver_option_3 = Radiobutton(title_section_2_3, text="Build and execute the code", value=3, relief="groove", width=23, anchor=W)
        solver_option_3.grid(row=3, column=1, columnspan=2)

        # SECTION 3 OUTPUT
        text_section_3 = ttk.Label(tab3, text="\nPlease specify what type of graphe(s) you would like to\ndisplay:\n")
        text_section_3.grid(row=0, column=0, columnspan=3, sticky=NSEW)

        cl_alpha = Checkbutton(tab3, text="Cl vs alpha", relief="groove", width=20, anchor=W)
        cl_alpha.grid(row=1, column=0)
        cl_alpha.grid_propagate(False)

        cd_alpha = Checkbutton(tab3, text="Cd vs alpha", relief="groove", width=20, anchor=W)
        cd_alpha.grid(row=2, column=0)
        cd_alpha.grid_propagate(False)

        cm_alpha = Checkbutton(tab3, text="Cm vs alpha", relief="groove", width=20, anchor=W)
        cm_alpha.grid(row=3, column=0)
        cm_alpha.grid_propagate(False)

        cl_convergence = Checkbutton(tab3, text="Cl convergence", relief="groove", width=20, anchor=W)
        cl_convergence.grid(row=4, column=0)
        cl_convergence.grid_propagate(False)

        cd_convergence = Checkbutton(tab3, text="Cd convergence", relief="groove", width=20, anchor=W)
        cd_convergence.grid(row=5, column=0)
        cd_convergence.grid_propagate(False)

        cm_convergence = Checkbutton(tab3, text="Cm convergence", relief="groove", width=20, anchor=W)
        cm_convergence.grid(row=6, column=0)
        cm_convergence.grid_propagate(False)

        residual_convergence = Checkbutton(tab3, text="Residual convergence", relief="groove", width=20, anchor=W)
        residual_convergence.grid(row=7, column=0)
        residual_convergence.grid_propagate(False)

        cp_xc = Checkbutton(tab3, text="Cp vs Xc", relief="groove", width=20, anchor=W)
        cp_xc.grid(row=1, column=1, columnspan=2)
        cp_xc.grid_propagate(False)

        mach_contour = Checkbutton(tab3, text="Mach contour", relief="groove", width=20, anchor=W)
        mach_contour.grid(row=2, column=1, columnspan=2)
        mach_contour.grid_propagate(False)

        cp_contour = Checkbutton(tab3, text="Cp contour", relief="groove", width=20, anchor=W)
        cp_contour.grid(row=3, column=1, columnspan=2)
        cp_contour.grid_propagate(False)

        slice_cp = Checkbutton(tab3, text="Slice Cp", relief="groove", width=20, anchor=W)
        slice_cp.grid(row=4, column=1, columnspan=2)
        slice_cp.grid_propagate(False)

        ttk.Label(tab3, text="Axis of cut", relief="groove", state="disabled").grid(row=5, column=1, sticky=NSEW)
        ttk.Entry(tab3, width=8, state="disabled").grid(row=5, column=2)
        
        ttk.Label(tab3, text="X coord", relief="groove", state="disabled").grid(row=6, column=1, sticky=NSEW)
        ttk.Entry(tab3, width=8, state="disabled").grid(row=6, column=2)
        
        ttk.Label(tab3, text="Y coord", relief="groove", state="disabled").grid(row=7, column=1, sticky=NSEW)
        ttk.Entry(tab3, width=8, state="disabled").grid(row=7, column=2)
        
        ttk.Label(tab3, text="Z coord", relief="groove", state="disabled").grid(row=8, column=1, sticky=NSEW)
        ttk.Entry(tab3, width=8, state="disabled").grid(row=8, column=2)

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
        
        self.flux_scheme = ttk.Combobox(self.flux_scheme_window, width=15)
        self.flux_scheme['values'] = ("Roe", "Ausm")
        self.flux_scheme.grid(row=1, column=1)

        self.scheme_order = ttk.Combobox(self.flux_scheme_window, width=15)
        self.scheme_order['values'] = ("1", "2")
        self.scheme_order.grid(row=2, column=1)
        
        ttk.Button(self.flux_scheme_window, text="Ok", command=self.flux_scheme_window.destroy).grid(row=3, column=1)
        ttk.Button(self.flux_scheme_window, text="Cancel", command=self.flux_scheme_window.destroy).grid(row=3, column=2)


root = Tk()
main_window = MainWindow(root)
root.mainloop() #Mainloop allows you to be display the window continuously until you close it