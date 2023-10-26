 // FileName:        system_Thread.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V12.4 TI

#include "system.h"

void *System_Thread(void *arg0);

/*********************************THREAD*************************************
 * Function: System_Thread
 * Preconditions: None.
 * Input:  Apuntador vac�o que puede referenciarse a cualquier tipo de dato.
 * Output: None.
 *
 *****************************************************************************/

void *System_Thread(void *arg0)
{
   bool flag = TRUE;

   /* Inicia el sistema (funci�n predeterminada). */
   SystemInit();

   /* Inicializa drivers de objetos. */
   System_InicialiceIO();
   System_InicialiceUART();

   if(flag != TRUE)
   {
       printf("Error al crear archivos. Cierre del programa\r\n");
       exit(1);
   }

   while(TRUE){
       //Apaga los LED antes de iniciar
       GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2, 0);

       //CONDICION PARA INICIAR EL PROGRAMA
       //Mientras la bandera de UCRXIFG no esté activa el programa no inicia
       while(EUSCI_A_CMSIS(MAIN_UART) -> IFG == 0x02 || EUSCI_A_CMSIS(MAIN_UART) -> IFG == 0x0A){}

       funcion_inicial();
       UART_putsf(MAIN_UART, "Inicia programa. \r\n");

       /* Maquina de estados sincronizada. */
       while(EUSCI_A_CMSIS(MAIN_UART) -> IFG != 0x02 && EUSCI_A_CMSIS(MAIN_UART) -> IFG != 0x0A)
       {
           process_events();
           usleep(1000);
       }
   }
}
