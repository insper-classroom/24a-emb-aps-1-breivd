#include "functions.h"
#include <stdlib.h>

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

void pisca (int led, int bzz, int freq) {
    for (int x=0; x<200; x++){
        gpio_put(led, 1);
        gpio_put(bzz, 1);
        sleep_us(freq);
        gpio_put(bzz, 0);
        sleep_us(freq); 
    }
    gpio_put(led, 0);
}
void beep(int pin, int freq, int time){
    long delay = 1000000 / (2 * freq);
    long cycles = (long)freq * time / 1000;
    for (long i = 0; i < cycles; i++){
        gpio_put(pin, 1);
        sleep_us(delay);
        gpio_put(pin, 0);
        sleep_us(delay);
    }
}

void music_start(){
    // Intro Star Wars
    int led_pins[] = {LED_PIN_R, LED_PIN_G, LED_PIN_B, LED_PIN_Y};
    int led_index = 0; 

    // Frequências, durações e atrasos para o tema de Star Wars
    int freqs[] = {440, 440, 440, 349, 523, 440, 349, 523, 440, 659, 659, 659, 698, 523, 415, 349, 523, 440};
    int times[] = {500, 500, 500, 350, 150, 500, 350, 150, 1000, 500, 500, 500, 350, 150, 500, 350, 150, 1000};
    int delays[] = {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150};

    for (int i = 0; i < sizeof(freqs)/sizeof(freqs[0]); i++) {
        beep(BZZ_PIN, freqs[i], times[i]);
        gpio_put(led_pins[led_index], 1);
        sleep_ms(delays[i]);
        gpio_put(led_pins[led_index], 0); 

        led_index = (led_index + 1) % (sizeof(led_pins)/sizeof(led_pins[0]));
    }
    sleep_ms(1000);
}

uint32_t obter_tempo() {
    uint32_t tempo_us = to_us_since_boot(get_absolute_time());
    return tempo_us;
}