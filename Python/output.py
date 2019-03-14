import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class Output():
    def __init__(self, master):
        self.master = master
        
        # SECTION 3: OUTPUT
        title_section_3 = ttk.LabelFrame(master, text="", labelanchor=N, height=430, width=396)
        title_section_3.grid(row=0, column=0, columnspan=3)
        title_section_3.grid_propagate(False)
            
        text_section_3 = ttk.Label(title_section_3, text="\n\n\n\nPlease specify what type of graphe(s) you would like to\ndisplay:\n")
        text_section_3.grid(row=0, column=0, columnspan=3, sticky=NSEW)

        self.cl_alpha = IntVar()
        self.cl_alpha.set(0)
        Checkbutton(title_section_3, text="Cl vs alpha", variable=self.cl_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=1, column=0, padx=2, pady=2)
            
        self.cd_alpha = IntVar()
        self.cd_alpha.set(0)
        Checkbutton(title_section_3, text="Cd vs alpha", variable=self.cd_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=2, column=0, padx=2, pady=2)

        self.cm_alpha = IntVar()
        self.cm_alpha.set(0)
        Checkbutton(title_section_3, text="Cm vs alpha", variable=self.cm_alpha, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=3, column=0, padx=2, pady=2)

        self.coefficients_convergence = IntVar()
        self.coefficients_convergence.set(0)
        Checkbutton(title_section_3, text="Cl, cd, cm convergence", variable=self.coefficients_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=4, column=0, padx=2, pady=2)

        # self.cd_convergence = IntVar()
        # self.cd_convergence.set(0)
        # Checkbutton(title_section_3, text="Cd convergence", variable=self.cd_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=5, column=0, padx=2, pady=2)

        # self.cm_convergence = IntVar()
        # self.cm_convergence.set(0)
        # Checkbutton(title_section_3, text="Cm convergence", variable=self.cm_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=6, column=0, padx=2, pady=2)

        self.residual_convergence = IntVar()
        self.residual_convergence.set(0)
        Checkbutton(title_section_3, text="Residual convergence", variable=self.residual_convergence, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=5, column=0, padx=2, pady=2)

        self.cp_xc = IntVar()
        self.cp_xc.set(0)
        Checkbutton(title_section_3, text="Cp vs Xc", variable=self.cp_xc, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=6, column=0, padx=2, pady=2)

        self.mach_iso = IntVar()
        self.mach_iso.set(0)
        Checkbutton(title_section_3, text="Mach isosurface", variable=self.mach_iso, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=1, column=1, columnspan=2, padx=2, pady=2)

        self.mach_contour = IntVar()
        self.mach_contour.set(0)
        Checkbutton(title_section_3, text="Mach contour", variable=self.mach_contour, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=2, column=1, columnspan=2, padx=2, pady=2)

        self.cp_contour = IntVar()
        self.cp_contour.set(0)
        Checkbutton(title_section_3, text="Cp contour", variable=self.cp_contour, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=3, column=1, columnspan=2, padx=2, pady=2)

        self.slice_cp = IntVar()
        self.slice_cp.set(0)
        Checkbutton(title_section_3, text="Slice Cp", variable=self.slice_cp, command=self.activateAxisOfCut, relief="groove", width=20, anchor=W, borderwidth=2).grid(row=4, column=1, columnspan=2, padx=2, pady=2)

        self.axis_cut = StringVar()
        self.axis_cut.set("x")
        self.axis_cut_label = ttk.Label(title_section_3, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.axis_cut_label.grid(row=5, column=1)
        self.axis_cut_entry = ttk.Entry(title_section_3, textvariable=self.axis_cut, width=11, state="disabled")
        self.axis_cut_entry.grid(row=5, column=2, padx=2, pady=2)

        self.x_coord = DoubleVar()    
        self.x_coord.set(0.0)
        self.x_coord_label = ttk.Label(title_section_3, text="X coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.x_coord_label.grid(row=6, column=1)
        self.x_coord_entry = ttk.Entry(title_section_3, textvariable=self.x_coord, width=11, state="disabled")
        self.x_coord_entry.grid(row=6, column=2, padx=2, pady=2)

        self.y_coord = DoubleVar()   
        self.y_coord.set(0.0) 
        self.y_coord_label = ttk.Label(title_section_3, text="Y coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.y_coord_label.grid(row=7, column=1)
        self.y_coord_entry = ttk.Entry(title_section_3, textvariable=self.y_coord, width=11, state="disabled")
        self.y_coord_entry.grid(row=7, column=2, padx=2, pady=2)

        self.z_coord = DoubleVar()
        self.z_coord.set(0.0)
        self.z_coord_label = ttk.Label(title_section_3, text="Z coord", relief="groove", state="disabled", borderwidth=2, width=10, anchor=CENTER)
        self.z_coord_label.grid(row=8, column=1)
        self.z_coord_entry = ttk.Entry(title_section_3, textvariable=self.z_coord, width=11, state="disabled")
        self.z_coord_entry.grid(row=8, column=2, padx=2, pady=2)

        # GENERAL BUTTONS
        clear_all_button = ttk.Button(master, text="Clear all")
        clear_all_button.grid(row=1, column=0, padx=2, pady=2)

        clear_button = ttk.Button(master, text="Clear this page", command=self.clearPage)
        clear_button.grid(row=1, column=1, padx=2, pady=2)

        solve_button = ttk.Button(master, text="Solve")
        solve_button.grid(row=1, column=2, padx=2, pady=2)

    # METHODS
    def activateAxisOfCut(self):
        slice_cp_result = self.slice_cp.get()

        if slice_cp_result == 1:
            self.axis_cut_label.configure(state="normal")
            self.axis_cut_entry.configure(state="normal")
            self.x_coord_label.configure(state="normal")
            self.x_coord_entry.configure(state="normal")
            self.y_coord_label.configure(state="normal")
            self.y_coord_entry.configure(state="normal")
            self.z_coord_label.configure(state="normal")
            self.z_coord_entry.configure(state="normal")

        elif slice_cp_result == 0:
            self.axis_cut_label.configure(state="disabled")
            self.axis_cut_entry.configure(state="disabled")
            self.x_coord_label.configure(state="disabled")
            self.x_coord_entry.configure(state="disabled")
            self.y_coord_label.configure(state="disabled")
            self.y_coord_entry.configure(state="disabled")
            self.z_coord_label.configure(state="disabled")
            self.z_coord_entry.configure(state="disabled")
    
    def clearPage(self):
        self.cl_alpha.set(0)
        self.cd_alpha.set(0)
        self.cm_alpha.set(0)
        self.coefficients_convergence.set(0)
        self.residual_convergence.set(0)
        self.cp_xc.set(0)
        self.mach_iso.set(0)
        self.mach_contour.set(0)
        self.cp_contour.set(0)
        self.slice_cp.set(0)
        self.axis_cut.set("x")
        self.x_coord.set(0.0)
        self.y_coord.set(0.0)
        self.z_coord.set(0.0)

    def writePartialOutput(self):

        cl_alpha_str = str(self.cl_alpha.get())
        cd_alpha_str = str(self.cd_alpha.get())
        cm_alpha_str = str(self.cm_alpha.get())
        coeff_conv_str = str(self.cl_convergence.get())
        res_conv_str = str(self.residual_convergence.get())
        cp_xc_str = str(self.cp_xc.get())
        mach_iso_str = str(self.mach_iso.get())
        mach_cont_str = str(self.mach_contour.get())
        cp_cont_str = str(self.cp_contour.get())
        
        slice_cp_str = str(self.slice_cp.get())
        if slice_cp_str == "1":
            axis_str = self.axis_cut.get()
            xcoord_str = str(self.x_coord.get())
            ycoord_str = str(self.y_coord.get())
            zcoord_str = str(self.z_coord.get())
        
        elif slice_cp_str == "0":
            axis_str = "x"
            xcoord_str = "0.0"
            ycoord_str = "0.0"
            zcoord_str = "0.0"

        partial_output = "\nOUTPUT (0-no 1-yes)\nclalpha cdalpha cmalpha\n"+(
                        cl_alpha_str+" "+cd_alpha_str+" "+cm_alpha_str)+(
                        "\ncoefficientsconv residualconv\n")+(
                        coeff_conv_str+" "+res_conv_str)+(
                        "\ncpxc machcontour cpcontour machisosurface\n")+(
                        cp_xc_str+" "+mach_cont_str+" "+cp_cont_str+" "+mach_iso_str)+(
                        "\nslicecp\n")+(
                        slice_cp_str)+(
                        "\naxis xcoord ycoord zcoord\n")+(
                        axis_str+" "+xcoord_str+" "+ycoord_str+" "+zcoord_str)

        return partial_output
