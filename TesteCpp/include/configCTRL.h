//
// Plataforma Steve
// Programa: configCTRL.h
// Data: 10/09/2022
//
// Versão 1.00
// Descrição: Cabeçalho de configuração do firmware 2.1
// da plataforma Steve 2.1_B
//
// Desenvolvimento: Time da eletrônica
// Empresa: Dell Lead
//

#ifndef CONFIGCTRL_H
#define CONFIGCTRL_H

//Configurações gerais
#define HIGH                    (1)
#define LOW                     (0)

/********************************************************************/
// Sensores
// Seleção do MUX  Antitombo (S1 = 1 e S0 = 1)
// Seleção do MUX  Ponto_Zero (S1 = 1 e S0 = 1)

/********************************************************************/
//Conexões diretas com o ESP32

#define STANDUP_AV              (32)        //Elevação
#define STANDUP_RC              (23)
#define HALL_STANDUP            (35)

#define SUP_CIRC_AV             (16)        //Sistema Circulatório
#define SUP_CIRC_RC             (5)
#define HALL_SUP_CIRC           (34)

/********************************************************************/
// Pinos do MUX 74HC4052

#define MUX_PORT_1              (36)        //Configuração do MUX
#define MUX_PORT_2              (39)
#define SELECT_MUX_S0           (21)
#define SELECT_MUX_S1           (22)
#define MUX_LOW                 (0)
#define MUX_HIGH                (1)

/********************************************************************/
// HALL's lidos pelo MUX

// Seleção do MUX  (S1 = 0 e S0 = 0)
#define PIN_HOR_ASSENTO_AV              (13)        //Ajuste horizontal do assento
#define PIN_HOR_ASSENTO_RC              (15)
#define PIN_VERT_ENCOSTO_AV             (27)        //Ajuste vertical do encosto
#define PIN_VERT_ENCOSTO_RC             (4)

// Seleção do MUX  (S1 = 0 e S0 = 1)
#define PIN_INC_ENC_AV                  (14)        //Inclinação do Encosto
#define PIN_INC_ENC_RC                  (2)
#define VERT_ASSENTO_AV                 (33)        //Ajuste vertical do assento
#define VERT_ASSENTO_RC                 (19)

// Seleção do MUX  (S1 = 1 e S0 = 0)
#define PIN_CIRC_DIR_AV                 (26)        //Ajuste vertical do suporte circulatório direito
#define PIN_CIRC_DIR_RC                 (17)
#define PIN_CIRC_ESQ_AV                 (25)        //Ajuste vertical do suporte circulatório esquerdo
#define PIN_CIRC_ESQ_RC                 (18)

// Seleção do MUX  (S1 = 1 e S0 = 1)
//Seleção do Anti tombo(1Y3) e entrada livre(2Y3)

#endif