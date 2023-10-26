 // FileName:        system_functions.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V12.4 TI

#include "system.h"
#define SEGUNDO __SYSTEM_CLOCK

uint8_t contadorEstado = 0x00; //Contador de cuantas veces se pone en pausa
uint8_t contadorApago = 0x00; //Contador de cuantas veces se presiona el boton de apago
uint8_t contadorSeg = 0x00; //Contador de segundos (para el timer)
bool estado = 0; //0 = Verde (En ejecucion), 1 = Rojo (Pausa)
bool prendido = 1; //Estado del LED RGB

void cambioDeColor(void);
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
    //Reinicio de las variables para otro ciclo
    prendido = 1;
    contadorEstado = 0x00;
    contadorApago = 0x00;
    contadorSeg = 0x00;
    //Configuracion de los timers
    //Modo oneshot
    //Prescaler de 1
    //32 bits
    T32_Configure1(TIMER32_OneShotMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize);
    //Registra y habilita la funcion de interrupcion
    Int_registerInterrupt(INT_T32_INT1, Timer32_INT1);
    Int_enableInterrupt(INT_T32_INT1);
    T32_EnableTimer1(); //Se habilita el timeR
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
    if(estado){ //Sistema en pausa
        return;
    }

    //Switch de PAUSA
    if((GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE) && contadorApago == 0x00)
    {
        contadorEstado++; //Incrementa el contador de estado
        //Asigna al estado lo mismo que la condicional if, o sea, un 1
        estado = (GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE);
        T32_SetLoadValue1(3 * SEGUNDO); //Si el boton esta presionado la interrupción dura 3 seg,
        //Si el contador es igual a 6 entonces se apaga el led
        prendido = prendido * !(contadorEstado == 0x06);
        cambioDeColor(); //Cambia de color el RGB
        if(contadorEstado < 0x06)
            UART_putsf(MAIN_UART, "Pausa. \r\n");
        if(contadorEstado == 0x06){
            UART_putsf(MAIN_UART, "Programa terminado. \r\n");
            EUSCI_A_CMSIS(MAIN_UART) -> IFG &= !0x0D;       //Borra la bandera UCRXIFG
        }
        while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE);
    }

    //Switch de APAGADO
    if(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE)
    {
        contadorApago++; //Incrementa el contador de apagado
        prendido = prendido * !(contadorApago & 0x02); //Si el contador es igual a dos entonces el estado de prendido es igual a 0
        cambioDeColor(); //Cambia de color el RGB
        if(contadorApago & 0x02){
            UART_putsf(MAIN_UART, "Programa terminado. \r\n");
            EUSCI_A_CMSIS(MAIN_UART) -> IFG &= !0x0D;       //Borra la bandera UCRXIFG
        }
        if(contadorApago & 0x01)
            UART_putsf(MAIN_UART, "Presione de nuevo para apagar. \r\n");
        //Reinicia el contador de apagado cuando llegue a 2
        contadorApago = contadorApago * !(contadorApago & 0x02);
        while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE);
    }


}

/*FUNCTION******************************************************************************
*
* Function Name    : Timer32_INT1
* Returned Value   : None.
* Comments         :
*
*END***********************************************************************************/

void Timer32_INT1(void)
{
    T32_ClearInterruptFlag1(); //Se limpia la bandera
    T32_EnableTimer1(); //Se habilita el timer
    T32_EnableInterrupt1(); //Habilitamos la interrupcion
    T32_SetLoadValue1(SEGUNDO); //Si el boton esta presionado dura 3 seg, sino dura 1
    cambioDeColor();

    //Si el estado esta en 0 y el contador de apago tiene un 1 en su cuenta, entonces suma uno
    contadorSeg += ((0x01) * !estado * (contadorApago == 0x01));
    //Si contadorSeg esta en el rango (0-3 seg), el valor de la variable queda igual, de caso contario se pone a 0
    contadorApago = contadorApago * !estado * !(contadorSeg == 0x03);
    //Si el contador a hecho una suma de 3 segundos entonces vuelve a 0
    contadorSeg = contadorSeg * !estado * !(contadorSeg == 0x03);

    if(estado != 0x00){
        UART_putsf(MAIN_UART, "Programa ejecutandose.\r\n");
        //Si el estado es verdadero entonces lo regresa a 0
        estado = (estado * !estado);
        cambioDeColor();
    }

}

/*FUNCTION******************************************************************************
*
* Function Name    : cambioDeColor
* Returned Value   : None.
* Comments         : cambia el color segun los estados de las variables
*
*END***********************************************************************************/
void cambioDeColor(void){
    //Varias condicionales en el valor que se le va enviar
    //si el contadorApago es igual a 1
    //si la variable prendido es 1
    //El valor de la variable estado
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2, 1 * estado * !(contadorApago & 0x01) * prendido);  //ROJO
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3, 1 * !estado * !(contadorApago & 0x01) * prendido); //VERDE
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  1 * (contadorApago & 0x01) * prendido);           //AZUL
}
