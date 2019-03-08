import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class Interface():
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
        title_section_1_1 = LabelFrame(tab1, text="1.1 Geometry and mesh", labelanchor=N, height=215, width=396)
        title_section_1_1.grid(row=0, column=0, columnspan=3)
        title_section_1_1.grid_propagate(False)

        text_section_1_1 = ttk.Label(title_section_1_1, text="\n\nPlease select the desired mesh or geometry:\n")
        text_section_1_1.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)

        import_mesh = ttk.Button(title_section_1_1, text="Import mesh", command=self.importMesh)
        import_mesh.grid(row=1, column=1, sticky=NSEW, padx=2, pady=2)

        import_geometry = ttk.Button(title_section_1_1, text="Import geometry", command=self.importGeometry)
        import_geometry.grid(row=1, column=3, sticky=NSEW, padx=2, pady=2)
        
        generate_geometry = ttk.Button(title_section_1_1, text="Generate geometry", command=self.generateGeometry)
        generate_geometry.grid(row=1, column=5, sticky=NSEW, padx=2, pady=2)

        show_resulting_mesh = ttk.Button(title_section_1_1, text="Show resulting mesh", command=self.showResultingMesh)
        show_resulting_mesh.grid(row=2, column=3, sticky=NSEW, padx=2, pady=2)

        # SECTION 1.2 INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(tab1, text="1.2 Input parameters", labelanchor=N, height=215, width=396)
        title_section_1_2.grid(row=1, column=0, columnspan=3)
        title_section_1_2.grid_propagate(False)

        text_section_1_2 = ttk.Label(title_section_1_2, text="\n\nPlease specify the required input values:\n")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky=NSEW, padx=2)

        cfl_label = ttk.Label(title_section_1_2, text="cfl", borderwidth=2, relief="groove", anchor=CENTER)
        cfl_label.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)
        cfl_entry = ttk.Entry(title_section_1_2, width=10)
        cfl_entry.grid(row=1, column=1, padx=2, pady=2)

        gamma_label = ttk.Label(title_section_1_2, text="gamma", borderwidth=2, relief="groove", anchor=CENTER)
        gamma_label.grid(row=2, column=0, sticky=NSEW, padx=2, pady=2)
        gamma_entry = ttk.Entry(title_section_1_2, width=10)
        gamma_entry.grid(row=2, column=1, padx=2, pady=2)

        mach_label = ttk.Label(title_section_1_2, text="mach", borderwidth=2, relief="groove", anchor=CENTER)
        mach_label.grid(row=3, column=0, sticky=NSEW, padx=2, pady=2)
        mach_entry = ttk.Entry(title_section_1_2, width=10)
        mach_entry.grid(row=3, column=1, padx=2, pady=2)

        cmac_label = ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove", anchor=CENTER)
        cmac_label.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)
        cmac_entry = ttk.Entry(title_section_1_2, width=10)
        cmac_entry.grid(row=1, column=3, padx=2, pady=2)

        angle_attack_label = ttk.Label(title_section_1_2, text="Angle of attack (deg)", borderwidth=2, relief="groove", anchor=CENTER)
        angle_attack_label.grid(row=2, column=2, sticky=NSEW, padx=2, pady=2)
        angle_attack_entry = ttk.Entry(title_section_1_2, width=10)
        angle_attack_entry.grid(row=2, column=3, padx=2, pady=2)

        rk_label = ttk.Label(title_section_1_2, text="Number of stages (RK)", borderwidth=2, relief="groove", anchor=CENTER)
        rk_label.grid(row=3, column=2, sticky=NSEW, padx=2, pady=2)
        rk_entry = ttk.Entry(title_section_1_2, width=10)
        rk_entry.grid(row=3, column=3, padx=2, pady=2)

        # SECTION 1 GENERAL BUTTONS
        ttk.Button(tab1, text="Clear all").grid(row=2, column=0, padx=2, pady=2)
        ttk.Button(tab1, text="Clear this page").grid(row=2, column=1, padx=2, pady=2)
        ttk.Button(tab1, text="Solve").grid(row=2, column=2, padx=2, pady=2)

        # SECTION 2. SOLVER
        # SECTION 2.1 CONVERGENCE CRITERIA
        title_section_2_1 = ttk.LabelFrame(tab2, text="2.1 Convergence criteria", labelanchor=N, height=130, width=396)
        title_section_2_1.grid(row=0, column=0, columnspan=3)
        title_section_2_1.grid_propagate(False)

        text_section_2_1 = ttk.Label(title_section_2_1, text="\nPlease specify the required convergence criteria:\n")
        text_section_2_1.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)

        ttk.Label(title_section_2_1, text="", width=5).grid(row=1, column=0)

        max_iter_label = ttk.Label(title_section_2_1, text="Max number of itterations", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        max_iter_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        max_iter_entry = ttk.Entry(title_section_2_1, width=15)
        max_iter_entry.grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        ttk.Label(title_section_2_1, text="", width=4).grid(row=1, column=5)

        convergence_crit_label = ttk.Label(title_section_2_1, text="Convergence criterion", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        convergence_crit_label.grid(row=2, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        convergence_crit_entry = ttk.Entry(title_section_2_1, width=15)
        convergence_crit_entry.grid(row=2, column=3, columnspan=2, padx=2, pady=2)

        # SECTION 2.2 SCHEME SELECTION
        title_section_2_2 = ttk.LabelFrame(tab2, text="2.2 Scheme Selection", labelanchor=N, height=110, width=396)
        title_section_2_2.grid(row=1, column=0, columnspan=3)
        title_section_2_2.grid_propagate(False)

        text_section_2_2 = ttk.Label(title_section_2_2, text="\nPlease select the required flux scheme:\n")
        text_section_2_2.grid(row=0, column=0, columnspan=3, sticky=NSEW, padx=2)

        ttk.Label(title_section_2_2, text="", width=12).grid(row=1, column=0)

        flux_scheme = ttk.Button(title_section_2_2, text="Select flux scheme", command=self.selectFluxScheme, width=23)
        flux_scheme.grid(row=1, column=1, sticky=NSEW)

        ttk.Label(title_section_2_2, text="", width=4).grid(row=1, column=2)

        # SECTION 2.3 SOLVER OPTIONS
        title_section_2_3 = ttk.LabelFrame(tab2, text="2.3 Solver options", labelanchor=N, height=190, width=396)
        title_section_2_3.grid(row=2, column=0, columnspan=3)
        title_section_2_3.grid_propagate(False)

        text_section_2_3 = ttk.Label(title_section_2_3, text="\nPlease select a code option:\n")
        text_section_2_3.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)
        
        ttk.Label(title_section_2_3, text="", width=5).grid(row=1, column=0)
        
        ttk.Label(title_section_2_3, text="Number of process", relief="groove", borderwidth=2, anchor=CENTER, width=22).grid(row=1, column=1, columnspan=2, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_2_3, width=15).grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        ttk.Label(title_section_2_3, text="", width=4).grid(row=1, column=5)
        
        solver_option_build = Radiobutton(title_section_2_3, text="Build the code", value=1, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build.grid(row=2, column=1, columnspan=4, padx=2, pady=2)

        solver_option_execute = Radiobutton(title_section_2_3, text="Execute the code", value=2, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_execute.grid(row=3, column=1, columnspan=4, padx=2, pady=2)

        solver_option_build_execute = Radiobutton(title_section_2_3, text="Build and execute the code", value=3, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build_execute.grid(row=4, column=1, columnspan=4, padx=2, pady=2)

        # SECTION 2 GENERAL BUTTONS
        ttk.Button(tab2, text="Clear all").grid(row=3, column=0, padx=2, pady=2)
        ttk.Button(tab2, text="Clear this page").grid(row=3, column=1, padx=2, pady=2)
        ttk.Button(tab2, text="Solve").grid(row=3, column=2, padx=2, pady=2)

        # SECTION 3 OUTPUT
        self.output = Output(tab3)

    # SECTION 1 METHODS
    def importMesh(self):
        self.mesh_window = Tk()
        self.mesh_window.title("Mesh importation")
        ttk.Label(self.mesh_window, text="\nImport the desired mesh:\n").grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        
        ttk.Button(self.mesh_window, text="Select a file", command=self.meshFileDialog).grid(row=1, column=0, padx=2)
        
        self.label = ttk.Label(self.mesh_window, text="", relief="solid", width=40)
        self.label.grid(row=1, column=1, columnspan=3, padx=2)
        
        ttk.Button(self.mesh_window, text="Ok", command=self.mesh_window.destroy).grid(row=2, column=1, pady=5)
        ttk.Button(self.mesh_window, text="Cancel", command=self.mesh_window.destroy).grid(row=2, column=2, pady=5)

    def meshFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label.configure(text=self.filename)

    def importGeometry(self):
        self.geometry_window = Tk()
        self.geometry_window.title("Geometry importation")
        ttk.Label(self.geometry_window, text="\nImport the desired geometry:\n").grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        
        ttk.Button(self.geometry_window, text="Select a file", command=self.geometryFileDialog).grid(row=1, column=0, padx=2)
        
        self.label = ttk.Label(self.geometry_window, text="", relief="solid", width=40)
        self.label.grid(row=1, column=1, columnspan=3, padx=2)

        ttk.Label(self.geometry_window, text="Number of blocks", borderwidth=2, relief="groove", anchor=CENTER).grid(row=2, column=1, sticky=NSEW, pady=5)
        ttk.Entry(self.geometry_window, width=15).grid(row=2, column=2, pady=5)

        ttk.Button(self.geometry_window, text="Ok", command=self.geometry_window.destroy).grid(row=3, column=1, pady=5)
        ttk.Button(self.geometry_window, text="Cancel", command=self.geometry_window.destroy).grid(row=3, column=2, pady=5)

    def geometryFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label.configure(text=self.filename)

    def generateGeometry(self):
        messagebox.askokcancel('Geometry Generation', 'Specify the needed information for geometry generation:')

    def showResultingMesh(self):
        messagebox.showinfo('Resulting Mesh')
    
    # SECTION 2 METHODS
    def selectFluxScheme(self):
        self.flux_scheme_window = Tk()
        self.flux_scheme_window.title("Scheme selection")
        ttk.Label(self.flux_scheme_window, text="\nPlease configure the following parameters:\n", anchor=W).grid(row=0, column=0, columnspan=4, padx=2, sticky=W)
        
        self.flux_scheme_label = ttk.Label(self.flux_scheme_window, text="Flux scheme:", anchor=CENTER)
        self.flux_scheme_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.flux_scheme_entry = ttk.Combobox(self.flux_scheme_window, values=("Roe", "Ausm"), width=15)
        self.flux_scheme_entry.grid(row=2, column=1, columnspan=2, pady=2)
        
        self.scheme_order_label = ttk.Label(self.flux_scheme_window, text="Scheme order:", anchor=CENTER)
        self.scheme_order_label.grid(row=3, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.scheme_order_entry = ttk.Combobox(self.flux_scheme_window, values=("1", "2"), width=15)
        self.scheme_order_entry.grid(row=4, column=1, columnspan=2, pady=2)
        self.scheme_order_entry.bind('<<ComboboxSelected>>', self.activateGradientAndLimiter)
        
        self.gradient_label = ttk.Label(self.flux_scheme_window, text="Gradient:", anchor=CENTER, state="disabled")
        self.gradient_label.grid(row=5, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.gradient_entry = ttk.Combobox(self.flux_scheme_window, values=("Green Gauss", "Least Squares"), width=15, state="disabled")
        self.gradient_entry.grid(row=6, column=1, columnspan=2, pady=2)

        self.limiter_label = ttk.Label(self.flux_scheme_window, text="Limiter:", anchor=CENTER, state="disabled")
        self.limiter_label.grid(row=7, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.limiter_entry = ttk.Combobox(self.flux_scheme_window, values=("Barth Jespersen", "Venkatakrishnan"), width=15, state="disabled")
        self.limiter_entry.grid(row=8, column=1, columnspan=2, pady=2)
        self.limiter_entry.bind('<<ComboboxSelected>>', self.activateOmegaOrK)

        self.omega_label = ttk.Label(self.flux_scheme_window, text="Omega", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.omega_label.grid(row=9, column=0, padx=2, pady=7)
        self.omega_entry = ttk.Entry(self.flux_scheme_window, width=10, state="disabled")
        self.omega_entry.grid(row=9, column=1, padx=2, pady=10)

        self.k_label = ttk.Label(self.flux_scheme_window, text="k", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.k_label.grid(row=9, column=2, padx=2, pady=7)
        self.k_entry = ttk.Entry(self.flux_scheme_window, width=10, state="disabled")
        self.k_entry.grid(row=9, column=3, padx=2, pady=10)

        ttk.Label(self.flux_scheme_window, text="Residual smoothing?", anchor=CENTER).grid(row=10, column=1, columnspan=2, padx=2)
        
        self.smoothing_yes = Radiobutton(self.flux_scheme_window, text="Yes", value=1, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_yes.grid(row=11, column=1, columnspan=2, padx=2, pady=2)

        self.smoothing_no = Radiobutton(self.flux_scheme_window, text="No", value=2, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_no.grid(row=12, column=1, columnspan=2, padx=2, pady=2)

        ttk.Button(self.flux_scheme_window, text="Ok", command=self.flux_scheme_window.destroy).grid(row=13, column=1, pady=10)
        ttk.Button(self.flux_scheme_window, text="Cancel", command=self.flux_scheme_window.destroy).grid(row=13, column=2, pady=10)
    
    def activateGradientAndLimiter(self, event):
        scheme_order_result = self.scheme_order_entry.get()

        if scheme_order_result == "2":
            self.gradient_label.configure(state="Normal")
            self.gradient_entry.configure(state="Normal")

            self.limiter_label.configure(state="Normal")
            self.limiter_entry.configure(state="Normal")

    def activateOmegaOrK(self, event):
        limiter_result = self.limiter_entry.get()
        
        if limiter_result == "Barth Jespersen":
            self.omega_label.configure(state="Normal")
            self.omega_entry.configure(state="Normal")
            self.k_label.configure(state="Disabled")
            self.k_entry.configure(state="Disabled")

        elif limiter_result == "Venkatakrishnan":
            self.k_label.configure(state="Normal")
            self.k_entry.configure(state="Normal")
            self.omega_label.configure(state="Disabled")
            self.omega_entry.configure(state="Disabled")

    # SECTION 3 METHODS
    def activateAxisOfCut(self):
        slice_cp_result = self.slice_cp.get()

        if slice_cp_result == 1:
            self.axis_cut_label.configure(state="Normal")
            self.axis_cut_entry.configure(state="Normal")
            self.x_coord_label.configure(state="Normal")
            self.x_coord_entry.configure(state="Normal")
            self.y_coord_label.configure(state="Normal")
            self.y_coord_entry.configure(state="Normal")
            self.z_coord_label.configure(state="Normal")
            self.z_coord_entry.configure(state="Normal")

        elif slice_cp_result == 0:
            self.axis_cut_label.configure(state="Disabled")
            self.axis_cut_entry.configure(state="Disabled")
            self.x_coord_label.configure(state="Disabled")
            self.x_coord_entry.configure(state="Disabled")
            self.y_coord_label.configure(state="Disabled")
            self.y_coord_entry.configure(state="Disabled")
            self.z_coord_label.configure(state="Disabled")
            self.z_coord_entry.configure(state="Disabled")

    # # GENERAL BUTTONS
    # def clearAll(self):
    #     #commandes....


class Output(Interface):
    def __init__(self, master):
        self.master = master
        
        #SECTION 3 OUTPUT
        title_section_3 = ttk.LabelFrame(master, text="", labelanchor=N, height=430, width=396)
        title_section_3.grid(row=0, column=0, columnspan=3)
        title_section_3.grid_propagate(False)
            
        text_section_3 = ttk.Label(title_section_3, text="\n\n\n\nPlease specify what type of graphe(s) you would like to\ndisplay:\n")
        text_section_3.grid(row=0, column=0, columnspan=3, sticky=NSEW)

        cl_alpha = IntVar()
        Checkbutton(title_section_3, text="Cl vs alpha", variable=cl_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=1, column=0, padx=2, pady=2)
            
        cd_alpha = IntVar()
        Checkbutton(title_section_3, text="Cd vs alpha", variable=cd_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=2, column=0, padx=2, pady=2)

        cm_alpha = IntVar()
        Checkbutton(title_section_3, text="Cm vs alpha", variable=cm_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=3, column=0, padx=2, pady=2)

        cl_convergence = IntVar()
        Checkbutton(title_section_3, text="Cl convergence", variable=cl_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=4, column=0, padx=2, pady=2)

        cd_convergence = IntVar()
        Checkbutton(title_section_3, text="Cd convergence", variable=cd_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=5, column=0, padx=2, pady=2)

        cm_convergence = IntVar()
        Checkbutton(title_section_3, text="Cm convergence", variable=cm_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=6, column=0, padx=2, pady=2)

        residual_convergence = IntVar()
        Checkbutton(title_section_3, text="Residual convergence", variable=residual_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=7, column=0, padx=2, pady=2)

        cp_xc = IntVar()
        Checkbutton(title_section_3, text="Cp vs Xc", variable=cp_xc, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=1, column=1, columnspan=2, padx=2, pady=2)

        mach_contour = IntVar()
        Checkbutton(title_section_3, text="Mach contour", variable=mach_contour, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=2, column=1, columnspan=2, padx=2, pady=2)

        cp_contour = IntVar()
        Checkbutton(title_section_3, text="Cp contour", variable=cp_contour, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=3, column=1, columnspan=2, padx=2, pady=2)

        self.slice_cp = IntVar()
        Checkbutton(title_section_3, text="Slice Cp", variable=self.slice_cp, command=self.activateAxisOfCut, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=4, column=1, columnspan=2, padx=2, pady=2)

        self.axis_cut_label = ttk.Label(title_section_3, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.axis_cut_label.grid(row=5, column=1)
        self.axis_cut_entry = ttk.Entry(title_section_3, width=11, state="disabled")
        self.axis_cut_entry.grid(row=5, column=2, padx=2, pady=2)
            
        self.x_coord_label = ttk.Label(title_section_3, text="X coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.x_coord_label.grid(row=6, column=1)
        self.x_coord_entry = ttk.Entry(title_section_3, width=11, state="disabled")
        self.x_coord_entry.grid(row=6, column=2, padx=2, pady=2)
            
        self.y_coord_label = ttk.Label(title_section_3, text="Y coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.y_coord_label.grid(row=7, column=1)
        self.y_coord_entry = ttk.Entry(title_section_3, width=11, state="disabled")
        self.y_coord_entry.grid(row=7, column=2, padx=2, pady=2)
            
        self.z_coord_label = ttk.Label(title_section_3, text="Z coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.z_coord_label.grid(row=8, column=1)
        self.z_coord_entry = ttk.Entry(title_section_3, width=11, state="disabled")
        self.z_coord_entry.grid(row=8, column=2, padx=2, pady=2)

        # SECTION 3 GENERAL BUTTONS
        ttk.Button(master, text="Clear all").grid(row=1, column=0, padx=2, pady=2)
        ttk.Button(master, text="Clear this page").grid(row=1, column=1, padx=2, pady=2)
        ttk.Button(master, text="Solve").grid(row=1, column=2, padx=2, pady=2)

root = Tk()
main_window = Interface(root)
root.mainloop()