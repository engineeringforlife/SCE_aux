#include "Arduino.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include <Wire.h>

//Broker MQTT Libraries
#include <WiFi.h>
#include <PubSubClient.h>


#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
#define TFT_GREY 0x5AEB




#define mainDELAY_LOOP_COUNT    400000 //( 0xffffff )

#define mainSENDER_1    1
#define mainSENDER_2    2
#define mainSENDER_3    3


static void vTFTPresentation( void *pvParameters );
static void vTFTDisplayValues( void *pvParameters );

QueueHandle_t xQueue;
SemaphoreHandle_t xMutex;
TaskHandle_t xTFTPresentationHandle;

typedef struct
{
  float ucValue1;
  float ucValue2;
  float ucValue3;
  float ucSource;
} xData;

/*
static const xData xStructsToSend[ 3 ] =
{
  { 100, 0, 0, mainSENDER_1 },
  { 200, 0, 0, mainSENDER_2 },
  { 203, 0, 0, mainSENDER_3 }
};
*/

/* Defini��es do LED */
#define PIN_LED     25
/* Defines do MQTT */
#define TOPICO_SUBSCRIBE_LED         "topico_liga_desliga_led"
#define TOPICO_PUBLISH_TEMPERATURA   "topico_sensor_temperatura"
#define TOPICO_PUBLISH_DISTANCIA     "topico_sensor_distancia"
#define TOPICO_PUBLISH_UMIDADE       "topico_sensor_umidade"

#define ID_MQTT  "43a21d06b4a0454c903ddeeb425e814f"

const char* SSID = "MEO-351390"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "df82e87bf3"; // Senha da rede WI-FI que deseja se conectar

const char* BROKER_MQTT = "broker.hivemq.com"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

//Vari�veis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient

/* Prototypes */
//float faz_leitura_temperatura(void);
//float faz_leitura_umidade(void);
void initWiFi(void);
void initMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void VerificaConexoesWiFIEMQTT(void);


void initWiFi(void)
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    reconnectWiFi();
}

/* Fun��o: inicializa par�metros de conex�o MQTT(endere�o do
 *         broker, porta e seta fun��o de callback)
 * Par�metros: nenhum
 * Retorno: nenhum
 */
void initMQTT(void)
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui fun��o de callback (fun��o chamada quando qualquer informa��o de um dos t�picos subescritos chega)
}

/* Fun��o: fun��o de callback
 *         esta fun��o � chamada toda vez que uma informa��o de
 *         um dos t�picos subescritos chega)
 * Par�metros: nenhum
 * Retorno: nenhum
 */
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    String msg;
    /* obtem a string do payload recebido */
    for(int i = 0; i < length; i++)
    {
       char c = (char)payload[i];
       msg += c;
    }
    Serial.print("Chegou a seguinte string via MQTT: ");
    Serial.println(msg);

    /* toma a��o dependendo da string recebida */
    if (msg.equals("1"))
    {
        digitalWrite(PIN_LED, HIGH);
        Serial.print("LED aceso mediante comando MQTT");
    }

    if (msg.equals("0"))
    {
        digitalWrite(PIN_LED, LOW);
        Serial.print("LED apagado mediante comando MQTT");
    }
}

/* Fun��o: reconecta-se ao broker MQTT (caso ainda n�o esteja conectado ou em caso de a conex�o cair)
 *         em caso de sucesso na conex�o ou reconex�o, o subscribe dos t�picos � refeito.
 * Par�metros: nenhum
 * Retorno: nenhum
 */
void reconnectMQTT(void)
{
    while (!MQTT.connected())
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT))
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE_LED);
        }
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

/* Fun��o: verifica o estado das conex�es WiFI e ao broker MQTT.
 *         Em caso de desconex�o (qualquer uma das duas), a conex�o
 *         � refeita.
 * Par�metros: nenhum
 * Retorno: nenhum
 */
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected())
        reconnectMQTT(); //se n�o h� conex�o com o Broker, a conex�o � refeita

     reconnectWiFi(); //se n�o h� conex�o com o WiFI, a conex�o � refeita
}

/* Fun��o: reconecta-se ao WiFi
 * Par�metros: nenhum
 * Retorno: nenhum
 */
void reconnectWiFi(void)
{
    //se j� est� conectado a rede WI-FI, nada � feito.
    //Caso contr�rio, s�o efetuadas tentativas de conex�o
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void plotLinear(char *label, int x, int y)
{
  int w = 36;
  tft.drawRect(x, y, w, 155, TFT_GREY);
  tft.fillRect(x + 2, y + 19, w - 3, 155 - 38, TFT_WHITE);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawCentreString(label, x + w / 2, y + 2, 2);
  for (int i = 0; i < 110; i += 10)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 6, TFT_BLACK);
  }
  for (int i = 0; i < 110; i += 50)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 9, TFT_BLACK);
  }
  tft.fillTriangle(x + 3, y + 127, x + 3 + 16, y + 127, x + 3, y + 127 - 5, TFT_RED);
  tft.fillTriangle(x + 3, y + 127, x + 3 + 16, y + 127, x + 3, y + 127 + 5, TFT_RED);
  tft.drawCentreString("---", x + w / 2, y + 155 - 18, 2);
}


void setup( void )
{
	//Inicializa��o da porta s�rie(debug
  Serial.begin(115200);
  while(!Serial);
  Serial.print( "Vamos ver se come�a aqui\n" );
  //Inicia o display TFT
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  /* Inicializa a conexao wi-fi */
  initWiFi();
  /* Inicializa a conexao ao broker MQTT */
  initMQTT();

  xQueue = xQueueCreate( 5, sizeof( xData ) );
  xMutex = xSemaphoreCreateMutex();
  if ( xQueue != NULL )
  {
	  if( xMutex != NULL ){
		  Serial.print( "Success\n" );
	      xTaskCreatePinnedToCore( vTFTPresentation, "vTFTPresentation", 1024, NULL, 2, &xTFTPresentationHandle, 1);

	  }else{
		  Serial.print( "The mutex not be created.\r\n" );
	  }
  }
  else
  {
	  Serial.print( "The queue not be created.\r\n" );
  }
}

void loop()
{
  vTaskDelete( NULL );
}



static void vTFTPresentation( void *pvParameters )
{
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;

  	  //Strings de apresenta��o do projecto
	  tft.drawString("Este projecto tem o ", 0, 0, 4);
	  tft.drawString("nome de \"data- ", 0, 25, 4);
	  tft.drawString("-logguer CAN\" e foi", 0, 50, 4);
	  tft.drawString("desenvolvido para a", 0, 75, 4);
	  tft.drawString("cadeira de SCE por:", 0, 100, 4);
	  tft.drawString("David Drumond", 15, 175, 4);
	  tft.drawString("Edgar Paulo", 15, 200, 4);

	  delay(10000);
	  //Limpa o ecr�
	  tft.fillScreen(TFT_BLACK);

	  Serial.print("\n********************************************************\n" );
	  Serial.print("\nvTFTPresentation is running and about to delete itself\r\n" );
	  //Create other tasks here
      xTaskCreatePinnedToCore( vTFTDisplayValues, "vTFTDisplayValues", 1024, NULL, 1, NULL, 1);
	  vTaskDelete(xTFTPresentationHandle);

}



static void vTFTDisplayValues( void *pvParameters )
{
  xData xSenderStructure;
  portBASE_TYPE xStatus;
  const TickType_t xTicksToWait = 50 / portTICK_PERIOD_MS;
  float humidity =0.0;
  float temp= 0.0;
  float ctemp = 0.0;
  uint8_t dataT[2] = {0};
  uint8_t dataH[2] = {0};
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  //Verificar se isto se repete ou se apenas dentro do for
  byte d = 40;
  plotLinear("TEMP", 0, 160);
  plotLinear("HUM", 1 * d, 160);
  plotLinear("LUM", 2 * d, 160);
  plotLinear("X", 3 * d, 160);
  plotLinear("Y", 4 * d, 160);
  plotLinear("Z", 5 * d, 160);
  Serial.print("\nvTFTDisplayValues\n" );

  for ( ;; )
  {




  }
}




