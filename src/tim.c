#include "tim.h"

void start_npx_timer(TIM_TypeDef* TIMx) {
  // Turn the timer off.
  TIMx->CR1 &= ~(TIM_CR1_CEN);
  // Reset the peripheral.
  // TODO: More timers.
  if (TIMx == TIM16) {
    RCC->APB2RSTR |=  (RCC_APB2RSTR_TIM16RST);
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM16RST);
  }
  // Set 'one-pulse' mode.
  //TIMx->CR1  |=  (TIM_CR1_OPM);
  // Set prescaler, auto-reload registers.
  TIMx->PSC   =  (0);
  TIMx->ARR   =  (0xFFFF);
  // Apply settings w/ timer update event.
  TIMx->EGR  |=  (TIM_EGR_UG);
  // Enable interrupt.
  //TIMx->DIER |=  (TIM_DIER_UIE);
  // Turn the timer on.
  //TIMx->CR1  |=  (TIM_CR1_CEN);
}

inline void next_pulse(TIM_TypeDef* TIMx) {
  uint16_t tval = 10;
  if ((grbs[ledt] & (1 << ledb))) { tval = 50; }
  TIMx->CR1   |=  (TIM_CR1_CEN);
  GPIOB->BSRR |=  (1 << PB_LED);
  while (TIMx->CNT < tval) {};
  GPIOB->BSRR |=  (1 << (16 + PB_LED));
  TIMx->CR1   &= ~(TIM_CR1_CEN);
  TIMx->CNT    =  (0);
  ++ledb;
  if (ledb > 23) {
    ledb = 0;
    ++ledt;
    if (ledt > NUM_LEDS) { ledt = 0; done = 1; }
  }
}

void stop_timer(TIM_TypeDef* TIMx) {
  TIMx->CR1 &= ~(TIM_CR1_CEN);
  TIMx->SR  &= ~(TIM_SR_UIF);
}
