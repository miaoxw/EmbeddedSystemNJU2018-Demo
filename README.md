# Lane Detection-Demo
## Introduction
This is a demo for software design of the coursework to be assigned on **Introduction to Embedded Systems** in the first semester of Year 2017-2018, *Software Institute, Nanjing University*.
This demo just simply implement the function of a four-wheeled robot walking forward within the range of two black lanes. It just works, and neither performance nor accuracy is the best.

## Dependencies
### Software parts
* Linux running on Raspberry Pi or Windows 10 IoT(Raspbian and Ubuntu recommended)
* OpenCV

Installation manuals can be found on the websites of Raspberry Pi and OpenCV.

### Hardware parts
* Raspberry Pi 2 or Raspberry Pi 3  
When using Raspberry Pi 2, maybe you need an extea wireless USB NIC device.
* L298N driver circuit
* DC motors
* Independent power supply for motors  
Raspberry Pi and motors shouldn't be powered by the same battery. This may interfere with the stability of Raspberry Pi.
* *Arduino connected to Raspberry Pi via USB (optional)*  
Without this, you can still take control of all your motors directly from Raspberry Pi's GPIO ports.

## Thanks
This demo refers to a work of @jdorweiler. The original links are listed below:
https://github.com/jdorweiler/lane-detection

The original repository has no licenses, so I relicense my works under MIT License.

## Licenses
This repostory is released under MIT License. However, it is still forbidden to use this repostory directly as your handouts of the course mentioned above and the same courses to be lectured in the future. It is a must that your handouts be coresponding to all requirements from MIT License.
