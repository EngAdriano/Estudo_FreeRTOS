//==================================================================================
// Estude de sistemas operacionais em tempo real - FreeRTOS
// Aula 25 - Introdução ao FreeRTOS - Semáforo, Filas, EventGroup e Notificações
// Canal do Youtube: Renato Sampaio
// Data: 16/10/2022
// Explicação: Task de Event Group  (Uma task espera que eventos aconteçam)
// Grupos de eventos : Aguardar certos acontecimentos
//==================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

//Variáveis globais
bool onOff = true;

//Variáveis de Handles para o Sistema Operacional FreeRTOS
EventGroupHandle_t eventGroupConectividade;
const int conexaoWifi = BIT0;           //Flags de controle para os eventos
const int conexaoMQTT = BIT1;           //esperados

xSemaphoreHandle ligarMQTT;

//Prtótipo das funções
void conectaWiFi(void *params);
void conectaMQTT(void *params);
void processa_dados(void *params);


//Função principal (Main)
void app_main()
{
    eventGroupConectividade = xEventGroupCreate();              //Crea o event group
    ligarMQTT = xSemaphoreCreateBinary();                       //Crea o semáforo

    xTaskCreate(&conectaWiFi, "Conecta ao WiFi", 2048, NULL, 1, NULL);              //Crea as tarefas WiFi
    xTaskCreate(&conectaMQTT, "Conecta ao Servidos MQTT", 2048, NULL, 1, NULL);     //MQTT
    xTaskCreate(&processa_dados, "Processa dados", 2048, NULL, 1, NULL);            //Processa dados
}

//Funções do programa

void conectaWiFi(void *params)
{
    while (true)
    {
        ESP_LOGI("WiFi", "Conectado ao WiFi");
        xEventGroupSetBits(eventGroupConectividade, conexaoWifi);   //Seta o bit do evento conexão WiFi
        xSemaphoreGive(ligarMQTT);                                  //Libera o semáforo
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    
}

void conectaMQTT(void *params)
{
    while (true)
    {
        xSemaphoreTake(ligarMQTT, portMAX_DELAY);
        ESP_LOGI("MQTT", "Conectando ao MQTT");

        if(onOff == true)
        {
            xEventGroupSetBits(eventGroupConectividade, conexaoMQTT);   //Seta o bit do evento conexão MQTT
            onOff = false;
            printf("\nConectado\n");
        }
        else
        {
            xEventGroupClearBits(eventGroupConectividade, conexaoMQTT); //Desliga bits
            onOff = true;
            printf("\nDesconectado\n\n");
        }

        
    }
    
}

void processa_dados(void *params)
{
    while (true)
    {
        //Aguarda WiFi e MQTT
        //Verifica se os bits do event group aconteceram: (Handle, bit0 | bit1, Zera flags(bits)?, Espera por todos os bits?, tempo de espera )
        xEventGroupWaitBits(eventGroupConectividade, conexaoWifi | conexaoMQTT, true, true, portMAX_DELAY);
        printf("Processando Dados\n\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI("TASK", "Desconecta da internet\n");
    }
    
}