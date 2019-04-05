import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
import os
import os.path
import subprocess
from input import Input
from solver import Solver
from output import Output


class Interface(Input, Solver, Output):
    def __init__(self, master): # Initialize the class
        master.title("GRAPHICAL USER INTERFACE")
        master.geometry("397x515")
        master.resizable(0,0)
        
        # TABS OF THE MAIN WINDOW
        tabControl = ttk.Notebook(master)
        tabControl.grid(row=0, column=0, columnspan=10, sticky='NESW')

        tab1 = ttk.Frame(tabControl)
        tabControl.add(tab1, text="1. Input")

        tab2 = ttk.Frame(tabControl)
        tabControl.add(tab2, text="2. Solver")

        tab3 = ttk.Frame(tabControl)
        tabControl.add(tab3, text="3. Output")

        tabControl.select(tab1)
        
        # MENU BAR
        menubar = Menu(master)
        master.config(menu=menubar)

        file_menu = Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Save As", command=self.saveOutputAs)
        file_menu.add_command(label="Import", command=self.importDataFile)

        help_menu = Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Help", menu=help_menu)
        help_menu.add_command(label="User guide", command=self.openUserGuide)

        # SECTION 1: INPUT
        self.input_ = Input(tab1)

        # SECTION 2: SOLVER
        self.solver_ = Solver(tab2)

        # SECTION 3: OUTPUT
        self.output_ = Output(tab3)

        # GENERAL BUTTONS
        clear_all_button_intput = ttk.Button(tab1, text="Clear All", command=self.clearAllPages)
        clear_all_button_intput.grid(row=2, column=0, padx=2, pady=2)

        clear_all_button_solver = ttk.Button(tab2, text="Clear All", command=self.clearAllPages)
        clear_all_button_solver.grid(row=3, column=0, padx=2, pady=2)

        clear_all_button_output = ttk.Button(tab3, text="Clear All", command=self.clearAllPages)
        clear_all_button_output.grid(row=2, column=0, padx=2, pady=2)

        clear_button_input = ttk.Button(tab1, text="Clear this page", command=self.input_.clearPage)
        clear_button_input.grid(row=2, column=1, padx=2, pady=2)

        clear_button_solver = ttk.Button(tab2, text="Clear this page", command=self.solver_.clearPage)
        clear_button_solver.grid(row=3, column=1, padx=2, pady=2)

        clear_button_output = ttk.Button(tab3, text="Clear this page", command=self.output_.clearPage)
        clear_button_output.grid(row=2, column=1, padx=2, pady=2)

        solve_button_input = ttk.Button(tab1, text="Solve", command=self.solveCode)
        solve_button_input.grid(row=2, column=2, padx=2, pady=2)
 
        solve_button_solver = ttk.Button(tab2, text="Solve", command=self.solveCode)
        solve_button_solver.grid(row=3, column=2, padx=2, pady=2)

        solve_button_output = ttk.Button(tab3, text="Solve", command=self.solveCode)
        solve_button_output.grid(row=2, column=2, padx=2, pady=2)
   
    def clearAllPages(self):
        self.input_.clearPage()
        self.solver_.clearPage()
        self.output_.clearPage()
    
    def solveCode(self):
        solver_option = self.solver_.solver_option.get()
        
        if solver_option == 1:
            command = "make"

        elif solver_option == 2:
            # nb_process_str = str(self.solver.nb_process.get())
            # command = "mpiexec -n " + nb_process_str + " ./bin/euler3D ./bin/output_interface"
            command = "./bin/euler3D ./bin/output_interface"

        elif solver_option == 3:
            command = "make clean; make; ./bin/euler3D ./bin/output_interface"
        
        self.saveEntries()
        root.destroy()
        os.system(command)

    def saveEntries(self):

        input_text = self.input_.writePartialOutput()
        solver_text = self.solver_.writePartialOutput()
        output_text = self.output_.writePartialOutput()

        file_path = "../euler3D/bin"
        file_name = "output_interface"

        complete_file_name = os.path.join(file_path, file_name)

        file = open(complete_file_name,"w")

        file.write(input_text + solver_text + output_text)
        file.close()

    def openUserGuide(self):
        print("Hello")
        # file_path = "~/Documents/"
        # file_name = "user_guide.pdf"

        # complete_file_name = os.path.join(file_path, file_name)

        # subprocess.Popen([file_name],shell=True)
    
    def saveOutputAs(self):

        input_text = self.input_.writePartialOutput()
        solver_text = self.solver_.writePartialOutput()
        output_text = self.output_.writePartialOutput()


        filename =  filedialog.asksaveasfilename(initialdir = "/home/etudiant/",title = "Save Output As",filetypes = (("plain text","*.txt"),("all files","*.*")))

        if filename != ():
            file = open(filename,"w")

            file.write(input_text + solver_text + output_text)
            file.close()

            info = filename + " has been created."

            messagebox.showinfo("Output Saved", info)

    def importDataFile(self):
        filename =  filedialog.askopenfilename(initialdir = "/home/etudiant/",title = "Import Data File",filetypes = (("plain text","*.txt"),("all files","*.*")))

        if filename != ():
            file = open(filename, "r")

            file.readline() # "MESH"
            
            file.readline() # "topologyfilename"
            filename, space = file.readline().split("\n") # File name

            file.readline() # "INPUT"
            
            file.readline() # "cfl gamma angleattackdeg"
            a = file.readline()
            cfl, gamma, angleattackdeg = a.split()

            file.readline() # "rkstage mach cmac"
            a = file.readline()
            rkstage, mach, cmac = a.split()

            file.readline() # "nbitermax convcriterion"
            a = file.readline()
            nbitermax, convcriterion = a.split()

            file.readline() # "residual smoothing (0-no 1-yes)"
            smoothing = file.readline()
            
            file.readline() # "fluxscheme schemeorder"
            a = file.readline()
            fluxscheme, schemeorder = a.split()

            file.readline() # "gradient limiter"
            a = file.readline()
            gradient, limiter = a.split()

            file.readline() # "omega k"
            a = file.readline()
            omega, k = a.split()

            file.readline() # "EXECUTABLE (0-no 1-yes)"
            
            file.readline() # "build execute"
            a = file.readline()
            build, execute = a.split()

            file.readline() # "OUTPUT (0-no 1-yes)"

            file.readline() # "filestype (0-Euler 1 -SU2)"
            filestype, space = file.readline().split("\n")
            
            file.readline() # "clalpha cdalpha cmalpha"
            a = file.readline()
            clalpha, cdalpha, cmalpha = a.split()

            file.readline() # "coefficientsconvergence residualconv"
            a = file.readline()
            coefficientsconvergence, residualconv = a.split()

            file.readline() # "cpxc machcontour cpcontour machisosurface"
            a = file.readline()
            cpxc, machcontour, cpcontour, machisosurface = a.split()

            file.readline() # "slicecp"
            slicecp, space = file.readline().split("\n")

            file.readline() # "axiscpxc xcoord ycoord zcoord"
            a = file.readline()
            axiscpxc, xcoord, ycoord, zcoord = a.split()

            file.readline() # "axisslicecp fcoord lcoord numberofslices"
            a = file.readline()
            axisslicecp, fcoord, lcoord, numberofslices = a.split()

            file.close()

            self.input_.saveImportedData(filename, cfl, gamma, angleattackdeg, rkstage, mach, cmac)
            self.solver_.saveImportedData(nbitermax, convcriterion, build, execute, smoothing, fluxscheme, schemeorder, gradient, limiter, omega, k)
            self.output_.saveImportedData(filestype, clalpha, cdalpha, cmalpha, coefficientsconvergence, residualconv, cpxc, machcontour, cpcontour, machisosurface, slicecp, axiscpxc, xcoord, ycoord, zcoord, axisslicecp, fcoord, lcoord, numberofslices)


root = Tk()
main_window = Interface(root)
root.mainloop()
main_window.saveEntries()
