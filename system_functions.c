 // FileName:        system_functions.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V12.4 TI

#include "system.h"
#define SEGUNDO __SYSTEM_CLOCK

void verde(void);
void rojo(void);
void Timer32_INT1(void);

/*FUNCTION*********************************************************************************
*
* Function Name    : System_InicialiceIO
* Returned Value   : None.
* Comments         :
*
*END****************************************************************************************/

void System_InicialiceIO(void)
{
    GPIO_init_board();
}

/*FUNCTION******************************************************************************
*
* Function Name    : System_InicialiceUART
* Returned Value   : None.
* Comments         :
*
*END***********************************************************************************/
void System_InicialiceUART (void)
{
    UART_init();
}

/*FUNCTION******************************************************************************
*
* Function Name    : funcion_inicial
* Returned Value   : None.
* Comments         :
*
*END***********************************************************************************/

void funcion_inicial (void)
{
    verde();
    //Configuracion de los timers
    //Modo oneshot
    //Prescaler de 1
    //32 bits
    T32_Configure1(TIMER32_OneShotMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize);
    //Registra y habilita la funcion de interrupcion
    Int_registerInterrupt(INT_T32_INT1, Timer32_INT1);
    Int_enableInterrupt(INT_T32_INT1);
    T32_EnableTimer1(); //Se habilita el timer
    T32_EnableInterrupt1(); //Habilitamos la interrupcion
    T32_SetLoadValue1(SEGUNDO); //Se asigna un segundo
}

/*FUNCTION******************************************************************************
*
* Function Name    : process_events
* Returned Value   : None.
* Comments         :
*
*END***********************************************************************************/

void process_events(void)
{
}

void Timer32_INT1(void)
{
    T32_ClearInterruptFlag1(); //Se limpia la bandera
    T32_EnableTimer1(); //Se habilita el timer
    T32_EnableInterrupt1(); //Habilitamos la interrupcion
    GPIO_setOutput(BSP_LED1_PORT,  BSP_LED1, !(GPIO_getInputPinValue(BSP_LED1_PORT, BSP_LED1_PORT)));
    //La salida alterna entre cero y uno
}

void rojo(void){
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  1);
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  0);
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);
}

void verde(void){
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  1);
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);
}
