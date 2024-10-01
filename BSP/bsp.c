/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                           CYPRESS PSoC5
*                                              with the
*                                     CY8CKIT-050 Development Kit
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_MODULE
#include <bsp.h>
#include <bsp_psoc.h>

#include <bsp_uart.h>
#include <bsp_gpio.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/
                                                                  

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_PreInit()
*
* Description : Board support package pre-initialization funtion.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This funtion initializes peripherals required before the OS is initialized (e.g interrupt controller
*                   external memory.
*********************************************************************************************************
*/


void BSP_PreInit (void)
{
    CPU_INT32U  reg_val;
    CPU_INT32U *p_vect_tbl;
    
    
    reg_val = CPU_REG_NVIC_VTOR;                                   /* Get the NVIC offset table                            */
    DEF_BIT_CLR(reg_val, DEF_BIT_29);                              /* Clear the TBLBASE bit                                */
    
     
    p_vect_tbl                  = (CPU_INT32U *)reg_val;           
                                                                   /* Install the PendSV & Systick Interrupt Handler       */
    p_vect_tbl[CPU_INT_PENDSV]  = (CPU_INT32U  )OS_CPU_PendSVHandler;
    p_vect_tbl[CPU_INT_SYSTICK] = (CPU_INT32U  )OS_CPU_SysTickHandler;
}


/*
*********************************************************************************************************
*                                               BSP_PostInit()
*
* Description : Board Support Package Post initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This funtion initilize peripherlas that requires the OS to be initialized.
*********************************************************************************************************
*/

void  BSP_PostInit (void)
{
    init_gpio();
    init_uart();
}


/*
*********************************************************************************************************
*                                       BSP_CPU_TickInit()
*
* Description : This function reads CPU registers to determine the CPU clock frequency of the chip in KHz.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  BSP_CPU_TickInit  (void)
{
    CPU_INT32U   cpu_clk_freq;
    CPU_INT32U   cnts;
    
    cpu_clk_freq = BSP_CPU_ClkFreq();                             /* Determine SysTick reference freq.                */                                                                        
#if (OS_VERSION > 30000u)                                         /* Determine nbr SysTick increments                 */
    cnts         = (cpu_clk_freq / OSCfg_TickRate_Hz);
#else
    cnts         = (cpu_clk_freq / OS_TICKS_PER_SEC);
#endif
    OS_CPU_SysTickInit(cnts);                                     /* Init uC/OS periodic time src (SysTick).          */
    
}

/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    return ((CPU_INT32U)BSP_PSOC_CPU_FREQ);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any pin on the board.
*
* Argument(s) : led     The ID of the pin to control:
*
*                       P1_6    turns ON P1_6 on J1 Pin 23 on the board
*                       P2_0    turns ON P2_0 on J1 Pin  1 on the board
*                       P2_1    turns ON P2_1 on J1 Pin  2 on the board (Blue LED)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_LED_On (CPU_INT08U led)
{
  CPU_INT08U err = 0;
  
  if(led == P1_6){
    err = gpio_high(PORT1,P1_6);
  }
  else if(led == P2_0){
    err = gpio_high(PORT2,P2_0);
  }
  else if(led == P2_1){
    err = gpio_high(PORT2,P2_1);
  }
  else{
    err++;
  }
  return err;
}


/*
*********************************************************************************************************
*                                              BSP_LED_Off()
*
* Description : Turn OFF any pin on the board.
*
* Argument(s) : led     The ID of the pin to control:
*
*                       P1_6    turns OFF P1_6 on J1 Pin 23 on the board
*                       P2_0    turns OFF P2_0 on J1 Pin  1 on the board
*                       P2_1    turns OFF P2_1 on J1 Pin  2 on the board (Blue LED)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_LED_Off (CPU_INT08U led)
{
  CPU_INT08U err = 0;
  
  if(led == P1_6){
    err = gpio_low(PORT1,P1_6);
  }
  else if(led == P2_0){
    err = gpio_low(PORT2,P2_0);
  }
  else if(led == P2_1){
    err = gpio_low(PORT2,P2_1);
  }
  else{
    err++;
  }
  return err;
}


/*
*********************************************************************************************************
*                                            BSP_LED_Toggle()
*
* Description : Turn TOGGLE any pin on the board.
*
* Argument(s) : led     The ID of the pin to control:
*
*                       P1_6    turns TOGGLE P1_6 on J1 Pin 23 on the board
*                       P2_0    turns TOGGLE P2_0 on J1 Pin  1 on the board
*                       P2_1    turns TOGGLE P2_1 on J1 Pin  2 on the board (Blue LED)
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : Not re-entrant.
*********************************************************************************************************
*/

CPU_INT08U  BSP_LED_Toggle (CPU_INT08U led)
{
  CPU_INT08U err = 0;
  static CPU_BOOLEAN toggle_status = 0;
  
  if(!toggle_status){
    err = BSP_LED_On(led);
    toggle_status = 1;
  }
  else if(toggle_status){
    err = BSP_LED_Off(led);
    toggle_status = 0;
  }
  return err;
}


/*
*********************************************************************************************************
*                                            BSP_PB_StatusGet()
*
* Description : Get the current status of the push button.
*
* Argument(s) : pb    Push button identifier.
*
*                           P2_2 Board SW1 (on J1 Pin 3)
*
* Return(s)   : DEF_ON    If the push button is pressed.
*               DEF_OFF   If the push button is not pressed
*               -1        If error occured
*
* Caller(s)   : application
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08S  BSP_PB_StatusGet (CPU_INT08U  pb)
{
  if(pb == P2_2){
    return gpio_read(PORT2, P2_2);    
  }
  else{
    return -1;
  }
}
