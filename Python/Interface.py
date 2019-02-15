from tkinter import *
main_window1 = Tk()
main_window1.title("1. Input")

title_section1 = LabelFrame(main_window1, text="1.1 Geometry and mesh", padx=20, pady=20)
title_section1.pack()

text_section1 = Label(title_section1, text="Please select the desired mesh or geometry:", justify=LEFT)
text_section1.pack()

title_section2 = LabelFrame(main_window1, text="1.2 Input parameters", padx=20, pady=20)
title_section2.pack()

text_section2 = Label(title_section2, text="Please specify the required input values:", justify=LEFT)
text_section2.pack()

main_window1.mainloop()