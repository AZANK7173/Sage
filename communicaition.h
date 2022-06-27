#ifndef communcation
#define comunication

#include <HTTPClient.h>
#include <math.h>
#include <stdio.h>

String get_data(String API_URL) {
  // busca dados
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + API_URL + "/exec?read";
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code

    String payload = http.getString();

    http.end();
    return payload;
  }

  else {
    Serial.println("Error on HTTP request");
    http.end();
    return "";
  }

}

String send_data(String API_URL, String message) {
  // envia dados
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + API_URL + "/exec?post=" + message;
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code

    String payload = http.getString();
    http.end();
    return "";
  }

  else {
    Serial.println("Error on HTTP request");
    http.end();
    return "";
  }
}

int split(String str, long arr[]){
  // tratamento da lista recebida por get_data
  char helper[10];
  int val = 0;

  int j = 0;
  int k = 0;
  int u = 0;

  for(int i = 0; str[i] != '\0'; i++){
      if(str[i] == ','){
          if(j != 0){
              val = 0;
              u = 0;
              for(; j > 0; j--){
                  val += (helper[j-1] - 48)*pow(10,u);
                  u++;
              }
              arr[k] = val;
              k++;
          }
      }
      else{
      helper[j] = str[i];
      j++;
      }
  }

  return 0;
}

void getAndProcessData(String API_URL, long out[]){
  String raw = get_data(API_URL);
  split(raw,out);
}

#endif
