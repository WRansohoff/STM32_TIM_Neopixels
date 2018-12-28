#ifndef _VVC_TIM_H
#define _VVC_TIM_H

#include "global.h"
#include "util.h"

void start_npx_timer(TIM_TypeDef* TIMx);
void next_pulse(TIM_TypeDef* TIMx);
void stop_timer(TIM_TypeDef* TIMx);

#endif
