#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_PIN 12       // LED azul do RGB
#define BUTTON_PIN 5     // Botão A
#define BUZZER_PIN 21    // Buzzer A

void initHardware() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Pull-up interno

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

void playTone(int duration) {
    duration = duration > 5 ? 5 : duration;  // Limita a 1 segundo
    printf("Tocando som por %d ms\n", duration);  // Log para depuração

    for (int i = 0; i < duration * 50; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500);
    }

    gpio_put(BUZZER_PIN, 0);  // Garante que o buzzer desligue no final
    printf("Som finalizado\n");  // Log para depuração
}

void startGame() {
    while (1) {
        printf("Prepare-se...\n");

        sleep_ms(rand() % 3000 + 2000);  // Tempo aleatório entre 2s e 5s

        gpio_put(LED_PIN, 1);  // Acende o LED
        absolute_time_t start = get_absolute_time();

        printf("Aguardando botão...\n");  // Log para depuração
        while (gpio_get(BUTTON_PIN) == 1);  // Aguarda botão ser pressionado

        absolute_time_t end = get_absolute_time();
        int reaction_time = absolute_time_diff_us(start, end) / 1000;

        gpio_put(LED_PIN, 0);  // Apaga o LED

        printf("Tempo de reação: %d ms\n", reaction_time);
        playTone(reaction_time);

        printf("Aguardando soltar botão...\n");  // Log para depuração
        while (gpio_get(BUTTON_PIN) == 0);  // Espera o botão ser solto
        sleep_ms(500);  // Delay antes de reiniciar a rodada
    }
}

int main() {
    stdio_init_all();
    initHardware();
    printf("Jogo Iniciado!\n");
    startGame();
    return 0;
}


/*

#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN 7  // Ajuste para o GPIO correto da BitDogLab
#define LED_PIN 15      // LED embutido no Raspberry Pi Pico

int main() {
    stdio_init_all();
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    int count = 0;
    bool last_state = true;
    
    printf("Iniciando contador de botões...\n");
    
    while (true) {
        bool current_state = gpio_get(BUTTON_PIN);
        
        if (!current_state && last_state) { // Detecta borda de descida (pressionado)
            count++;
            printf("Botão pressionado! Contagem: %d\n", count);
            gpio_put(LED_PIN, 1); // Liga LED
            sleep_ms(200);        // Evita múltiplas detecções rápidas
            gpio_put(LED_PIN, 0); // Desliga LED
        }
        
        last_state = current_state;
        sleep_ms(10); // Pequeno atraso para evitar ruído
    }
}
*/