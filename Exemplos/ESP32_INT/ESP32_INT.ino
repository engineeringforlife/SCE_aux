#include "Arduino.h"
#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_task_wdt.h"
//The setup function is called once at startup of the sketch
/*
  Departamento de Engenharia Electrotecnica - ESTG
  Tutorial de Interrupções Externas - Exemplo 1
  - Configuração de INT (associada a um botão de pressão)
  através das funções de alto nível
  Sempre que o botão de pressão for premido ou libertado
  (por cada mudança de flanco) irá mudar o estado do LED;
*/
// Variáveis globais
int pin_led = 5;
int pin_button = 0; // Pino associado a INT
volatile boolean state = LOW;
// Contador parcial de interrupções
volatile int interruptCounter;
// Contador global de interrupções
int totalInterruptCounter;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR blink_EVENT(void);
void setup() {
  // Inicializar a porta série
  // Baud-rate de 115200
  Serial.begin(115200);
  // aguardar ligação da porta série
  while ( !Serial );
  // Configuracao do GPIO5 como saída
  pinMode(pin_led, OUTPUT);
  // Configuracao do GPIO0 como entrada
  // (com pull up)
  pinMode(pin_button, INPUT_PULLUP);
  // Atribuicao da ISR "blink_EVENT" quando ocorre a
  // interrupcao INT, em qualquer mudanca de flanco do
  // "pin_button“
  attachInterrupt(digitalPinToInterrupt(pin_button), blink_EVENT,
                  CHANGE);
  interrupts(); // Global Interrupt Enable
}
void loop()
{
  if (interruptCounter > 0) {
    // Inicio proteção acesso exclusivo à variável
    portENTER_CRITICAL(&timerMux);
    // Decrementa o valor do contador parcial de interrupções
    interruptCounter--;
    // Fim proteção acesso exclusivo à variável
    portEXIT_CRITICAL(&timerMux);
    // Incrementa o valor do contador global de interrupções
    totalInterruptCounter++;
    Serial.print("Número total de interrupções: ");
    Serial.println(totalInterruptCounter);
  }
}
/* ISR a executar quando ocorre a interrupcao INT1 */
void IRAM_ATTR blink_EVENT(void) {
  // Inicio proteção acesso exclusivo à variável
  portENTER_CRITICAL_ISR(&timerMux);
  // Incrementa o valor do contador parcial de interrupções
  interruptCounter++;
  // Comuta o estado de "state" de LOW para HIGH ou vice-versa
  state = !state; // igual a state = ~state;
  // Escreve o valor HIGH ou LOW num pino digital
  digitalWrite(pin_led, state);
  // Fim proteção acesso exclusivo à variável
  portEXIT_CRITICAL_ISR(&timerMux);
}
