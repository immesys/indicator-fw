
#ifndef __LIB_H__
#define __LIB_H__

#include <stdint.h>
#define NLEDS 240

typedef struct __attribute__((packed)) {
  uint8_t g;
  uint8_t r;
  uint8_t b;
} led_t;

extern uint8_t pbuf1 [NLEDS*3];
extern uint8_t pbuf2 [NLEDS*3];

extern led_t *lbuf1;
extern led_t *lbuf2;

typedef struct {
  uint32_t idx;
  led_t color;
} lerp_param;

#define LERP_END lerp_param{}

void lerp(lerp_param *p, uint8_t nparams);
void set_quad(uint8_t quadrant, led_t color);

#endif
