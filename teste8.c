#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definições dos pinos da BitDogLab
#define LED_R 13       // LED vermelho do RGB
#define LED_G 11       // LED verde do RGB
#define LED_B 12       // LED azul do RGB
#define BUTTON_A 5     // Botão A
#define BUTTON_B 6     // Botão B
#define BUZZER_PIN 21  // Buzzer A

int led_state = 0;      // Estado para alternar as cores do LED
int rodada_count = 0;   // Contador de rodadas
int best_reaction_time = 10000; // Inicializando com um tempo de reação bem alto (10 segundos)

// Função para inicializar o hardware
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

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);  // Pull-up interno

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);  // Pull-up interno

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// Função para definir as cores do arco-íris
void setRainbowColor(int color) {
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);

    switch (color) {
        case 0:  // Vermelho
            gpio_put(LED_R, 1);
            break;
        case 1:  // Laranja
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            break;
        case 2:  // Amarelo
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            break;
        case 3:  // Verde
            gpio_put(LED_G, 1);
            break;
        case 4:  // Azul
            gpio_put(LED_B, 1);
            break;
        case 5:  // Anil
            gpio_put(LED_B, 1);
            gpio_put(LED_R, 1);
            break;
        case 6:  // Violeta
            gpio_put(LED_B, 1);
            gpio_put(LED_R, 1);
            break;
        default:
            break;
    }
}

// Função para tocar som no buzzer
void playTone(int duration) {
    duration = duration > 5 ? 5 : duration;
    for (int i = 0; i < duration * 50; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500);
    }
    gpio_put(BUZZER_PIN, 0);
}

// Função para tocar som de erro (descendente)
void playErrorTone() {
    printf("Opa! botão errado\n");

    int freqs[] = {1000, 800, 600, 400, 200};  // Tons descendentes
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 100; j++) {
            gpio_put(BUZZER_PIN, 1);
            sleep_us(freqs[i]);
            gpio_put(BUZZER_PIN, 0);
            sleep_us(freqs[i]);
        }
        sleep_ms(50);
    }

    gpio_put(BUZZER_PIN, 0);
}

// Função para tocar um som de celebração (novo recorde)
void playCelebrationTone() {
    int freqs[] = {1500, 1600, 1700, 1800, 1900, 2000};  // Tons ascendentes
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 100; j++) {
            gpio_put(BUZZER_PIN, 1);
            sleep_us(1000000 / freqs[i] / 2);  // Meia duração da nota
            gpio_put(BUZZER_PIN, 0);
            sleep_us(1000000 / freqs[i] / 2);  // Meia duração da nota
        }
        sleep_ms(100);  // Aguarda um pouco entre as notas
    }
}

// Função para piscar os LEDs 5 vezes antes de iniciar o jogo
void blinkLEDs() {
    for (int i = 0; i < 5; i++) {
        // Pisca todos os LEDs
        gpio_put(LED_R, 1);
        gpio_put(LED_G, 1);
        gpio_put(LED_B, 1);
        sleep_ms(200);
        gpio_put(LED_R, 0);
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 0);
        sleep_ms(200);
    }
}

// Função para tocar a melodia de Super Mario Bros
void playMarioMelody() {
    // Notas da melodia de Mario Bros (frequências em Hz)
    int notes[] = {659, 659, 659, 523, 440, 349, 523, 659, 659, 659, 523, 440, 349};
    // Durações das notas em milissegundos
    int durations[] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 800};
    
    // Toca cada nota da melodia
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 100; j++) {
            gpio_put(BUZZER_PIN, 1);
            sleep_us(1000000 / notes[i] / 2);  // Meia duração da nota (tempo para o som)
            gpio_put(BUZZER_PIN, 0);
            sleep_us(1000000 / notes[i] / 2);  // Meia duração da nota (tempo para o silêncio)
        }
        sleep_ms(durations[i]);  // Aguarda a duração total da nota
    }
}

// Função principal do jogo
void startGame() {
    while (rodada_count < 5) {  // Limita o número de rodadas a 5
        printf("Rodada %d: Prepare-se...\n", rodada_count + 1);
        sleep_ms(rand() % 3000 + 2000);

        int current_led = led_state;
        setRainbowColor(current_led);
        absolute_time_t start = get_absolute_time();
        //printf("Aguardando botão...\n");

        int correct_button = (current_led == 0 || current_led == 3) ? BUTTON_B : BUTTON_A;  

        while (gpio_get(correct_button) == 1) {
            if (gpio_get(BUTTON_A) == 0 && correct_button != BUTTON_A) {
                playErrorTone();
                sleep_ms(500);
                continue;
            }
            if (gpio_get(BUTTON_B) == 0 && correct_button != BUTTON_B) {
                playErrorTone();
                sleep_ms(500);
                continue;
            }
        }

        gpio_put(LED_R, 0);
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 0);

        absolute_time_t end = get_absolute_time();
        int reaction_time = absolute_time_diff_us(start, end) / 1000;

        printf("Tempo de reação: %d ms\n", reaction_time);
        playTone(reaction_time);

        // Verifica se o jogador bateu o recorde
        if (reaction_time < best_reaction_time) {
            best_reaction_time = reaction_time;
            printf("Wow!! Novo recorde! Tempo: %d ms\n", best_reaction_time);
            playCelebrationTone();  // Toca o som de celebração
        }

        //printf("Aguardando soltar botão...\n");
        while (gpio_get(correct_button) == 0);
        sleep_ms(500);

        led_state = (led_state + 1) % 7;  // Avança para a próxima cor do arco-íris
        rodada_count++;  // Incrementa o contador de rodadas
    }

    printf("Fim do jogo! Você completou 5 rodadas.\n");

    // Reinicia o jogo após 10 segundos
    sleep_ms(10000);
    printf("Reiniciando o jogo...\n");
    rodada_count = 0;  // Reinicia o contador de rodadas
    best_reaction_time = 10000;  // Reinicia o recorde de tempo
    startGame();  // Reinicia o jogo
}

int main() {
    stdio_init_all();
    initHardware();
    printf("Jogo Iniciado!\n");

    // Toque a melodia de Mario Bros ao iniciar o jogo
    playMarioMelody();

    // Pisca os LEDs 5 vezes antes de começar o jogo
    blinkLEDs();

    startGame();
    return 0;
}