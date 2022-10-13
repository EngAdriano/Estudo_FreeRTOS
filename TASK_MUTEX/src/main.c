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
#include "freertos/semphr.h"
#include "esp_log.h"         

float temperatura;
xSemaphoreHandle mutexI2C;

float acessa_i2c(int comando)
{
    if(comando == 1)
    {
        ESP_LOGI("I2C", "Leitura do sensor de Temperatura");
        return 20.0 + ((float) rand() / (float)(RAND_MAX/10));
    }
    else
    {
        ESP_LOGI("I2C", "Escrita do LCD");
        printf("Tela LCD - Temperatura = %f", temperatura);
    }

    return 0;
}

void le_sensor(void * params)
{
    while(true)
    {
        if(xSemaphoreTake(mutexI2C, 1000 / portTICK_PERIOD_MS))
        {
            temperatura = acessa_i2c(1);
            ESP_LOGI("Leitura", "Temperatura %f", temperatura);   //LOG de Informação
            xSemaphoreGive(mutexI2C);
        }
        else
        {
            ESP_LOGE("Leitura", "Não foi possível ler o sensor");  //LOG de ERRO
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void lcd_display(void * params)
{
    while ((true))
    {
        if(xSemaphoreTake(mutexI2C, 1000 / portTICK_PERIOD_MS))
        {
            ESP_LOGI("Display", "Escreve no LCD");
            acessa_i2c(2);
            xSemaphoreGive(mutexI2C);
        }
        else
        {
            ESP_LOGE("Display", "Não foi possível escrever no display");  //LOG de ERRO
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    
}

void app_main() 
{
    mutexI2C = xSemaphoreCreateMutex();

    xTaskCreate(&le_sensor, "Leitura Sensor 1", 2048, NULL, 2, NULL); 
    xTaskCreate(&lcd_display, "Atualização do display", 2048, NULL, 2, NULL);
}