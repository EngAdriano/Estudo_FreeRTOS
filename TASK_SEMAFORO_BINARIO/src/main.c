//==================================================================================
// Estude de sistemas operacionais em tempo real - FreeRTOS
// Aula 25 - Introdução ao FreeRTOS - Semáforo, Filas, EventGroup -Notificações
// Canal do Youtube: Renato Sampaio
// Data: 16/10/2022
// Explicação: Fazer por meio de semáforo que uma task espere o resultado de outra.
//==================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

xSemaphoreHandle semaforoBinario;

void conexao_servidor(void *params);
void processa_dados(void *params);

void app_main()
{
    semaforoBinario = xSemaphoreCreateBinary();
    xTaskCreate(&conexao_servidor, "Conexao com o servidor", 2048, NULL, 1, NULL);
    xTaskCreate(&processa_dados, "Processa dados", 2048, NULL, 1, NULL);
}

void conexao_servidor(void *params)
{
    while (true)
    {
        ESP_LOGI("Servidor", "Conectado ao servidor");
        xSemaphoreGive(semaforoBinario);                //(give) liberar o semáforo
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void processa_dados(void *params)
{
    while (true)
    {
        //Aguarda conexão
        xSemaphoreTake(semaforoBinario, portMAX_DELAY); //Aguarda o máximo de tempo que puder (infinito) (Take = Pega)
        printf("Página carregada\n");
    }
    
}