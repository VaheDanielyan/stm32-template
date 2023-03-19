#include <swo.h>

/* Override low-level _write system call */
int _write(int file, char *ptr, int len) {
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        ITM_SendChar(*ptr++);
    }
    return len;
}

void swo_init()
{
    DEMCR |= ( 1 << 24);
    // Enable stimulus port 0
    ITM_TRACE_EN |= ( 1 << 0);
}
