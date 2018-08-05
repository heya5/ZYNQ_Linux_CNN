# ZYNQ_Linux_CNN

## Development environment
- Vivado 2016.4

## Generate LeNet IP using Vivado HLS
On windows, open Vivado HLS 2016.4 Command Prompt.
On Linux, open a new terminal.
Then change directory to the project's directory named **HLS** and run
```
vivado_hls -f run_hls.tcl
```
This command will generate the LeNet IP that we need.
