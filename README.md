# STM32 Template

Generic project template for stm32 applications.

## Usage Guide

- Copy all of the contents of the folder to the new project folder
- Create a new folder in the bsp folder with the board name
    - Copy the ioc file into the folder
    - Open CubeMX and generate code
- Open bsp/board_def.h and add the new board's name
- Create bsp/${BOARD_NAME}.h 
    - Mirror everything written in the default_board.h
    - Add any other defines needed by your board
- Open bsp/bsp.h and add an if statement matching the board name in board_def.h
- Copy CMakeLists.txt from bsp/default_board to your board's folder
    - Open bsp/${BOARD_NAME}/CMakeLists.txt and edit the following variables. The values for them can be found in cubeMX generated Makefile
        - MCU_FAMILY
        - MCU_MODEL
        - CPU_PARAMETERS
        - STARTUP_SCRIPT
        - MCU_LINKER_SCRIPT
    - Fix STM32CUBEMX_SOURCES and STM32CUBEMX_INCLUDE_DIRECTORIES as per your needs
- Go to the top level Makefile and edit the variable ${BOARD} to match your board name
- Go to the top level CMakeLists file and edit the project name
    - Rename the ./project folder and the project/project.* file names to match the project
- Done.
