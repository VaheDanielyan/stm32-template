#ifndef BSP_H
#define BSP_H

#include "board_def.h"

#ifndef BOARD
#error PLEASE SELECT ONE OF THE SUPPORTED BOARDS
#endif

#if BOARD == default_board
    #include "default_board.h"
#else
#error BOARD UNSUPPORTED
#endif

#endif
