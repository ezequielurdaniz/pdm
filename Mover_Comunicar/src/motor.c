/*
 * motor.c
 *
 *  Created on: 2 jul. 2019
 *      Author: ezequiel
 */
/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include "motor.h"

/*=====[Declarations of public functions]=======================*/

void configlimitMotor(void){		// Configuracion gpio

	gpioConfig( LED1, GPIO_OUTPUT ); //salida //MOTOR X->
	gpioConfig( LED2, GPIO_OUTPUT ); //salida //MOTOR X<-
	gpioConfig( LED3, GPIO_OUTPUT ); //salida //MOTOR Y->
	gpioConfig( LEDB, GPIO_OUTPUT ); //salida //MOTOR Y<-
	gpioConfig( GPIO0, GPIO_INPUT ); //entrada //Limite X max
	gpioConfig( GPIO1, GPIO_INPUT ); //entrada  //Limite X min
	gpioConfig( GPIO2, GPIO_INPUT ); //entrada  //Limite Y max
	gpioConfig( GPIO6, GPIO_INPUT ); //entrada  //Limite Y min
	}

void bottonPressed_avance (	gpioMap_t tecla ){  // Muevo motor

	switch(tecla){
			case TEC1:
				gpioWrite(LED1, ON); //MOTOR X->
				break;
			case TEC2:
				gpioWrite(LED2, ON); //MOTOR X<-
				break;
			case TEC3:
				gpioWrite(LED3, ON); //MOTOR Y->
				break;
			case TEC4:
				gpioWrite(LEDB, ON); //MOTOR Y<-
				break;
			default:
				//Sin accion.
				break;
			}
	}


void bottonReleased_freno ( gpioMap_t tecla ){							//Freno motor

	switch(tecla){
			case TEC1:
				gpioWrite(LED1, OFF); 						//MOTOR X->
				break;
			case TEC2:
				gpioWrite(LED2, OFF); 						//MOTOR X<-
				break;
			case TEC3:
				gpioWrite(LED3, OFF); 						//MOTOR Y->
				break;
			case TEC4:
				gpioWrite(LEDB, OFF); 						//MOTOR Y<-
				break;
			default:
												//Sin accion.
				break;
			}
	}

int limite ( void ) {										//Limite
	for(int i=0;i<=3;i++){
		sensor=0;									//Inicializo sensor
	switch(i){
			case 0:
				valor = !gpioRead(GPIO0);
				if(valor == 1){
					sensor=1;						//Limite X_max
				}
				break;
			case 1:
				valor = !gpioRead(GPIO1);
				if(valor == 1){
					sensor=2;						//Limite X_min
				}
				break;
			case 2:
				valor = !gpioRead(GPIO2);
				if(valor == 1){
					sensor=3;						//Limite Y_max
				}
				break;
			case 3:
				valor = !gpioRead(GPIO6);
				if(valor == 1){
					sensor=4;						//Limite Y_min
				}
				break;
			default:
				sensor=0;
				break;

			}
	}
	return sensor;
	}
