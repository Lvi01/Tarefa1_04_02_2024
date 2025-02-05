// Autor: [Seu Nome]
// Data: 2025-02-04
// Descrição: Programa para controle de um semáforo utilizando a placa Raspberry Pi Pico.
//            O semáforo alterna entre os estados vermelho, amarelo e verde em intervalos de 3 segundos,
//            utilizando temporizadores de hardware para garantir a precisão da temporização.

// Inclusão de bibliotecas necessárias para o programa
#include <stdio.h>            // Biblioteca padrão de E/S
#include "pico/stdlib.h"     // Biblioteca padrão do Pico para GPIO, temporização e comunicação serial
#include "hardware/timer.h" // Biblioteca para gerenciamento de temporizadores de hardware

// Definição de constantes
#define LED_RED_PIN 13        // GPIO13 - LED Vermelho
#define LED_YELLOW_PIN 12     // GPIO12 - LED Amarelo
#define LED_GREEN_PIN 11     // GPIO11 - LED Verde
#define INTERVALO 3000      // Intervalo de troca de estado em milissegundos (3 segundos)

// Protótipo da função de callback do temporizador
/**
 * @brief Callback do temporizador para controlar o semáforo.
 *
 * Esta função é chamada periodicamente pelo temporizador para alternar o estado dos LEDs
 * que representam um semáforo.
 *
 * @param t Ponteiro para a estrutura do temporizador.
 * @return true para continuar a repetição do temporizador, false para parar.
 */
bool semaforo_callback(struct repeating_timer *t);

/**
 * @brief Inicializa os componentes do semáforo.
 * 
 * Esta função inicializa os pinos dos LEDs do semáforo e configura o semáforo no estado inicial.
 */
void init_components();

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    init_components(); // Inicializa os componentes

    // Declara e inicializa o temporizador
    struct repeating_timer timer_Semaforo;
    add_repeating_timer_ms(INTERVALO, semaforo_callback, NULL, &timer_Semaforo);

    // Loop principal
    while (1) {
        printf("1 segundo passou\n");
        sleep_ms(1000);
    }

    return 0;
}

// Função de callback do temporizador para alternar os estados do semáforo
bool semaforo_callback(struct repeating_timer *t) {
    static uint8_t estado = 1; // Estado atual do semáforo

    switch (estado) {
        case 0:  // Vermelho
            printf("Vermelho\n");
            gpio_put(LED_RED_PIN, 1);     // Liga o LED vermelho
            gpio_put(LED_YELLOW_PIN, 0); // Desliga o LED amarelo
            gpio_put(LED_GREEN_PIN, 0); // Desliga o LED verde
            estado = 1;
            break;
        case 1:  // Amarelo
            printf("Amarelo\n");
            gpio_put(LED_RED_PIN, 0);        // Desliga o LED vermelho
            gpio_put(LED_YELLOW_PIN, 1);    // Liga o LED amarelo
            gpio_put(LED_GREEN_PIN, 0);    // Desliga o LED verde
            estado = 2;
            break;
        case 2:  // Verde
            printf("Verde\n");
            gpio_put(LED_RED_PIN, 0);     // Desliga o LED vermelho
            gpio_put(LED_YELLOW_PIN, 0); // Desliga o LED amarelo
            gpio_put(LED_GREEN_PIN, 1); // Liga o LED verde
            estado = 0;
            break;
    }
    return true;
}

void init_components() {
   // Inicializa os LEDs como saída
    gpio_init(LED_RED_PIN);               // Inicializa o pino do LED vermelho
    gpio_set_dir(LED_RED_PIN, GPIO_OUT); // Configura o pino do LED vermelho como saída

    gpio_init(LED_YELLOW_PIN);               // Inicializa o pino do LED amarelo
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT); // Configura o pino do LED amarelo como saída

    gpio_init(LED_GREEN_PIN);               // Inicializa o pino do LED verde
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT); // Configura o pino do LED verde como saída

    // Inicia o semáforo no estado vermelho
    gpio_put(LED_RED_PIN, 1);     // Liga o LED vermelho
    gpio_put(LED_YELLOW_PIN, 0); // Desliga o LED amarelo
    gpio_put(LED_GREEN_PIN, 0); // Desliga o LED verde
}
