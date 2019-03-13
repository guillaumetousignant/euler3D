import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class Solver():
    def __init__(self, master):
        self.master = master
        
        # SECTION 2.1: CONVERGENCE CRITERIA
        title_section_2_1 = ttk.LabelFrame(master, text="2.1 Convergence criteria", labelanchor=N, height=130, width=396)
        title_section_2_1.grid(row=0, column=0, columnspan=3)
        title_section_2_1.grid_propagate(False)

        text_section_2_1 = ttk.Label(title_section_2_1, text="\nPlease specify the required convergence criteria:\n")
        text_section_2_1.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)

        ttk.Label(title_section_2_1, text="", width=5).grid(row=1, column=0)

        self.max_iter_entry = IntVar()
        max_iter_label = ttk.Label(title_section_2_1, text="Max number of itterations", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        max_iter_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        ttk.Entry(title_section_2_1, textvariable=self.max_iter_entry, width=15).grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        ttk.Label(title_section_2_1, text="", width=4).grid(row=1, column=5)

        self.convergence_crit_entry = DoubleVar()
        convergence_crit_label = ttk.Label(title_section_2_1, text="Convergence criterion", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        convergence_crit_label.grid(row=2, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        ttk.Entry(title_section_2_1, textvariable=self.convergence_crit_entry, width=15).grid(row=2, column=3, columnspan=2, padx=2, pady=2)

        # SECTION 2.2: SCHEME SELECTION
        title_section_2_2 = ttk.LabelFrame(master, text="2.2 Scheme Selection", labelanchor=N, height=110, width=396)
        title_section_2_2.grid(row=1, column=0, columnspan=3)
        title_section_2_2.grid_propagate(False)

        text_section_2_2 = ttk.Label(title_section_2_2, text="\nPlease select the required flux scheme:\n")
        text_section_2_2.grid(row=0, column=0, columnspan=3, sticky=NSEW, padx=2)

        ttk.Label(title_section_2_2, text="", width=12).grid(row=1, column=0)

        flux_scheme = ttk.Button(title_section_2_2, text="Select flux scheme", command=self.selectFluxScheme, width=23)
        flux_scheme.grid(row=1, column=1, sticky=NSEW)

        ttk.Label(title_section_2_2, text="", width=4).grid(row=1, column=2)

        # SECTION 2.3: SOLVER OPTIONS
        title_section_2_3 = ttk.LabelFrame(master, text="2.3 Solver options", labelanchor=N, height=190, width=396)
        title_section_2_3.grid(row=2, column=0, columnspan=3)
        title_section_2_3.grid_propagate(False)

        text_section_2_3 = ttk.Label(title_section_2_3, text="\nPlease select a code option:\n")
        text_section_2_3.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)
        
        ttk.Label(title_section_2_3, text="", width=5).grid(row=1, column=0)
        
        ttk.Label(title_section_2_3, text="Number of process", relief="groove", borderwidth=2, anchor=CENTER, width=22).grid(row=1, column=1, columnspan=2, sticky=NSEW, padx=2, pady=2)
        ttk.Entry(title_section_2_3, width=15).grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        ttk.Label(title_section_2_3, text="", width=4).grid(row=1, column=5)
        
        self.solver_option = IntVar()
        solver_option_build = Radiobutton(title_section_2_3, text="Build the code", value=1, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build.grid(row=2, column=1, columnspan=4, padx=2, pady=2)

        solver_option_execute = Radiobutton(title_section_2_3, text="Execute the code", value=2, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_execute.grid(row=3, column=1, columnspan=4, padx=2, pady=2)

        solver_option_build_execute = Radiobutton(title_section_2_3, text="Build and execute the code", value=3, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build_execute.grid(row=4, column=1, columnspan=4, padx=2, pady=2)

        # GENERAL BUTTONS
        ttk.Button(master, text="Clear all").grid(row=3, column=0, padx=2, pady=2)
        ttk.Button(master, text="Clear this page").grid(row=3, column=1, padx=2, pady=2)
        ttk.Button(master, text="Solve").grid(row=3, column=2, padx=2, pady=2)

    # METHODS
    def selectFluxScheme(self):
        self.newWindow = Toplevel(self.master)
        self.flux_Scheme = SelectFluxScheme(self.newWindow)

    def writePartialOutput(self):
               
        nbnitermax_str = str(self.max_iter_entry.get())
        convcriterion_str = str(self.convergence_crit_entry.get())
        
        solveroption = self.solver_option.get()
        if solveroption == 1:
            build_str = "1"
            execute_str = "0"
        
        elif solveroption == 2:
            build_str = "0"
            execute_str = "1"
        
        elif solveroption == 3:
            build_str = "1"
            execute_str = "1"

        partial_output = "\nnbitermax convcriterion\n"+nbnitermax_str+" "+convcriterion_str+self.flux_Scheme.writePartialOutput()+"\nEXECUTABLE (0-no 1-yes)\nbuild execute\n"+build_str+" "+execute_str
        return partial_output


class SelectFluxScheme():
    def __init__(self, master):
        self.master = master

        self.master.title("Scheme selection")
        ttk.Label(self.master, text="\nPlease configure the following parameters:\n", anchor=W).grid(row=0, column=0, columnspan=4, padx=2, sticky=W)
        
        self.flux_scheme = StringVar()
        self.flux_scheme_label = ttk.Label(self.master, text="Flux scheme:", anchor=CENTER)
        self.flux_scheme_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.flux_scheme_entry = ttk.Combobox(self.master, values=("Roe", "Ausm"), textvariable=self.flux_scheme, width=15)
        self.flux_scheme_entry.grid(row=2, column=1, columnspan=2, pady=2)
        
        self.scheme_order = StringVar()
        self.scheme_order_label = ttk.Label(self.master, text="Scheme order:", anchor=CENTER)
        self.scheme_order_label.grid(row=3, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.scheme_order_entry = ttk.Combobox(self.master, values=("1", "2"), textvariable=self.scheme_order, width=15)
        self.scheme_order_entry.grid(row=4, column=1, columnspan=2, pady=2)
        self.scheme_order_entry.bind('<<ComboboxSelected>>', self.activateGradientAndLimiter)
        
        self.gradient = StringVar()
        self.gradient_label = ttk.Label(self.master, text="Gradient:", anchor=CENTER, state="disabled")
        self.gradient_label.grid(row=5, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.gradient_entry = ttk.Combobox(self.master, values=("Green Gauss", "Least Squares"), textvariable = self.gradient, width=15, state="disabled")
        self.gradient_entry.grid(row=6, column=1, columnspan=2, pady=2)

        self.limiter = StringVar()
        self.limiter_label = ttk.Label(self.master, text="Limiter:", anchor=CENTER, state="disabled")
        self.limiter_label.grid(row=7, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.limiter_entry = ttk.Combobox(self.master, values=("Barth Jespersen", "Venkatakrishnan"), textvariable=self.limiter, width=15, state="disabled")
        self.limiter_entry.grid(row=8, column=1, columnspan=2, pady=2)
        self.limiter_entry.bind('<<ComboboxSelected>>', self.activateOmegaOrK)

        self.omega = IntVar()
        self.omega_label = ttk.Label(self.master, text="Omega power (1.0eX)", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.omega_label.grid(row=9, column=0, padx=2, pady=7)
        self.omega_entry = ttk.Entry(self.master, textvariable=self.omega, width=10, state="disabled")
        self.omega_entry.grid(row=9, column=1, padx=2, pady=10)

        self.k = DoubleVar()
        self.k_label = ttk.Label(self.master, text="k", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.k_label.grid(row=9, column=2, padx=2, pady=7)
        self.k_entry = ttk.Entry(self.master, textvariable=self.k, width=10, state="disabled")
        self.k_entry.grid(row=9, column=3, padx=2, pady=10)

        ttk.Label(self.master, text="Residual smoothing?", anchor=CENTER).grid(row=10, column=1, columnspan=2, padx=2)
        
        self.smoothing = IntVar()
        self.smoothing_yes = Radiobutton(self.master, text="Yes", value=1, variable=self.smoothing, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_yes.grid(row=11, column=1, columnspan=2, padx=2, pady=2)

        self.smoothing_no = Radiobutton(self.master, text="No", value=0, variable=self.smoothing, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_no.grid(row=12, column=1, columnspan=2, padx=2, pady=2)

        ttk.Button(self.master, text="Ok", command=self.saveAndDestroyWindow).grid(row=13, column=1, pady=10)
        ttk.Button(self.master, text="Cancel", command=self.master.destroy).grid(row=13, column=2, pady=10)
    
    def activateGradientAndLimiter(self, event):
        scheme_order_result = self.scheme_order_entry.get()

        if scheme_order_result == "2":
            self.gradient_label.configure(state="normal")
            self.gradient_entry.configure(state="normal")

            self.limiter_label.configure(state="normal")
            self.limiter_entry.configure(state="normal")

        elif scheme_order_result == "1":
            self.gradient_label.configure(state="disabled")
            self.gradient_entry.configure(state="disabled")

            self.limiter_label.configure(state="disabled")
            self.limiter_entry.configure(state="disabled")

            self.omega_label.configure(state="disabled")
            self.omega_entry.configure(state="disabled")
            
            self.k_label.configure(state="disabled")
            self.k_entry.configure(state="disabled")

    def activateOmegaOrK(self, event):
        limiter_result = self.limiter_entry.get()
        
        if limiter_result == "Barth Jespersen":
            self.omega_label.configure(state="normal")
            self.omega_entry.configure(state="normal")

            self.k_label.configure(state="disabled")
            self.k_entry.configure(state="disabled")

        elif limiter_result == "Venkatakrishnan":
            self.k_label.configure(state="normal")
            self.k_entry.configure(state="normal")

            self.omega_label.configure(state="disabled")
            self.omega_entry.configure(state="disabled")
    
    def saveAndDestroyWindow(self):
        self.writePartialOutput()
        self.master.destroy()

    def writePartialOutput(self):
        smoothing_str = str(self.smoothing.get())
        fluxscheme_str = self.flux_scheme.get().lower()
        schemeorder_str = self.scheme_order.get()
        
        gradient_str = self.gradient.get()
        if gradient_str == "Green Gauss":
            gradient_str = "greengauss"
        
        elif gradient_str == "Least Squares":
            gradient_str = "leastsquares"
        
        limiter_str = self.limiter.get()
        if limiter_str == "Barth Jespersen":
            limiter_str = "barthjespersen"
        
        elif limiter_str == "Venkatakrishnan":
            limiter_str = "venkatakrishnan"
        
        omega_str = str(self.omega.get())
        omega_str = "1.0e"+omega_str
        k_str = str(self.k.get()) 

        partial_output ="\nresidual smoothing (0-no 1-yes)\n" + smoothing_str + (
                        "\nfluxscheme schemeorder\n" + fluxscheme_str + " " + schemeorder_str) + (
                        "\ngradient limiter\n" + gradient_str + " " + limiter_str) + (
                        "\nomega k\n" + omega_str + " " + k_str)
        
        return partial_output
        
        
        