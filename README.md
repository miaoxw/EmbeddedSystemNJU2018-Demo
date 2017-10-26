# EmbeddedSystemNJU2017-Demo
Demo and designated library file for software design of the coursework to be assigned on Introduction to Embedded Systems in the first semester of Year 2017-2018, Software Institute, Nanjing University.

## Contents
* Basic principles of code of the static library
* Header file to be included in order to utilize the library
* .a static library file  
Provided in `Releases` section
* Demos to demonstrate usage
* Demos to use OpenCV

## Dependencies
### Hardware
* RaspberryPi  
RaspberryPi 3 Model B is provided. When using Raspberry Pi 2, maybe you need an extra wireless USB NIC device.
* Driver circuit for powering DC motors
* DC motors and steering engine  
The former is for motion and the latter is for turning.
* Independent power supply for motors  
Raspberry Pi and motors shouldn't be powered by the same battery. This may interfere with the stability of Raspberry Pi.

### Software
* Linux running on Raspberry Pi (Raspbian and Ubuntu recommended)
* OpenCV
* WiringPi (usually integrated with Raspbian)

Installation manuals can be found on the websites of Raspberry Pi and OpenCV.

## Rules and restrictions
* These documents are visible on CMS and(or) Wiki pages of this repository. Violation shall receive appropriate punishment on gradings.
* The library is open-source, but using codes directly in the contest is forbidden.
* The library is released under the MIT liccense.

## Help and assistance
* According to the rule of competition, there is no assistance in practical coding.
* If you consider bugs about this library, please test on those demos first. The library is considered bug-free only if any of those demos fails to run.
Malfunctions are usually caused by hardware wearing-down of wirings or parts. You can call the stuff to repair the hardware part.

## Thanks
This demo related to OpenCV refers to a work of @jdorweiler. The original links are listed below:
https://github.com/jdorweiler/lane-detection

The original repository has no licenses, so I relicense my works under MIT License.
