# Ground Station

This app is used to be the bridge between the Android application and the 
drone interface, as well as handling the AI processes.

## Installation

Some dependencies must be installed before runnning the program

#### Libconfig
This library permits to read a config file and parse settings from it :

> $ sudo apt-get install libconfig++-dev

In order to launch the program, you must duplicate the file "config/config.cfg.TEMPLATE", calling the duplicate
"config/config.cfg" and put your wanted settings.

This config.cfg file is unique to this computer and should (will) never be committed.

## How to run

THIS APPLICATION MUST BE LAUNCHED AFTER THE DRONE INTERFACE ONE (or another program that opens the channels)

Launch the script "./compile.sh" while in this folder (the "drone_controller" one)
and run the application created in the "build folder".

If the script doesn't work for any reason, you can compile yourself by typing :

```
$ sudo mkdir build
$ cd build
$ cmake ..
$ make -j
```