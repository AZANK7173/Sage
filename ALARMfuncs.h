#ifndef ALARMfuncs
#define ALARMfuncs

#include "global.h"
#include "time.h"

unsigned long get_unix_time() {
  // pega o tempo atual no fuso-horário local (em padrão UNIX)
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return (0);
  }
  time(&now);
  return now;
}

int check_alarm(long arr[], long memory[], int *block) {
  // itera pelos alarmes
  long n1;
  long n2;
  long play = 0;
  long alarme;
  long dist;
  
  time_t t = get_unix_time();

  // checa se agora está próximo o suficiente de algum alarme?
  if (*block) {
    return 0;
  }

  for (int i = 0; i < MEMORY_SIZE; i++) {
    alarme = memory[2*i];
    dist = t - alarme;
    dist = (dist < 0) ? 99 : dist;
    if (dist < MARGIN) {
      play = memory[2*i]; // o tempo atual está próximo o suficiente de algum alarme
      n1 = memory[2*i + 1];
  
      arr[0] = play;
      arr[1] = n1;
      // o alarme ainda não foi tocado
      *block = 1;
      return 1;
    }
  }

  return 0;
}

#endif
