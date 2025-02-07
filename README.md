**********************************************************************************************************************
                                                Led React game v. 1.3 
**********************************************************************************************************************

Objetivo do Jogo:
O objetivo do jogo é testar a rapidez do jogador em apertar o botão correto, quando a cor correspondente do LED aparecer. 
O tempo de reação é medido em milissegundos e a cada rodada, o jogador tenta superar seu próprio recorde.

**********************************************************************************************************************

Componentes Utilizados:
Placa BitDogLab com microcontrolador Raspberry Pi Pico W
LEDs RGB 5050 WS2812B (conectados aos pinos 13, 11 e 12)
Botões (A e B, conectados aos pinos 5 e 6)
Buzzer (conectado ao pino 21)

**********************************************************************************************************************

Funcionamento:
Inicialização do Jogo:

O jogo começa com um som de introdução (notas simples) e uma explicação das regras.
O jogador deve apertar os botões conforme a cor do LED acesa.
Cor do LED e Resposta do Jogador:

O LED acende em uma das cores do arco-íris, e o jogador deve apertar o botão correto:
Vermelho, Laranja, Verde, Azul → Botão B
Amarelo, Anil, Violeta → Botão A
Se o jogador apertar o botão errado, um som de erro é tocado.
Medindo o Tempo de Reação:

O tempo de reação é registrado, e o som é tocado conforme o tempo: um tom de sucesso se o tempo for rápido, ou um som de 
erro se o jogador apertar o botão errado.
O jogo acompanha o tempo mais rápido de cada rodada e o melhor tempo de reação global.
Recordes:

A cada rodada, o jogo verifica se o jogador quebrou seu recorde pessoal.
Quando um novo recorde global é alcançado, um som de celebração é tocado.
Histórico de Melhores Tempos:

Ao fim de 5 rodadas, o jogo exibe o histórico dos 5 melhores tempos de reação, permitindo ao jogador ver seu progresso.
Reinício do Jogo:

Após 5 rodadas, o jogo reinicia automaticamente após 10 segundos, com um efeito de LEDs piscando e o histórico de tempos 
sendo mostrado novamente.

Recursos Adicionais:
Efeitos Visuais: O LED RGB cria um efeito de arco-íris dinâmico para a resposta do jogador.
Sonoridade: O buzzer toca diferentes sequências de som para indicar sucesso, erro ou a superação de um recorde.
Melhoria de Performance: O jogo mantém um histórico dos melhores tempos dos últimos jogos e o jogador pode tentar 
superá-los a cada nova rodada.

**********************************************************************************************************************

https://github.com/user-attachments/assets/67a54276-92e5-4d2a-bcd5-b9c07885801c

Jogo sendo excecutado na placa bitdoglab com microprocessador raspberry pi pico w 

Para executar o código na placa BitDogLab com o microcontrolador Raspberry Pi Pico W, os componentes devem ser conectados 
conforme as definições dos pinos no código. 
os componentes devem ser conectados à placa BitDogLab com base nas definições dos pinos.

1. LEDs RGB (Vermelho, Verde, Azul)
O código usa três pinos para controlar o LED RGB de 3 cores (Vermelho, Verde e Azul). Os pinos usados são:

LED_R (Vermelho): Pino 13
LED_G (Verde): Pino 11
LED_B (Azul): Pino 12
Conexões:

O pino 13 da BitDogLab vai para o pino de controle do LED vermelho.
O pino 11 vai para o pino de controle do LED verde.
O pino 12 vai para o pino de controle do LED azul.
Cada pino de controle de LED deve estar conectado ao terminal apropriado do LED RGB (anodo ou cátodo, dependendo do tipo de LED) 
e os pinos de alimentação (VCC e GND) devem ser conectados corretamente.
2. Botões (A e B)
Os botões são definidos como:

BUTTON_A: Pino 5
BUTTON_B: Pino 6
Conexões:

O pino 5 da BitDogLab deve ser conectado ao Botão A. O outro terminal do botão vai para o GND (terra).
O pino 6 deve ser conectado ao Botão B. O outro terminal do botão também vai para o GND.
Os botões são configurados com resistores de pull-up internos, o que significa que, quando pressionados, o pino conectado ao botão 
será levado a 0V (GND).

3. Buzzer
O buzzer é controlado pelo pino:

BUZZER_PIN: Pino 21
Conexões:

O pino 21 da BitDogLab deve ser conectado ao terminal positivo do buzzer.
O outro terminal do buzzer vai para o GND.
Ligação Resumida:
Componente	Pino da BitDogLab	Descrição da Conexão
LED Vermelho (RGB)	Pino 13	Conectado ao LED vermelho
LED Verde (RGB)	Pino 11	Conectado ao LED verde
LED Azul (RGB)	Pino 12	Conectado ao LED azul
Botão A	Pino 5	Conectado a um botão, o outro terminal no GND
Botão B	Pino 6	Conectado a outro botão, o outro terminal no GND
Buzzer	Pino 21	Conectado ao buzzer, o outro terminal no GND
Considerações Importantes:
Resistor de Pull-up: O código usa resistores de pull-up internos nos botões A e B. Isso significa que quando o botão é 
pressionado, o pino será lido como 0V (GND), e quando solto, será lido como 3.3V (ou VCC).
Controle dos LEDs: Como os LEDs são controlados por pinos digitais, certifique-se de que eles sejam LEDs RGB comuns de 
3 pinos (um para cada cor), e que os terminais de alimentação (VCC e GND) estejam conectados adequadamente.

**********************************************************************************************************************


link do Projeto no simulador wokwi:
https://wokwi.com/projects/422175428422596609
![projeto final embarcatech](https://github.com/user-attachments/assets/02588312-e27e-433a-8bf7-2fe0f6811440)

 * O projeto no simulador wokwi teve o led RGB substituido pelos leds VERMELHO, AZUL E VERDE por critério de funcionalidades
 * do simulador.
