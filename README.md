# C++ Bootcamp LAB 2021 - Team Smokey

This is Smokey's lab project for the C++ Bootcamp 2021

This project aims to emulate an enginge based on a users key inputs and
transmits messages over CAN.

The program has been tested to run on one Linux computer with virtual can.

## Installation

To set up virtual can use below commands. `modeprobe` only needs to be set
once. The ip link commands needs to be set every time the machine is restarted.

In the below commands vcan0 is the interface name of the bus.

``` bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```

## Build

Change directory to where the git repo is located, create a build folder and run
cmake and make commands from there

``` bash
$ cd <git_root>
$ mkdir build
$ cd build
$ cmake ..
$ make
```
this builds all three neccesary libraries and binaries in their respecitve
subfolders.

## Run

You need to start all three binaries in three separate terminal windows and run
them separately. Starting from location after build above.

### Window 1
``` bash
$ cd app/input_handler/
$ ./smokey_input_handler
```

### Window 2
``` bash
$ cd app/emulator/
$ ./smokey_emulator vcan0
```
### Window 3
``` bash
$ cd app/avic/
$ ./avic -c vcan0
```

The input_handler window has to be active for the user to input arguments.

## Arguments

The input arguments accepted by the input handler are defined below

|key|command             |
|---|--------------------|
| q | quit applications  |
| s | start/stop engine  |
| d | gear drive         |
| r | gear rear          |
| n | gear neutral       |
| p | gear park          |
| 0 ... 9 | throttle 0 - 90 %       |

## Team members

* Niklas Hultman
* Marie Liljenroth
* David Andersson
* Daniel Muhr
