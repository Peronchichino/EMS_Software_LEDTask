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

#include <Pin_1.h>
#include <Pin_2.h>
#include <push_button.h>

#define HIGH 1
#define LOW 0

#define PORT1 (1<<0)
#define PORT2 (1<<1)

#define P1_6 (1<<6)
#define P2_0 (1<<0)
#define P2_1 (1<<1)
#define P2_2 (1<<2)

CPU_VOID init_gpio(CPU_VOID);
CPU_INT08U gpio_high(CPU_INT08U port, CPU_INT08U pin);
CPU_INT08U gpio_low(CPU_INT08U port, CPU_INT08U pin);
CPU_INT08S gpio_read(CPU_INT08U port, CPU_INT08U pin);

/* [] END OF FILE */
