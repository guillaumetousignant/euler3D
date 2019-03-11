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

        # GENERAL BUTTONS
        ttk.Button(master, text="Clear all").grid(row=1, column=0, padx=2, pady=2)
        ttk.Button(master, text="Clear this page").grid(row=1, column=1, padx=2, pady=2)
        ttk.Button(master, text="Solve").grid(row=1, column=2, padx=2, pady=2)

    # METHODS
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