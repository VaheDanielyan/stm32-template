#ifndef SWO_H
#define SWO_H

#include <bsp.h>

#define DEMCR                 *((volatile uint32_t*) 0xE000EDFCu)
/* ITM register addresses */
#define ITM_STIMULUS_PORT0    *((volatile uint32_t*) 0xE0000000u)
#define ITM_TRACE_EN          *((volatile uint32_t*) 0xE0000E00u)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void swo_init();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SWO_H */
