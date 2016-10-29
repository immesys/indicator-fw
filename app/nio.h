#ifndef __NIO_H__
#define __NIO_H__

#include <stdint.h>
uint32_t dolength(uint8_t* b1, uint8_t* b2, int length) __attribute__ ((long_call, section(".ramfunc")));

#endif
