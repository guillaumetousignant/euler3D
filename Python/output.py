import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class Output():
    def __init__(self, master):
        self.master = master
        
        # SECTION 3: OUTPUT
        # SECTION 3.1: FILES TYPE
        title_section_3_1 = ttk.LabelFrame(master, text="3.1 Files type", labelanchor=N, height=135, width=396)
        title_section_3_1.grid(row=0, column=0, columnspan=3)
        title_section_3_1.grid_propagate(False)
        title_section_3_1.grid_columnconfigure(0, weight=1)

        text_section_3_1 = ttk.Label(title_section_3_1, text="\nPlease specify the type of files you would like to display:\n")
        text_section_3_1.grid(row=0, column=0, sticky=NSEW)

        self.files_type = IntVar()
        self.files_type.set(1)
        self.files_type_euler = Radiobutton(title_section_3_1, text="Euler", value=0, variable=self.files_type, relief="groove", width=10, borderwidth=2, anchor=W)
        self.files_type_euler.grid(row=1, column=0, columnspan=2, sticky=N, padx=2, pady=2)
        self.files_type_su2 = Radiobutton(title_section_3_1, text="SU2", value=1, variable=self.files_type, relief="groove", width=10, borderwidth=2, anchor=W)
        self.files_type_su2.grid(row=2, column=0, columnspan=2, sticky=N, padx=2, pady=2)

        # SECTION 3.2: GRAPHS
        title_section_3_2 = ttk.LabelFrame(master, text="3.2 Graphs", labelanchor=N, height=325, width=396)
        title_section_3_2.grid(row=1, column=0, columnspan=4)
        title_section_3_2.grid_propagate(False)
        title_section_3_2.grid_columnconfigure(1, weight=1)
        title_section_3_2.grid_columnconfigure(3, weight=1)

        text_section_3_2 = ttk.Label(title_section_3_2, text="\nPlease specify the type of graphs you would like to display:\n")
        text_section_3_2.grid(row=0, column=0, columnspan=4, sticky=NSEW)

        self.cl_alpha = IntVar()
        self.cl_alpha.set(0)
        cl_alpha_button = Checkbutton(title_section_3_2, text="Cl vs alpha", variable=self.cl_alpha, relief="groove", anchor=W, borderwidth=2)
        cl_alpha_button.grid(row=1, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)
            
        self.cd_alpha = IntVar()
        self.cd_alpha.set(0)
        cd_alpha_button = Checkbutton(title_section_3_2, text="Cd vs alpha", variable=self.cd_alpha, relief="groove", anchor=W, borderwidth=2)
        cd_alpha_button.grid(row=2, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cm_alpha = IntVar()
        self.cm_alpha.set(0)
        cm_alpha_button = Checkbutton(title_section_3_2, text="Cm vs alpha", variable=self.cm_alpha, relief="groove", anchor=W, borderwidth=2)
        cm_alpha_button.grid(row=3, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.coefficients_convergence = IntVar()
        self.coefficients_convergence.set(0)
        coefficients_convergence_button = Checkbutton(title_section_3_2, text="Cl, cd, cm convergence", variable=self.coefficients_convergence, relief="groove", anchor=W, borderwidth=2)
        coefficients_convergence_button.grid(row=4, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cp_xc = IntVar()
        self.cp_xc.set(0)
        cp_xc_button = Checkbutton(title_section_3_2, text="Cp vs Xc", variable=self.cp_xc, command=self.activateCpXc, relief="groove", anchor=W, borderwidth=2)
        cp_xc_button.grid(row=5, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.axis_cut_cp_xc = StringVar()
        self.axis_cut_cp_xc.set("x")
        self.axis_cut_cp_xc_label = ttk.Label(title_section_3_2, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.axis_cut_cp_xc_label.grid(row=6, column=0, padx=2, pady=2)
        self.axis_cut_cp_xc_entry = ttk.Entry(title_section_3_2, textvariable=self.axis_cut_cp_xc, state="disabled", justify=CENTER)
        self.axis_cut_cp_xc_entry.grid(row=6, column=1, padx=2, pady=2, sticky=NSEW)

        self.x_coord = DoubleVar()    
        self.x_coord.set(0.0)
        self.x_coord_label = ttk.Label(title_section_3_2, text="X coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.x_coord_label.grid(row=7, column=0, padx=2, pady=2)
        self.x_coord_entry = ttk.Entry(title_section_3_2, textvariable=self.x_coord, state="disabled", justify=CENTER)
        self.x_coord_entry.grid(row=7, column=1, padx=2, pady=2, sticky=NSEW)

        self.y_coord = DoubleVar()   
        self.y_coord.set(0.0) 
        self.y_coord_label = ttk.Label(title_section_3_2, text="Y coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.y_coord_label.grid(row=8, column=0, padx=2, pady=2)
        self.y_coord_entry = ttk.Entry(title_section_3_2, textvariable=self.y_coord, state="disabled", justify=CENTER)
        self.y_coord_entry.grid(row=8, column=1, padx=2, pady=2, sticky=NSEW)

        self.z_coord = DoubleVar()
        self.z_coord.set(0.0)
        self.z_coord_label = ttk.Label(title_section_3_2, text="Z coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.z_coord_label.grid(row=9, column=0, padx=2, pady=2)
        self.z_coord_entry = ttk.Entry(title_section_3_2, textvariable=self.z_coord, state="disabled", justify=CENTER)
        self.z_coord_entry.grid(row=9, column=1, padx=2, pady=2, sticky=NSEW)

        self.residual_convergence = IntVar()
        self.residual_convergence.set(0)
        residual_convergence_button = Checkbutton(title_section_3_2, text="Residual convergence", variable=self.residual_convergence, relief="groove", anchor=W, borderwidth=2)
        residual_convergence_button.grid(row=1, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.mach_iso = IntVar()
        self.mach_iso.set(0)
        mach_iso_button = Checkbutton(title_section_3_2, text="Mach isosurface", variable=self.mach_iso, relief="groove", anchor=W, borderwidth=2)
        mach_iso_button.grid(row=2, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.mach_contour = IntVar()
        self.mach_contour.set(0)
        mahc_contour_button = Checkbutton(title_section_3_2, text="Mach contour", variable=self.mach_contour, relief="groove", anchor=W, borderwidth=2)
        mahc_contour_button.grid(row=3, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cp_contour = IntVar()
        self.cp_contour.set(0)
        cp_contour_button = Checkbutton(title_section_3_2, text="Cp contour", variable=self.cp_contour, relief="groove", anchor=W, borderwidth=2)
        cp_contour_button.grid(row=4, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.slice_cp = IntVar()
        self.slice_cp.set(0)
        slice_cp_button = Checkbutton(title_section_3_2, text="Slice Cp", variable=self.slice_cp, command=self.activateSliceCp, relief="groove", anchor=W, borderwidth=2)
        slice_cp_button.grid(row=5, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.axis_cut_slice_cp = StringVar()
        self.axis_cut_slice_cp.set("x")
        self.axis_cut_slice_cp_label = ttk.Label(title_section_3_2, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.axis_cut_slice_cp_label.grid(row=6, column=2, padx=2, pady=2)
        self.axis_cut_slice_cp_entry = ttk.Entry(title_section_3_2, textvariable=self.axis_cut_slice_cp, state="disabled", justify=CENTER)
        self.axis_cut_slice_cp_entry.grid(row=6, column=3, padx=2, pady=2, sticky=N)
        
        self.nb_slices = IntVar()
        self.nb_slices.set(1)
        self.nb_slices_label = ttk.Label(title_section_3_2, text="Number of slices", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.nb_slices_label.grid(row=7, column=2, padx=2, pady=2)
        self.nb_slices_entry = ttk.Entry(title_section_3_2, textvariable=self.nb_slices, state="disabled", justify=CENTER)
        self.nb_slices_entry.grid(row=7, column=3, padx=2, pady=2, sticky=N)

        self.first_coord = DoubleVar()
        self.first_coord.set(0.0)
        self.first_coord_label = ttk.Label(title_section_3_2, text="First coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.first_coord_label.grid(row=8, column=2, padx=2, pady=2)
        self.first_coord_entry = ttk.Entry(title_section_3_2, textvariable=self.first_coord, state="disabled", justify=CENTER)
        self.first_coord_entry.grid(row=8, column=3, padx=2, pady=2, sticky=N)

        self.last_coord = DoubleVar()
        self.last_coord.set(0.0)
        self.last_coord_label = ttk.Label(title_section_3_2, text="Last coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.last_coord_label.grid(row=9, column=2, padx=2, pady=2)
        self.last_coord_entry = ttk.Entry(title_section_3_2, textvariable=self.last_coord, state="disabled", justify=CENTER)
        self.last_coord_entry.grid(row=9, column=3, padx=2, pady=2, sticky=N)

    # METHODS
    def activateCpXc(self):
        cp_xc_result = self.cp_xc.get()

        if cp_xc_result == 1:
            self.axis_cut_cp_xc_label.configure(state="normal")
            self.axis_cut_cp_xc_entry.configure(state="normal")
            self.x_coord_label.configure(state="normal")
            self.x_coord_entry.configure(state="normal")
            self.y_coord_label.configure(state="normal")
            self.y_coord_entry.configure(state="normal")
            self.z_coord_label.configure(state="normal")
            self.z_coord_entry.configure(state="normal")

        elif cp_xc_result == 0:
            self.axis_cut_cp_xc_label.configure(state="disabled")
            self.axis_cut_cp_xc_entry.configure(state="disabled")
            self.x_coord_label.configure(state="disabled")
            self.x_coord_entry.configure(state="disabled")
            self.y_coord_label.configure(state="disabled")
            self.y_coord_entry.configure(state="disabled")
            self.z_coord_label.configure(state="disabled")
            self.z_coord_entry.configure(state="disabled")

    def activateSliceCp(self):
        slice_cp_result = self.slice_cp.get()

        if slice_cp_result == 1:
            self.axis_cut_slice_cp_label.configure(state="normal")
            self.axis_cut_slice_cp_entry.configure(state="normal")
            self.nb_slices_label.configure(state="normal")
            self.nb_slices_entry.configure(state="normal")
            self.first_coord_label.configure(state="normal")
            self.first_coord_entry.configure(state="normal")
            self.last_coord_label.configure(state="normal")
            self.last_coord_entry.configure(state="normal")

        elif slice_cp_result == 0:
            self.axis_cut_slice_cp_label.configure(state="disabled")
            self.axis_cut_slice_cp_entry.configure(state="disabled")
            self.nb_slices_label.configure(state="disabled")
            self.nb_slices_entry.configure(state="disabled")
            self.first_coord_label.configure(state="disabled")
            self.first_coord_entry.configure(state="disabled")
            self.last_coord_label.configure(state="disabled")
            self.last_coord_entry.configure(state="disabled")
    
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
        self.axis_cut_cp_xc.set("x")
        self.x_coord.set(0.0)
        self.y_coord.set(0.0)
        self.z_coord.set(0.0)

        self.axis_cut_cp_xc_label.configure(state="disabled")
        self.axis_cut_cp_xc_entry.configure(state="disabled")
        self.x_coord_label.configure(state="disabled")
        self.x_coord_entry.configure(state="disabled")
        self.y_coord_label.configure(state="disabled")
        self.y_coord_entry.configure(state="disabled")
        self.z_coord_label.configure(state="disabled")
        self.z_coord_entry.configure(state="disabled")
        self.nb_slices_label.configure(state="disabled")
        self.nb_slices_entry.configure(state="disabled")
        self.first_coord_label.configure(state="disabled")
        self.first_coord_entry.configure(state="disabled")
        self.last_coord_label.configure(state="disabled")
        self.last_coord_entry.configure(state="disabled")

    def writePartialOutput(self):

        cl_alpha_str = str(self.cl_alpha.get())
        cd_alpha_str = str(self.cd_alpha.get())
        cm_alpha_str = str(self.cm_alpha.get())
        coeff_conv_str = str(self.coefficients_convergence.get())
        res_conv_str = str(self.residual_convergence.get())
        cp_xc_str = str(self.cp_xc.get())
        mach_iso_str = str(self.mach_iso.get())
        mach_cont_str = str(self.mach_contour.get())
        cp_cont_str = str(self.cp_contour.get())
        
        slice_cp_str = str(self.slice_cp.get())
        if slice_cp_str == "1":
            axis_str = self.axis_cut_cp_xc.get()
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
