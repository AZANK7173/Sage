#ifndef global
#define global

// PIN CONFIG
#define SERVO_PIN1 18
#define SERVO_PIN2 19
#define BUZZER_PIN 21
#define BUTTON_PIN 16

// TIMER CONFIG
#define TIMEOUT1 (30)
#define TIMEOUT2 (1*60)

// SERVO CONFIG
#define SERVO_DELAY 20
#define SERVO_DEG 15

// 
#define MEMORY_SIZE 10 // tamanho da memória FLASH
#define TOTAL_MEDS 4

// ALARM CONFIG
#define MARGIN 15 // margem de tolerância para o alarme (se now - t < margin, o alarme deve tocar)

#endif
