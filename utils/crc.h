#ifndef CRC_H
#define CRC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint8_t crc8(const void* vptr, uint32_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CRC_H */
