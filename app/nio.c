
#include "irq.h"
#include "periph_conf.h"
#include "periph_cpu.h"
#include <stdint.h>
#include "xtimer.h"
#include "nio.h"

volatile uint32_t *regs = &(PORT->Group[0].OUTSET.reg);
volatile uint32_t *regc = &(PORT->Group[0].OUTCLR.reg);

inline void delayA(void)  __attribute__((always_inline));
inline void delayA(void)
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
}
inline void delayB(void)  __attribute__((always_inline));
inline void delayB(void)
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
}
inline void delayC(void)  __attribute__((always_inline));
inline void delayC(void)
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
}
inline void delayD(void)  __attribute__((always_inline));
inline void delayD(void)
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
}
inline void doqbyte(uint32_t dat1, uint32_t dat2, volatile uint32_t *regs, volatile uint32_t *regc) __attribute__((always_inline));
inline void doqbyte(uint32_t dat1, uint32_t dat2, volatile uint32_t *regs, volatile uint32_t *regc)
{
    uint32_t b = 1;
    uint32_t ls = 0x200000;
    uint32_t rs = 0x4000;
    uint32_t i = 32;
    for (;i>0;i--) {
      *regs = ls;
      *regs = rs;
      delayA();
      if (!(dat1 & b)) {
        *regc = ls;
      } else {
        *regc = 0;
      }
      if (!(dat2 & b)) {
        *regc = rs;
      } else {
        *regc = 0;
      }
      delayB();
      *regc = ls;
      *regc = rs;
      if (i == 1)
      {
        delayD();
      } else {
        delayC();
      }
      b <<= 1;
    }
}

__attribute__ ((long_call, section(".ramfunc"))) uint32_t dolength(uint8_t* b1, uint8_t* b2, int length) {
  unsigned irqstate = irq_disable();
  while(length > 0) {
    doqbyte(*((uint32_t*)b1), *((uint32_t*)b2), regs, regc);
    b1+=4;
    b2+=4;
    length -= 4;
  }
  xtimer_ticks32_t rv = xtimer_now();
  irq_restore(irqstate);
  return rv.ticks32;
}
