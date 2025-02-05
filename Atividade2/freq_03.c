// Autor: Levi Silva Freitas
// Data: 2025-02-04
// Descrição: Programa para controle de LEDs utilizando a placa Raspberry Pi Pico.  
//            O sistema acende todos os LEDs ao pressionar um botão e, em seguida,  
//            os apaga sequencialmente a cada 3 segundos, utilizando temporizadores de hardware.  
//            A interrupção do botão é desativada durante o processo e reativada ao final.

// Inclusão de bibliotecas necessárias para o programa
#include <stdio.h>            // Biblioteca padrão de E/S
#include "pico/stdlib.h"     // Biblioteca padrão do Pico para GPIO, temporização e comunicação serial
#include "hardware/timer.h" // Biblioteca para gerenciamento de temporizadores de hardware
#include "pico/time.h"     // Biblioteca para gerenciamento de temporizadores e alarmes.

// Definição de constantes
#define LED_RED_PIN 13             // GPIO13 - LED Vermelho
#define LED_YELLOW_PIN 12         // GPIO12 - LED Amarelo
#define LED_GREEN_PIN 11         // GPIO11 - LED Verde
#define button_A 5              // GPIO5 - Botão A
#define INTERVALO_1 3000       // Intervalo de troca de estado em milissegundos (3 segundos)
#define INTERVALO_2 6000      // Intervalo de troca de estado em milissegundos (6 segundo)
#define INTERVALO_3 9000     // Intervalo de troca de estado em milissegundos (9 segundos)

// Variáveis globais para controle do tempo
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

// Protótipos de funções

/**
 * @brief Função de callback para desligar os LEDs do semáforo.
 * 
 * @param id O identificador do temporizador.
 * @param user_data Dados do usuário.
 * @return int64_t O tempo em microssegundos para o próximo evento.
 */
int64_t turn_off_callback(alarm_id_t id, void *user_data);

/**
 * @brief Inicializa os componentes do semáforo.
 * 
 * Esta função inicializa os pinos dos LEDs do semáforo e configura o semáforo no estado inicial.
 */
void init_components();

/**
 * @brief Função de interrupção com debouncing.
 * 
 * @param gpio O pino GPIO que gerou a interrupção.
 * @param events Os eventos que ocorreram.
 */
static void gpio_irq_handler(uint gpio, uint32_t events); 

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    init_components(); // Inicializa os componentes

    // Configuração da interrupção com callback para o botão A
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);  // Habilita a interrupção no botão A

    // Loop principal
    while (1) {
        printf("1 segundo passou\n");
        sleep_ms(1000);
    }

    return 0;
}

// Implementação das funções
// Função de callback para desligar os LEDs do semáforo
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    static uint8_t estado = 1; // Estado atual do semáforo

    switch (estado) {
        case 1: 
            printf("Apagando o LED vermelho\n");
            gpio_put(LED_RED_PIN, 0);        // Desliga o LED vermelho
            estado = 2;
            break;
        case 2:
            printf("Apagando o LED amarelo\n");
            gpio_put(LED_YELLOW_PIN, 0); // Desliga o LED amarelo
            estado = 3;
            break;
        case 3:
            printf("Apagando o LED verde\n");
            gpio_put(LED_GREEN_PIN, 0); // Desliga o LED verde
            gpio_set_irq_enabled(button_A, GPIO_IRQ_EDGE_FALL, true); // Habilita a interrupção no botão A novamente
            estado = 1;
            break;
    }
    return 0;
}

// Inicializa os componentes do semáforo
void init_components() {
    // Inicializa os LEDs como saída
    gpio_init(LED_RED_PIN);               // Inicializa o pino do LED vermelho
    gpio_set_dir(LED_RED_PIN, GPIO_OUT); // Configura o pino do LED vermelho como saída

    gpio_init(LED_YELLOW_PIN);               // Inicializa o pino do LED amarelo
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT); // Configura o pino do LED amarelo como saída

    gpio_init(LED_GREEN_PIN);               // Inicializa o pino do LED verde
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT); // Configura o pino do LED verde como saída

    // Garante que os LEDs estão desligados
    gpio_put(LED_RED_PIN, 0);     // Desliga o LED vermelho
    gpio_put(LED_YELLOW_PIN, 0); // Desliga o LED amarelo
    gpio_put(LED_GREEN_PIN, 0); // Desliga o LED verde
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento, para evitar o debouncing
    if (current_time - last_time > 200000) // 200 ms de debouncing e livre para novos eventos
    {
        last_time = current_time; // Atualiza o tempo do último evento
        gpio_set_irq_enabled(button_A, GPIO_IRQ_EDGE_FALL, false); // Desabilita a interrupção no botão A para evitar múltiplos eventos
        printf("Botão apertado, rotina iniciada\n");
        gpio_put(LED_RED_PIN, 1);     // Liga o LED vermelho
        gpio_put(LED_YELLOW_PIN, 1); // Liga o LED amarelo
        gpio_put(LED_GREEN_PIN, 1); // Liga o LED verde
        add_alarm_in_ms(INTERVALO_1, turn_off_callback, NULL, false);   // Adiciona um alarme para desligar o primeiro LED em 3 segundos
        add_alarm_in_ms(INTERVALO_2, turn_off_callback, NULL, false);  // Adiciona um alarme para desligar o segundo LED em 6 segundos
        add_alarm_in_ms(INTERVALO_3, turn_off_callback, NULL, false); // Adiciona um alarme para desligar o terceiro LED em 9 segundos
    } 
}