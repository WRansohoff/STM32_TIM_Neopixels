#include "interrupts_c.h"

void TIM1_up_TIM16_IRQ_handler(void) {
  GPIOB->BSRR |=  (1 << (16 + PB_LED));
  if (TIM16->SR & TIM_SR_UIF) {
    TIM16->SR  &= ~(TIM_SR_UIF);
    if (ledt == NUM_LEDS && ledb == 23) { done = 1; }
    else { next_pulse(TIM16); }
  }
}
