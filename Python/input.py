import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
import os
import os.path
import shutil


class Input():
    def __init__(self, master):
        self.master = master

        # SECTION 1.1: GEOMETRY AND MESH
        title_section_1_1 = LabelFrame(master, text="1.1 Geometry and mesh", labelanchor=N, height=230, width=396)
        title_section_1_1.grid(row=0, column=0, columnspan=3)
        title_section_1_1.grid_propagate(False)
        title_section_1_1.grid_columnconfigure(0, weight=1)
        title_section_1_1.grid_columnconfigure(1, weight=1)
        title_section_1_1.grid_columnconfigure(2, weight=1)

        text_section_1_1 = ttk.Label(title_section_1_1, text="\n\nPlease select the desired mesh or geometry:\n")
        text_section_1_1.grid(row=0, column=0, columnspan=3, sticky=NSEW, padx=2)

        import_mesh = Button(title_section_1_1, text=" Import \n  mesh  ", command=self.importMesh, anchor=CENTER, takefocus=0)
        import_mesh.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)

        import_geometry = Button(title_section_1_1, text="Import\ngeometry", command=self.importGeometry, anchor=CENTER, takefocus=0)
        import_geometry.grid(row=1, column=1, sticky=NSEW, padx=2, pady=2)
        
        generate_geometry = Button(title_section_1_1, text="Generate\ngeometry", command=self.generateGeometry, anchor=CENTER, takefocus=0)
        generate_geometry.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)

        show_resulting_mesh = Button(title_section_1_1, text="Show resulting\nmesh", command=self.showResultingMesh, anchor=CENTER, takefocus=0)
        show_resulting_mesh.grid(row=2, column=1, sticky=NSEW, padx=2, pady=2)

        # SECTION 1.2: INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(master, text="1.2 Input parameters", labelanchor=N, height=230, width=396)
        title_section_1_2.grid(row=1, column=0, columnspan=3)
        title_section_1_2.grid_propagate(False)
        title_section_1_2.grid_columnconfigure(1, weight=1)
        title_section_1_2.grid_columnconfigure(3, weight=1)

        text_section_1_2 = ttk.Label(title_section_1_2, text="\n\nPlease specify the required input values:\n")
        text_section_1_2.grid(row=0, column=0, columnspan=4, sticky=NSEW, padx=2)

        self.cfl = DoubleVar()
        self.cfl.set(7.5)
        self.cfl_label = ttk.Label(title_section_1_2, text="     cfl     ", borderwidth=2, relief="groove", anchor=CENTER)
        self.cfl_label.grid(row=1, column=0, sticky=NSEW, padx=2, pady=2)
        self.cfl_entry = ttk.Entry(title_section_1_2, textvariable=self.cfl, justify=CENTER, takefocus=0)
        self.cfl_entry.grid(row=1, column=1, sticky=NSEW, padx=2, pady=2)

        self.gamma = DoubleVar()
        self.gamma.set(1.4)
        self.gamma_label = ttk.Label(title_section_1_2, text="    gamma    ", borderwidth=2, relief="groove", anchor=CENTER)
        self.gamma_label.grid(row=2, column=0, sticky=NSEW, padx=2, pady=2)
        self.gamma_entry = ttk.Entry(title_section_1_2, textvariable=self.gamma, justify=CENTER, takefocus=0)
        self.gamma_entry.grid(row=2, column=1, sticky=NSEW, padx=2, pady=2)

        self.mach = DoubleVar()
        self.mach.set(0.8)
        self.mach_label = ttk.Label(title_section_1_2, text="    mach    ", borderwidth=2, relief="groove", anchor=CENTER)
        self.mach_label.grid(row=3, column=0, sticky=NSEW, padx=2, pady=2)
        self.mach_entry = ttk.Entry(title_section_1_2, textvariable=self.mach, justify=CENTER, takefocus=0)
        self.mach_entry.grid(row=3, column=1, sticky=NSEW, padx=2, pady=2)

        self.cmac = DoubleVar()
        self.cmac.set(1.0)
        self.cmac_label = ttk.Label(title_section_1_2, text="cmac", borderwidth=2, relief="groove", anchor=CENTER)
        self.cmac_label.grid(row=1, column=2, sticky=NSEW, padx=2, pady=2)
        self.cmac_entry = ttk.Entry(title_section_1_2, textvariable=self.cmac, justify=CENTER, takefocus=0)
        self.cmac_entry.grid(row=1, column=3, sticky=NSEW, padx=2, pady=2)

        self.angle_attack = DoubleVar()
        self.angle_attack.set(0.0)
        self.angle_attack_label = ttk.Label(title_section_1_2, text="Angle of attack (deg)", borderwidth=2, relief="groove", anchor=CENTER)
        self.angle_attack_label.grid(row=2, column=2, sticky=NSEW, padx=2, pady=2)
        self.angle_attack_entry = ttk.Entry(title_section_1_2, textvariable=self.angle_attack, justify=CENTER, takefocus=0)
        self.angle_attack_entry.grid(row=2, column=3, sticky=NSEW, padx=2, pady=2)

        self.rk = IntVar()
        self.rk.set(5)
        self.rk_label = ttk.Label(title_section_1_2, text="Number of stages (RK)", borderwidth=2, relief="groove", anchor=CENTER)
        self.rk_label.grid(row=3, column=2, sticky=NSEW, padx=2, pady=2)
        self.rk_entry = ttk.Entry(title_section_1_2, textvariable=self.rk, justify=CENTER, takefocus=0)
        self.rk_entry.grid(row=3, column=3, sticky=NSEW, padx=2, pady=2)
        
        self.filename_mesh = StringVar()
        self.filename_mesh.set("void")
        self.filename_geometry = StringVar()
        self.filename_geometry.set("void")
        self.filename_topology = StringVar()
        self.filename_topology.set("void")
 
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
        
        self.filename_label_mesh = ttk.Label(self.mesh_window, text=self.filename_mesh.get(), relief="solid", width=60)
        self.filename_label_mesh.grid(row=1, column=1, columnspan=3, padx=2)

        if self.filename_mesh.get() != "void":
            self.filename_label_mesh.configure(text=self.filename_mesh.get())
        else:
            self.filename_label_mesh.configure(text="")
        
        ok_button = ttk.Button(self.mesh_window, text="Ok", command=self.saveAndDestroyMeshWindow)
        ok_button.grid(row=2, column=1, pady=5)

        cancel_button = ttk.Button(self.mesh_window, text="Cancel", command=self.mesh_window.destroy)
        cancel_button.grid(row=2, column=2, pady=5)

    def meshFileDialog(self):
        self.filename_mesh.set(filedialog.askopenfilename(initialdir="/home/etudiant/", title="Select a file", filetypes=(("SU2", "*.su2"),("All Files", "*.*"))))

        if self.filename_mesh.get() == "":
            self.filename_label_mesh.configure(text="")
        
        elif self.filename_mesh.get().endswith('.su2'):
            self.filename_label_mesh.configure(text=self.filename_mesh.get())
        else:
            messagebox.showwarning("Warning", "Chosen mesh file must be a SU2 file!")
            self.filename_label_mesh.configure(text=self.filename_mesh.get())
        
        self.mesh_window.lift()
        
    def importGeometry(self):
        self.geometry_window = Toplevel(self.master)
        self.geometry_window.title("Geometry importation")
        self.geometry_window.resizable(0,0)
        self.geometry_window.lift()

        text_geometry_importation = ttk.Label(self.geometry_window, text="\nImport the desired geometry:\n")
        text_geometry_importation.grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        
        select_file_button = ttk.Button(self.geometry_window, text="Select a file", command=self.geometryFileDialog)
        select_file_button.grid(row=1, column=0, padx=2)
        
        self.filename_label_geometry = ttk.Label(self.geometry_window, text="", relief="solid", width=60)
        self.filename_label_geometry.grid(row=1, column=1, columnspan=3, padx=2)
        if self.filename_geometry.get() != "void":
            self.filename_label_geometry.configure(text=self.filename_geometry.get())
        else:
            self.filename_label_geometry.configure(text="")

        ok_button = ttk.Button(self.geometry_window, text="Ok", command=self.saveImportedGeometry)
        ok_button.grid(row=3, column=1, pady=5)
        cancel_button = ttk.Button(self.geometry_window, text="Cancel", command=self.geometry_window.destroy)
        cancel_button.grid(row=3, column=2, pady=5)

        self.geometry_window.lift()

    def geometryFileDialog(self):
        self.filename_geometry.set(filedialog.askopenfilename(initialdir="/home/etudiant/", title="Select a file", filetypes=(("csm", "*.csm"),("All Files", "*.*"))))
        
        if self.filename_geometry.get() == "":
            self.filename_label_geometry.configure(text="")
        
        elif self.filename_geometry.get().endswith('.csm'):
            self.filename_label_geometry.configure(text=self.filename_geometry.get())
        
        else:
            messagebox.showwarning("Warning", "Chosen geometry file must be a csm file!")
            self.filename_label_geometry.configure(text=self.filename_geometry.get())

        self.geometry_window.lift()
    
    def saveImportedGeometry(self):
        if self.filename_geometry.get() == "":
            messagebox.showwarning("Warning", "Please import a geometry file.")
        
        elif self.filename_geometry.get() == "void":
            messagebox.showwarning("Warning", "Please import a geometry file.")

        else:
            self.geometry_window.destroy()
            info = "Pointwise will open momentarily. Please be sure to know where you save your mesh file. You will have to import it in the software to solve it."
            messagebox.showinfo("Ready for meshing", info)
            os.system("pointwise")

        self.geometry_window.lift()

    def generateGeometry(self):
        self.geometry_generation_window = Toplevel(self.master)
        self.geometry_generation_window.title("Geometry Generation")
        self.geometry_generation_window.resizable(0,0)
        self.geometry_generation_window.lift()

        ttk.Label(self.geometry_generation_window, text="\nSpecify the needed information for geometry generation:\n").grid(row=0, column=0, columnspan=4, sticky=W, padx=2)
        ttk.Label(self.geometry_generation_window, text="NACA profile:").grid(row=1, column=0, columnspan=2, sticky=W, padx=2, pady=2)
           
        self.max_camber = IntVar()
        self.max_camber.set(0)
        self.max_camber_label = ttk.Label(self.geometry_generation_window, text="Max camber (%)", borderwidth=2, relief="groove", width=20)
        self.max_camber_label.grid(row=2, column=0, columnspan=2, sticky=NSEW, padx=2)
        self.max_camber_entry = ttk.Entry(self.geometry_generation_window, textvariable=self.max_camber, width=10)
        self.max_camber_entry.grid(row=2, column=2, sticky=NW, padx=2)
        ttk.Label(self.geometry_generation_window, text="(0 to 9.5%)", anchor=CENTER, width=10).grid(row=2, column=3, sticky=NSEW)
        
        self.max_camber_position = IntVar()
        self.max_camber_position.set(0)
        self.max_camber_position_label = ttk.Label(self.geometry_generation_window, text="Max camber position (%)", borderwidth=2, relief="groove", width=20)
        self.max_camber_position_label.grid(row=3, column=0, columnspan=2, sticky=NSEW, padx=2)
        self.max_camber_position_entry = ttk.Entry(self.geometry_generation_window, textvariable=self.max_camber_position, width=10)
        self.max_camber_position_entry.grid(row=3, column=2, sticky=NW, padx=2)
        ttk.Label(self.geometry_generation_window, text="(0 to 90%)", anchor=CENTER, width=10).grid(row=3, column=3, sticky=NSEW)

        self.thickness = IntVar()
        self.thickness.set(12)        
        self.thickness_label = ttk.Label(self.geometry_generation_window, text="Thickness (%)", borderwidth=2, relief="groove", width=20)
        self.thickness_label.grid(row=4, column=0, columnspan=2, sticky=NSEW, padx=2)
        self.thickness_entry = ttk.Entry(self.geometry_generation_window, textvariable=self.thickness, width=10)
        self.thickness_entry.grid(row=4, column=2, sticky=NW, padx=2)
        ttk.Label(self.geometry_generation_window, text="(1 to 40%)", anchor=CENTER, width=10).grid(row=4, column=3, sticky=NSEW)
      
        refresh = ttk.Button(self.geometry_generation_window, text="Refresh NACA", command=self.changeNACADigits)
        refresh.grid(row=5, column=0, sticky=NSEW, padx=2, pady=2)
        self.naca_result = ttk.Label(self.geometry_generation_window, text="NACA 0012", borderwidth=2, relief="groove", width=10)
        self.naca_result.grid(row=5, column=1, sticky=NSEW, padx=2, pady=2)

        ttk.Label(self.geometry_generation_window, text="\n").grid(row=6, column=0, columnspan=4)

        self.span = DoubleVar()
        self.span.set(5.0)
        self.span_label = ttk.Label(self.geometry_generation_window, text="Span", borderwidth=2, relief="groove")
        self.span_label.grid(row=7, column=0, sticky=NSEW, padx=2)
        self.span_entry = ttk.Entry(self.geometry_generation_window, textvariable=self.span, width=10)
        self.span_entry.grid(row=7, column=1, padx=2)

        self.croot_ctip = DoubleVar()
        self.croot_ctip.set(1.0)
        self.croot_ctip_label = ttk.Label(self.geometry_generation_window, text="Croot/Ctip", borderwidth=2, relief="groove")
        self.croot_ctip_label.grid(row=8, column=0, sticky=NSEW, padx=2, pady=2)
        self.croot_ctip_entry = ttk.Entry(self.geometry_generation_window, textvariable=self.croot_ctip, width=10)
        self.croot_ctip_entry.grid(row=8, column=1, padx=2)

        ttk.Label(self.geometry_generation_window, text="\n").grid(row=9, column=0, columnspan=4)
        ttk.Label(self.geometry_generation_window, text="Mesh file type:").grid(row=10, column=0, columnspan=3, sticky=W, padx=2, pady=2)

        self.mesh_type = IntVar()
        self.mesh_type.set(3)
        self.mesh_type_egads = Radiobutton(self.geometry_generation_window, text=".egads", value=1, variable=self.mesh_type, relief="groove", borderwidth=2, anchor=W, width=10)
        self.mesh_type_egads.grid(row=11, column=0, sticky=NSEW, padx=2, pady=2)

        self.mesh_type_iges = Radiobutton(self.geometry_generation_window, text=".iges", value=2, variable=self.mesh_type, relief="groove", borderwidth=2, anchor=W, width=10)
        self.mesh_type_iges.grid(row=12, column=0, sticky=NSEW, padx=2, pady=2)

        self.mesh_type_step = Radiobutton(self.geometry_generation_window, text=".step", value=3, variable=self.mesh_type, relief="groove", borderwidth=2, anchor=W, width=10)
        self.mesh_type_step.grid(row=13, column=0, sticky=NSEW, padx=2, pady=2)

        self.show_geometry = IntVar()
        self.show_geometry.set(0)
        self.show_geometry_label = ttk.Label(self.geometry_generation_window, text="\n\nWould you like to visualize geometry in ESP?", anchor=CENTER)
        self.show_geometry_label.grid(row=14, column=0, columnspan=2, padx=2)
        
        self.show_geometry_yes = Radiobutton(self.geometry_generation_window, text="Yes", value=1, variable=self.show_geometry, relief="groove", borderwidth=2, width=8, anchor=W)
        self.show_geometry_yes.grid(row=15, column=0, padx=2, pady=2, sticky=NSEW)

        self.show_geometry_no = Radiobutton(self.geometry_generation_window, text="No", value=0, variable=self.show_geometry, relief="groove", borderwidth=2, width=8, anchor=W)
        self.show_geometry_no.grid(row=16, column=0, padx=2, pady=2, sticky=NSEW)

        ok_button = ttk.Button(self.geometry_generation_window, text="Ok", command=self.saveGeneratedGeometry)
        ok_button.grid(row=17, column=1, pady=5)
        cancel_button = ttk.Button(self.geometry_generation_window, text="Cancel", command=self.geometry_generation_window.destroy)
        cancel_button.grid(row=17, column=2, pady=5)

    def changeNACADigits(self):
        first_digit = str(self.max_camber.get())

        if first_digit == "0":
            second_digit = "0"
        
        else:
            if self.max_camber_position.get() < 10:
                second_digit = "1"
            else:
                second_digit = str(self.max_camber_position.get())
                second_digit = second_digit[0]
        
        third_fourth_digit = str(self.thickness.get())
        naca_result_text = "NACA " + first_digit + second_digit + third_fourth_digit
        self.naca_result.configure(text=naca_result_text)
    
    def saveGeneratedGeometry(self):
        first_digit = str(self.max_camber.get())
        second_digit = str(self.max_camber_position.get())
        third_fourth_digit = str(self.thickness.get())
        span = str(self.span.get())
        corde_ratio = str(self.croot_ctip.get())
        mesh_type = str(self.mesh_type.get())

        if mesh_type == "1":
            mesh_type = ".egads"
        
        elif mesh_type == "2":
            mesh_type = ".iges"
        
        else:
            mesh_type = ".step"

        mesh_file_name = "NACA" + first_digit + second_digit + third_fourth_digit + "_S" + span + "_CR" + corde_ratio + mesh_type
        info =  mesh_file_name + " has been created. Pointwise will open momentarily. Please be sure to know where you save your mesh file. You will have to import it in the software to solve it."

        file_path = '../euler3D/'
        file_name = "NACA_ESP.csm"

        complete_file_name = os.path.join(file_path, file_name)

        file = open(complete_file_name,"w")

        file.write("despmtr   series_w    " + first_digit + second_digit + third_fourth_digit + ".00000\n" + (
                    "dimension wing   3   5   1\n") + (
                    "despmtr   wing[3,:]   \"     0.00000;     " + span + "000;     0.00000;     " + corde_ratio + "0000;     180.00000;\"\n\n") + (
                    "mark\n") + (
                    "udprim    naca   Series   series_w\n") + (
                    "rotatez   -wing[3,5]   0   0\n") + (
                    "rotatex   90   0   0\n") + (
                    "scale     wing[3,4]   0   0   0\n") + (
                    "translate wing[3,1]   -wing[3,2]   wing[3,3]\n\n") + (
                    "udprim    naca   Series   series_w\n") + (
                    "rotatez   -wing[3,5]   0   0\n") + (
                    "rotatex   90   0   0\n") + (
                    "rule      0\n\n") + (
                    "DUMP $/" + mesh_file_name + " 0 0\n") + (
                    "end"))
        
        file.close()
        
        self.geometry_generation_window.destroy()

        if self.show_geometry.get() == 0:
            os.system("serveCSM -batch ~/Documents/EulerFred/euler3D/NACA_ESP")
        elif self.show_geometry.get() == 1:
            os.system("serveCSM ~/Documents/EulerFred/euler3D/NACA_ESP")

        messagebox.showinfo("Ready for meshing", info)

        os.system("pointwise")

    def showResultingMesh(self):
        messagebox.showinfo('Resulting Mesh')

    def saveAndDestroyMeshWindow(self):
        self.writePartialOutputMesh()
        
        if self.filename_mesh.get() != "void" and self.filename_mesh.get() != "":
            self.partition_window = Toplevel(self.master)
            self.partition_window.title("Mesh Partitionning?")
            self.partition_window.resizable(0,0)
            self.partition_window.lift()

            ttk.Label(self.partition_window, text="Do you want to partition your mesh?").grid(row=0, column=0, columnspan=4)

            self.partition = IntVar()
            self.partition.set(0)
            self.partition_yes = Radiobutton(self.partition_window, text="Yes", value=1, variable=self.partition, command=self.activateNumberBlocks, relief="groove", borderwidth=2, width=5, anchor=W, takefocus=0, padx=2, pady=2)
            self.partition_yes.grid(row=1, column=1, columnspan=2, padx=2, pady=2)
            self.partition_no = Radiobutton(self.partition_window, text="No", value=0, variable=self.partition, command=self.activateNumberBlocks, relief="groove", borderwidth=2, width=5, anchor=W, takefocus=0)
            self.partition_no.grid(row=2, column=1, columnspan=2, padx=2, pady=2)

            self.number_blocks = IntVar()
            self.number_blocks.set(3)
            self.number_blocks_label = ttk.Label(self.partition_window, text="Number of blocks", state="disabled", borderwidth=2, relief="groove", anchor=CENTER, width=15)
            self.number_blocks_label.grid(row=3, column=1, padx=2, pady=2)
            self.number_blocks_entry = ttk.Entry(self.partition_window, textvariable=self.number_blocks, state="disabled", justify=CENTER, takefocus=0, width=15)
            self.number_blocks_entry.grid(row=3, column=2, padx=2, pady=2)

            ok_button = ttk.Button(self.partition_window, text="Ok", command=self.callPartitioningScript)
            ok_button.grid(row=4, column=1, pady=5)
            cancel_button = ttk.Button(self.partition_window, text="Cancel", command=self.partition_window.destroy)
            cancel_button.grid(row=4, column=2, pady=5)
        
        else:
            messagebox.showwarning("Warning", "Please import a mesh file.")
            self.mesh_window.lift()

    def callPartitioningScript(self):
        self.partition_window.destroy()
        self.mesh_window.destroy()
      
        if self.partition.get() == 1:            
            command = "./MeshPartitioning/Mesh_Partitioning " + str(self.filename_mesh.get()) + " " + str(self.number_blocks.get()) + " local_mesh_B topology.top"
            os.system(command)
            self.filename_topology.set("topology.top")
        else:
            shutil.copyfile(self.filename_mesh.get(), "single_block.su2")
            self.filename_topology.set("single_block.top")
            
    def activateNumberBlocks(self):
        if self.partition.get() == 1:
            self.number_blocks_label.configure(state="normal")
            self.number_blocks_entry.configure(state="normal")
        elif self.partition.get() == 0:
            self.number_blocks_label.configure(state="disabled")
            self.number_blocks_entry.configure(state="disabled")

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
        
        self.partial_output_mesh = "MESH\ntopologyfilename\n" + str(self.filename_topology.get())

        return self.partial_output_mesh

    def writePartialOutput(self):
        cfl_str = str(self.cfl.get())
        gamma_str = str(self.gamma.get())
        angle_attack_str = str(self.angle_attack.get())
        rk_str = str(self.rk.get())
        mach_str = str(self.mach.get())
        cmac_str = str(self.cmac.get())

        if 'self.partial_output_mesh' in globals():
            partial_output = self.partial_output_mesh+(
                             "\nINPUT\ncfl gamma angleattackdeg\n")+(
                             cfl_str+" "+gamma_str+" "+angle_attack_str)+(
                             "\nrkstage mach cmac\n")+(
                             rk_str+" "+mach_str+" "+cmac_str)                        
        else:
            partial_output = "MESH\ntopologyfilename\n"+(
                             str(self.filename_topology.get()))+(
                             "\nINPUT\ncfl gamma angleattackdeg\n")+(
                             cfl_str+" "+gamma_str+" "+angle_attack_str)+(
                             "\nrkstage mach cmac\n")+(
                             rk_str+" "+mach_str+" "+cmac_str)  
        
        return partial_output

    def saveImportedData(self, filename_var, cfl_var, gamma_var, angle_attack_var, rk_var, mach_var, cmac_var):
        self.filename_mesh.set(filename_var)
        self.cfl.set(cfl_var)
        self.gamma.set(gamma_var)
        self.angle_attack.set(angle_attack_var)
        self.rk.set(rk_var)
        self.mach.set(mach_var)
        self.cmac.set(cmac_var)