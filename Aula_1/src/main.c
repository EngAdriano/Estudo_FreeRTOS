//======================================================================
//Estudo Aula24 - Introdução ao FreeRTOS (Tasks e Mutex) - Parte1
//Canal Youtube: Renato Sampaio
//Data: 12/10/2022
//
//Estudante: Eng. José Adriano
//======================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"                    //Para utilizar o LOG para o ESP

void task1(void *params)
{
    while(true)
    {
        //printf("Leitura de sensores\n");
        ESP_LOGI("TASK1", "Leitura de sensores");  //LOG de informação
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void *params)
{
    while(true)
    {
        //printf("Escrever no display\n");
        ESP_LOGI("TASK2", "Escrever no display");  //LOG de informação
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main() 
{
    //xTaskCreate(&task1, "leitura", 2048, "Task 1", 1, NULL); //Não faço a seleção do nucleo
    //xTaskCreate(&task2, "Display", 2048, "Task 2", 1, NULL); //Não faço a seleção do núcleo

    //Create para selecionar o núcleo em que a task vai rodar
    xTaskCreatePinnedToCore(&task1, "leitura", 2048, "Task 1", 1, NULL, 0); //Núcleo 0
    xTaskCreatePinnedToCore(&task2, "Display", 2048, "Task 2", 1, NULL, 1); //Núcleo 1

}