pumpControl
===========

Arduino sketch for controlling 8 wire stepper motor as peristaltic pump.

This project was undertaken to create a microfluidics system for recirculated panning of phage libraries over rare/precious cell types (e.g. activated primary CD4 or dendritic cells, etc.) and continuous washing of non-specific phage off of those cells. Cells would be captured via magnetic separation beads using rare earth magnets.

PNAS April 26, 2011 108 (17) 6909-6914; https://doi.org/10.1073/pnas.1014753108

I had a working peristaltic pump from a biacore T100 as the core of the system. Additional major components to control the pump are:

Arduino Uno microcontroller | Nanotec SMC11 Compact Microstep Controller | Mean Well 24VDC / 6A switching power supply | LCD display | Potentiometer & knob

As implemented, the Arduino takes input from the potentiometer and sends a clock signal to the stepper driver, which in turn sends coordinated, high power pulses to the stepper motor. The motor is wired bipolar parallel. The speed at which the motor is rotating is output to the LCD screen to allow for reproducibility from run to run. I still need to calibrate peristaltic tubing such that the code can incorporate a conversion factor from rpm to microliters per minute (there are dummy values in the code currently.) 
