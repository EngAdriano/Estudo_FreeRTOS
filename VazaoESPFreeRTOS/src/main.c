//Sensor de vazão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

//#define LED 2;

// definir porta de leitura do sensor de Vazao
const int portaVazao = GPIO_NUM_35;
const int LED = GPIO_NUM_2;

// declarar protótipo da tarefa que irá realizar leitura do sensor de vazao
static void leituraVazao(void *params);
void iniciaVazao(gpio_num_t Port);
void piscaLed(void *params);

//Declaração de variáveis globais
volatile uint pulsos_vazao = 0;
float vazao = 0;
// interrupção
void IRAM_ATTR gpio_isr_handler_up(void* arg)
{
  pulsos_vazao++;
  portYIELD_FROM_ISR();
}

void app_main()
{
  iniciaVazao((gpio_num_t) portaVazao);

  xTaskCreate(&leituraVazao, "leituraVazao", 2048, NULL, 1, NULL);
  xTaskCreate(&piscaLed, "PiscaLed", 2048, NULL, 1, NULL);
}

/*
Inicializa sensor de vazão com interrupção na subida de um pulso
 */
void iniciaVazao(gpio_num_t Port)
{
  gpio_set_direction(Port, GPIO_MODE_INPUT);
  gpio_set_intr_type(Port, GPIO_INTR_NEGEDGE);
  gpio_set_pull_mode(Port, GPIO_PULLUP_ONLY);
  gpio_intr_enable(Port);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(Port, gpio_isr_handler_up, (void*) Port);
}

static void leituraVazao(void *params)
{
  while (1) {
    vazao = pulsos_vazao/5.5;
	  printf("\nPulsos num segundo: %d \n", (int)pulsos_vazao);
    if(pulsos_vazao >= 3000)
    {
      pulsos_vazao = 0;
    }
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }

}

void piscaLed(void *params)
{
  gpio_pad_select_gpio(LED);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    int estado = 0;

    while (true)
    {
      gpio_set_level(LED, estado);
      //vTaskDelay(10 / portTICK_PERIOD_MS);
      vTaskDelay(pdMS_TO_TICKS(10));
      estado = !estado;
    }
}
