/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdlib.h>
#include <time.h>

const int BTN_PIN_R = 10;
const int BTN_PIN_G = 11;
const int BTN_PIN_B = 12;
const int BTN_PIN_Y = 13;

const int BZZ_PIN = 14;

const int LED_PIN_R = 21;
const int LED_PIN_G = 20;
const int LED_PIN_B = 19;
const int LED_PIN_Y = 18;


volatile int FLAG_BTN_R = 0;
volatile int FLAG_BTN_G = 0;
volatile int FLAG_BTN_B = 0;
volatile int FLAG_BTN_Y = 0;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4){
    if(gpio == BTN_PIN_R){
      FLAG_BTN_R = 1;
    }
    else if(gpio == BTN_PIN_G){
      FLAG_BTN_G = 1;
    }
    else if(gpio == BTN_PIN_B){
      FLAG_BTN_B = 1;
    }
    else if(gpio == BTN_PIN_Y){
      FLAG_BTN_Y = 1;
    } 
  }
}

void butao (int btn, int led, int bzz, int freq) {
    for (int x=0; x<200; x++){
        gpio_put(led, 1);
        gpio_put(bzz, 1);
        sleep_us(freq);
        gpio_put(bzz, 0);
        sleep_us(freq); 
    }
    gpio_put(led, 0);
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);

    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);

    gpio_init(LED_PIN_Y);
    gpio_set_dir(LED_PIN_Y, GPIO_OUT);

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    gpio_init(BTN_PIN_B);
    gpio_set_dir(BTN_PIN_B, GPIO_IN);
    gpio_pull_up(BTN_PIN_B);

    gpio_init(BTN_PIN_Y);
    gpio_set_dir(BTN_PIN_Y, GPIO_IN);
    gpio_pull_up(BTN_PIN_Y);

    gpio_init(BZZ_PIN);
    gpio_set_dir(BZZ_PIN, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BTN_PIN_B, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BTN_PIN_Y, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    // codigo

    int sequencia_genius[4];
    int sequencia_jogada[4];

    srand(time(NULL));

    for (int i = 0; i < 4; i++) {
        sequencia_genius[i] = rand() % 4; // Gera um número aleatório de 0 a NUM_BOTOES-1
    }

    while (true) {

        if (FLAG_BTN_R){
            butao(FLAG_BTN_R, LED_PIN_R, BZZ_PIN, 440);

        }FLAG_BTN_R = 0;
        if (FLAG_BTN_G){
            butao(FLAG_BTN_G, LED_PIN_G, BZZ_PIN, 660);
        }FLAG_BTN_G = 0;
        if (FLAG_BTN_B){
            butao(FLAG_BTN_B, LED_PIN_B, BZZ_PIN, 880);
        }FLAG_BTN_B = 0;
        if (FLAG_BTN_Y){
            butao(FLAG_BTN_Y, LED_PIN_Y, BZZ_PIN, 1220);
        }FLAG_BTN_Y = 0;
    }
}
