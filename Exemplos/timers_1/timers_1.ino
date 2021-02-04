/* Departamento de Engenharia Electrotécnica
  Tutorial Temporizadores - Exemplo 1
  Sempre que contagem atinge 1000000 irá mudar o estado do
  LED;
*/
#include "Arduino.h"
// Variáveis globais
int pin_led = 5;
volatile boolean state = LOW;
// Contador parcial de interrupções
volatile int interruptCounter;
// Contador global de interrupções
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  // Inicio proteção acesso exclusivo à variável
  portENTER_CRITICAL_ISR(&timerMux);
  // Incrementa o valor do contador parcial de interrupções
  interruptCounter++;
  // Comuta o estado de "state" de LOW para HIGH ou viceversa
  state = !state; // igual a state = ~state;
  // Escreve o valor HIGH ou LOW num pino digital
  digitalWrite(pin_led, state);
  // Fim proteção acesso exclusivo à variável
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup() {
  // Inicializar a porta série
  // Baud-rate de 115200
  Serial.begin(115200);
  // aguardar ligação da porta série
  while ( !Serial );
  // Configuração do Timer 0
  // - prescaler 80
  // - contagem crescente
  // Configuracao do GPIO5 como saída
  pinMode(pin_led, OUTPUT);
  timer = timerBegin(0, 80, true);
  // Atribuicao da ISR "onTimer" quando ocorre a interrupcao
  // do TIMER0, quando a contagem atinge 1000000
  timerAttachInterrupt(timer, &onTimer, true);
  // Definição do valor da contagem:
  // interrupção gerada quando a contagem atinge 1000000
  timerAlarmWrite(timer, 1000000, true);
  // Ativa TIMER0
  timerAlarmEnable(timer);
}
void loop() {
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
