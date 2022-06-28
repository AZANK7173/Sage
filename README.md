# Sage -  Disposer de remédios IoT


Esse repositório é dedicado a reservar os códigos desenvolvidos no projeto de um disposer de remédios para idosos que pode ser controlado pela internet. O projeto utiliza um ESP32-NodeMCU32 com módulo Wi-Fi e dois servos motores para acionar a deposição do remédio na vasilha. 

O desenvolvimento foi realizado em C e C++ e teve como interface de desenvolvimento o Aruino IDLE.

Além disso, pode-se encontrar o código ´code.gs´ que contém o script utilizado como App Script para realizar a lógica de PUT e GET da planilha, esse script é inserido na secção de implementações na planilha do Google Sheets. Ademais, neste repositório também se encontra o princípio do código do site que servirá como interface para a comunicação dos usuários com o sistema embarcado (disponível no arquivo ´index.html´). Contudo, o desenvolvimento do site ainda não foi concluído, fazendo com que os testes e aplicações sejam limitados a interação Google Sheets - ESP.
