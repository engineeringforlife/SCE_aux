/*
 *  Projeto: controle e monitoramento de perif�ricos no ESP32
 *           via MQTT com app MQTT DASH
 *  Autores: Pedro Bertoleti e FilipeFlop
 *  Data: Fevereiro/2019
 */

#include <WiFi.h>
#include <PubSubClient.h>


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

/* Fun��o de setup */
void setup()
{
    Serial.begin(115200);

    /* Configura��o do pino ligado ao LED como output
       e inicializa��o do mesmo em LOW */
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED,LOW);


    /* Inicializa a conexao wi-fi */
    initWiFi();

    /* Inicializa a conexao ao broker MQTT */
    initMQTT();
}

/* Loop principal */
void loop()
{
    char temperatura_str[10] = {0};
    char umidade_str[10]     = {0};

    /* garante funcionamento das conex�es WiFi e ao broker MQTT */
    VerificaConexoesWiFIEMQTT();

    /* Compoe as strings a serem enviadas pro dashboard (campos texto) */
   // sprintf(temperatura_str,"%.2fC", 5);
  //  sprintf(umidade_str,"%.2f", 6);

    /*  Envia as strings ao dashboard MQTT */
    MQTT.publish(TOPICO_PUBLISH_TEMPERATURA, "50");
    MQTT.publish(TOPICO_PUBLISH_UMIDADE, umidade_str);

    /* keep-alive da comunica��o com broker MQTT */
    MQTT.loop();

    /* Refaz o ciclo ap�s 2 segundos */
    delay(2000);
}
