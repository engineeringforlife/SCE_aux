/* Departamento de Engenharia Electrot�cnica
  Tutorial Temporizadores - Exemplo 1
  Sempre que contagem atinge 1000000 ir� mudar o estado do
  LED;
*/
#include "Arduino.h"
// Vari�veis globais
int pin_led = 5;
volatile boolean state = LOW;
// Contador parcial de interrup��es
volatile int interruptCounter;
// Contador global de interrup��es
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  // Inicio prote��o acesso exclusivo � vari�vel
  portENTER_CRITICAL_ISR(&timerMux);
  // Incrementa o valor do contador parcial de interrup��es
  interruptCounter++;
  // Comuta o estado de "state" de LOW para HIGH ou viceversa
  state = !state; // igual a state = ~state;
  // Escreve o valor HIGH ou LOW num pino digital
  digitalWrite(pin_led, state);
  // Fim prote��o acesso exclusivo � vari�vel
  portEXIT_CRITICAL_ISR(&timerMux);
}
void setup() {
  // Inicializar a porta s�rie
  // Baud-rate de 115200
  Serial.begin(115200);
  // aguardar liga��o da porta s�rie
  while ( !Serial );
  // Configura��o do Timer 0
  // - prescaler 80
  // - contagem crescente
  // Configuracao do GPIO5 como sa�da
  pinMode(pin_led, OUTPUT);
  timer = timerBegin(0, 80, true);
  // Atribuicao da ISR "onTimer" quando ocorre a interrupcao
  // do TIMER0, quando a contagem atinge 1000000
  timerAttachInterrupt(timer, &onTimer, true);
  // Defini��o do valor da contagem:
  // interrup��o gerada quando a contagem atinge 1000000
  timerAlarmWrite(timer, 1000000, true);
  // Ativa TIMER0
  timerAlarmEnable(timer);
}
void loop() {
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
