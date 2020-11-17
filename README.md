# Speedometer  
----------------------------  
## About  
**Author** - Kyle Brooks  
**Project** - MED503  
**Created** - 25/02/2019  
**Description** - Software/Hardware project   

## Installation
Install the .ino onto the Arduino using a compatible IDE

## Usage
With the displays and GPS wired into the Arduino (details of pins in code comments) 
power the device and once it finds a satellite, it will begin to display the speed.  
It is important to note a GPS signal is easier to find outside.  
  
## Libraries
*SevSeg*, *SoftwareSerial*, *TinyGPS++*

## Notes

Uses GPS and 7-segment displays

The rx from the gps goes into the tx on the board, like wise with tx from gps to rx


