
#include "irq.h"
#include "periph_conf.h"
#include "periph_cpu.h"
#include <stdint.h>
#include "xtimer.h"
//d18
//d25

#define PIN1H              (LED_PORT.OUTSET.reg = (1 << LED_PIN))

static inline void delay_jiffy(uint32_t amt) {
  while(--amt) {
    asm("");
  }
}
static inline void pin1h(void) {
  static uint32_t *reg = (uint32_t*) &(PORT->Group[0].OUTSET.reg);
  *reg = 0x40000;
}
static inline void pin1l(void) {
  static uint32_t *reg = (uint32_t*) &(PORT->Group[0].OUTCLR.reg);
  *reg = 0x40000;
}
static inline void pin2h(void) {
  static uint32_t *reg = (uint32_t*) &(PORT->Group[0].OUTSET.reg);
  *reg = 0x2000000;
}
static inline void pin2l(void) {
  static uint32_t *reg = (uint32_t*) &(PORT->Group[0].OUTCLR.reg);
  *reg = 0x2000000;
}
static inline void delay400(void) {
  delay_jiffy(10);
  //Tuning slide
  asm volatile("nop"::);
  asm volatile("nop"::);
  asm volatile("nop"::);
}
static inline void delay450(void) {
  delay_jiffy(12);
  //Tuning slide
  asm volatile("nop"::);
  asm volatile("nop"::);
  asm volatile("nop"::);
}
static inline void dobit(uint8_t mask, uint8_t b1, uint8_t b2) {
  pin1h();
  pin2h();
  delay400();
  if ((b1 & mask) == 0) {
    pin1l();
  }
  if ((b2 & mask) == 0) {
    pin2l();
  }
  delay400();
  pin1l();
  pin2l();
  delay450();
}

static inline void dobyte(uint8_t b1, uint8_t b2) {
  dobit(0x80, b1, b2);
  dobit(0x40, b1, b2);
  dobit(0x20, b1, b2);
  dobit(0x10, b1, b2);
  dobit(0x08, b1, b2);
  dobit(0x04, b1, b2);
  dobit(0x02, b1, b2);
  dobit(0x01, b1, b2);
}

uint32_t dolength(uint8_t* b1, uint8_t* b2, uint32_t length) {
  unsigned irqstate = irq_disable();
  while(length--) {
    dobyte(*b1, *b2);
    b1++;
    b2++;
  }
  xtimer_ticks32_t rv = xtimer_now();
  irq_restore(irqstate);
  return rv.ticks32;
}
