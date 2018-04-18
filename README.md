# Arcade Framework

This C++ framework lets you add your own **games** and **libraries**.

For instance, you can create a Tetris game compatible with the project *(see documentation in* [doc/](../master/doc/MyArcade.pdf)*)* and then play it on all the availables graphical libraries.

The **libraries** are only porting of existing graphic libs (e.g. SDL2, GTK, QT) re-designed to work the same way.

## Usage

- Clone the repo.
- Install SFML & SDL2 if you want to test the current libraries
- Open a terminal and execute *make* command to compile the sources
- Start with the desired library with the following command
``./arcade ./lib/lib_arcade_libname.so ``

## Games

**Nibbler/Snake** (on SDL2 here)

<img src="https://image.ibb.co/fuWfK7/yay.png" width="480" height="360" />

**Pacman** (on SFML lib here)

<img src="https://image.ibb.co/cF6fcS/pac.png" width="480" height="360" />

## Graphic libraries

**SDL2 library**

<img src="https://image.ibb.co/k9wDxS/sdlenu.png" width="480" height="360" />

**SFML Library**

<img src="https://image.ibb.co/e5WfcS/sfml.png" width="480" height="360" />

**Ncurse Library**

(desactived for mac os compatibility issue but you can uncomment lines in Makefile to make it work)

## Keys
 There are a bunch of keys that are working through all games :
 - N next graphical library
 - P previous graphical library
 - B next game
 - O previous game
 - R restart game
 - M menu
 - X exit
