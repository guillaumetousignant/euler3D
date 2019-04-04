import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class Solver():
    def __init__(self, master):
        self.master = master
        
        # SECTION 2.1: CONVERGENCE CRITERIA
        title_section_2_1 = ttk.LabelFrame(master, text="2.1 Convergence criteria", labelanchor=N, height=140, width=396)
        title_section_2_1.grid(row=0, column=0, columnspan=3)
        title_section_2_1.grid_propagate(False)
        title_section_2_1.grid_rowconfigure(0, weight=1)
        title_section_2_1.grid_rowconfigure(1, weight=1)
        title_section_2_1.grid_rowconfigure(2, weight=1)
        title_section_2_1.grid_columnconfigure(3, weight=1)

        text_section_2_1 = ttk.Label(title_section_2_1, text="\nPlease specify the required convergence criteria:\n")
        text_section_2_1.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)

        label_void = ttk.Label(title_section_2_1, text="", width=5)
        label_void.grid(row=1, column=0)

        self.max_iter = IntVar()
        self.max_iter.set(300)
        self.max_iter_label = ttk.Label(title_section_2_1, text="Max number of itterations", borderwidth=2, relief="groove", anchor=CENTER)
        self.max_iter_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.max_iter_entry = ttk.Entry(title_section_2_1, textvariable=self.max_iter, width=15, justify=CENTER, takefocus=0)
        self.max_iter_entry.grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        label_void_2 = ttk.Label(title_section_2_1, text="", width=4)
        label_void_2.grid(row=1, column=5)

        self.convergence_crit = IntVar()
        self.convergence_crit.set(-15)
        self.convergence_crit_label = ttk.Label(title_section_2_1, text="Convergence criterion power (1.0eX)", borderwidth=2, relief="groove", anchor=CENTER)
        self.convergence_crit_label.grid(row=2, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.convergence_crit_entry = ttk.Entry(title_section_2_1, textvariable=self.convergence_crit, width=15, justify=CENTER, takefocus=0)
        self.convergence_crit_entry.grid(row=2, column=3, columnspan=2, padx=2, pady=2)

        # SECTION 2.2: SCHEME SELECTION
        title_section_2_2 = ttk.LabelFrame(master, text="2.2 Scheme Selection", labelanchor=N, height=120, width=396)
        title_section_2_2.grid(row=1, column=0, columnspan=3)
        title_section_2_2.grid_propagate(False)

        text_section_2_2 = ttk.Label(title_section_2_2, text="\nPlease select the required flux scheme:\n")
        text_section_2_2.grid(row=0, column=0, columnspan=3, sticky=NSEW, padx=2)

        label_void_3 = ttk.Label(title_section_2_2, text="", width=12)
        label_void_3.grid(row=1, column=0)

        flux_scheme_button = ttk.Button(title_section_2_2, text="Select flux scheme", command=self.selectFluxScheme, width=23, takefocus=0)
        flux_scheme_button.grid(row=1, column=1, sticky=NSEW)

        label_void_4 = ttk.Label(title_section_2_2, text="", width=4)
        label_void_4.grid(row=1, column=2)

        # SECTION 2.3: SOLVER OPTIONS
        title_section_2_3 = ttk.LabelFrame(master, text="2.3 Solver options", labelanchor=N, height=200, width=396)
        title_section_2_3.grid(row=2, column=0, columnspan=3)
        title_section_2_3.grid_propagate(False)

        text_section_2_3 = ttk.Label(title_section_2_3, text="\nPlease select a code option:\n")
        text_section_2_3.grid(row=0, column=0, columnspan=6, sticky=NSEW, padx=2)
        
        label_void_5 = ttk.Label(title_section_2_3, text="", width=5)
        label_void_5.grid(row=1, column=0)
        
        self.nb_process = IntVar()
        self.nb_process.set(1)
        self.nb_process_label = ttk.Label(title_section_2_3, text="Number of process", relief="groove", borderwidth=2, anchor=CENTER, width=22)
        self.nb_process_label.grid(row=1, column=1, columnspan=2, sticky=NSEW, padx=2, pady=2)
        self.nb_process_entry = ttk.Entry(title_section_2_3, textvariable=self.nb_process, width=15, justify=CENTER, takefocus=0)
        self.nb_process_entry.grid(row=1, column=3, columnspan=2, padx=2, pady=2)

        label_void_6 = ttk.Label(title_section_2_3, text="", width=4)
        label_void_6.grid(row=1, column=5)
        
        self.solver_option = IntVar()
        self.solver_option.set(3)
        self.solver_option_build = Radiobutton(title_section_2_3, text="Build the code", value=1, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W, takefocus=0)
        self.solver_option_build.grid(row=2, column=1, columnspan=4, padx=2, pady=2)

        self.solver_option_execute = Radiobutton(title_section_2_3, text="Execute the code", value=2, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W, takefocus=0)
        self.solver_option_execute.grid(row=3, column=1, columnspan=4, padx=2, pady=2)

        self.solver_option_build_execute = Radiobutton(title_section_2_3, text="Build and execute the code", value=3, variable=self.solver_option, relief="groove", borderwidth=2, width=23, anchor=W, takefocus=0)
        self.solver_option_build_execute.grid(row=4, column=1, columnspan=4, padx=2, pady=2)

        # INITIALIZATION OF FLUX SCHEME VARIABLES: 
        # those variables have to be initialized before the method is called, otherwise A LOT of problems will be encountered...
        self.flux_scheme = StringVar()
        if self.flux_scheme.get() == "Roe" or self.flux_scheme.get() == "":
            self.flux_scheme.set("Roe")
        else:
            self.flux_scheme.set("Ausm")


        self.scheme_order = StringVar()
        if self.scheme_order.get() == "1" or self.scheme_order.get() == "":
            self.scheme_order.set("1")
        else:
            self.scheme_order.set("2")


        self.gradient = StringVar()
        if self.gradient.get() == "Green Gauss" or self.gradient.get() == "greengauss" or self.gradient.get() == "":
            self.gradient.set("Green Gauss")
        else:
            self.gradient.set("Least Squares")


        self.limiter = StringVar()
        if self.limiter.get() == "Barth Jespersen" or self.limiter.get() == "barthjespersen" or self.limiter.get() == "":
            self.limiter.set("Barth Jespersen")
        else:
            self.limiter.set("Venkatakrishnan")


        self.omega = IntVar()
        if self.omega.get() == -16 or self.omega.get() == 0:
            self.omega.set("-16")
        else:
            self.omega.set(self.omega.get())


        self.k = DoubleVar()
        if self.k.get() == 5.0 or self.k.get() == 0.0:
            self.k.set(5.0)
        else:
            self.k.set(self.k.get())


        self.smoothing = IntVar()
        if self.smoothing.get() == 1:
            self.smoothing.set(1)
        else:
            self.smoothing.set(0)

    # METHODS
    def selectFluxScheme(self):
        self.flux_scheme_window = Toplevel(self.master)
        self.flux_scheme_window.title("Scheme selection")
        self.flux_scheme_window.resizable(0,0)
        self.flux_scheme_window.lift()
        text_flux_scheme_window = ttk.Label(self.flux_scheme_window, text="\nPlease configure the following parameters:\n", anchor=W)
        text_flux_scheme_window.grid(row=0, column=0, columnspan=4, padx=2, sticky=W)
        

        # If statements: to return last values entered (with the state of the labels, if necessary).
        if self.flux_scheme.get() == "Roe" or self.flux_scheme.get() == "":
            self.flux_scheme.set("Roe")
        else:
            self.flux_scheme.set("Ausm")
        self.flux_scheme_label = ttk.Label(self.flux_scheme_window, text="Flux scheme:", anchor=CENTER)
        self.flux_scheme_label.grid(row=1, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.flux_scheme_entry = ttk.Combobox(self.flux_scheme_window, values=("Roe", "Ausm"), width=15, textvariable=self.flux_scheme, justify=CENTER)
        self.flux_scheme_entry.grid(row=2, column=1, columnspan=2, pady=2)
        

        if self.scheme_order.get() == "1" or self.scheme_order.get() == "":
            self.scheme_order.set("1")
        else:
            self.scheme_order.set("2")
        self.scheme_order_label = ttk.Label(self.flux_scheme_window, text="Scheme order:", anchor=CENTER)
        self.scheme_order_label.grid(row=3, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.scheme_order_entry = ttk.Combobox(self.flux_scheme_window, values=("1", "2"), width=15, textvariable=self.scheme_order, justify=CENTER)
        self.scheme_order_entry.grid(row=4, column=1, columnspan=2, pady=2)
        self.scheme_order_entry.bind('<<ComboboxSelected>>', self.activateGradientAndLimiter)


        if self.gradient.get() == "Green Gauss" or self.gradient.get() == "greengauss" or self.gradient.get() == "":
            self.gradient.set("Green Gauss")
        else:
            self.gradient.set("Least Squares")
        self.gradient_label = ttk.Label(self.flux_scheme_window, text="Gradient:", anchor=CENTER, state="disabled")
        self.gradient_label.grid(row=5, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.gradient_entry = ttk.Combobox(self.flux_scheme_window, values=("Green Gauss", "Least Squares"), width=15, state="disabled", textvariable=self.gradient, justify=CENTER)
        self.gradient_entry.grid(row=6, column=1, columnspan=2, pady=2)
        if self.scheme_order.get() == "2":
            self.gradient_label.configure(state="normal")
            self.gradient_entry.configure(state="normal")
        else:
            self.gradient_label.configure(state="disabled")
            self.gradient_entry.configure(state="disabled")
        

        if self.limiter.get() == "Barth Jespersen" or self.limiter.get() == "barthjespersen" or self.limiter.get() == "":
            self.limiter.set("Barth Jespersen")
        else:
            self.limiter.set("Venkatakrishnan")
        self.limiter_label = ttk.Label(self.flux_scheme_window, text="Limiter:", anchor=CENTER, state="disabled")
        self.limiter_label.grid(row=7, column=1, columnspan=2, padx=2, pady=2, sticky=NSEW)
        self.limiter_entry = ttk.Combobox(self.flux_scheme_window, values=("Barth Jespersen", "Venkatakrishnan"), width=15, state="disabled", textvariable=self.limiter, justify=CENTER)
        self.limiter_entry.grid(row=8, column=1, columnspan=2, pady=2)
        self.limiter_entry.bind('<<ComboboxSelected>>', self.activateOmegaOrK)
        if self.scheme_order.get() == "2":
            self.limiter_label.configure(state="normal")
            self.limiter_entry.configure(state="normal")
        else:
            self.limiter_label.configure(state="disabled")
            self.limiter_entry.configure(state="disabled")


        if self.omega.get() == -16 or self.omega.get() == 0:
            self.omega.set(-16)
        else:
            self.omega.set(self.omega.get())
        self.omega_label = ttk.Label(self.flux_scheme_window, text="Omega power\n(1.0eX)", width=13, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.omega_label.grid(row=9, column=0, padx=2, pady=7)
        self.omega_entry = ttk.Entry(self.flux_scheme_window, textvariable=self.omega, width=10, state="disabled", justify=CENTER)
        self.omega_entry.grid(row=9, column=1, padx=2, pady=10)
        if self.scheme_order.get() == "2" and self.limiter.get() == "Barth Jespersen":
            self.omega_label.configure(state="normal")
            self.omega_entry.configure(state="normal")
        else:
            self.omega_label.configure(state="disabled")
            self.omega_entry.configure(state="disabled")


        if self.k.get() == 5.0 or self.k.get() == 0.0:
            self.k.set(5.0)
        else:
            self.k.set(self.k.get())
        self.k_label = ttk.Label(self.flux_scheme_window, text="k", width=13, anchor=CENTER, borderwidth=2, relief="groove", state="disabled")
        self.k_label.grid(row=9, column=2, padx=2, pady=7)
        self.k_entry = ttk.Entry(self.flux_scheme_window, textvariable=self.k, width=10, state="disabled", justify=CENTER)
        self.k_entry.grid(row=9, column=3, padx=2, pady=10)
        if self.scheme_order.get() == "2" and self.limiter.get() == "Venkatakrishnan":
            self.k_label.configure(state="normal")
            self.k_entry.configure(state="normal")
        else:
            self.k_label.configure(state="disabled")
            self.k_entry.configure(state="disabled")


        if self.smoothing.get() == 1:
            self.smoothing.set(1)
        else:
            self.smoothing.set(0)
        self.smoothing_label = ttk.Label(self.flux_scheme_window, text="Residual smoothing?", anchor=CENTER)
        self.smoothing_label.grid(row=10, column=1, columnspan=2, padx=2)
        
        self.smoothing_yes = Radiobutton(self.flux_scheme_window, text="Yes", value=1, variable=self.smoothing, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_yes.grid(row=11, column=1, columnspan=2, padx=2, pady=2)

        self.smoothing_no = Radiobutton(self.flux_scheme_window, text="No", value=0, variable=self.smoothing, relief="groove", borderwidth=2, width=8, anchor=W)
        self.smoothing_no.grid(row=12, column=1, columnspan=2, padx=2, pady=2)

        ok_button = ttk.Button(self.flux_scheme_window, text="Ok", command=self.saveAndDestroyWindow)
        ok_button.grid(row=13, column=1, pady=10)

        cancel_button = ttk.Button(self.flux_scheme_window, text="Cancel", command=self.flux_scheme_window.destroy)
        cancel_button.grid(row=13, column=2, pady=10)

    def activateGradientAndLimiter(self, event):
        scheme_order_result = self.scheme_order_entry.get()

        if scheme_order_result == "2":
            self.gradient_label.configure(state="normal")
            self.gradient_entry.configure(state="normal")

            self.limiter_label.configure(state="normal")
            self.limiter_entry.configure(state="normal")

            self.omega_label.configure(state="normal")
            self.omega_entry.configure(state="normal")

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
        self.writePartialOutputFluxScheme()
        self.flux_scheme_window.destroy()

    def clearPage(self):
        self.max_iter.set(0)
        self.convergence_crit.set(0)
        self.nb_process.set(0)
        self.solver_option.set(3)

        self.flux_scheme.set("Roe")
        self.scheme_order.set("1")
        self.gradient.set("Green Gauss")
        self.limiter.set("Barth Jespersen")
        self.omega.set(6)
        self.k.set(5.0)
        self.smoothing.set(1)

    def writePartialOutputFluxScheme(self):
        smoothing_str = str(self.smoothing.get())
        flux_scheme_str = self.flux_scheme.get().lower()
        scheme_order_str = self.scheme_order.get()
        
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
        
        self.partial_output_flux_scheme = "\nresidual smoothing (0-no 1-yes)\n" + smoothing_str + (
                                          "\nfluxscheme schemeorder\n" + flux_scheme_str + " " + scheme_order_str) + (
                                          "\ngradient limiter\n" + gradient_str + " " + limiter_str) + (
                                          "\nomega k\n" + omega_str + " " + k_str)
        
        return self.partial_output_flux_scheme

    def writePartialOutput(self):
        nb_niter_max_str = str(self.max_iter.get())
        conv_criterion_str = str(self.convergence_crit.get())
        
        solver_option = self.solver_option.get()
        if solver_option == 1:
            build_str = "1"
            execute_str = "0"
        
        elif solver_option == 2:
            build_str = "0"
            execute_str = "1"
        
        elif solver_option == 3:
            build_str = "1"
            execute_str = "1"
        
        if 'self.partial_output_flux_scheme' in globals():
            partial_output = "\nnbitermax convcriterion\n" + nb_niter_max_str + " " + conv_criterion_str + self.partial_output_flux_scheme + "\nEXECUTABLE (0-no 1-yes)\nbuild execute\n" + build_str + " " + execute_str
        
        else:
            smoothing_str = str(self.smoothing.get())
            flux_scheme_str = self.flux_scheme.get().lower()
            scheme_order_str = self.scheme_order.get()
        
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

            self.partial_output_flux_scheme = "\nresidual smoothing (0-no 1-yes)\n" + smoothing_str + (
                                          "\nfluxscheme schemeorder\n" + flux_scheme_str + " " + scheme_order_str) + (
                                          "\ngradient limiter\n" + gradient_str + " " + limiter_str) + (
                                          "\nomega k\n" + omega_str + " " + k_str)
            
            partial_output = "\nnbitermax convcriterion\n" + nb_niter_max_str + " " + conv_criterion_str + self.partial_output_flux_scheme + "\nEXECUTABLE (0-no 1-yes)\nbuild execute\n" + build_str + " " + execute_str                   
        
        return partial_output

    def saveImportedData(self, nb_iter_max_var, conv_criterion_var, build_var, execute_var, smoothing_var, flux_scheme_var, scheme_order_var, gradient_var, limiter_var, omega_var, k_var):
        self.max_iter.set(nb_iter_max_var)
        self.convergence_crit.set(conv_criterion_var)

        if build_var == "1" and execute_var == "0":
            self.solver_option.set(1)

        elif build_var == "0" and execute_var == "1":
            self.solver_option.set(2)

        elif build_var == "1" and execute_var == "1":
            self.solver_option.set(3)

        self.smoothing.set(smoothing_var)
        self.flux_scheme.set(flux_scheme_var)
        self.scheme_order.set(scheme_order_var)
        self.gradient.set(gradient_var)
        self.limiter.set(limiter_var)
        self.omega.set(omega_var)
        self.k.set(k_var)