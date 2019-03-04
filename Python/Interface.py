import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog


class MainWindow():
    def __init__(self, master): # Initialize the object
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

        # SECTION 1. INPUT
        # SECTION 1.1 GEOMETRY AND MESH
        title_section_1_1 = ttk.LabelFrame(tab1, text="1.1 Geometry and mesh")
        title_section_1_1.grid(row=0, column=0, columnspan=10)

        text_section_1_1 = ttk.Label(title_section_1_1, text="Please select the desired mesh or geometry: ")
        text_section_1_1.grid(row=0, column=0, columnspan=10, sticky='W')

        import_mesh = Button(title_section_1_1, text="Import mesh", command=self.importMesh)
        import_mesh.grid(row=1, column=1)

        import_geometry = Button(title_section_1_1, text="Import geometry", command=self.importGeometry)
        import_geometry.grid(row=1, column=3)

        generate_geometry = Button(title_section_1_1, text="Generate geometry", command=self.generateGeometry)
        generate_geometry.grid(row=1, column=5)

        show_resulting_mesh = Button(title_section_1_1, text="Show resulting mesh", command=self.showResultingMesh)
        show_resulting_mesh.grid(row=2, column=3)

        # SECTION 1.2 INPUT VALUES
        title_section_1_2 = ttk.LabelFrame(tab1, text="1.2 Input parameters")
        title_section_1_2.grid(row=1, column=0, columnspan=10)

        text_section_1_2 = ttk.Label(title_section_1_2, text="Please specify the required input values: ")
        text_section_1_2.grid(row=0, column=0, columnspan=10, sticky='W')

        ttk.Label(title_section_1_2, text="cfl").grid(row=1, column=0)
        ttk.Entry(title_section_1_2).grid(row=1, column=1)

        ttk.Label(title_section_1_2, text="gamma").grid(row=2, column=0)
        ttk.Entry(title_section_1_2).grid(row=2, column=1)

        ttk.Label(title_section_1_2, text="mach").grid(row=3, column=0)
        ttk.Entry(title_section_1_2).grid(row=3, column=1)

        ttk.Label(title_section_1_2, text="cmac").grid(row=1, column=2)
        ttk.Entry(title_section_1_2).grid(row=1, column=3)

        ttk.Label(title_section_1_2, text="Angle of attack (deg)").grid(row=2, column=2)
        ttk.Entry(title_section_1_2).grid(row=2, column=3)

        ttk.Label(title_section_1_2, text="Number of stages (RK)").grid(row=3, column=2)
        ttk.Entry(title_section_1_2).grid(row=3, column=3)

        # label_nb_block = ttk.Label(title_section_1_1, text="Number of blocks")
        # label_nb_block.grid(row=4, column=2, columnspan=2)

        # nb_block = ttk.Entry(title_section_1_1)
        # nb_block.grid(row=4, column=4, columnspan=2)

        # nb_process = Frame(text="Number of process")
        # nb_process.grid()

    def importMesh(self):
        self.meshwindow = Tk()
        self.meshwindow.title("Mesh importation")
        ttk.Label(self.meshwindow, text="Import the desired mesh: ").grid(row=0, column=0)
        ttk.Button(self.meshwindow, text="Select a file", command=self.meshFileDialog).grid(row=1, column=2)
        ttk.Button(self.meshwindow, text="Ok", command=self.meshwindow.destroy).grid(row=2, column=1)
        ttk.Button(self.meshwindow, text="Cancel", command=self.meshwindow.destroy).grid(row=2, column=2)

    def meshFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label = ttk.Label(self.meshwindow, text="")
        self.label.grid(row=1, column=1)
        self.label.configure(text=self.filename)

    def importGeometry(self):
        self.geometrywindow = Tk()
        self.geometrywindow.title("Geometry importation")
        ttk.Label(self.geometrywindow, text="Import the desired geometry: ").grid(row=0, column=0)
        ttk.Button(self.geometrywindow, text="Select a file", command=self.geometryFileDialog).grid(row=1, column=2)
        ttk.Button(self.geometrywindow, text="Ok", command=self.geometrywindow.destroy).grid(row=2, column=1)
        ttk.Button(self.geometrywindow, text="Cancel", command=self.geometrywindow.destroy).grid(row=2, column=2)

    def geometryFileDialog(self):
        self.filename = filedialog.askopenfilename(initialdir="/", title="Select a file", filetypes=(("jpeg", "*.jpg"),("All Files", "*.*")))
        self.label = ttk.Label(self.geometrywindow, text="")
        self.label.grid(row=1, column=1)
        self.label.configure(text=self.filename)

    def generateGeometry(self):
        messagebox.askokcancel('Geometry Generation', 'Specify the needed information for geometry generation:')

    def showResultingMesh(self):
        messagebox.showinfo('Resulting Mesh')
        
    

        # SECTION 1.2 INPUT PARAMETERS




# # SECTION 1.2: INPUT PARAMETERS
# title_section_1_2 = LabelFrame(tab1, text="1.2 Input parameters", padx=20, pady=20)
# title_section_1_2.pack(fill="both", expand="yes")

# text_section_1_2 = Label(title_section_1_2, text="Please specify the required input values:")
# text_section_1_2.pack()

# ##################### 2. SOLVER #####################
# # SECTION 2.1: CONVERGENCE CRITERIAS
# title_section_2_1 = LabelFrame(tab2, text="2.1 Convergence criterias", padx=20, pady=20)
# title_section_2_1.pack(fill="both", expand="yes")

# text_section_2_1 = Label(title_section_2_1, text="Please specify the required convergence criterias:")
# text_section_2_1.pack()

# # SECTION 2.2: SCHEME SELECTION
# title_section_2_2 = LabelFrame(tab2, text="2.2 Scheme Selection", padx=20, pady=20)
# title_section_2_2.pack(fill="both", expand="yes")

# text_section_2_2 = Label(title_section_2_2, text="Please select the desired flux scheme:")
# text_section_2_2.pack()

# # SECTION 2.3: SOLVER OPTIONS
# title_section_2_3 = LabelFrame(tab2, text="2.3 Solver Options", padx=20, pady=20)
# title_section_2_3.pack(fill="both", expand="yes")

# text_section_2_3 = Label(title_section_2_3, text="Please select other code options:")
# text_section_2_3.pack()

# ##################### 3. OUTPUT #####################
# text_section_3 = Label(tab3, text="Please specify the graphs that you would like to display:")
# text_section_3.pack()

# DISPLAYING OF THE MAIN WINDOW
# main_window1.mainloop()

root = Tk()
main_window = MainWindow(root)
root.mainloop() #Mainloop allows you to be display the window continuously until you close it