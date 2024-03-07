#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "string.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdlib.h>
#include <stdint.h>
#include "pico/time.h"


extern const int BTN_PIN_R;
extern const int BTN_PIN_G;
extern const int BTN_PIN_B;
extern const int BTN_PIN_Y;

extern const int BZZ_PIN;

extern const int LED_PIN_R;
extern const int LED_PIN_G;
extern const int LED_PIN_B;
extern const int LED_PIN_Y;


extern volatile int FLAG_BTN_R;
extern volatile int FLAG_BTN_G;
extern volatile int FLAG_BTN_B;
extern volatile int FLAG_BTN_Y;

void btn_callback(uint gpio, uint32_t events);
void pisca (int led, int bzz, int freq);
void beep(int pin, int freq, int time);
void music_start();
uint32_t obter_tempo();

#endif