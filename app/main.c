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

#include "lib.h"
uint32_t dolength(uint8_t* b1, uint8_t* b2, uint32_t length);
extern void delay50u(void);

uint8_t pbuf1 [NLEDS*3];
uint8_t pbuf2 [NLEDS*3];



led_t c_black = {.r = 0, .g = 0, .b = 0};
led_t c_chk = {.g = 0x00, .r = 0xff, .b = 0x00};

led_t *lbuf1 = (led_t *) &pbuf1[0];
led_t *lbuf2 = (led_t *) &pbuf2[0];

void send_udp(char *addr_str, uint16_t port, uint8_t *data, uint16_t datalen);
void process_next_frame(void);
inline void delay_45(void)  __attribute__((always_inline));
inline void delay_45(void)
{
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
}
inline void delay_40(void)  __attribute__((always_inline));
inline void delay_40(void)
{
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  //delay_jiffy(20);
}
extern void nmain(void);
int main(void)
{
  gpio_init(GPIO_PIN(0,18), GPIO_OUT);
  gpio_init(GPIO_PIN(0,25), GPIO_OUT);
    nmain();
    #if 0
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
    #endif
}


void process_next_frame(void)
{

}
