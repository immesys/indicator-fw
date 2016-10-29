
#include "lib.h"
#include <stdint.h>
#include <stdio.h>
#if 0
static const uint8_t quadrant_data1 = [
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
];
static const uint8_t quadrant_data2 = [
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
  0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
];
#endif

void lerp(lerp_param *p, uint8_t nparams)
{
  led_t last_color = p[0].color;
  uint32_t last_index = 0;
  led_t next_color = p[0].color;
  uint32_t next_index = 0;

  int paramindex = 0;
  for (int i = 0; i < 2*NLEDS; i++) {
    if (paramindex+1 < nparams && p[paramindex].idx == i) {
      last_index = next_index;
      last_color = next_color;
      paramindex++;
      next_color = p[paramindex].color;
      next_index = p[paramindex].idx;
    }
    printf("nxi = %d, lxi = %d\n", next_index, last_index);
    uint8_t r = last_color.r + ((next_color.r - last_color.r)*(i-last_index))/(next_index-last_index);
    uint8_t g = last_color.g + ((next_color.g - last_color.g)*(i-last_index))/(next_index-last_index);
    uint8_t b = last_color.b + ((next_color.b - last_color.b)*(i-last_index))/(next_index-last_index);
    if (i < NLEDS) {
      lbuf1[i].r = r;
      lbuf1[i].g = g;
      lbuf1[i].b = b;
    } else {
      lbuf2[i-NLEDS].r = r;
      lbuf2[i-NLEDS].g = g;
      lbuf2[i-NLEDS].b = b;
    }
  }
}
#if 0
void set_quad(uint8_t quadrant, led_t color)
{
  for (int i = 0; i < NLEDS; i++) {
    if (quadrant_data1[i] == quadrant) {
      lbuf1[i] = color;
    }
    if (quadrant_data2[i] == quadrant) {
      lbuf2[i] = color;
    }
  }
}
#endif
