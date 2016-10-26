#include <stdio.h>
#include <rtt_stdio.h>
#include "thread.h"
#include "xtimer.h"
#include <string.h>

#include "msg.h"
#include "net/gnrc.h"
#include "net/gnrc/ipv6.h"
#include "net/gnrc/udp.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc/netreg.h"

#include <at30ts74.h>
#include <mma7660.h>
#include <periph/gpio.h>
#include <periph/i2c.h>

uint32_t dolength(uint8_t* b1, uint8_t* b2, uint32_t length);

#define NLEDS 300
uint8_t pbuf1 [NLEDS*3];
uint8_t pbuf2 [NLEDS*3];

typedef struct __attribute__((packed)) {
  uint8_t g;
  uint8_t r;
  uint8_t b;
} led_t;

led_t c_black = {.r = 0, .g = 0, .b = 0};
led_t c_chk = {.g = 0xFF, .r = 0x00, .b = 0x55};

led_t *lbuf1 = (led_t *) &pbuf1[0];
led_t *lbuf2 = (led_t *) &pbuf2[0];

void send_udp(char *addr_str, uint16_t port, uint8_t *data, uint16_t datalen);
void process_next_frame(void);

int main(void)
{
    //Clear the arrays to chk
    for (uint32_t i = 0; i < NLEDS; i++) {
      lbuf1[i] = c_chk;
      lbuf2[i] = c_chk;
    }

    while(1) {
      uint32_t then = dolength(&pbuf1[0],&pbuf2[0], NLEDS);

      // Do some processing
      process_next_frame();

      // Ensure we do proper blanking
      while ((xtimer_now().ticks32 - then) < 2);
    }
    return 0;
}


void process_next_frame(void)
{

}
