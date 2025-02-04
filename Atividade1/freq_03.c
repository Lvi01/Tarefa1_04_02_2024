#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

// Função de callback que será chamada repetidamente pelo temporizador
bool semaforo_callback(struct repeating_timer *t) {
    static int estado = 1;

    switch (estado) {
        case 0:  // Vermelho
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 0);
            estado = 1;
            break;
        case 1:  // Amarelo
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 1);
            estado = 2;
            break;
        case 2:  // Verde
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 1);
            estado = 0;
            break;
    }
    return true;
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    //Inicializar o pino GPIO12
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    //Inicializar o pino GPIO13
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 1);

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer_Segundos, timer_Semaforo;

    // Configura o temporizador para chamar a função de callback_semaforo.
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer_Semaforo);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        // Rotina principal do programa
        printf("1 segundo passou\n");
        sleep_ms(1000);
    }
    return 0;
}
