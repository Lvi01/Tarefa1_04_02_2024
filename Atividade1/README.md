# 🚦 Atividade 1: Temporizador Periódico

Este repositório contém a implementação da Atividade 1, que consiste em simular um semáforo utilizando temporização periódica com a função add_repeating_timer_ms() do Pico SDK.

# 📌 Objetivo

Criar um sistema de controle de LEDs que simula um semáforo, alternando suas cores a cada 3 segundos, seguindo uma lógica cíclica:

# 🔴 Vermelho → 🟡 Amarelo → 🟢 Verde

Além disso, o programa deve imprimir mensagens na porta serial a cada 1 segundo.

# 🔩 Componentes Utilizados

Microcontrolador: Raspberry Pi Pico W

LEDs: Vermelho, Amarelo e Verde

Resistores: 330 Ω para cada LED

Software: Pico SDK, VS Code, Wokwi

# ⚙️ Funcionamento

1️⃣ O código inicia com o LED vermelho aceso.

2️⃣ A cada 3 segundos, a função de callback do temporizador altera o estado dos LEDs.

3️⃣ O ciclo se repete indefinidamente.

4️⃣ A cada 1 segundo, uma mensagem é enviada para a porta serial.

# ✅ Requisitos Implementados

✔️ Uso de add_repeating_timer_ms() para temporização periódica

✔️ Alternância de LEDs conforme a lógica do semáforo

✔️ Impressão de mensagens a cada segundo na porta serial

✔️ Simulação no Wokwi para validação
