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

#include <cpu.h>

#include <UART_1.h>

static CPU_INT08U Start_of_Packet = '#';
static CPU_INT08U End_of_Packet = '$';

CPU_VOID init_uart(CPU_VOID);
CPU_INT08U uart_get_byte(CPU_VOID);
CPU_VOID uart_send_byte(CPU_INT08U byte);

/* [] END OF FILE */
