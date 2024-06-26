
# PetCare

[![4-Contributor](https://img.shields.io/badge/Contributors%20-4-brightgreen.svg?style=flat-square)](https://github.com/koinzh/PetCare/graphs/contributors)     [![License](https://img.shields.io/badge/License%20-MIT-red.svg?style=flat-square)](https://github.com/koinzh/PetCare/blob/main/LICENSE) 
[![Stars](https://img.shields.io/badge/Stars%20-3-yellow.svg?style=flat-square)](https://github.com/koinzh/PetCare/stargazers) 
[![Fork](https://img.shields.io/badge/Fork%20-0-blue.svg?style=flat-square)](https://github.com/koinzh/PetCare/forks)


## Contents
- [Introduction](#introduction)
- [Demo](#demo)
- [Equipment](#equipment)
- [Circuit Diagram](#circuit-diagram)
- [Features](#features)
- [Get started](#get-started)
- [Version control](#version-control)
- [License](#license)
- [Acknowledgement](#acknowledgement)
- [Contact us](#contact-us)
- [Developer Log](#developer-log)


## Introduction
This project is the course design of UofG ENG 5220 Realtime Embedded Programing. In this course, we are the team 7. 

When pets-owners leave home for a long time, feeding pets with food and water is a big problem. So we make an automatic pet feeder to help people feed their pets when they are busy. The design used raspberry PI to make an automatic feeder, real-time monitoring of pet movement and food. Upload the feeding records to aliyun cloud server. This project can realize intelligent food and water feeding, protecting the health of pets.


## Demo
[Food system](https://vm.tiktok.com/ZGeu3ysVg/)

[Water system](https://vm.tiktok.com/ZGeu38K81/)

[system testing](https://vm.tiktok.com/ZGeu3hqQ6/)

Full version video and Follow us on: 
* [TikTok](https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1)


## Equipment
* Raspberry Pi 3B+ 
* Ultrasonic sensor (HC-SR04)
* Weight sensor (HX711)
* Step motor (28BYJ-48)
* Water sensor
* Water pump


## Circuit Diagram
![circuit diagram](docs/circuit-diagram.png)


## Features
This project uses raspberry PI to make an automatic pet-care system, which has a feeder with real-time monitoring of pet movement and food weight, a water feeder, and transfer the data of feeding activities to aliyun cloud server.  

In this system, the ultrasonic sensor detects the distance to the pet, and the feeder starts working when the pet is close. The weight sensor detects the weight of the food in the bowl. When the food weight is less than threshold, the motor starts to rotate the baffle 90 degrees to replenish the food. When the food weight is greater than threshold, the motor rotates backward. User can change the weight threshold through app. 

The water sensor detects the level of water in the container. When the water level is less than the setting height, start the water pump to draw water from the water storage tank and add it to the water feeding container. The water pump runs for 1 second. 

Following link to the UML documentation:

![uml](docs/uml/html/index.html)


## Get Started
The default branch of this repository is `main`, which contains the latest stable version of the project. 

This is an example of how to list things you need to use the software and how to install them. 

<details>
  <summary>Click to expand!</summary>
  
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
    cd PetCare/codes
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
    sudo ./PetCare
    ```
</details>


## License
MIT license


## Version control
check the repository to see the avilabe version


## Acknowledgement
* [Cmake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html#a-basic-starting-point-step-1)

* [README templete](https://github.com/othneildrew/Best-README-Template)

* [C++](https://www.learncpp.com/)


## Contact us 
* Yutong Wang https://github.com/BigWYT

* Bowen Ren https://github.com/midori-jojo

* Zhiyu Ren https://github.com/rasethna

* Xiaoyu Zhang https://github.com/koinzh

* Project Link: https://github.com/koinzh/PetCare

* TikTok Link: https://www.tiktok.com/@smartpetcaresyste?_t=8kk3llkyQGP&_r=1


## Developer Log

<details>
  <summary>Click to expand!</summary>

  * Date: 2024-03-05

    Creat petCare repository. Updated readme file and license in main branch. Creat develop branch.

  * Date: 2024-03-06

    Upload code of weight sensor in develop branch.

  * Date: 2024-03-07

    Updated cmake file. Upload code of ultrasonic sensor and motor.

  * Date: 2024-03-12

    Change wring to pigpio of motor and ultrasonic sensor.

  * Date: 2024-03-17

    Updated code of weight sensor.

  * Date: 2024-03-19

    Set aliyun cloud server.

  * Date: 2024-04-09

    Updated code of sensor test (thread, callback, io).

  * Date: 2024-04-10

    Updated readme file (introduction, equipment, object).

  * Date: 2024-04-12

    Merge branch newlib to branch develop.

  * Date: 2024-04-13

    Debug test code for weight sensor.

  * Date: 2024-04-15

    Built the device. Finished successfully.

</details>
