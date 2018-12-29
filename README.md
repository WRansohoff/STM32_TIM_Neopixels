# Overview

This is an example of how to run WS2812B and SK6812 'Neopixel' LEDs using an STM32 timer peripheral. Right now it only supports the STM32L432KC, STM32F030K6, and STM32F103C8 with inexact timings, but I'm hoping to generalize it.

Why not use hardware interrupts? Because it takes the STM32 20-30 clock cycles to enter an interrupt, and that's usually longer than 300 nanoseconds. Along those lines, the `next_pulse` method should probably be considered a critical section if you use interrupts.
