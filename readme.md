<!--[![4-Contributor](https://img.shields.io/badge/Contributors%20-4-brightgreen.svg?style=flat-square)](https://github.com/Shujing106/realtimeEmbedded/graphs/contributors)     [![License](https://img.shields.io/badge/License%20-MIT-red.svg?style=flat-square)](https://github.com/Shujing106/realtimeEmbedded/blob/main/LICENSE) [![Stars](https://img.shields.io/badge/Stars%20-2-yellow.svg?style=flat-square)](https://github.com/Shujing106/realtimeEmbedded/blob/main/LICENSE) [![Fork](https://img.shields.io/badge/Fork%20-1-blue.svg?style=flat-square)](https://github.com/Shujing106/realtimeEmbedded/blob/main/LICENSE) 
-->

# Demo
<!--[image](https://github.com/Shujing106/realtimeEmbedded/blob/bc505a64a9148ac952772ca07c4a7179f093678b/video/autoPetFeeder.gif)-->

Full version video and Follow us on: 
* [TikTok](https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1)

# Introduction
<!--We are one group students at the University of Glasgow. This project is the course design of our real-time embedded system. In this course, we are the team 21. We find that when pets-owners leave home for a long time, feeding pets is a big problem. So we decide to make one automatic pet feeder to help that people to feed their pets when they are busy. Basically, using raspberry PI to make an automatic feeder, real-time monitoring of pet movement and food weight. Realize intelligent feeding, protect the health of pets. -->

<!--![image](https://github.com/Shujing106/realtimeEmbedded/blob/fe9dbf94ca11b8fd0e8629ee8bc73eff777eb14c/image/Demo2.jpg)-->

# Equipment
<!--
* Raspberry Pi 3B+ 
* Ultrasonic sensor (HC-SR04)
* Weight sensor (HX711)
* Step motor (28BYJ-48)
* Paperboard  
* Large plastic bottle
* Bowl
-->

# Circuit Diagram
<!--![image](https://github.com/Shujing106/realtimeEmbedded/blob/947e1cb685058c497032255ce45a63e7fd66b8ab/image/circuit%20diagram.JPG)-->

# Object
<!--
* Ultrasonic sensors detect the distance from the pet, and the feeder starts working when the pet approaches.
* The weight sensor detects the weight of the food in the bowl. When the weight of food < 10g, starts the motor to make the baffle turn to replenish food. When the weight of food > 50g, the motor rotates backward.

* Limiting conditions:  
   1.There will be a 4h cooldown time after feeding is first turned on.  
   2.The machine can only add the food for three times within 24 hours.
-->

# Get Started
This is an example of how to list things you need to use the software and how to install them.
<!--
* Git
  ```sh
  sudo apt-get update && upgrade
  ```  
  ```
  sudo apt-get install git-core
  ```
   
* Cmake
  ```sh
  sudo apt-get install cmake 
  ```

* wiringPi
  ```sh
  git clone https://github.com/WiringPi/WiringPi
  ```
  ```
  cd WiringPi
  ```
  ```
  sudo ./build
  ```
  
* Clone the project
  ```sh
  git clone https://github.com/Shujing106/AutoPetFeeder.git
  ```
* Navigate to the project folder
  ```sh
  cd AutoPetFeeder/codes/src
  ```
  ```
  mkdir build
  ```
  ```
  cd build
  ```
 
* Link the required files and libraries using CMake
  ```sh
  cmake ..
  ```
 
* Build the CMake project
  ```sh
  make
  ```

* Run application
  ```sh
  ./AutoPetFeeder
  ```
 -->
# Version Control
check the repository to see the avilabe version

# License
MIT license

# Acknowledgement
* [Cmake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html#a-basic-starting-point-step-1)

* [README templete](https://github.com/othneildrew/Best-README-Template)

<!--* [Thread](https://github.com/berndporr/cppThread/blob/master/CppThread.h)-->

* [C++](https://www.learncpp.com/)

# Contact us 
* Yutong Wang https://github.com/BigWYT
* Bowen Ren https://github.com/midori-jojo
* Zhiyu Ren https://github.com/rasethna
* Xiaoyu Zhang https://github.com/koinzh
* Project Link: https://github.com/koinzh/PetCare
* TikTok Link: https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1

