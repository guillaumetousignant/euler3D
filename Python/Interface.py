import tkinter
from tkinter import *
from tkinter import ttk

# MAIN WINDOW CREATION:
main_window1 = Tk()
main_window1.title("GRAPHICAL USER INTERFACE")

# TABS CREATION FOR THE MAIN WINDOW
tabControl = ttk.Notebook(main_window1)

# Tab 1 -> 1. Input
tab1 = Frame(tabControl)
tabControl.add(tab1, text="1. Input")

# Tab 2 -> 2. Solver
tab2 = Frame(tabControl)
tabControl.add(tab2, text="2. Solver")

# Tab 3 -> 3. Output
tab3 = Frame(tabControl)
tabControl.add(tab3, text="3. Output")

tabControl.pack(fill="both", expand="yes")

# SECTION 1: GEOMETRY AND MESH
title_section1 = LabelFrame(main_window1, text="1.1 Geometry and mesh", padx=20, pady=20)
title_section1.pack(fill="both", expand="yes")

text_section1 = Label(title_section1, text="Please select the desired mesh or geometry:")
text_section1.pack()

# SECTION 2: INPUT PARAMETERS
title_section2 = LabelFrame(main_window1, text="1.2 Input parameters", padx=20, pady=20)
title_section2.pack(fill="both", expand="yes")

text_section2 = Label(title_section2, text="Please specify the required input values:")
text_section2.pack()

# DISPLAYING OF THE MAIN WINDOW (1. Input)
main_window1.mainloop()