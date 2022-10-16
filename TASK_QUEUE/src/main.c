//==================================================================================
// Estude de sistemas operacionais em tempo real - FreeRTOS
// Aula 25 - Introdução ao FreeRTOS - Semáforo, Filas, EventGroup -Notificações
// Canal do Youtube: Renato Sampaio
// Data: 16/10/2022
// Explicação: Exemplo de Filas
//==================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

//Variáveis globais
float temperatura_media;

//Fila para utilização das task's
xQueueHandle fila_de_temperaturas;

void leitura_de_sensores(void *params);
void calcula_media_movel(void *params);

void app_main()
{
    //Criação da fila com tamanho e sizeoff do tipo
    fila_de_temperaturas = xQueueCreate(5, sizeof(float));

    //Criação das task's
    xTaskCreate(&leitura_de_sensores, "Le Temperatura", 2048, NULL, 1, NULL);
    xTaskCreate(&calcula_media_movel, "Calcula temperatura media", 2048, NULL, 2, NULL);
}

void leitura_de_sensores(void *params)
{
    float temperatura;
    while (true)
    {
        //Leitura da temperatura do sensor
        temperatura = 20.0 + ((float) rand() / (float)(RAND_MAX/10));

        long resposta = xQueueSend(fila_de_temperaturas, &temperatura, (1000 / portTICK_PERIOD_MS));  //Envia dado para a fila e espera até 1s.

         if(resposta)
         {
            ESP_LOGI("Leitura", "Temperatura adicionada a fila");
         }
         else
         {
            ESP_LOGE("Leitura", "Falha do envio da temperatura");
         }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void calcula_media_movel(void *params)
{
    float temperatura = 0.0;
    float temperatura_anterior = 0.0;
    while (true)
    {
        if(xQueueReceive(fila_de_temperaturas, &temperatura, (5000 / portTICK_PERIOD_MS))) //Tira o dado da fila
        {
            temperatura_media = (temperatura_anterior + temperatura)/2.0;
            temperatura_anterior = temperatura;
            printf("Temperatura média %f\n", temperatura_media);
        }
        else
        {
            ESP_LOGE("Calculo", "Dados não disponíveis");
        }
    }
}