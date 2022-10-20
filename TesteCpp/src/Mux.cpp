//
// Plataforma Steve - Versão 1.0 - FreeRTOS
// Programa: Mux.cpp
// Data de criação: 18/10/2022
// Data de ultima modificação : 17/10/2022
//
// Versão 1.00 Release
// Descrição: header classe Atuador
// para a plataforma Steve 2.1_B
//
// Desenvolvimento: Time da eletrônica
// Empresa: Dell Lead
// Versão final terminada em xx/xx/2022 
//
#include "Mux.h"

Mux::Mux(const gpio_num_t pinS1, const gpio_num_t pinS0, const gpio_num_t pinPort1, const gpio_num_t pinPort2):
S1(pinS1), S0(pinS0), port1(pinPort1), port2(pinPort2)
{
    this->S1 = pinS1;
    this->S0 = pinS0;
    this->port1 = pinPort1;
    this->port2 = pinPort2;

    gpio_pad_select_gpio(this->S1);
    gpio_set_direction(this->S1, GPIO_MODE_OUTPUT);
    gpio_pad_select_gpio(this->S0);
    gpio_set_direction(this->S0, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(this->port1);
    gpio_set_direction(this->port1, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(this->port2);
    gpio_set_direction(this->port2, GPIO_MODE_INPUT);
}

void Mux::setSelect(const gpio_num_t S1, const gpio_num_t S0)
{
    gpio_set_level(this->S1, S1);
    gpio_set_level(this->S0, S0);
}

int Mux::readMux(const gpio_num_t muxPort)
{
    return gpio_get_level(muxPort);
}