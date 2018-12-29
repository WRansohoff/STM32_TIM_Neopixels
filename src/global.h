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
  #define PB_LED   (11)
  #define GP_TIM   (TIM2)
  #define NPX_P0   (1)
  #define NPX_P1   (40)
#elif  VVC_F0
  #define PB_LED   (0)
  #define GP_TIM   (TIM16)
  #define NPX_P0   (1)
  #define NPX_P1   (20)
#else
  #define PB_LED   (0)
  #define GP_TIM   (TIM16)
  #define NPX_P0   (10)
  #define NPX_P1   (50)
#endif
#define NUM_LEDS   (3)

// Global variables.
char     done;
uint32_t core_clock_hz;
int      ledi, ledb, ledt;
uint32_t grbs[NUM_LEDS];

#endif
