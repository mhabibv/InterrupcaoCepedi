#ifndef AUXLEDS_H
#define AUXLEDS_H

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.pio.h"


// Definindo o número de LEDs e o pino de saída
#define NUM_PIXELS 25
#define OUT_PIN 7

// Definindo os protótipos das funções
void init_led(uint8_t pin);
void toggle_led(uint8_t pin);
uint8_t get_pixel_index(uint8_t i);
void display_frame(const uint32_t matrix[10][25], uint8_t frame);
void setup_matrix(void);

// Definindo os números de 0 a 9 como matrizes de LEDs
extern const uint32_t digits[10][25];

#endif
