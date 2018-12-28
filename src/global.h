#ifndef _VVC_GLOBAL_H
#define _VVC_GLOBAL_H

#include <stdint.h>

#ifdef VVC_F0
  #include "stm32f0xx.h"
#elif VVC_F1
  #include "stm32f1xx.h"
#elif  VVC_L0
  #include "stm32l0xx.h"
#elif  VVC_L4
  #include "stm32l4xx.h"
#endif

// Global defines.
#ifdef VVC_F1
  #define PB_LED   (12)
#else
  #define PB_LED   (0)
#endif
#define NUM_LEDS   (3)

// Global variables.
char     done;
uint32_t core_clock_hz;
int      ledi, ledb, ledt;
uint32_t grbs[NUM_LEDS];

#endif
