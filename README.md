# PongCPP
Open source Pong created in SFML and C++


## Project Setup
To play PongCPP you need to have SFML and a C++ compiler installed (Recommend GCC 7.3.0)
### CMakeLists.txt
The CMakeList file contains all build instructions for this project. By default the libraries are linked dynamically, 
so check to be sure you have up to date SFML dlls in the build directory or else the program may not link properly.
CMakeLists also include variables set for the include and library directories of SFML, change the values according to where you have SFML.
