import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
from input import Input
from solver import Solver
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
    

root = Tk()
main_window = Interface(root)
root.mainloop()