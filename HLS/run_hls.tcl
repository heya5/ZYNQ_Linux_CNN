############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
############################################################

# Reset the project with the -reset option
open_project -reset LeNet_IP
set_top CNN_HLS1
add_files src/CNN_HLS.cpp
add_files src/CNN_HLS.h
add_files src/cnn.cpp
add_files src/cnn.h
add_files src/layers.h
add_files -tb src/CNN_tb.cpp

# Reset the project with the -reset option
open_solution -reset "solution1"
set_part {xc7z020clg400-1} -tool vivado
create_clock -period 10 -name default

# Leave the previous directives commented out
#source "./LeNet_IP/solution1/directives.tcl"

# Not run csim and cosim
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog

exit