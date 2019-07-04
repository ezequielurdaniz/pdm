/*
 * Mover_Comunicar.h
 *
 *  Created on: 2 jul. 2019
 *      Author: ezequiel
 */

#ifndef PDM_MOVER_COMUNICAR_INC_MOVER_COMUNICAR_H_
#define PDM_MOVER_COMUNICAR_INC_MOVER_COMUNICAR_H_

/*=====[Inclusions of public function dependencies]==========================*/
#include "sapi.h"
#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

// FSM Nombre de estados DESPLAZAMIENTO

typedef enum{
	BUTTON_ARRIBA,
	BUTTON_PRESIONADO,
	BUTTON_SUELTO,
	BUTTON_ABAJO,
	GIRO_MOTOR,
	LIMITE
} fsmState_t;

// FSM Nombre de estados COMUNICACION
typedef enum{
	CONFIG_UART,
	INICIO_UART,
	BUFFER_DATOS,
	DATOS,
	ENVIOS
} fsmStateCOM_t;


/*=====[Prototypes (declarations) of public functions]=======================*/
// FSM funciones

void fsmError( void );
void fsmInit( void );
void fsmUpdate(gpioMap_t);

void fsmError_COM( void );
void fsmInit_COM( void );
void fsmUpdate_COM(void);


/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

#endif /* PDM_MOVER_COMUNICAR_INC_MOVER_COMUNICAR_H_ */

