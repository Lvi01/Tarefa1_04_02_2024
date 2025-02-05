# 🔵🔴🟢 Atividade 2: Temporizador One-Shot

Este repositório contém a implementação da Atividade 2, que consiste em criar um sistema de temporização utilizando um botão (pushbutton) para ativar LEDs sequencialmente. O controle de tempo é feito com a função add_alarm_in_ms() do Pico SDK.

# 📌 Objetivo

Criar um sistema no Raspberry Pi Pico W onde:

1️⃣ Ao pressionar um botão, três LEDs acendem simultaneamente.

2️⃣ A cada 3 segundos, um LED se apaga até que todos estejam desligados.

3️⃣ Durante a sequência, o botão não pode ser pressionado novamente.

4️⃣ O código pode ser testado no BitDogLab utilizando um LED RGB e o botão no GPIO 05.

5️⃣ Implementado debounce via software para evitar leituras indesejadas do botão.

# 🔩 Componentes Utilizados

Microcontrolador: Raspberry Pi Pico W

LEDs: Azul, Vermelho e Verde

Resistores: 330 Ω para cada LED

Pushbutton: Para ativação do temporizador one-shot

Software: Pico SDK, VS Code, Wokwi, BitDogLab

# ⚙️ Funcionamento

1️⃣ O usuário pressiona o botão → todos os LEDs acendem.

2️⃣ Após 3 segundos, um LED se apaga.

3️⃣ Após mais 3 segundos, outro LED se apaga.

4️⃣ Após mais 3 segundos, o último LED se apaga.

5️⃣ O botão só pode ser pressionado novamente quando todos os LEDs estiverem apagados.

# ✅ Requisitos Implementados

✔️ Uso de add_alarm_in_ms() para temporização one-shot

✔️ Sequência de LEDs ativada pelo botão e controlada pelo temporizador

✔️ Prevenção de novas ativações enquanto o ciclo não for concluído

✔️ Simulação no Wokwi e testes no BitDogLab

✔️ Implementação opcional de debounce via software
