import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog

class Input():
    def __init__(self, master):
        self.master = master

        # SECTION 1.1: GEOMETRY AND MESH
        title_section_1_1 = LabelFrame(master, text="1.1 Geometry and mesh", labelanchor=N, height=215, width=396)
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

        # SECTION 1.2: INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(master, text="1.2 Input parameters", labelanchor=N, height=215, width=396)
        title_section_1_2.grid(row=1, column=0, columnspan=3)
        title_section_1_2.grid_propagate(False)

        text_section_1_2 = ttk.Label(title_section_1_2, text="\n\nPlease specify the required input values:\n")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky=NSEW, padx=2)

        self.cfl_entry = DoubleVar()
        cfl_label = ttk.Label(title_section_1_2, text="cfl", borderwidth=2, relief="groove", anchor=CENTER)
        cfl_label.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.cfl_entry, width=10).grid(row=1, column=1, padx=2, pady=2)

        self.gamma_entry = DoubleVar()
        gamma_label = ttk.Label(title_section_1_2, text="gamma", borderwidth=2, relief="groove", anchor=CENTER)
        gamma_label.grid(row=2, column=0, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.gamma_entry, width=10).grid(row=2, column=1, padx=2, pady=2)

        self.mach_entry = DoubleVar()
        mach_label = ttk.Label(title_section_1_2, text="mach", borderwidth=2, relief="groove", anchor=CENTER)
        mach_label.grid(row=3, column=0, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.mach_entry, width=10).grid(row=3, column=1, padx=2, pady=2)

        self.cmac_entry = DoubleVar()
        cmac_label = ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove", anchor=CENTER)
        cmac_label.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.cmac_entry, width=10).grid(row=1, column=3, padx=2, pady=2)

        self.angle_attack_entry = DoubleVar()
        angle_attack_label = ttk.Label(title_section_1_2, text="Angle of attack (deg)", borderwidth=2, relief="groove", anchor=CENTER)
        angle_attack_label.grid(row=2, column=2, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.angle_attack_entry, width=10).grid(row=2, column=3, padx=2, pady=2)

        self.rk_entry = DoubleVar()
        rk_label = ttk.Label(title_section_1_2, text="Number of stages (RK)", borderwidth=2, relief="groove", anchor=CENTER)
        rk_label.grid(row=3, column=2, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_1_2, textvariable=self.rk_entry, width=10).grid(row=3, column=3, padx=2, pady=2)

        # GENERAL BUTTONS
        ttk.Button(master, text="Clear all").grid(row=2, column=0, padx=2, pady=2)
        ttk.Button(master, text="Clear this page").grid(row=2, column=1, padx=2, pady=2)
        ttk.Button(master, text="Solve").grid(row=2, column=2, padx=2, pady=2)

    # METHODS
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

    def writePartialOutput(self):
        cfl_str = str(self.cfl_entry.get())
        gamma_str = str(self.gamma_entry.get())
        angleattackdeg_str = str(self.angle_attack_entry.get())
        rk_str = str(self.rk_entry.get())
        mach_str = str(self.mach_entry.get())
        cmac_str = str(self.cmac_entry.get())

        partial_output = "INPUT\ncfl gamma angleattackdeg\n"+(
                        cfl_str+" "+gamma_str+" "+angleattackdeg_str)+(
                        "\nrkstage mach cmac\n")+(
                        rk_str+" "+mach_str+" "+cmac_str)                        
        
        return partial_output