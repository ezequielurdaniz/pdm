/*=============================================================================
 * Author: Ezequiel Urdaniz <urdanizezequiel@gmail.com>
 * Date: 2019/07/02
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "Mover_Comunicar.h"
#include "motor.h"
#include "uart.h"


/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

fsmState_t fsmState;
fsmStateCOM_t fsmStateCOM;

//fsmDate_t Datatec1,Datatec2,Datatec3,Datatec4;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void ){
	// ----- Setup -----------------------------------
	boardInit();

	fsmInit();								//Inicializo State Desplazamiento
	configlimitMotor();  							//Configuracion GPIO
	delay_t tiempo1;
	delayInit(&tiempo1,10);
	delay_t tiempo2;
	delayInit(&tiempo2,10);
	delay_t tiempo3;
	delayInit(&tiempo3,10);
	delay_t tiempo4;
	delayInit(&tiempo4,10);


	fsmInit_COM(); 								//Inicializo State Comunicacion
	delay_t tiempoCOM
	delayInit(&tiempoCOM,5);




   // ----- Repetir  -------------------------

   while( TRUE ) {
//--------------------- Maquina de estado Desplazamiento -------------//

	   if (delayRead( &tiempo1)){
		   fsmUpdate(TEC1);
	   	   }
	   if (delayRead( &tiempo2)){
		   fsmUpdate(TEC2);
	  	   }
	   if (delayRead( &tiempo3)){
		   fsmUpdate(TEC3);
	  	   }
	   if (delayRead( &tiempo4)){
		   fsmUpdate(TEC4);
	  	   }

//--------------------- Maquina de estado comunicacion -------------//

	   if (delayRead( &tiempoCOM)){
		   fsmUpdate_COM();
	  	  }
   }

   return 0;
}

/*=====[Declarations of public functions]====================================*/

//------------------------------ DESPLAZAMIENTO ----------------------------//

void fsmError( void ){ 								//Reset el FSM:
	fsmState = BUTTON_ARRIBA;
	}

void fsmInit( void ){								//Init stated
	fsmState = BUTTON_ARRIBA;
	}

void fsmUpdate (gpioMap_t tecla){

	switch( fsmState ){
		case BUTTON_ARRIBA:
			if(!gpioRead(tecla)){ 					//Tecla arriba
				fsmState = BUTTON_PRESIONADO;
			}
			break;

		case BUTTON_PRESIONADO:
			if(!gpioRead(tecla)){ 					//Tecla presionada
				fsmState = BUTTON_ABAJO;

			}
			else{
				fsmState = BUTTON_ARRIBA;
			}
			break;

		case BUTTON_ABAJO:
			if(!gpioRead(tecla)){ 					//Tecla abajo
				fsmState = GIRO_MOTOR;
			}
			else{
				fsmState = BUTTON_SUELTO;
			}
			break;

		case BUTTON_SUELTO:
			if(gpioRead(tecla)){ 					//Tecla suelta
				fsmState = BUTTON_ARRIBA;
				bottonReleased_freno(tecla);   			//Freno segun tecla
			}
			else{
				fsmState = BUTTON_ABAJO;
			}
			break;

		case GIRO_MOTOR:
			fsmState = BUTTON_ABAJO;
			bottonPressed_avance(tecla);   				//Desplazo segun tecla
			sensor = limite(); 			   		//Limite
			if(sensor!=0){ 						//Sensor activado
				fsmState = LIMITE;
			}
			break;

		case LIMITE:
			bottonReleased_freno(tecla);   				//Freno
			fsmState = BUTTON_ARRIBA;
			break;

		default:
			fsmError();
			break;
	}
}
//-------------------------- COMUNICACION-------------------------------------//

void fsmError_COM( void ){ 							//Reset el FSMCOM
	fsmStateCOM = CONFIG_UART;
	}
void fsmInit_COM( void ){ 							//Init StateCOM:
	fsmStateCOM = CONFIG_UART;
	}

void fsmUpdate_COM(void){

	switch( fsmStateCOM ){
		case CONFIG_UART:
			uartInit_c();						//Configuracion UART
			fsmStateCOM = INICIO_UART;
			break;

		case INICIO_UART:
			dato=0;							//Inicializo datos
			flagdat = OFF;						//Flag de datos
			fsmStateCOM = BUFFER_DATOS;
			break;

		case BUFFER_DATOS:
			if(flagdat){
			fsmStateCOM = ENVIOS;					//Flag datos ON
			}
			else{
			fsmStateCOM = DATOS;					//Flag datos OFF
			}
			break;

		case DATOS:
			fsmStateCOM = BUFFER_DATOS;
										//Recive dato a la UART_USB
			flagdat = RecivirDato(dato);  				//Guardo dato y bandera ON/OFF
			break;

		case ENVIOS:
			fsmStateCOM = BUFFER_DATOS;
	        enviarDato(dato);						//Envia el dato a la UART_USB
	        flagdat = OFF;
			break;

		default:
			fsmError_COM();
			break;
	}
}
//-------------------------- ------------------------------------------------//
