import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from input import Input
from output import Output


class Interface():
    def __init__(self, master): # Initialize the class
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

        # SECTION 1: INPUT
        self.input = Input(tab1)

        # SECTION 2: SOLVER
        self.solver = Solver(tab2)

        # SECTION 3: OUTPUT
        self.output = Output(tab3)
    

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

        max_iter_label = ttk.Label(title_section_2_1, text="Max number of itterations", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        max_iter_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        max_iter_entry = ttk.Entry(title_section_2_1, width=15)
        max_iter_entry.grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        ttk.Label(title_section_2_1, text="", width=4).grid(row=1, column=5)

        convergence_crit_label = ttk.Label(title_section_2_1, text="Convergence criterion", borderwidth=2, relief="groove", anchor=CENTER, width=22)
        convergence_crit_label.grid(row=2, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        convergence_crit_entry = ttk.Entry(title_section_2_1, width=15)
        convergence_crit_entry.grid(row=2, column=3, columnspan=2, padx=2, pady=2)

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
        
        solver_option_build = Radiobutton(title_section_2_3, text="Build the code", value=1, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build.grid(row=2, column=1, columnspan=4, padx=2, pady=2)

        solver_option_execute = Radiobutton(title_section_2_3, text="Execute the code", value=2, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_execute.grid(row=3, column=1, columnspan=4, padx=2, pady=2)

        solver_option_build_execute = Radiobutton(title_section_2_3, text="Build and execute the code", value=3, relief="groove", borderwidth=2, width=23, anchor=W)
        solver_option_build_execute.grid(row=4, column=1, columnspan=4, padx=2, pady=2)

        # GENERAL BUTTONS
        ttk.Button(master, text="Clear all").grid(row=3, column=0, padx=2, pady=2)
        ttk.Button(master, text="Clear this page").grid(row=3, column=1, padx=2, pady=2)
        ttk.Button(master, text="Solve").grid(row=3, column=2, padx=2, pady=2)

    # METHODS
    def selectFluxScheme(self):
        self.newWindow = Toplevel(self.master)
        self.flux_Scheme = SelectFluxScheme(self.newWindow)


class SelectFluxScheme():
    def __init__(self, master):
        self.master = master

        self.master.title("Scheme selection")
        ttk.Label(self.master, text="\nPlease configure the following parameters:\n", anchor=W).grid(row=0, column=0, columnspan=4, padx=2, sticky=W)
        
        self.flux_scheme_label = ttk.Label(self.master, text="Flux scheme:", anchor=CENTER)
        self.flux_scheme_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.flux_scheme_entry = ttk.Combobox(self.master, values=("Roe", "Ausm"), width=15)
        self.flux_scheme_entry.grid(row=2, column=1, columnspan=2, pady=2)
        
        self.scheme_order_label = ttk.Label(self.master, text="Scheme order:", anchor=CENTER)
        self.scheme_order_label.grid(row=3, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.scheme_order_entry = ttk.Combobox(self.master, values=("1", "2"), width=15)
        self.scheme_order_entry.grid(row=4, column=1, columnspan=2, pady=2)
        self.scheme_order_entry.bind('<<ComboboxSelected>>', self.activateGradientAndLimiter)
        
        self.gradient_label = ttk.Label(self.master, text="Gradient:", anchor=CENTER, state="disabled")
        self.gradient_label.grid(row=5, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.gradient_entry = ttk.Combobox(self.master, values=("Green Gauss", "Least Squares"), width=15, state="disabled")
        self.gradient_entry.grid(row=6, column=1, columnspan=2, pady=2)

        self.limiter_label = ttk.Label(self.master, text="Limiter:", anchor=CENTER, state="disabled")
        self.limiter_label.grid(row=7, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.limiter_entry = ttk.Combobox(self.master, values=("Barth Jespersen", "Venkatakrishnan"), width=15, state="disabled")
        self.limiter_entry.grid(row=8, column=1, columnspan=2, pady=2)
        self.limiter_entry.bind('<<ComboboxSelected>>', self.activateOmegaOrK)

        self.omega_label = ttk.Label(self.master, text="Omega", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.omega_label.grid(row=9, column=0, padx=2, pady=7)
        self.omega_entry = ttk.Entry(self.master, width=10, state="disabled")
        self.omega_entry.grid(row=9, column=1, padx=2, pady=10)

        self.k_label = ttk.Label(self.master, text="k", width=10, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.k_label.grid(row=9, column=2, padx=2, pady=7)
        self.k_entry = ttk.Entry(self.master, width=10, state="disabled")
        self.k_entry.grid(row=9, column=3, padx=2, pady=10)

        ttk.Label(self.master, text="Residual smoothing?", anchor=CENTER).grid(row=10, column=1, columnspan=2, padx=2)
        
        self.smoothing_yes = Radiobutton(self.master, text="Yes", value=1, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_yes.grid(row=11, column=1, columnspan=2, padx=2, pady=2)

        self.smoothing_no = Radiobutton(self.master, text="No", value=2, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_no.grid(row=12, column=1, columnspan=2, padx=2, pady=2)

        ttk.Button(self.master, text="Ok", command=self.master.destroy).grid(row=13, column=1, pady=10)
        ttk.Button(self.master, text="Cancel", command=self.master.destroy).grid(row=13, column=2, pady=10)
    
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


root = Tk()
main_window = Interface(root)
root.mainloop()