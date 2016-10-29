#include <stdio.h>
#include <stdint.h>

#include "lib.h"


uint8_t pbuf1 [NLEDS*3];
uint8_t pbuf2 [NLEDS*3];

led_t *lbuf1 = (led_t *) &pbuf1[0];
led_t *lbuf2 = (led_t *) &pbuf2[0];

int main(void)
{
  lerp_param z[] = {
    {0, {.r=0, .g=0, .b=0}},
    {480, {.r=255, .g=255, .b=255}}
  };
  lerp(&z[0], 2);
  for (int i = 0; i < NLEDS; i++) {
    printf("lbuf1[%d] .r=%d .g=%d .b=%d\n", i, lbuf1[i].r, lbuf1[i].g, lbuf1[i].b);
  }
  for (int i = 0; i < NLEDS; i++) {
    printf("lbuf2[%d] .r=%d .g=%d .b=%d\n", i, lbuf2[i].r, lbuf2[i].g, lbuf2[i].b);
  }
  lbuf[4] = {.r = 255, .g=0, .b=0};
  return 0;
}
