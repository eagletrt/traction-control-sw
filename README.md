# traction-control-sw
Traction Control software for Fenice Pro Max.
## Clone and compile me
```bash
git clone --recurse-submodules git@github.com:eagletrt/traction-control-sw
cd traction-control-sw
make
```
The binary is in **bin/**

# Simulator setup
First enable simulator mode, this is line in `inc/defines.h`:
```C
#define SIMULATOR 1
```
make sure that there is `SIMULATOR 1` and not `SIMULATOR 0`.

> **NOTE:**  When using this repo for the simulation with [vehicle-simulator-wrapper](https://github.com/eagletrt/vehicle-simulator-wrapper) keep `SIMULATOR 0`

Then in `src/main.cpp` you should change the CAN interfaces:  
In the initial part of main.cpp the function `can_init` is called with a string specifying the name of the CAN socket that should be opened. make sure that the sockets are:
- "vcan0"
- "vcan1"

Then **recompile** with the command `make` and execute the binary in `bin/` folder.
