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
  Tutorial de Interrup��es Externas - Exemplo 1
  - Configura��o de INT (associada a um bot�o de press�o)
  atrav�s das fun��es de alto n�vel
  Sempre que o bot�o de press�o for premido ou libertado
  (por cada mudan�a de flanco) ir� mudar o estado do LED;
*/
// Vari�veis globais
int pin_led = 5;
int pin_button = 0; // Pino associado a INT
volatile boolean state = LOW;
// Contador parcial de interrup��es
volatile int interruptCounter;
// Contador global de interrup��es
int totalInterruptCounter;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR blink_EVENT(void);
void setup() {
  // Inicializar a porta s�rie
  // Baud-rate de 115200
  Serial.begin(115200);
  // aguardar liga��o da porta s�rie
  while ( !Serial );
  // Configuracao do GPIO5 como sa�da
  pinMode(pin_led, OUTPUT);
  // Configuracao do GPIO0 como entrada
  // (com pull up)
  pinMode(pin_button, INPUT_PULLUP);
  // Atribuicao da ISR "blink_EVENT" quando ocorre a
  // interrupcao INT, em qualquer mudanca de flanco do
  // "pin_button�
  attachInterrupt(digitalPinToInterrupt(pin_button), blink_EVENT,
                  CHANGE);
  interrupts(); // Global Interrupt Enable
}
void loop()
{
  if (interruptCounter > 0) {
    // Inicio prote��o acesso exclusivo � vari�vel
    portENTER_CRITICAL(&timerMux);
    // Decrementa o valor do contador parcial de interrup��es
    interruptCounter--;
    // Fim prote��o acesso exclusivo � vari�vel
    portEXIT_CRITICAL(&timerMux);
    // Incrementa o valor do contador global de interrup��es
    totalInterruptCounter++;
    Serial.print("N�mero total de interrup��es: ");
    Serial.println(totalInterruptCounter);
  }
}
/* ISR a executar quando ocorre a interrupcao INT1 */
void IRAM_ATTR blink_EVENT(void) {
  // Inicio prote��o acesso exclusivo � vari�vel
  portENTER_CRITICAL_ISR(&timerMux);
  // Incrementa o valor do contador parcial de interrup��es
  interruptCounter++;
  // Comuta o estado de "state" de LOW para HIGH ou vice-versa
  state = !state; // igual a state = ~state;
  // Escreve o valor HIGH ou LOW num pino digital
  digitalWrite(pin_led, state);
  // Fim prote��o acesso exclusivo � vari�vel
  portEXIT_CRITICAL_ISR(&timerMux);
}
