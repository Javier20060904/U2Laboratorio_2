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

   while(!getchar()); //Detectar tecla
   printf("INICIANDO PROGRAMA"); //Permite la inicializacion del programa
   funcion_inicial();

   /* M�quina de estados sincronizada. */
   while(TRUE)
   {
       process_events();
       usleep(1000);
   }
}
