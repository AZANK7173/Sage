#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <stdio.h>
#include <ESP32Servo.h>
#include "atuators.h"
#include "communicaition.h"
#include "global.h"
#include "ALARMfuncs.h"

Servo myservo;
Servo myservo2;
/************/

// Variaveis globais do servidor/memória
const char* ssid = "MIKA 2.4";
const char* password = "pacocarainha";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;
String API_URL = "AKfycbwsI2bBGI3cyWjOWMxUXBBWlPfVMQXkyZfkz7fiVmHGUyTknrj8nAKJZ9a-EoJ-Y3cJUg";
long memory[MEMORY_SIZE*2];

// Variaveis globais da máquina de estados
enum estado {IDLE, BUZZ};
enum evento {NENHUM_EVENTO = -1, timeout1, timeout2, alarm_disp, bttn};
enum acao {NENHUMA_ACAO = -1, A01, A02, A03, A04, A02_A03};

typedef struct trans {
  enum estado prox;
  enum acao acao_tomada;
} trans;

trans matriz[2][4] = {
  {{IDLE, A04}, {IDLE, NENHUMA_ACAO}, {BUZZ, A01}, {IDLE, A03}},
  {{BUZZ, NENHUMA_ACAO}, {IDLE, A03}, {BUZZ, NENHUMA_ACAO}, {IDLE, A02_A03}},
};

int codigoEvento;
int codigoAcao;
int estado;
int estado_atual = IDLE;

// variaveis globais, atualizadas conforme o alarme
long arr[2] = {0, 0};
long n1;
int quant1 = 0;
int quant2 = 0;
long last_alarm = 0;
int block = 0;
int btn_press = 0;

// variaveis globais para time_out
long t1_start;
long t2_start;
int  t2_on = 0;

// variaveis globais para servo
int pos1 = 1;
int pos2 = 1;


int obterEvento() {
  if (get_unix_time() - t1_start > TIMEOUT1) {
    Serial.write("TIMEOUT1\n");
    // atualiza ultima vez que evento foi executado
    t1_start = get_unix_time();

    // retorna código do evento
    return timeout1;
  }

  if ((get_unix_time() - t2_start > TIMEOUT2) && t2_on) {
    Serial.write("TIMEOUT2\n");
    t2_on = 0;
    return timeout2;
  }

  // se o alarme tocou, os valores de n1 e n2 são atualizados
  int flag_alarm = check_alarm(arr, memory, &block);
  if (flag_alarm) {
    Serial.write("Deu o alarme\n");

    // last alarm
    last_alarm = arr[0];
    n1 = arr[1];
    return alarm_disp;
  }

  if (check_btn(btn_press)) {
    btn_press = 0;
    digitalWrite(BUZZER_PIN,LOW);
    Serial.write("Apertou o butão\n");
    return bttn;
  }

  return NENHUM_EVENTO;
}

void executarAcao(int codigoAcao) {

  /*
    0 > Buzina ON
    1 > Atuadores ON
    2 > Envia para servidor
    3 > Puxa  do servidor
    4 > 1 & 2
  */

  switch (codigoAcao)
  {
    case 0:
      btn_press = 0;
      digitalWrite(BUZZER_PIN, HIGH);
      t2_start = get_unix_time(); // reinicia timer 2
      t2_on = 1;
      break;
    case 1:
      send_data(API_URL, "timeout"); 
      break;
    case 2:
      Serial.write("case 2");
      break;
    case 3:
      getAndProcessData(API_URL, memory);
      t1_start = get_unix_time(); // reinicia timer 1
      break;
    case 4:
      t2_on = 0;
      dispense(myservo, myservo2, n1, &pos1, &pos2);
      updateQuants(n1,&quant1,&quant2);
      send_data(API_URL,String(TOTAL_MEDS - quant1) + "-" + String(TOTAL_MEDS - quant2));
      break;
      
    default:
      break;
  }
}

int obterAcao(int estado, int codigoEvento) {
  return matriz[estado][codigoEvento].acao_tomada;
}

int obterProximoEstado(int estado, int codigoEvento) {
  return matriz[estado][codigoEvento].prox;
}

void vTask1( void *pvParameters );

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  init_servos(myservo, myservo2);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  t1_start = get_unix_time();
  t2_start = get_unix_time();
  getAndProcessData(API_URL, memory);
  xTaskCreate( vTask1, "Task 1", 10000, NULL, 1, NULL);
  
}

void vTask1( void *pvParameters )
{
  const TickType_t xDelay10ms = pdMS_TO_TICKS(10);
  for( ;; )
  {
    vTaskDelay(xDelay10ms);
    if(digitalRead(BUTTON_PIN) == LOW){
    btn_press += 1;
    }
  
    // reativa alarmes
    if(block){
      if (get_unix_time() - last_alarm > MARGIN){
        block = 0;
      }
    }
  
    codigoEvento = obterEvento();
    if (codigoEvento != NENHUM_EVENTO)
    {
      codigoAcao = obterAcao(estado_atual, codigoEvento);
      estado_atual = obterProximoEstado(estado_atual, codigoEvento);
      executarAcao(codigoAcao);
    }
  }
}

void loop() {
  // Tudo será feito nas tasks
}
