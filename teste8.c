/*

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
    duration = duration > 5 ? 5 : duration;  // Limita a .5 segundos
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

*/

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definições dos pinos da BitDogLab
#define LED_R 13       // LED vermelho do RGB
#define LED_G 11       // LED verde do RGB
#define LED_B 12       // LED azul do RGB
#define BUTTON_PIN 5   // Botão A
#define BUZZER_PIN 21  // Buzzer A

int led_state = 0;  // Estado para alternar as cores do LED

void initHardware() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Pull-up interno

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// Alterna a cor do LED RGB e acende
void changeLedColor() {
    // Desliga todas as cores antes de ligar a próxima
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);

    // Alterna entre as cores e acende o LED
    if (led_state == 0) {
        gpio_put(LED_R, 1);  // Vermelho
    } else if (led_state == 1) {
        gpio_put(LED_G, 1);  // Verde
    } else {
        gpio_put(LED_B, 1);  // Azul
    }

    // Atualiza o estado para a próxima rodada
    led_state = (led_state + 1) % 3;
}

// Função para tocar som no buzzer
void playTone(int duration) {
    duration = duration > 5 ? 5 : duration;  // Limita a 1 segundo
    //printf("Tocando som por %d ms\n", duration);

    for (int i = 0; i < duration * 50; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500);
    }

    gpio_put(BUZZER_PIN, 0);
   // printf("Som finalizado\n");
}

void startGame() {
    while (1) {
        printf("Prepare-se...\n");

        sleep_ms(rand() % 3000 + 2000);  // Tempo aleatório entre 2s e 5s

        changeLedColor();  // Muda a cor do LED RGB (e acende)
        absolute_time_t start = get_absolute_time();

        printf("Aguardando botão...\n");
        while (gpio_get(BUTTON_PIN) == 1);  // Aguarda botão ser pressionado

        gpio_put(LED_R, 0);  // Apaga o LED
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 0);

        absolute_time_t end = get_absolute_time();
        int reaction_time = absolute_time_diff_us(start, end) / 1000;

        printf("Tempo de reação: %d ms\n", reaction_time);
        playTone(reaction_time);

        printf("Aguardando soltar botão...\n");
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
