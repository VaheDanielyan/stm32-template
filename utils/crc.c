#include <crc.h>

uint8_t crc8(const void* vptr, uint32_t size)
{
  const uint8_t* data = (const uint8_t*) vptr;
  unsigned crc = 0;
  for (uint32_t j = size; j; j--, data++) {
    crc ^= (*data << 8);
    for (uint32_t i = 8; i; i--) {
      if (crc & 0x8000) {
        crc ^= (0x1070 << 3);
      }
      crc <<= 1;
    }
  }
  return (uint8_t)(crc >> 8);
}

