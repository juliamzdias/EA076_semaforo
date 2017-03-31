#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int count, caso, button, LDR, safety;

/* User includes (#include below this line is not maintained by Processor Expert) */

void Cpu_OnNMIINT(void)
{
    /* Write your code here ... */
}

//A função TI1_OnInterrupt foi usada para contagem de tempo. A cada 0,5s o programa executa essa rotina.

void TI1_OnInterrupt(void)
{
    count ++;

    if(caso==4){
   	 LED_RED_PPL_NegVal(); //Pisca o LED a cada segundo
    }

    if(LDR>140){
   	 safety++;      
     
     if (safety>=20){     //assegura que o programa aguarde 10s depois que o LDR mudar de valor antes de ir para o caso 5
   		 caso=5;
   		 LED_YEL_CAR_NegVal();
   		 count=0;
   	 }

    } else if ((LDR<=140) && (caso==5)){ 
   	 caso=1;
   	 safety=0;
    }
}

// EInt1_OnInterrupt é uma interrupção externa de máxima prioridade, acionada a cada vez que o botão é pressionado

void EInt1_OnInterrupt(void)
{
    button=1;
    count=0; //O contador é zerado para garantir que haja um tempo de espera antes da mudança para o caso 2
}

void AD1_OnEnd(void)
{
    /* Write your code here ... */
}

void AD1_OnCalibrationEnd(void)
{
    /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif
