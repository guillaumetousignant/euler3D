#!/usr/bin/bash

#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/tecplot/360ex_2018r1/bin/
export LD_LIBRARY_PATH=/apps/local/tecplot_360/2018/360ex_2018r1/bin:$LD_LIBRARY_PATH
python3 runPostProcessing.py
