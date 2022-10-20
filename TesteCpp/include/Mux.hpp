//
// Plataforma Steve - Versão 1.0 - FreeRTOS
// Programa: Mux.h
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

#include <stdio.h>
#include "driver/gpio.h"


#ifndef MUX_HPP
#define MUX_HPP

class Mux
{
    public:
        Mux(const gpio_num_t pinS1, const gpio_num_t pinS0, const gpio_num_t pinPort1, const gpio_num_t pinPort2);

        void setSelect(const gpio_num_t S1, const gpio_num_t S0);
        int readMux(const gpio_num_t muxPort);

    private:
        gpio_num_t S1;
        gpio_num_t S0;
        gpio_num_t port1;
        gpio_num_t port2;
};
    
#endif