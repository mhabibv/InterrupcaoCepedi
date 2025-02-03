#include "auxleds.h"

#define NUM_PIXELS 25  // Número total de LEDs na matriz
#define OUT_PIN 7  // Pino de saída para controle dos LEDs

// Inicializa a interface PIO e o estado da máquina
PIO pio = pio0;
uint sm = 0;

// Função para alternar o estado de um LED específico
void toggle_led(uint8_t pin){
    gpio_put(pin, !gpio_get(pin));
}

// Configura a matriz de LEDs e inicializa a PIO
void setup_matrix() {
    bool success;
    success = set_sys_clock_khz(133000, false); // Define o clock do sistema para 133 MHz
    stdio_init_all(); // Inicializa entrada e saída padrão

    uint offset = pio_add_program(pio, &pio_matrix_program); // Adiciona o programa PIO
    sm = pio_claim_unused_sm(pio, true); // Obtém um state machine disponível
    pio_matrix_program_init(pio, sm, offset, OUT_PIN); // Inicializa o programa na PIO
}

// Converte o índice de um pixel para a posição correta na matriz de LEDs
uint8_t get_pixel_index(uint8_t i) {
    uint8_t x = i % 5; // Obtém a coordenada X
    uint8_t y = i / 5; // Obtém a coordenada Y
    
    // Define a posição correta dependendo da linha ser par ou ímpar
    return (y % 2 == 0) ? 24 - (y * 5 + x) : 24 - (y * 5 + (4 - x));
}

// Exibe um quadro da matriz de LEDs
void display_frame(const uint32_t matrix[10][25], uint8_t frame) {
    for (uint8_t i = 0; i < NUM_PIXELS; i++) {
        uint8_t position = get_pixel_index(i); // Obtém o índice correto do pixel
        pio_sm_put_blocking(pio0, sm, matrix[frame][position]); // Envia os dados do pixel para a PIO
    }
}

// Inicializa um LED específico como saída
void init_led(uint8_t pin){
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

const uint32_t digits[10][25] = {

    // 0
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 1
    {
    0x00000000, 0x00000000, 0x190000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x190000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x190000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x190000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x190000, 0x00000000, 0x00000000
    },

    // 2

    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 3
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 4
    {
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000
    },

    // 5
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 6
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 7
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000
    },

    // 8
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    },

    // 9
    {
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x190000, 0x00000000, 
    0x00000000, 0x190000, 0x190000, 0x190000, 0x00000000
    }
};
