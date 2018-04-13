# Arcade Framework

This C++ framework let you add your own **games** and **libraries**.

For instance, you can create a Tetris game compatible with the project *(see documentation in* doc/*)* and then play it on all the availables graphical libraries.

The **libraries** are only porting of existing graphic libs (e.g. SDL2, GTK, QT) re-designed to work the same way.

## Usage

- Clone the repo.
- Install SFML & SDL2 if you want to test the actual libraries
- Open a terminal and execute *make* command to compile the sources
- Start with the desired library with the following command
``./arcade ./lib/lib_arcade_libname.so ``

## Games

**Nibbler/Snake** (on SDL2 here)

![alt text](https://image.ibb.co/fakHP7/nibb.png)

**Pacman** (on SFML lib here)

![alt text](https://image.ibb.co/cF6fcS/pac.png)

## Graphic libraries

**SDL2 library**

![alt text](https://image.ibb.co/k9wDxS/sdlenu.png)

**SFML Library**

![alt text](https://image.ibb.co/e5WfcS/sfml.png)

## Keys
 There are a bunch of keys that are working through all games :
 - N next graphical library
 - P previous graphical library
 - B next game
 - O previous game
 - R restart game
 - M menu
 - X exit
