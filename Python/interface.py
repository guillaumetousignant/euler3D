import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
import os.path
from input import Input
from solver import Solver
from output import Output


class Interface(Input, Solver, Output):
    def __init__(self, master): # Initialize the class
        master.title("GRAPHICAL USER INTERFACE")
        master.geometry("397x485")
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

        # SECTION 1: INPUT
        self.input = Input(tab1)

        # SECTION 2: SOLVER
        self.solver = Solver(tab2)

        # SECTION 3: OUTPUT
        self.output = Output(tab3)

        # GENERAL BUTTONS
        clear_all_button_intput = ttk.Button(tab1, text="Clear All", command=self.clearAllPages)
        clear_all_button_intput.grid(row=2, column=0, padx=2, pady=2)

        clear_all_button_solver = ttk.Button(tab2, text="Clear All", command=self.clearAllPages)
        clear_all_button_solver.grid(row=3, column=0, padx=2, pady=2)

        clear_all_button_output = ttk.Button(tab3, text="Clear All", command=self.clearAllPages)
        clear_all_button_output.grid(row=2, column=0, padx=2, pady=2)

        clear_button_input = ttk.Button(tab1, text="Clear this page", command=self.input.clearPage)
        clear_button_input.grid(row=2, column=1, padx=2, pady=2)

        clear_button_solver = ttk.Button(tab2, text="Clear this page", command=self.solver.clearPage)
        clear_button_solver.grid(row=3, column=1, padx=2, pady=2)

        clear_button_output = ttk.Button(tab3, text="Clear this page", command=self.output.clearPage)
        clear_button_output.grid(row=2, column=1, padx=2, pady=2)

        # solve_button_input = ttk.Button(tab1, text="Solve", command=self.solve)
        # solve_button_input.grid(row=3, column=2, padx=2, pady=2)

        # solve_button_solver = ttk.Button(tab1, text="Solve", command=self.solve)
        # solve_button_solver.grid(row=3, column=2, padx=2, pady=2)

        # solve_button_output = ttk.Button(tab1, text="Solve", command=self.solve)
        # solve_button_output.grid(row=3, column=2, padx=2, pady=2)

    def clearAllPages(self):
        self.input.clearPage()
        self.solver.clearPage()
        self.output.clearPage()

    def save_entry(self):

        # input = self.input.writePartialOutput()
        # solver = self.solver.writePartialOutput()
        # output = self.output.writePartialOutput()

        file_path = '/home/etudiant/Documents/'
        file_name = "output_interface.txt"

        complete_file_name = os.path.join(file_path, file_name)

        file = open(complete_file_name,"w")

        # file.write(input+solver+output)
        file.write("Hey, keep up the good work!")
        file.close()        


root = Tk()
main_window = Interface(root)
root.mainloop()
main_window.save_entry()
