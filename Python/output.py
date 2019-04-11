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
        title_section_3_1.grid_rowconfigure(0, weight=1)
        title_section_3_1.grid_rowconfigure(4, weight=1)

        ttk.Label(title_section_3_1, text=" ").grid(row=0, column=0, sticky=NSEW)

        text_section_3_1 = ttk.Label(title_section_3_1, text="\nPlease specify the type of files you would like to display:\n")
        text_section_3_1.grid(row=1, column=0, sticky=NSEW)

        self.files_type_ = IntVar()
        self.files_type_.set(0)
        files_type_euler = Radiobutton(title_section_3_1, text=" Developped software", value=0, variable=self.files_type_, relief="groove", width=20, borderwidth=2, anchor=W, takefocus=0)
        files_type_euler.grid(row=2, column=0, columnspan=2, sticky=N, padx=2, pady=2)
        files_type_su2 = Radiobutton(title_section_3_1, text=" SU2", value=1, variable=self.files_type_, relief="groove", width=20, borderwidth=2, anchor=W, takefocus=0)
        files_type_su2.grid(row=3, column=0, columnspan=2, sticky=N, padx=2, pady=2)

        ttk.Label(title_section_3_1, text=" ").grid(row=4, column=0, sticky=NSEW)

        # SECTION 3.2: GRAPHS
        title_section_3_2 = ttk.LabelFrame(master, text="3.2 Graphs", labelanchor=N, height=325, width=396)
        title_section_3_2.grid(row=1, column=0, columnspan=4)
        title_section_3_2.grid_propagate(False)
        title_section_3_2.grid_columnconfigure(1, weight=1)
        title_section_3_2.grid_columnconfigure(3, weight=1)
        title_section_3_2.grid_rowconfigure(0, weight=1)
        title_section_3_2.grid_rowconfigure(11, weight=1)

        ttk.Label(title_section_3_2, text=" ").grid(row=0, column=0, columnspan=4, sticky=NSEW)

        text_section_3_2 = ttk.Label(title_section_3_2, text="\nPlease specify the type of graphs you would like to display:\n")
        text_section_3_2.grid(row=1, column=0, columnspan=4, sticky=NSEW)

        self.cl_alpha_ = IntVar()
        self.cl_alpha_.set(0)
        cl_alpha_button = Checkbutton(title_section_3_2, text=" Cl vs alpha", variable=self.cl_alpha_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        cl_alpha_button.grid(row=2, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)
            
        self.cd_alpha_ = IntVar()
        self.cd_alpha_.set(0)
        cd_alpha_button = Checkbutton(title_section_3_2, text=" Cd vs alpha", variable=self.cd_alpha_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        cd_alpha_button.grid(row=3, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cm_alpha_ = IntVar()
        self.cm_alpha_.set(0)
        cm_alpha_button = Checkbutton(title_section_3_2, text=" Cm vs alpha", variable=self.cm_alpha_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        cm_alpha_button.grid(row=4, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.coefficients_convergence_ = IntVar()
        self.coefficients_convergence_.set(0)
        coefficients_convergence_button = Checkbutton(title_section_3_2, text=" Cl, cd, cm convergence", variable=self.coefficients_convergence_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        coefficients_convergence_button.grid(row=5, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cp_xc_ = IntVar()
        self.cp_xc_.set(0)
        cp_xc_button = Checkbutton(title_section_3_2, text=" Cp vs Xc", variable=self.cp_xc_, command=self.activateCpXc, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        cp_xc_button.grid(row=6, column=0, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.axis_cut_cp_xc_ = StringVar()
        self.axis_cut_cp_xc_.set("x")
        self.axis_cut_cp_xc_label_ = ttk.Label(title_section_3_2, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.axis_cut_cp_xc_label_.grid(row=7, column=0, padx=2, pady=2)
        self.axis_cut_cp_xc_entry_ = ttk.Entry(title_section_3_2, textvariable=self.axis_cut_cp_xc_, state="disabled", justify=CENTER, takefocus=0)
        self.axis_cut_cp_xc_entry_.grid(row=7, column=1, padx=2, pady=2, sticky=NSEW)

        self.x_coord_ = DoubleVar()
        self.x_coord_.set(0.0)
        self.x_coord_label_ = ttk.Label(title_section_3_2, text="X coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.x_coord_label_.grid(row=8, column=0, padx=2, pady=2)
        self.x_coord_entry_ = ttk.Entry(title_section_3_2, textvariable=self.x_coord_, state="disabled", justify=CENTER, takefocus=0)
        self.x_coord_entry_.grid(row=8, column=1, padx=2, pady=2, sticky=NSEW)

        self.y_coord_ = DoubleVar()   
        self.y_coord_.set(0.0) 
        self.y_coord_label_ = ttk.Label(title_section_3_2, text="Y coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.y_coord_label_.grid(row=9, column=0, padx=2, pady=2)
        self.y_coord_entry_ = ttk.Entry(title_section_3_2, textvariable=self.y_coord_, state="disabled", justify=CENTER, takefocus=0)
        self.y_coord_entry_.grid(row=9, column=1, padx=2, pady=2, sticky=NSEW)

        self.z_coord_ = DoubleVar()
        self.z_coord_.set(0.0)
        self.z_coord_label_ = ttk.Label(title_section_3_2, text="Z coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.z_coord_label_.grid(row=10, column=0, padx=2, pady=2)
        self.z_coord_entry_ = ttk.Entry(title_section_3_2, textvariable=self.z_coord_, state="disabled", justify=CENTER, takefocus=0)
        self.z_coord_entry_.grid(row=10, column=1, padx=2, pady=2, sticky=NSEW)

        self.residual_convergence_ = IntVar()
        self.residual_convergence_.set(0)
        residual_convergence_button = Checkbutton(title_section_3_2, text=" Residual convergence", variable=self.residual_convergence_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        residual_convergence_button.grid(row=2, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.mach_iso_ = IntVar()
        self.mach_iso_.set(0)
        mach_iso_button = Checkbutton(title_section_3_2, text=" Mach isosurface", variable=self.mach_iso_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        mach_iso_button.grid(row=3, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.mach_contour_ = IntVar()
        self.mach_contour_.set(0)
        mahc_contour_button = Checkbutton(title_section_3_2, text=" Mach contour", variable=self.mach_contour_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        mahc_contour_button.grid(row=4, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.cp_contour_ = IntVar()
        self.cp_contour_.set(0)
        cp_contour_button = Checkbutton(title_section_3_2, text=" Cp contour", variable=self.cp_contour_, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        cp_contour_button.grid(row=5, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.slice_cp_ = IntVar()
        self.slice_cp_.set(0)
        slice_cp_button = Checkbutton(title_section_3_2, text=" Slice Cp", variable=self.slice_cp_, command=self.activateSliceCp, relief="groove", anchor=W, borderwidth=2, takefocus=0)
        slice_cp_button.grid(row=6, column=2, columnspan=2, sticky=NSEW, padx=2, pady=2)

        self.axis_cut_slice_cp_ = StringVar()
        self.axis_cut_slice_cp_.set("x")
        self.axis_cut_slice_cp_label_ = ttk.Label(title_section_3_2, text="Axis of cut", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.axis_cut_slice_cp_label_.grid(row=7, column=2, padx=2, pady=2)
        self.axis_cut_slice_cp_entry_ = ttk.Entry(title_section_3_2, textvariable=self.axis_cut_slice_cp_, state="disabled", justify=CENTER, takefocus=0)
        self.axis_cut_slice_cp_entry_.grid(row=7, column=3, padx=2, pady=2, sticky=N)
        
        self.nb_slices_ = IntVar()
        self.nb_slices_.set(0)
        self.nb_slices_label_ = ttk.Label(title_section_3_2, text="Number of slices", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.nb_slices_label_.grid(row=8, column=2, padx=2, pady=2)
        self.nb_slices_entry_ = ttk.Entry(title_section_3_2, textvariable=self.nb_slices_, state="disabled", justify=CENTER, takefocus=0)
        self.nb_slices_entry_.grid(row=8, column=3, padx=2, pady=2, sticky=N)

        self.first_coord_ = DoubleVar()
        self.first_coord_.set(0.0)
        self.first_coord_label_ = ttk.Label(title_section_3_2, text="First coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.first_coord_label_.grid(row=9, column=2, padx=2, pady=2)
        self.first_coord_entry_ = ttk.Entry(title_section_3_2, textvariable=self.first_coord_, state="disabled", justify=CENTER, takefocus=0)
        self.first_coord_entry_.grid(row=9, column=3, padx=2, pady=2, sticky=N)

        self.last_coord_ = DoubleVar()
        self.last_coord_.set(0.0)
        self.last_coord_label_ = ttk.Label(title_section_3_2, text="Last coord", relief="groove", state="disabled", borderwidth=2, width=15, anchor=CENTER)
        self.last_coord_label_.grid(row=10, column=2, padx=2, pady=2)
        self.last_coord_entry_ = ttk.Entry(title_section_3_2, textvariable=self.last_coord_, state="disabled", justify=CENTER, takefocus=0)
        self.last_coord_entry_.grid(row=10, column=3, padx=2, pady=2, sticky=N)

        ttk.Label(title_section_3_2, text=" ").grid(row=11, column=0, columnspan=4, sticky=NSEW)

    # METHODS
    def activateCpXc(self):
        cp_xc_result = self.cp_xc_.get()

        if cp_xc_result == 1:
            self.axis_cut_cp_xc_label_.configure(state="normal")
            self.axis_cut_cp_xc_entry_.configure(state="normal")
            self.x_coord_label_.configure(state="normal")
            self.x_coord_entry_.configure(state="normal")
            self.y_coord_label_.configure(state="normal")
            self.y_coord_entry_.configure(state="normal")
            self.z_coord_label_.configure(state="normal")
            self.z_coord_entry_.configure(state="normal")

        elif cp_xc_result == 0:
            self.axis_cut_cp_xc_label_.configure(state="disabled")
            self.axis_cut_cp_xc_entry_.configure(state="disabled")
            self.x_coord_label_.configure(state="disabled")
            self.x_coord_entry_.configure(state="disabled")
            self.y_coord_label_.configure(state="disabled")
            self.y_coord_entry_.configure(state="disabled")
            self.z_coord_label_.configure(state="disabled")
            self.z_coord_entry_.configure(state="disabled")

    def activateSliceCp(self):
        slice_cp_result = self.slice_cp_.get()

        if slice_cp_result == 1:
            self.axis_cut_slice_cp_label_.configure(state="normal")
            self.axis_cut_slice_cp_entry_.configure(state="normal")
            self.nb_slices_label_.configure(state="normal")
            self.nb_slices_entry_.configure(state="normal")
            self.first_coord_label_.configure(state="normal")
            self.first_coord_entry_.configure(state="normal")
            self.last_coord_label_.configure(state="normal")
            self.last_coord_entry_.configure(state="normal")

        elif slice_cp_result == 0:
            self.axis_cut_slice_cp_label_.configure(state="disabled")
            self.axis_cut_slice_cp_entry_.configure(state="disabled")
            self.nb_slices_label_.configure(state="disabled")
            self.nb_slices_entry_.configure(state="disabled")
            self.first_coord_label_.configure(state="disabled")
            self.first_coord_entry_.configure(state="disabled")
            self.last_coord_label_.configure(state="disabled")
            self.last_coord_entry_.configure(state="disabled")
    
    def clearPage(self):
        self.cl_alpha_.set(0)
        self.cd_alpha_.set(0)
        self.cm_alpha_.set(0)
        self.coefficients_convergence_.set(0)
        self.residual_convergence_.set(0)
        self.cp_xc_.set(0)
        self.mach_iso_.set(0)
        self.mach_contour_.set(0)
        self.cp_contour_.set(0)
        self.slice_cp_.set(0)
        self.axis_cut_cp_xc_.set("x")
        self.axis_cut_slice_cp_.set("x")
        self.x_coord_.set(0.0)
        self.y_coord_.set(0.0)
        self.z_coord_.set(0.0)
        self.first_coord_.set(0.0)
        self.last_coord_.set(0.0)
        self.nb_slices_.set(0)
        self.files_type_.set(0)

        self.axis_cut_cp_xc_label_.configure(state="disabled")
        self.axis_cut_cp_xc_entry_.configure(state="disabled")
        self.axis_cut_slice_cp_label_.configure(state="disabled")
        self.axis_cut_slice_cp_entry_.configure(state="disabled")
        self.x_coord_label_.configure(state="disabled")
        self.x_coord_entry_.configure(state="disabled")
        self.y_coord_label_.configure(state="disabled")
        self.y_coord_entry_.configure(state="disabled")
        self.z_coord_label_.configure(state="disabled")
        self.z_coord_entry_.configure(state="disabled")
        self.nb_slices_label_.configure(state="disabled")
        self.nb_slices_entry_.configure(state="disabled")
        self.first_coord_label_.configure(state="disabled")
        self.first_coord_entry_.configure(state="disabled")
        self.last_coord_label_.configure(state="disabled")
        self.last_coord_entry_.configure(state="disabled")

    def writePartialOutput(self):

        cl_alpha_str = str(self.cl_alpha_.get())
        cd_alpha_str = str(self.cd_alpha_.get())
        cm_alpha_str = str(self.cm_alpha_.get())
        coeff_conv_str = str(self.coefficients_convergence_.get())
        res_conv_str = str(self.residual_convergence_.get())
        cp_xc_str = str(self.cp_xc_.get())
        mach_iso_str = str(self.mach_iso_.get())
        mach_cont_str = str(self.mach_contour_.get())
        cp_cont_str = str(self.cp_contour_.get())
        filetype_str = str(self.files_type_.get())
        
        cp_xc_str = str(self.cp_xc_.get())
        if cp_xc_str == "1":
            axis_cp_xc_str = self.axis_cut_cp_xc_.get()
            xcoord_str = str(self.x_coord_.get())
            ycoord_str = str(self.y_coord_.get())
            zcoord_str = str(self.z_coord_.get())
        
        elif cp_xc_str == "0":
            axis_cp_xc_str = "x"
            xcoord_str = "0.0"
            ycoord_str = "0.0"
            zcoord_str = "0.0"

        slice_cp_str = str(self.slice_cp_.get())
        if slice_cp_str == "1":
            axis_slice_cp_str = self.axis_cut_cp_xc_.get()
            firstcoord_str = str(self.first_coord_.get())
            lastcoord_str = str(self.last_coord_.get())
            nb_slice_str = str(self.nb_slices_.get())

        elif slice_cp_str == "0":
            axis_slice_cp_str = "x"
            firstcoord_str = "0.0"
            lastcoord_str = "0.0"
            nb_slice_str = "0"



        partial_output = "\nOUTPUT (0-no 1-yes)"+(
                         "\nfilestype (0-Euler 1-SU2)\n")+(
                         filetype_str)+(
                         "\nclalpha cdalpha cmalpha\n")+(
                         cl_alpha_str+" "+cd_alpha_str+" "+cm_alpha_str)+(
                         "\ncoefficientsconvergence residualconv\n")+(
                         coeff_conv_str+" "+res_conv_str)+(
                         "\ncpxc machcontour cpcontour machisosurface\n")+(
                         cp_xc_str+" "+mach_cont_str+" "+cp_cont_str+" "+mach_iso_str)+(
                         "\nslicecp\n")+(
                         slice_cp_str)+(
                         "\naxiscpxc xcoord ycoord zcoord\n")+(
                         axis_cp_xc_str+" "+xcoord_str+" "+ycoord_str+" "+zcoord_str)+(
                         "\naxisslicecp fcoord lcoord numberofslices\n")+(
                         axis_slice_cp_str+" "+firstcoord_str+" "+lastcoord_str+" "+nb_slice_str)

        return partial_output

    def saveImportedData(self, file_type_var, cl_alpha_var, cd_alpha_var, cm_alpha_var, coeff_conv_var, res_conv_var, cp_xc_var, mach_cont_var, cp_cont_var, 
                        mach_iso_var, slice_cp_var, axis_cp_xc_var, xcood_var, ycoord_var, zcoord_var, axis_slice_cp_var, first_coord_var, last_coord_var, nb_slice_var):

        self.files_type_.set(file_type_var)
        self.cl_alpha_.set(cl_alpha_var)
        self.cd_alpha_.set(cd_alpha_var)
        self.cm_alpha_.set(cm_alpha_var)
        self.coefficients_convergence_.set(coeff_conv_var)
        self.residual_convergence_.set(res_conv_var)
        self.cp_xc_.set(cp_xc_var)
        self.mach_contour_.set(mach_cont_var)
        self.cp_contour_.set(cp_cont_var)
        self.mach_iso_.set(mach_iso_var)

        self.slice_cp_.set(slice_cp_var)
        self.axis_cut_cp_xc_.set(axis_cp_xc_var)
        self.x_coord_.set(xcood_var)
        self.y_coord_.set(ycoord_var)
        self.z_coord_.set(zcoord_var)
        self.axis_cut_slice_cp_.set(axis_slice_cp_var)
        self.first_coord_.set(first_coord_var)
        self.last_coord_.set(last_coord_var)
        self.nb_slices_.set(nb_slice_var)

        if self.cp_xc_.get() == 1:
            self.axis_cut_cp_xc_entry_.configure(state="normal")
            self.axis_cut_cp_xc_label_.configure(state="normal")
            self.x_coord_entry_.configure(state="normal")
            self.x_coord_label_.configure(state="normal")
            self.y_coord_entry_.configure(state="normal")
            self.y_coord_label_.configure(state="normal")
            self.z_coord_entry_.configure(state="normal")
            self.z_coord_label_.configure(state="normal")
        else:
            self.axis_cut_cp_xc_entry_.configure(state="disabled")
            self.axis_cut_cp_xc_label_.configure(state="disabled")
            self.x_coord_entry_.configure(state="disabled")
            self.x_coord_label_.configure(state="disabled")
            self.y_coord_entry_.configure(state="disabled")
            self.y_coord_label_.configure(state="disabled")
            self.z_coord_entry_.configure(state="disabled")
            self.z_coord_label_.configure(state="disabled")

        if self.slice_cp_.get() == 1:
            self.axis_cut_slice_cp_entry_.configure(state="normal")
            self.axis_cut_slice_cp_label_.configure(state="normal")
            self.nb_slices_entry_.configure(state="normal")
            self.nb_slices_label_.configure(state="normal")
            self.first_coord_entry_.configure(state="normal")
            self.first_coord_label_.configure(state="normal")
            self.last_coord_entry_.configure(state="normal")
            self.last_coord_label_.configure(state="normal")
        else:
            self.axis_cut_slice_cp_entry_.configure(state="disabled")
            self.axis_cut_slice_cp_label_.configure(state="disabled")
            self.nb_slices_entry_.configure(state="disabled")
            self.nb_slices_label_.configure(state="disabled")
            self.first_coord_entry_.configure(state="disabled")
            self.first_coord_label_.configure(state="disabled")
            self.last_coord_entry_.configure(state="disabled")
            self.last_coord_label_.configure(state="disabled")
