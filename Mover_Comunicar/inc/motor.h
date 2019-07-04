/*
 * main.h
 *
 *  Created on: 2 jul. 2019
 *      Author: ezequiel
 */

#ifndef PDM_MOVER_COMUNICAR_INC_MOTOR_H_
#define PDM_MOVER_COMUNICAR_INC_MOTOR_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include <stdint.h>
#include <stddef.h>

/*=====[Definitions of public data types]====================================*/

bool_t valor;
int sensor;

/*=====[Prototypes (declarations) of public functions]=======================*/

void configlimitMotor(void);			// Configuracion gpio
void bottonPressed_avance (gpioMap_t);  	// Muevo motor
void bottonReleased_freno (gpioMap_t);		// Freno motor
int limite(void); 				// Limites



#endif /* PDM_MOVER_COMUNICAR_INC_MOTOR_H_ */
