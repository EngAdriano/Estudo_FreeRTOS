//==================================================================================
// Estude de sistemas operacionais em tempo real - FreeRTOS
// Aula 25 - Introdução ao FreeRTOS - Semáforo, Filas, EventGroup -Notificações
// Canal do Youtube: Renato Sampaio
// Data: 16/10/2022
// Explicação: Exemplo de Notificações
//==================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receptorHandle = NULL;

void emissor(void *params);
void receptor(void * params);

void app_main()
{
    xTaskCreate(&receptor, "Receptor", 2048, NULL, 2, &receptorHandle);
    xTaskCreate(&emissor, "Emissor_1", 2048, NULL, 2, NULL);
    xTaskCreate(&emissor, "Emissor_2", 2048, NULL, 2, NULL);
}

void emissor(void *params)
{
    while(true)
    {
        xTaskNotifyGive(receptorHandle);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void receptor(void * params)
{
    while(true)
    {
        //Aguarda
        int quantidade = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Notificações recebidas %d\n", quantidade);
    }
}