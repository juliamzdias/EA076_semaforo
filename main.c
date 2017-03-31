/**
 *
 * EA076 - Projeto 1: Semáforo
 *
 * Isabella Bigatto   	 138537
 * Júlia Dias   	156019
 *
 * Implementação de um conjunto de semáforos, um para carros e outro para pedestres, que funcionam
 * com o auxílio de um botão e um LDR.
 *
 **/

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "LED_RED_CAR.h"
#include "BitIoLdd2.h"
#include "LED_YEL_CAR.h"
#include "BitIoLdd3.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "LED_GREEN_CAR.h"
#include "BitIoLdd4.h"
#include "LED_RED_PPL.h"
#include "BitIoLdd5.h"
#include "LED_GREEN_PPL.h"
#include "BitIoLdd6.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

int LED_GREEN_CAR, LED_YEL_CAR, LED_RED_CAR, LED_RED_PPL, LED_GREEN_PPL;
int caso=1, button=0, count=0, safety=0; 
volatile uint8_t LDR;

int main(void)
{    
    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                	***/

    while (1){

   	 AD1_GetValue8(&LDR);    		 //Retorna o valor já convertido do LDR

   	 //O problema foi dividido em 5 casos distintos, relacionados aos estados dos semáforos

   	 if (caso==1){
   		 LED_RED_CAR_PutVal(0);   	 //O valor 0 determina LED OFF
   		 LED_GREEN_CAR_PutVal(1);    //O valor 1 determina LED ON
   		 LED_RED_PPL_PutVal(1);
   		 LED_YEL_CAR_PutVal(0);

   		 /*Se o botão é acionado, o sistema aguarda 5s para mudar de caso.
   			 Essa condição só funciona se estiver claro, ou seja, LDR<=140.*/
   		 
   		 if ((button==1) && (count>=10) && (LDR<=140)){
   			 caso=2;
   			 count=0;
   			 button=0;
   		 }
   	 }    

   	 else if (caso==2){
   		 LED_GREEN_CAR_PutVal(0);
   		 LED_YEL_CAR_PutVal(1);
   		 LED_RED_PPL_PutVal(1);
   		 
   		 //Permanece no caso 2 por 3s até trocar para o caso 3
   		 if(count>=6){
   			 caso=3;
   			 count=0;
   		 }
   	 }

   	 else if (caso==3){
   		 LED_YEL_CAR_PutVal(0);
   		 LED_RED_CAR_PutVal(1);
   		 LED_RED_PPL_PutVal(0);
   		 LED_GREEN_PPL_PutVal(1);
   		 if(count>=6){
   			 caso=4;
   			 count=0;
   		 }
   	 }

   	 else if (caso==4){
   		 LED_RED_CAR_PutVal(1);
   		 LED_GREEN_PPL_PutVal(0);
   		 if (count>=10){
   			 caso=1;
   			 count=0;
   		 }
   	 }

      else if (caso==5){
   		 LED_RED_CAR_PutVal(0);
   		 LED_GREEN_CAR_PutVal(0);
   		 LED_GREEN_PPL_PutVal(0);
   		 LED_RED_PPL_PutVal(0);
   	 }

   	 AD1_Measure(TRUE);   	 //Mede o valor de tensão do LDR
    
  }

    /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
    PEX_RTOS_START();              	/* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
    /*** End of RTOS startup code.  ***/
    /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
}
