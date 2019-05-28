#!/usr/bin/bash

export LD_LIBRARY_PATH="/apps/local/tecplot_360/2018/360ex_2018r1/bin:/apps/local/tecplot_360/2018/360ex_2018r1/bin/sys${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

python runPostProcessing.py
