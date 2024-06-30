# WindowClick
Simple game written in C++ with the SDL2 library

# How it works
At the start, there spawns one window at the center of the screen, when you click inside of it, another window in a random location will spawn etc..  you can see in the Window how long you took to click the last Window after it spawned, the goal is it, to get the lowest time possible. To close, just press the X in your bar above the Window.

# How to run
1. Download WindowClick and Font.ttf from the latest release and make sure you have SDL2 and SDL2_ttf librarys installed
2. Open Terminal
3. Type: cd Downloads
4. Type: chmod +x WindowClick
5. Double click the file.

# How to compile from source
Requirements:
Linux System, g++, SDL2 library
For Arch: sudo pacman -S gcc sdl2
For Debian based distrobutions(eg Ubuntu): sudo apt install gcc g++ libsdl2-dev
For dnf package manager: sudo dnf install gcc-c++ SDL2-devel

How to compile:
Change into the Directory the WindowClick.cpp file is located and run: 
g++ WindowClick1.1.cpp -o WindowClick -lSDL2

