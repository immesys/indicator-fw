#if 0
#include "irq.h"
#include "periph_conf.h"
#include "periph_cpu.h"
#include <stdint.h>
#include "xtimer.h"
//d18
//d25

#define RAMFUNC __attribute__ ((long_call, section (".ramfunc")))

#define PIN1H              (LED_PORT.OUTSET.reg = (1 << LED_PIN))

#include <periph/gpio.h>

uint32_t *setreg = (uint32_t*) &(PORT->Group[0].OUTSET.reg);
uint32_t *clrreg = (uint32_t*) &(PORT->Group[0].OUTCLR.reg);

static inline void delay_jiffy(uint32_t amt) {
  while(--amt) {
    asm("");
  }
}

inline void pinNop(void)  __attribute__((always_inline));
inline void pinNop(void) {
  *setreg = 0x40000;
}
inline void pin1h(void) __attribute__((always_inline));
inline void pin1h(void) {
  *setreg = 0x40000;
}
inline void pin1l(void) __attribute__((always_inline));
inline void pin1l(void) {
  *clrreg = 0x40000;
}
inline void pin2h(void) __attribute__((always_inline));
inline void pin2h(void) {
//  *setreg = 0x2000000;
}
inline void pin2l(void) __attribute__((always_inline));
inline void pin2l(void) {
//  *clrreg = 0x2000000;
}
inline void delay450(void)  __attribute__((always_inline));
inline void delay450(void)
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

inline void delay400(void)  __attribute__((always_inline));
inline void delay400(void)
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

  //added with memory
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  //delay_jiffy(20);
}

inline void dobit(uint8_t mask, uint8_t b1, uint8_t b2) __attribute__((always_inline));
inline void dobit(uint8_t mask, uint8_t b1, uint8_t b2){
  pin1h();
  pin2h();
  delay400();
  if ((b1 & mask) == 0) {
    pin1l();
  } else {
    pinNop();
  }
  if ((b2 & mask) == 0) {
    pin2l();
  } else {
    pinNop();
  }
  delay400();
  pin1l();
  pin2l();
  delay450();
}

inline void dobyte(uint8_t b1, uint8_t b2) __attribute__((always_inline));
inline void dobyte(uint8_t b1, uint8_t b2) {
  dobit(0x80, b1, b2);
  dobit(0x40, b1, b2);
  dobit(0x20, b1, b2);
  dobit(0x10, b1, b2);
  dobit(0x08, b1, b2);
  dobit(0x04, b1, b2);
  dobit(0x02, b1, b2);
  dobit(0x01, b1, b2);
}

void delay50u(void) {
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
  delay400();
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

void interval(void) __attribute__ ((long_call, section(".ramfunc")));

__attribute__ ((long_call, section(".ramfunc"))) void interval(void) {
  uint32_t i;
  for (i=0; i < 960000; i++) {
    //1
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
    //2
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
    //3
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
    //4
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
    //5
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
    //6
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
    //7
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
    //8
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
    //9
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
    //10
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
}
void tset(void);
void tset(void)
{
  volatile uint32_t *regs = &(PORT->Group[0].OUTSET.reg);
  volatile uint32_t *regc = &(PORT->Group[0].OUTCLR.reg);
  irq_disable();
  for (int k = 0; k < 20; k++)
  {
    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;

    //end of the loop, do soemthing shorter to compensate for loop instruction
    delay400();
  }
}
void tclr(void);
void tclr(void)
{
  volatile uint32_t *regs = &(PORT->Group[0].OUTSET.reg);
  volatile uint32_t *regc = &(PORT->Group[0].OUTCLR.reg);
  irq_disable();
  for (int k = 0; k < 20; k++)
  {
    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x2040000;
    delay400();
    *regc = 0x2040000;

    //end of the loop, do soemthing shorter to compensate for loop instruction
    delay400();
  }
}
void nmain(void)
{
  volatile uint32_t *regs = &(PORT->Group[0].OUTSET.reg);
  volatile uint32_t *regc = &(PORT->Group[0].OUTCLR.reg);
//  uint32_t val = (1<<18) | (1 << 25);
  irq_disable();

  while(1) {
    tset();
    interval();
    tclr();
    interval();
  }
  while(1){
  for (int k = 0; k < 5*60; k++)
  {
    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;
    delay450();

    *regs = 0x2040000;
    delay400();
    *regc = 0x00000;
    delay400();
    *regc = 0x2040000;

    //end of the loop, do soemthing shorter to compensate for loop instruction
    delay400();
  }
//  while(1);
  for (int ll = 0; ll < 200; ll++) {
    delay450();
  }
}
}

#endif
