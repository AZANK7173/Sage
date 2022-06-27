#ifndef atuators
#define atuators

#include "global.h"
#include <ESP32Servo.h>

void updateQuants(long mod, int *quant1, int *quant2){
  // função para atualizar as variaveis que armazenam as quantidades
  // dos remédios 1 e 2

  
  // dispense 1 remédio do tipo 1
  if(mod == 1){
    *quant1 += 1;
  }
  // dispense 1 remédio do tipo 2
  else if(mod == 2){
    *quant2 += 1;
  }
  // dispense 1 remédio de cada
  else if(mod == 3){
    *quant1 += 1;
    *quant2 += 2;
  }
}

void init_servos(Servo myservo, Servo myservo2){
  // função para inicialização dos servos motores
  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo2.setPeriodHertz(50);    // standard 50 hz servo // ????
}

void oneStep(Servo servo,int n, int servo_pin){
  // função que dispensa o comprimido de posição "n" do servo "servo" conectado no
  // pino "servo-pin"
  
  servo.attach(servo_pin, 500, 2400);
  int pos;
  int final_pos = n*35;
  int current_pos = 0;

  for (pos = 0; pos <= final_pos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  delay(50);
  for (pos = final_pos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  servo.detach();
}


void dispense(Servo myservo, Servo myservo2, long n1, int *pos1, int *pos2){
  
  // função para interpretação dos modos de operação
  
  if (n1 == 1){
    digitalWrite(BUZZER_PIN,LOW);    
    oneStep(myservo, *pos1, SERVO_PIN1);
    *pos1 += 1;
    
  }
  else if (n1 == 2){
    digitalWrite(BUZZER_PIN,LOW);
    oneStep(myservo2, *pos2, SERVO_PIN2);
    *pos2 += 1;

  }
  else if (n1 == 3){
    digitalWrite(BUZZER_PIN,LOW);
    oneStep(myservo, *pos1, SERVO_PIN1);
    oneStep(myservo2, *pos2, SERVO_PIN2);
    *pos1 += 1;
    *pos2 += 1;
      
  }
}


int check_btn(int btn_press) {
  // checa botão
  if(btn_press > 0){
    return 1;
  }
  else{
    return 0;
  }
}

#endif
