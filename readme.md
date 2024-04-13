
[![4-Contributor](https://img.shields.io/badge/Contributors%20-4-brightgreen.svg?style=flat-square)](https://github.com/koinzh/PetCare/graphs/contributors)     [![License](https://img.shields.io/badge/License%20-MIT-red.svg?style=flat-square)](https://github.com/koinzh/PetCare/blob/main/LICENSE) 
[![Stars](https://img.shields.io/badge/Stars%20-0-yellow.svg?style=flat-square)](https://github.com/koinzh/PetCare/stargazers) 
[![Fork](https://img.shields.io/badge/Fork%20-0-blue.svg?style=flat-square)](https://github.com/koinzh/PetCare/forks) 

# PetCare

## Contents
- [Demo](#demo)
- [Introduction](#introduction)
- [Equipment](#equipment)
- [Circuit Diagram](#circuit-diagram)
- [Object](#object)
- [Get started](#get-started)
- [Version Control](#version-controrl)
- [License](#license)
- [Acknowledgement](#acknowledgement)
- [Contact us](#contact-us)
- [Developer Log](#developer-log)


## Demo
link

Full version video and Follow us on: 
* [TikTok](https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1)

## Introduction
This project is the course design of real-time embedded system. In this course, we are the team 7. 

When pets-owners leave home for a long time, feeding pets with food and water is a big problem. So we make an automatic pet feeder to help people feed their pets when they are busy. The design used raspberry PI to make an automatic feeder, real-time monitoring of pet movement and food. Upload the feeding records to aliyun cloud server. This project can realize intelligent feeding, protecting the health of pets.


# Equipment
* Raspberry Pi 3B+ 
* Ultrasonic sensor (HC-SR04)
* Weight sensor (HX711)
* Step motor (28BYJ-48)
* Water pump
* Water pipes
* Paper boxes  
* Plastic bottles

## Circuit Diagram
link

## Object
The ultrasonic sensor detects the distance to the pet and when the pet is close, the feeder starts working.

In this system, the ultrasonic sensor detects the distance to the pet, and the feeder starts working when the pet is close. The weight sensor detects the weight of the food in the bowl. When the food weight is less than 300 grams, the motor starts to rotate the baffle 90 degrees to replenish the food. When the food weight is greater than 300 grams, the motor rotates backward. 

The water sensor detects the level of water in the container. When the water level is less than the setting height, start the water pump to draw water from the water storage tank and add it to the water feeding container. The water pump runs for 1 second. 

## Get Started
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
## Version Control
check the repository to see the avilabe version

## License
MIT license

## Acknowledgement
* [Cmake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html#a-basic-starting-point-step-1)

* [README templete](https://github.com/othneildrew/Best-README-Template)

<!--* [Thread](https://github.com/berndporr/cppThread/blob/master/CppThread.h)-->

* [C++](https://www.learncpp.com/)

## Contact us 
* Yutong Wang https://github.com/BigWYT
* Bowen Ren https://github.com/midori-jojo
* Zhiyu Ren https://github.com/rasethna
* Xiaoyu Zhang https://github.com/koinzh
* Project Link: https://github.com/koinzh/PetCare
* TikTok Link: https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1


## Developer Log

### Date: 2024-03-05

Creat petCare repository. Updated readme file and license in main branch. Creat develop branch.

[Commit Hash](84cefb5a07092db359458b0f08de884c4061afbc)

[Commit Hash](24623916f1564136cc317fe44f99f03da742a266)

### Date: 2024-03-06

Upload code of weight sensor in develop branch.

[Commit Hash](890d4d2d68e7b10aea9346ca4bba831bbc629261)

### Date: 2024-03-07

Updated cmake file. Upload code of ultrasonic sensor and motor.

[Commit Hash](929d23a873c1a9b7131b06dd0c0c3710c8315c3b)

### Date: 2024-03-12

Change wring to pigpio of motor and ultrasonic sensor.

[Commit Hash](4f586a4687837716ebbfc18c81b4414db15a2400)

### Date: 2024-03-17

Updated code of weight sensor.

[Commit Hash](4ef864c57f7ab4c859d34144348a069ec7bb271d)

### Date: 2024-03-19

Set aliyun cloud server.

[Commit Hash](93f8312c9f3eaf5bb15ff3926f7aae0baafa5c62)

### Date: 2024-04-09

Updated code of sensor test (thread, callback, io).

[Commit Hash](f0abb124684403b31471bd1b16d1c880295b9158)

### Date: 2024-04-10

Updated readme file (introduction, equipment, object).

[Commit Hash](4d08b4308eeddacef85a08f1795b338abf2c4990)

### Date: 2024-04-12

Merge branch newlib to branch develop.

[Commit Hash](10a1d3392eb5221e733013856561ed79f58a3863)

### Date: 2024-04-13

Debug test code for sensor.