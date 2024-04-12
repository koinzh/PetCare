
[![4-Contributor](https://img.shields.io/badge/Contributors%20-4-brightgreen.svg?style=flat-square)](https://github.com/koinzh/PetCare/graphs/contributors)     [![License](https://img.shields.io/badge/License%20-MIT-red.svg?style=flat-square)](https://github.com/koinzh/PetCare/blob/main/LICENSE) 
[![Stars](https://img.shields.io/badge/Stars%20-0-yellow.svg?style=flat-square)](https://github.com/koinzh/PetCare/stargazers) 
[![Fork](https://img.shields.io/badge/Fork%20-0-blue.svg?style=flat-square)](https://github.com/koinzh/PetCare/forks) 

# Demo
link

Full version video and Follow us on: 
* [TikTok](https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1)

# Introduction
description 
This project is the course design of real-time embedded system. In this course, we are the team 7. When pets-owners leave home for a long time, feeding pets with food and water is a big problem. So we make an automatic pet feeder to help people feed their pets when they are busy. The design used raspberry PI to make an automatic feeder, real-time monitoring of pet movement and food. Upload the feeding records to aliyun cloud server. This project can realize intelligent feeding, protecting the health of pets.


# Equipment
* Raspberry Pi 3B+ 
* Ultrasonic sensor (HC-SR04)
* Weight sensor (HX711)
* Step motor (28BYJ-48)
* Water pump
* Water pipes
* Paper boxes  
* Plastic bottles

# Circuit Diagram
link

# Object
The ultrasonic sensor detects the distance to the pet and when the pet is close, the feeder starts working.

The weight sensor detects the weight of the food in the bowl. When the food weight is less than 10 grams, the motor is started to rotate the baffle to replenish the food. When the food weight is greater than 50 grams, the motor rotates backward. There will be a 4-hour cooling time after starting feeding for the first time. The machine can only add food three times within 24 hours.

The water level sensor detects the level of water in the container. When the water level is less than 10 cm, start the water pump to draw water from the water storage tank and add it to the water feeding container. The water pump runs for 1 seconds.

# Get Started
This is an example of how to list things you need to use the software and how to install them.

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

* pigpio
  ```sh
  git clone https://github.com/joan2937/pigpio
  ```
  ```
  cd pigpio
  ```
  ```
  sudo apt update
  sudo apt full-upgrade
  ```
  ```
  make
  sudo make install
  ```
  ```
  sudo pigpiod
  ```

  
* Clone the project
  ```sh
  git clone https://github.com/koinzh/PetCare.git
  ```
* Navigate to the project folder
  ```sh
  cd PetCare/codes/(updating)
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
  ./PetCare
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

