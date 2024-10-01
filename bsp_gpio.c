/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <bsp_gpio.h>

/*
*********************************************************************************************************
*                                       init_gpio()
*
* Description : This function initializes the Pin_1 GPIO module (P1_6, J1 Pin 23), the
*               Pin_2 GPIO module (P2_0, J1 Pin 1 and P2_1, J1 Pin 2) and the push button
*               GPIO module (P2_2, J1 Pin 3). On P2_1 a blue on-board LED is connected. On
*               P2_2 on side of a GND-connected button is connected.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : Not re-entrant.
*********************************************************************************************************
*/

CPU_VOID init_gpio(CPU_VOID)
{
  Pin_1_SetDriveMode(Pin_1_DM_STRONG);
  Pin_2_SetDriveMode(Pin_2_DM_STRONG);
  push_button_SetDriveMode(push_button_DM_STRONG);
  push_button_Write(1);
}

/*
*********************************************************************************************************
*                                       gpio_high()
*
* Description : This function set based on a chosen port (PORT1, PORT2) the digital level
*               of a chosen pin (P1_6, P2_0, P2_1) on digital high (~ 5V).
*
* Argument(s) : port ... indicates which port should be addressed (PORT1, PORT2)
*               pin  ... indicates which pin of the chosen port is addressed (P1_6, P2_0, P2_1)
*
* Return(s)   : 0 ... if no error occurred
*               >1... if an error occurred
*
* Caller(s)   : Application.
*
* Note(s)     : Not re-entrant.
*********************************************************************************************************
*/

CPU_INT08U gpio_high(CPU_INT08U port, CPU_INT08U pin)
{
  CPU_INT08U err = 0;
  
  if(port == PORT1){
    if(pin == P1_6){
      Pin_1_Write(HIGH);
    }
    else{
      err++;
    }
  }
  else if(port == PORT2){
    if(pin == P2_0){
      Pin_2_Write(P2_0); 
    }
    else if(pin == P2_1){
      Pin_2_Write(P2_1);
    }
    else{
      err++;
    }
  }
  else{
    err++;
  }
  return err;    
}

/*
*********************************************************************************************************
*                                       gpio_low()
*
* Description : This function resets based on a chosen port (PORT1, PORT2) the digital level
*               of a chosen pin (P1_6, P2_0, P2_1) on digital low (0V).
*
* Argument(s) : port ... indicates which port should be addressed (PORT1, PORT2)
*               pin  ... indicates which pin of the chosen port is addressed (P1_6, P2_0, P2_1)
*
* Return(s)   : 0 ... if no error occurred
*               >1... if an error occurred
*
* Caller(s)   : Application.
*
* Note(s)     : Not re-entrant.
*********************************************************************************************************
*/

CPU_INT08U gpio_low(CPU_INT08U port, CPU_INT08U pin)
{
  CPU_INT08U err = 0;
  
  if(port == PORT1){
    if(pin == P1_6){
      Pin_1_Write(LOW);
    }
    else{
      err++;
    }
  }
  else if(port == PORT2){
    if(pin == P2_0){
      Pin_2_Write(!(P2_0)); 
    }
    else if(pin == P2_1){
      Pin_2_Write(!(P2_1));
    }
    else{
      err++;
    }
  }
  else{
    err++;
  }
  return err;   
}

/*
*********************************************************************************************************
*                                       gpio_read()
*
* Description : This function reads the digital level of a chosen port (PORT2) and pin (P2_2).
*
* Argument(s) : port ... indicates which port should be addressed (PORT2)
*               pin  ... indicates which pin of the chosen port is addressed (P2_2)
*
* Return(s)   : 0 ... if no error occurred
*               -1... if an error occurred
*
* Caller(s)   : Application.
*
* Note(s)     : Not re-entrant.
*********************************************************************************************************
*/

CPU_INT08S gpio_read(CPU_INT08U port, CPU_INT08U pin)
{
  CPU_INT08S err = 0;
  
  if(port == PORT2){
    if(pin == P2_2){
      err = push_button_Read();    
    }
    else{
      err = -1;
    }
  }
  else{
    err = -1;
  }
  return err;
}


/* [] END OF FILE */
