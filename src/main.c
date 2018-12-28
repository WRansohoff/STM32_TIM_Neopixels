#include "main.h"

/**
 * Main program.
 */
int main(void) {
  // Initial clock setup.
  clock_setup();
  // Clean out the initial LED colors.
  for (ledi = 0; ledi < NUM_LEDS; ++ledi) {
    grbs[ledi] = 0x000AAA00;
  }
  ledb = 0;
  ledt = 0;
  done = 0;

  // Enable the GPIOA and GPIOB peripherals.
  #ifdef VVC_F0
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;
  #elif  VVC_F1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  #elif  VVC_L0
    RCC->IOPENR  |= RCC_IOPENR_IOPAEN;
    RCC->IOPENR  |= RCC_IOPENR_IOPBEN;
  #elif  VVC_L4
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
  #endif

  // Output type: Push-pull, high-speed.
  // TODO: low-speed?
  #if defined(VVC_F1)
    #if (PB_LED < 8)
      GPIOB->CRL    &= ~(0xF << (PB_LED * 4));
      GPIOB->CRL    |=  (0x3 << (PB_LED * 4));
    #else
      GPIOB->CRH    &= ~(0xF << ((PB_LED - 8) * 4));
      GPIOB->CRH    |=  (0x3 << ((PB_LED - 8) * 4));
    #endif
  #else
    GPIOB->MODER    &= ~(0x3 << (PB_LED * 2));
    GPIOB->MODER    |=  (0x1 << (PB_LED * 2));
    GPIOB->OTYPER   &= ~(0x1 << PB_LED);
    GPIOB->OSPEEDR  |=  (0x3 << (PB_LED * 2));
    GPIOB->ODR      |=  (1 << PB_LED);
  #endif

  // Setup timer interrupt.
  NVIC_SetPriorityGrouping(0x05);
  uint32_t exti_pri_encoding = NVIC_EncodePriority(0x05, 0x03, 0x03);
  NVIC_SetPriority(TIM1_UP_TIM16_IRQn, exti_pri_encoding);
  NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

  start_npx_timer(TIM16);
  while (1) {
    while (!done) {
      next_pulse(TIM16);
    }
    ledb = 0;
    ledt = 0;
    done = 0;
    delay_cycles(2000000);
  }
}
