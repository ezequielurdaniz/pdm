/*
 * uart.h
 *
 *  Created on: 2 jul. 2019
 *      Author: ezequiel
 */

#ifndef PDM_MOVER_COMUNICAR_INC_UART_H_
#define PDM_MOVER_COMUNICAR_INC_UART_H_

/*==================[inclusions]=============================================*/
#include "sapi.h"     // <= sAPI header
#include <stdint.h>
#include <stddef.h>

/*==================[(Proptotipo) functions definition]==========================*/
void uartInit_c(void);
void enviarDato(uint8_t dato);
int RecivirDato(uint8_t dato);

/*==================[external data definition]===============================*/

uint8_t dato  ; //= 0;
uint8_t flagdat; // flagdat ON//OFF

#endif /* PDM_MOVER_COMUNICAR_INC_UART_H_ */
