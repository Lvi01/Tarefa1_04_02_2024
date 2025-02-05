# 🚦 Simulação de Temporizadores no Raspberry Pi Pico W

Este repositório contém a implementação das atividades relacionadas ao uso de temporizadores periódicos e de um disparo (one-shot) utilizando a plataforma Raspberry Pi Pico W e o Pico SDK.
A resolução de cada atividade pode ser encontrada nas suas respectivas pastas dentro do repositório, para garantir sua organização e legibilidade.

# 📌 Objetivo

Implementar dois sistemas de controle utilizando LEDs e botões para explorar os temporizadores disponíveis no Pico SDK. A simulação será feita no Wokwi e os testes serão realizados no VS Code com o suporte da Ferramenta Educacional BitDogLab.

# 🔩 Componentes Utilizados

Microcontrolador: Raspberry Pi Pico W

LEDs: Vermelho, amarelo, verde, azul

Resistores: 330 Ω para cada LED

Pushbutton: Para ativação do temporizador one-shot

Software: Pico SDK, VS Code, Wokwi, BitDogLab


# ⚡ Funcionalidades

# 🔴🟡🟢 Atividade 1: Temporizador Periódico

Alternância de LEDs em um semáforo a cada 3 segundos com add_repeating_timer_ms().

Sequência de cores: vermelho → amarelo → verde.

Impressão de mensagens a cada 1 segundo via porta serial.

# 🔵🔴🟢 Atividade 2: Temporizador One-Shot

LEDs ativados ao pressionar um botão com add_alarm_in_ms().

Acionamento progressivo dos LEDs a cada 3 segundos.


O botão não pode ser pressionado durante a execução da sequência.

Implementação opcional de debounce via software.

# ✅ Requisitos Implementados

✔️ Desenvolvimento em linguagem C com Pico SDK

✔️ Uso do Wokwi para simulação dos circuitos

✔️ Integração com BitDogLab para testes com LED RGB e pushbutton

✔️ Código estruturado com funções de callback para temporizadores

✔️ Implementação de testes básicos para validação
