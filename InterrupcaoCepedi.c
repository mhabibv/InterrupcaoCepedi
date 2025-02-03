#include <stdio.h>
#include "pico/stdlib.h"
#include "auxleds.h"

// Definição dos pinos usados
#define LED_PIN 13   // GPIO do LED indicador
#define BUTTON_UP 6  // Botão de incremento
#define BUTTON_DOWN 5 // Botão de decremento

// Variáveis globais
volatile uint8_t current_number = 0;   // Número exibido na matriz de LEDs
const uint8_t debounce_interval = 100; // Intervalo de debounce em milissegundos
absolute_time_t button_debounce_time;  // Controle de debounce do botão

/**
 * @brief Manipulador de interrupção para os botões.
 * 
 * Verifica qual botão foi pressionado e atualiza o número exibido na matriz de LEDs.
 * Implementa debounce para evitar múltiplas leituras indesejadas.
 * 
 * @param pin GPIO do botão acionado.
 * @param events Tipo de evento ocorrido na interrupção.
 */
void button_irq_handler(uint pin, uint32_t events) {
    if (time_reached(button_debounce_time)) { // Verifica se passou o tempo de debounce
        if (pin == BUTTON_UP) {
            current_number = (current_number + 1) % 10; // Incrementa e volta a 0 ao atingir 10
        } else if (pin == BUTTON_DOWN) {
            current_number = (current_number == 0) ? 9 : current_number - 1; // Decrementa e volta a 9 se for 0
        }

        display_frame(digits, current_number); // Atualiza a matriz de LEDs com o novo número
        
        // Atualiza o tempo de debounce para evitar leituras repetidas
        button_debounce_time = delayed_by_ms(get_absolute_time(), debounce_interval * 2);
    }
}

/**
 * @brief Inicializa um botão configurando seu pino como entrada com pull-up.
 * 
 * @param pin GPIO do botão a ser inicializado.
 */
void init_button(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin); // Ativa o pull-up para evitar leituras flutuantes
}

/**
 * @brief Função principal do programa.
 * 
 * Inicializa os periféricos, configura os botões e entra em loop para controle do LED e da matriz de LEDs.
 */
int main() {
    // Inicialização dos periféricos
    stdio_init_all(); // Inicializa a comunicação serial
    setup_matrix();   // Configura a matriz de LEDs
    init_led(LED_PIN); // Inicializa o LED indicador
    init_button(BUTTON_UP); // Configura botão de incremento
    init_button(BUTTON_DOWN); // Configura botão de decremento

    // Define tempos iniciais para debounce e LED
    absolute_time_t next_led_time = delayed_by_ms(get_absolute_time(), debounce_interval);
    button_debounce_time = delayed_by_ms(get_absolute_time(), debounce_interval * 2);

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_UP, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_DOWN, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);

    // Exibe o número inicial na matriz de LEDs
    display_frame(digits, current_number);

    // Loop principal
    while (1) {
        // Verifica se chegou o momento de alternar o LED indicador
        if (time_reached(next_led_time)) {
            toggle_led(LED_PIN); // Alterna o estado do LED
            next_led_time = delayed_by_ms(get_absolute_time(), debounce_interval); // Atualiza tempo do LED
        }
        sleep_ms(1); // Pequeno atraso para evitar consumo excessivo de CPU
    }
}
