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
        text_section_1_1.grid(row=0, column=0, columnspan=3, sticky=NSEW, padx=2)

        import_mesh = Button(title_section_1_1, text="Import mesh", command=self.importMesh, anchor=CENTER)
        import_mesh.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)

        import_geometry = Button(title_section_1_1, text="Import\ngeometry", command=self.importGeometry, anchor=CENTER)
        import_geometry.grid(row=1, column=1, sticky=NSEW, padx=2, pady=2)
        
        generate_geometry = Button(title_section_1_1, text="Generate\ngeometry", command=self.generateGeometry, anchor=CENTER)
        generate_geometry.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)

        show_resulting_mesh = Button(title_section_1_1, text="Show resulting\nmesh", command=self.showResultingMesh, anchor=CENTER)
        show_resulting_mesh.grid(row=2, column=1, sticky=NSEW, padx=2, pady=2)

        # SECTION 1.2: INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(master, text="1.2 Input parameters", labelanchor=N, height=215, width=396)
        title_section_1_2.grid(row=1, column=0, columnspan=3)
        title_section_1_2.grid_propagate(False)

        text_section_1_2 = ttk.Label(title_section_1_2, text="\n\nPlease specify the required input values:\n")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky=NSEW, padx=2)

        self.cfl = DoubleVar()
        self.cfl.set(7.5)
        self.cfl_label = ttk.Label(title_section_1_2, text="cfl", borderwidth=2, relief="groove", anchor=CENTER)
        self.cfl_label.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)
        self.cfl_entry = ttk.Entry(title_section_1_2, textvariable=self.cfl, width=10)
        self.cfl_entry.grid(row=1, column=1, padx=2, pady=2)

        self.gamma = DoubleVar()
        self.gamma.set(1.4)
        self.gamma_label = ttk.Label(title_section_1_2, text="gamma", borderwidth=2, relief="groove", anchor=CENTER)
        self.gamma_label.grid(row=2, column=0, sticky=NSEW, padx=2, pady=2)
        self.gamma_entry = ttk.Entry(title_section_1_2, textvariable=self.gamma, width=10)
        self.gamma_entry.grid(row=2, column=1, padx=2, pady=2)

        self.mach = DoubleVar()
        self.mach.set(0.8)
        self.mach_label = ttk.Label(title_section_1_2, text="mach", borderwidth=2, relief="groove", anchor=CENTER)
        self.mach_label.grid(row=3, column=0, sticky=NSEW, padx=2, pady=2)
        self.mach_entry = ttk.Entry(title_section_1_2, textvariable=self.mach, width=10)
        self.mach_entry.grid(row=3, column=1, padx=2, pady=2)

        self.cmac = DoubleVar()
        self.cmac.set(1.0)
        self.cmac_label = ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove", anchor=CENTER)
        self.cmac_label.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)
        self.cmac_entry = ttk.Entry(title_section_1_2, textvariable=self.cmac, width=10)
        self.cmac_entry.grid(row=1, column=3, padx=2, pady=2)

        self.angle_attack = DoubleVar()
        self.angle_attack.set(0.0)
        self.angle_attack_label = ttk.Label(title_section_1_2, text="Angle of attack (deg)", borderwidth=2, relief="groove", anchor=CENTER)
        self.angle_attack_label.grid(row=2, column=2, sticky=NSEW, padx=2, pady=2)
        self.angle_attack_entry = ttk.Entry(title_section_1_2, textvariable=self.angle_attack, width=10)
        self.angle_attack_entry.grid(row=2, column=3, padx=2, pady=2)

        self.rk = IntVar()
        self.rk.set(5)
        self.rk_label = ttk.Label(title_section_1_2, text="Number of stages (RK)", borderwidth=2, relief="groove", anchor=CENTER)
        self.rk_label.grid(row=3, column=2, sticky=NSEW, padx=2, pady=2)
        self.rk_entry = ttk.Entry(title_section_1_2, textvariable=self.rk, width=10)
        self.rk_entry.grid(row=3, column=3, padx=2, pady=2)

        self.filename_mesh = "void"
 
    # METHODS
    def importMesh(self):
        self.mesh_window = Toplevel(self.master)
        self.mesh_window.title("Mesh importation")
        self.mesh_window.resizable(0,0)
        self.mesh_window.lift()

        text_mesh_importation = ttk.Label(self.mesh_window, text="\nImport the desired mesh:\n")
        text_mesh_importation.grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        
        select_file_button = ttk.Button(self.mesh_window, text="Select a file", command=self.meshFileDialog)
        select_file_button.grid(row=1, column=0, padx=2)
        
        self.filename_label_mesh = ttk.Label(self.mesh_window, text="", relief="solid", width=40)
        self.filename_label_mesh.grid(row=1, column=1, columnspan=3, padx=2)
        
        ok_button = ttk.Button(self.mesh_window, text="Ok", command=self.saveAndDestroyWindow)
        ok_button.grid(row=2, column=1, pady=5)

        cancel_button = ttk.Button(self.mesh_window, text="Cancel", command=self.mesh_window.destroy)
        cancel_button.grid(row=2, column=2, pady=5)

    def meshFileDialog(self):
        self.filename_mesh = filedialog.askopenfilename(initialdir="/home/etudiant/", title="Select a file", filetypes=(("SU2", "*.su2"),("All Files", "*.*")))

        if self.filename_mesh=="":
            self.filename_label_mesh.configure(text="")
        
        elif self.filename_mesh.endswith('.su2'):
            self.filename_label_mesh.configure(text=self.filename_mesh)
        else:
            messagebox.showwarning("Warning", "Chosen mesh file must be a SU2 file!")
            self.filename_label_mesh.configure(text=self.filename_mesh)
        
    def importGeometry(self):
        geometry_window = Toplevel(self.master)
        geometry_window.title("Geometry importation")
        geometry_window.resizable(0,0)
        geometry_window.lift()

        text_geometry_importation = ttk.Label(geometry_window, text="\nImport the desired geometry:\n")
        text_geometry_importation.grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        
        select_file_button = ttk.Button(geometry_window, text="Select a file", command=self.geometryFileDialog)
        select_file_button.grid(row=1, column=0, padx=2)
        
        self.filename_label_geometry = ttk.Label(geometry_window, text="", relief="solid", width=40)
        self.filename_label_geometry.grid(row=1, column=1, columnspan=3, padx=2)

        self.number_blocks = IntVar()
        self.number_blocks.set(3)
        self.number_blocks_label = ttk.Label(geometry_window, text="Number of blocks", borderwidth=2, relief="groove", anchor=CENTER)
        self.number_blocks_label.grid(row=2, column=1, sticky=NSEW, pady=5)
        self.number_blocks_entry = ttk.Entry(geometry_window, width=15, textvariable=self.number_blocks)
        self.number_blocks_entry.grid(row=2, column=2, pady=5)

        ok_button = ttk.Button(geometry_window, text="Ok", command=geometry_window.destroy)
        ok_button.grid(row=3, column=1, pady=5)
        cancel_button = ttk.Button(geometry_window, text="Cancel", command=geometry_window.destroy)
        cancel_button.grid(row=3, column=2, pady=5)

    def geometryFileDialog(self):
        self.filename_geometry = filedialog.askopenfilename(initialdir="/home/etudiant/", title="Select a file", filetypes=(("csm", "*.csm"),("All Files", "*.*")))
        
        if self.filename_geometry=="":
            self.filename_label_geometry.configure(text="")
        
        elif self.filename_geometry.endswith('.csm'):
            self.filename_label_geometry.configure(text=self.filename_geometry)
        
        else:
            messagebox.showwarning("Warning", "Chosen geometry file must be a csm file!")
            self.filename_label_geometry.configure(text=self.filename_geometry)

    def generateGeometry(self):
        messagebox.askokcancel('Geometry Generation', 'Specify the needed information for geometry generation:')

    def showResultingMesh(self):
        messagebox.showinfo('Resulting Mesh')

    def saveAndDestroyWindow(self):
        self.writePartialOutputMesh()
        self.mesh_window.destroy()

    def clearAllPages(self):
        self.cfl.set(0.0)
        self.gamma.set(0.0)
        self.mach.set(0.0)
        self.cmac.set(0.0)
        self.angle_attack.set(0.0)
        self.rk.set(0)
    
    def clearPage(self):
        self.cfl.set(0.0)
        self.gamma.set(0.0)
        self.mach.set(0.0)
        self.cmac.set(0.0)
        self.angle_attack.set(0.0)
        self.rk.set(0)

    def writePartialOutputMesh(self):
        
        self.partial_output_mesh = "MESH\ntopologyfilename\n" + self.filename_mesh

        return self.partial_output_mesh

    def writePartialOutput(self):
        cfl_str = str(self.cfl.get())
        gamma_str = str(self.gamma.get())
        angle_attack_str = str(self.angle_attack.get())
        rk_str = str(self.rk.get())
        mach_str = str(self.mach.get())
        cmac_str = str(self.cmac.get())

        if 'self.partial_output_mesh' in globals():
            partial_output = self.partial_output_mesh + (
                            "\nINPUT\ncfl gamma angleattackdeg\n" + cfl_str + " " + gamma_str + " " + angle_attack_str) + (
                            "\nrkstage mach cmac\n" + rk_str + " " + mach_str + " " + cmac_str)                        
        else:
            partial_output = "MESH\ntopologyfilename\n" + self.filename_mesh + (
                            "\nINPUT\ncfl gamma angleattackdeg\n" + cfl_str + " " + gamma_str + " " + angle_attack_str) + (
                            "\nrkstage mach cmac\n" + rk_str + " " + mach_str + " " + cmac_str)  
        
        return partial_output