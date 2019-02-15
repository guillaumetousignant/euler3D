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

##################### 1. INPUT #####################
# SECTION 1.1: GEOMETRY AND MESH
title_section_1_1 = LabelFrame(tab1, text="1.1 Geometry and mesh", padx=20, pady=20)
title_section_1_1.pack(fill="both", expand="yes")

text_section_1_1 = Label(title_section_1_1, text="Please select the desired mesh or geometry:")
text_section_1_1.pack()

# SECTION 1.2: INPUT PARAMETERS
title_section_1_2 = LabelFrame(tab1, text="1.2 Input parameters", padx=20, pady=20)
title_section_1_2.pack(fill="both", expand="yes")

text_section_1_2 = Label(title_section_1_2, text="Please specify the required input values:")
text_section_1_2.pack()

##################### 2. SOLVER #####################
# SECTION 2.1: CONVERGENCE CRITERIAS
title_section_2_1 = LabelFrame(tab2, text="2.1 Convergence criterias", padx=20, pady=20)
title_section_2_1.pack(fill="both", expand="yes")

text_section_2_1 = Label(title_section_2_1, text="Please specify the required convergence criterias:")
text_section_2_1.pack()

# SECTION 2.2: SCHEME SELECTION
title_section_2_2 = LabelFrame(tab2, text="2.2 Scheme Selection", padx=20, pady=20)
title_section_2_2.pack(fill="both", expand="yes")

text_section_2_2 = Label(title_section_2_2, text="Please select the desired flux scheme:")
text_section_2_2.pack()

# SECTION 2.3: SOLVER OPTIONS
title_section_2_3 = LabelFrame(tab2, text="2.3 Solver Options", padx=20, pady=20)
title_section_2_3.pack(fill="both", expand="yes")

text_section_2_3 = Label(title_section_2_3, text="Please select other code options:")
text_section_2_3.pack()

##################### 3. OUTPUT #####################

# DISPLAYING OF THE MAIN WINDOW
main_window1.mainloop()