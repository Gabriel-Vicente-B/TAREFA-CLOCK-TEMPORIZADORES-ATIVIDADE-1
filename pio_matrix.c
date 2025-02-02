#include "pico/stdlib.h"   // Biblioteca padrão para entrada e saída no Raspberry Pi Pico
#include "pico/time.h"     // Biblioteca para manipulação de tempo e temporizadores

#define vermelho 11  // Define o pino GPIO para o LED vermelho
#define amarelo 12   // Define o pino GPIO para o LED amarelo
#define verde 13     // Define o pino GPIO para o LED verde

// Enumeração para representar os estados do semáforo
enum traffic_light_state {VERMELHO, AMARELO, VERDE} estado_atual = VERDE;  
// Define a variável global 'estado_atual', que começa no estado VERDE

// Função de callback que é chamada a cada intervalo do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(vermelho, 0);
    gpio_put(amarelo, 0);
    gpio_put(verde, 0);

    // Alterna entre os estados do semáforo
    switch (estado_atual) {
        case VERMELHO:
            estado_atual = AMARELO; // Passa do vermelho para amarelo
            gpio_put(amarelo, 1);  // Acende o LED amarelo
            break;
        case AMARELO:
            estado_atual = VERDE;  // Passa do amarelo para verde
            gpio_put(verde, 1);    // Acende o LED verde
            break;
        case VERDE:
            estado_atual = VERMELHO; // Passa do verde para vermelho
            gpio_put(vermelho, 1);   // Acende o LED vermelho
            break;
    }
    return true; // Retorna verdadeiro para manter o temporizador ativo
}

int main() {
    // Inicializa os pinos GPIO e os define como saída
    gpio_init(vermelho);
    gpio_init(amarelo);
    gpio_init(verde);
    gpio_set_dir(vermelho, GPIO_OUT);
    gpio_set_dir(amarelo, GPIO_OUT);
    gpio_set_dir(verde, GPIO_OUT);

    // Configura um temporizador repetitivo que chama a função de callback a cada 3000ms (3 segundos)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal que imprime o estado do semáforo a cada segundo
    while (true) {
        sleep_ms(1000);  // Espera 1 segundo
        printf("Semaforo: %d\n", estado_atual);  // Exibe o estado atual do semáforo no terminal
    }

    return 0; // Código nunca chega aqui, pois o loop while é infinito
}
