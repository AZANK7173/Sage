# Sage - an IoT pill disposer

This repository is dedicated to reserving the codes developed in the project of a drug disposer for the elderly that can be controlled over the internet. The project uses an ESP32-NodeMCU32 with Wi-Fi module and two servo motors to trigger the deposition of the medicine in the vessel.

The code was developted in C and C++ and the interface utilized was the Aruino IDLE.

The prototype of the project developed presents the fully functional physical tool and the communication with the internet takes place through the google sheets API, in which certain inputs by the user (such as the time the medicine should be taken) make the IoT box beeps a signal and release the medicines at the correct time. The code that configures the google sheets API to send data to the embedded system can be found in the `code.gs` file.

The repository files are:

* `Embarcados_Manual_do_Usuario.pdf`: User manual with system explanations and use cases
* `atuators.h`: Servo motors configuration and logic code
* `code.gs`: App Script configuration to communicate with the online table
* `communicaition.h`: File that configures and defines the functions for ESP32 communication with the internet
* `global.h`: Definition of global variables and pins
* `sketch.ino`: RTOS application code for the ESP32
* `index.html`: Principle of an application that captures data coming from the embedded system and displays it (not completed)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Sage -  Disposer de remédios IoT 


Esse repositório é dedicado a reservar os códigos desenvolvidos no projeto de um disposer de remédios para idosos que pode ser controlado pela internet. O projeto utiliza um ESP32-NodeMCU32 com módulo Wi-Fi e dois servos motores para acionar a deposição do remédio na vasilha. 

O código foi montado em C e C++ e teve como interface de desenvolvimento o Aruino IDLE.

O protótipo do projeto desenvolvido apresenta a ferramenta física completamente funcional e a comunicação com a internet se da por meio da API do google sheets, em que determinadas entradas por parte do usuário (como o horário que o remédio deve ser tomado) fazem com que a caixa IoT apite um sinal e libere os remédios no horário correto. O código que configura a API do google sheets para enviar dados para o sistema embarcado pode ser encontrado no arquivo `code.gs`.

Os arquivos do repositório compõe: 

* `Embarcados_Manual_do_Usuario.pdf`: Manual do usuário com os exemplos e explicações do sistema
* `atuators.h`: Aplicação da lógica de funcionameto dos motores do sistema 
* `code.gs`: Configuração do App Script para comunicação com a tabela online
* `communicaition.h`: Arquivo que configura e define as funções para a comunicação do ESP32 com a internet
* `global.h`: Definição de variáveis globais e pinos
* `sketch.ino`: Aplicação de RTOS do sistema
* `index.html`: Princípio de uma aplicação que captura os dados vindos do sistema embarcado (não concluído)
