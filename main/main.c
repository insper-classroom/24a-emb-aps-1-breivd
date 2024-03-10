/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "functions.h"

const int BTN_PIN_R = 10;
const int BTN_PIN_G = 11;
const int BTN_PIN_B = 12;
const int BTN_PIN_Y = 13;

const int BZZ_PIN = 14;

const int LED_PIN_R = 18;
const int LED_PIN_G = 19;
const int LED_PIN_B = 20;
const int LED_PIN_Y = 21;

volatile int FLAG_BTN_R = 0;
volatile int FLAG_BTN_G = 0;
volatile int FLAG_BTN_B = 0;
volatile int FLAG_BTN_Y = 0;

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

    stdio_init_all();                                                                           //++ Initialize rp2040

    //musiquinha inicial

    music_start();

    // codigo

    bool genius = true;

    int sequencia_genius[100] = {0};
    int sequencia_jogada[100] = {0}; // inicializa todos os elementos da lista como 0;
    int index = 0;
    int n = 1;

    const int red = 0;
    const int green = 1;
    const int blue = 2;
    const int yellow = 3;

    int i = 0;
   

    while (1) {

        while (genius) {
            
            srandom((unsigned int) obter_tempo());

            sequencia_genius[i] = random() % 4;
            
            
            for (int j = 0; j < n; j++){
                sleep_ms(500);
                if (sequencia_genius[j] == red){
                    pisca(LED_PIN_R, BZZ_PIN, 440);
                }
                else if (sequencia_genius[j] == green){
                    pisca(LED_PIN_G, BZZ_PIN, 660);
                }
                else if (sequencia_genius[j] == blue){
                    pisca(LED_PIN_B, BZZ_PIN, 880);
                }
                else if (sequencia_genius[j] == yellow){
                    pisca(LED_PIN_Y, BZZ_PIN, 1220);
                }
            }

            genius = false;

            i++;
        }

        if (FLAG_BTN_R){
            pisca(LED_PIN_R, BZZ_PIN, 440);
            sequencia_jogada[index] = red;
            index++;
        }FLAG_BTN_R = 0;
        if (FLAG_BTN_G){
            pisca(LED_PIN_G, BZZ_PIN, 660);
            sequencia_jogada[index] = green;
            index++;
        }FLAG_BTN_G = 0;
        if (FLAG_BTN_B){
            pisca(LED_PIN_B, BZZ_PIN, 880);
            sequencia_jogada[index] = blue;
            index++;
        }FLAG_BTN_B = 0;
        if (FLAG_BTN_Y){
            pisca(LED_PIN_Y, BZZ_PIN, 1220);
            sequencia_jogada[index] = yellow;
            index++;
        }FLAG_BTN_Y = 0;

        if (index >= n){
            for (int k = 0; k < n; k++){
                if (sequencia_genius[k] != sequencia_jogada[k]){

                    printf("oce errou.");
                    for (int x=0; x<2000; x++){
                        gpio_put(LED_PIN_B, 1);
                        gpio_put(LED_PIN_R, 1);
                        gpio_put(LED_PIN_Y, 1);
                        gpio_put(LED_PIN_G, 1);
                        gpio_put(BZZ_PIN, 1);
                        sleep_us(1200);
                        gpio_put(BZZ_PIN, 0);
                        sleep_us(1200); 
                    }
                    gpio_put(LED_PIN_B, 0);
                    gpio_put(LED_PIN_R, 0);
                    gpio_put(LED_PIN_Y, 0);
                    gpio_put(LED_PIN_G, 0);
                    for (int y = 0; y<n-1;y++){
                        pisca(LED_PIN_B, BZZ_PIN, 880);
                        sleep_ms(500);
                    }
                    
                    return 0;
                
                } else { 
                    printf("voce acertou... \n");
                    index = 0;
                    genius = true;
                }
            }
            
            n+=1;
            
        }

        if (n == 100) {
            printf("voce ganhou");
            return 1;
        }

    }
}