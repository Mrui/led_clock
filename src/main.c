/*
 ===============================================================================
 Name        : led_clock.c
 Author      : Toni Heikkinen
 Version     :
 Copyright   : Toni Heikkinen (murrix@gmail.com Mrui@github)
 Description : main definition

 Special thanks : ARMwizard by Alexan Software http://alexan.edaboard.eu
 ===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC11Uxx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#include <hal_pio.h>
#include <seg.h>

typedef enum {
	CLOCK, GPS
} status_type;
volatile static status_type fsm = CLOCK;

static uint8_t minutes[2] = { 0, 0 };
static uint8_t hours[2] = { 0, 0 };
static int counter = 0;
volatile static int kp = 0;
volatile static int i = 0;
volatile static int usart_delay = 0;
volatile static int usart_sending = 0;
volatile char usart_read_buffer[8];
volatile int usart_buffer_pos = 0;

volatile static int sw1_laststate = 0;
volatile static int sw2_laststate = 0;
volatile static int sw3_laststate = 0;
volatile static int sw4_laststate = 0;
volatile static int sw5_laststate = 0;

// Initialize all pins, timers and interrupts.
void init_all();
void usart_senddata(char send);

/******************************************************************************
 System Tick Interrupt service function
 ******************************************************************************/
void SysTick_Handler(void) {
	/* write code here */

}

void TIMER32_0_IRQHandler(void) {
	/* write code here */
	i++;
	counter++;
	usart_delay++;
	if (i > 4) {
		i = 0;
		if (sw2_laststate == 1 && !SW2_DATA) {
			sw2_laststate = 0;
		}
		if (sw3_laststate == 1 && !SW3_DATA) {
			sw3_laststate = 0;
		}
		if (sw4_laststate == 1 && !SW4_DATA) {
			sw4_laststate = 0;
		}
		if (sw5_laststate == 1 && !SW5_DATA) {
			sw5_laststate = 0;
		}
	}

	if (fsm == GPS) {
		if ((i % 10 == 0))
			DUAL_LEDS_TOGGLE;
	}
	else
		DUAL_LEDS_ON;

	if (usart_delay > 4 && usart_sending != 0) {
		usart_sending = 0;
	}

	if (counter > 6000) {
		counter = 0;
		if (minutes[1] < 9)
			minutes[1]++;
		else {
			minutes[1] = 0;
			if (minutes[0] < 5)
				minutes[0]++;
			else {
				minutes[0] = 0;
				if (hours[0] < 9 && (hours[1] != 2 || hours[0] < 3))
					hours[0]++;
				else {
					hours[0] = 0;
					if (hours[1] < 2)
						hours[1]++;
					else
						hours[1] = 0;
				}
			}

		}
	}
	/* list of all available flags, select which to use */
	LPC_CT32B0->IR = (1UL << 0); /* Clear MAT0.0 interrupt flag */
//LPC_CT32B0->IR = (1UL<<1);   /* Clear MAT0.1 interrupt flag */
//LPC_CT32B0->IR = (1UL<<2);   /* Clear MAT0.2 interrupt flag */
//LPC_CT32B0->IR = (1UL<<3);   /* Clear MAT0.3 interrupt flag */
//LPC_CT32B0->IR = (1UL<<4);   /* Clear CAP0.0 interrupt flag */
}

/******************************************************************************
 32-bit Timer1 (CT32B1) Interrupt service function
 ******************************************************************************/
void TIMER32_1_IRQHandler(void) {
	/* write code here */
	switch (kp++) {
	case 0:
		showMinute1(minutes[0]);
		break;
	case 1:
		showMinute2(minutes[1]);
		break;
	case 2:
		showHour1(hours[0]);
		break;
	case 3:
		showHour2(hours[1]);
		break;
	default:
		kp = 0;
		break;
	}
	/* list of all available flags, select which to use */
//LPC_CT32B1->IR = (1UL<<0);   /* Clear MAT1.0 interrupt flag */
	LPC_CT32B1->IR = (1UL << 1); /* Clear MAT1.1 interrupt flag */
//LPC_CT32B1->IR = (1UL<<2);   /* Clear MAT1.2 interrupt flag */
//LPC_CT32B1->IR = (1UL<<3);   /* Clear MAT1.3 interrupt flag */
//LPC_CT32B1->IR = (1UL<<4);   /* Clear CAP1.0 interrupt flag */
//LPC_CT32B1->IR = (1UL<<5);   /* Clear CAP1.1 interrupt flag */
}

/******************************************************************************
 UART Interrupt service function
 ******************************************************************************/
void UART_IRQHandler(void) {
	/* write code here */
	usart_buffer_pos++;
	usart_read_buffer[usart_buffer_pos] = LPC_USART->RBR;
	while(usart_buffer_pos > 0) {
		usart_senddata(usart_read_buffer[usart_buffer_pos]);
		usart_buffer_pos--;
	}
}

/******************************************************************************
 GPIO pin interrupt 0 service function
 ******************************************************************************/
void FLEX_INT0_IRQHandler(void) {
	/* write code here */

	/* The following clears the pin interrupt flag when set to EDGE mode, if the pin is set the LEVEL sense then it switches the pin interrupt detection level [LOW<->HIGH] (may be removed if this is not wanted) */
	LPC_GPIO_PIN_INT->IST = (1UL << 0); /* Clear RISING/FALLING EDGE interrupt flag */
}

/******************************************************************************
 GPIO pin interrupt 1 service function
 ******************************************************************************/
void FLEX_INT1_IRQHandler(void) {
	/* write code here */
	if (sw2_laststate < 1 && SW2_DATA)
	{
		// Hours[0] second button from left.
		sw2_laststate = 1;

	}
	/* The following clears the pin interrupt flag when set to EDGE mode, if the pin is set the LEVEL sense then it switches the pin interrupt detection level [LOW<->HIGH] (may be removed if this is not wanted) */
	LPC_GPIO_PIN_INT->IST = (1UL << 1); /* Clear RISING/FALLING EDGE interrupt flag */
}

/******************************************************************************
 GPIO pin interrupt 2 service function
 ******************************************************************************/
void FLEX_INT2_IRQHandler(void) {
	/* write code here */
	if (sw3_laststate < 1 && SW3_DATA) {
		sw3_laststate = 1;
		counter = 0;
		usart_senddata('M');
		if (minutes[1] < 9)
		minutes[1]++;
		else {
			minutes[1] = 0;
			if (minutes[0] < 5)
			minutes[0]++;
			else
			minutes[0] = 0;
		}
	}

//	fsm = PROGRAM;
	/* The following clears the pin interrupt flag when set to EDGE mode, if the pin is set the LEVEL sense then it switches the pin interrupt detection level [LOW<->HIGH] (may be removed if this is not wanted) */
	LPC_GPIO_PIN_INT->IST = (1UL << 2); /* Clear RISING/FALLING EDGE interrupt flag */
}

/******************************************************************************
 GPIO pin interrupt 3 service function
 ******************************************************************************/
void FLEX_INT3_IRQHandler(void) {
	/* write code here */

	if (sw4_laststate < 1 && SW4_DATA)
	{
		// First from left.
		sw4_laststate = 1;

		if (fsm == CLOCK) {
			fsm = GPS;
			usart_senddata('O');
		}
		else {
			fsm = CLOCK;
			usart_senddata('F');
		}
	}
	/* The following clears the pin interrupt flag when set to EDGE mode, if the pin is set the LEVEL sense then it switches the pin interrupt detection level [LOW<->HIGH] (may be removed if this is not wanted) */
	LPC_GPIO_PIN_INT->IST = (1UL << 3); /* Clear RISING/FALLING EDGE interrupt flag */
}

/******************************************************************************
 GPIO pin interrupt 4 service function
 ******************************************************************************/
void FLEX_INT4_IRQHandler(void) {
	/* write code here */
	if (sw5_laststate < 1 && SW5_DATA) {
		sw5_laststate = 1;
		usart_senddata('H');
		if (hours[0] < 9 && (hours[1] != 2 || hours[0] < 3))
		hours[0]++;
		else {
			hours[0] = 0;
			if (hours[1] < 2)
			hours[1]++;
			else
			hours[1] = 0;
		}
	}
	/* The following clears the pin interrupt flag when set to EDGE mode, if the pin is set the LEVEL sense then it switches the pin interrupt detection level [LOW<->HIGH] (may be removed if this is not wanted) */
	LPC_GPIO_PIN_INT->IST = (1UL << 4); /* Clear RISING/FALLING EDGE interrupt flag */
}

int main(void) {

	init_all();

	sw1_laststate = 0;
	sw2_laststate = 0;
	sw3_laststate = 0;
	sw4_laststate = 0;
	sw5_laststate = 0;

	GPS_ON;

	i = 0;
	usart_senddata('I');
	// Enter an infinite loop, just incrementing a counter
	while (1) {
		if (fsm == CLOCK) {

		} else if (fsm == GPS) {

		}
	}
	return 0;
}

// Init 7 segment control as output PIO's, pull-down resistor enabled.
void init_all() {

	LPC_SYSCON->SYSAHBCLKDIV = 0x01; /* set AHB clock divider to 1/1 */
	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 6); /* enable clock for GPIO (default is disabled)*/
	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 16); /* enable clock for IOCON (default is disabled)*/
	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 12); /* enable clock for USART (default is disabled)*/
	LPC_SYSCON->UARTCLKDIV = 0x04;

	// Enable bypass for sys_osc_clk. Clock from external 20 MHz oscillator
	LPC_SYSCON->SYSOSCCTRL = 0x00000001;

	// Configuring USART
	// Set BAUDRATE to 57200
	LPC_USART->FDR = 0x00000045; // Setting fractional divider to MULVAL to 2 and DIVADDVAL to 1
	LPC_USART->DLL = 0x00000008; // Set DLL to 173
	LPC_USART->DLM = 0x00000000;

	// First set PIO:s as generic GPIO's
	// Leds as GPIO, open drain enabled, pull up resistor enabled
	LPC_IOCON->TRST_PIO0_14 = 0x1; /* F_SEG */
	LPC_IOCON->TDO_PIO0_13 = 0x1; /* G_SEG */
	LPC_IOCON->TMS_PIO0_12 = 0x1; /* DP_SEG */

	// Potentiometer as analog input.
	LPC_IOCON->TDI_PIO0_11 = 0x00000092; /* binary: 00000000_00000000_00000000_10010010 */

	// Switches as GPIO with hysteresis on with pull-up resistors
	LPC_IOCON->PIO0_1 = 0x000000F0;
	LPC_IOCON->PIO0_20 = 0x000000F0;
	LPC_IOCON->PIO0_2 = 0x000000F0;
	LPC_IOCON->PIO1_26 = 0x000000F0;
	LPC_IOCON->PIO1_27 = 0x000000F0;

	// USART PINS
	LPC_IOCON->PIO0_18 = 0x00000091; /* binary: 00000000_00000000_00000000_10010001 */
	LPC_IOCON->PIO0_19 = 0x00000091; /* binary: 00000000_00000000_00000000_10010001 */

	// GPS PINS
	LPC_IOCON->PIO0_8 = 0x00000091; /* binary: 00000000_00000000_00000000_10010001 */
	LPC_IOCON->PIO0_9 = 0x00000091; /* binary: 00000000_00000000_00000000_10010001 */
	LPC_IOCON->SWCLK_PIO0_10 = 0x00000092; /* binary: 00000000_00000000_00000000_10010010 */
	LPC_IOCON->SWDIO_PIO0_15 = 0x00000090; /* binary: 00000000_00000000_00000000_10010000 */

	// Init display
	INIT_A_SEG;
	INIT_B_SEG;
	INIT_C_SEG;
	INIT_D_SEG;
	INIT_E_SEG;
	INIT_F_SEG;
	INIT_G_SEG;
	INIT_DP_SEG;
	INIT_7SEG_CTRL_1;
	INIT_7SEG_CTRL_2;
	INIT_7SEG_CTRL_3;
	INIT_7SEG_CTRL_4;

	INIT_DEBUG_LED;
	DEBUG_LED_OFF;

	SEG_CTRL_1_OFF;
	SEG_CTRL_2_OFF;
	SEG_CTRL_3_OFF;
	SEG_CTRL_4_OFF;

	A_SEG_OFF;
	B_SEG_OFF;
	C_SEG_OFF;
	D_SEG_OFF;
	E_SEG_OFF;
	F_SEG_OFF;
	G_SEG_OFF;

	INIT_DUAL_LEDS;
	DUAL_LEDS_ON;

	INIT_POT;
	// Switches
	INIT_SW1;
	INIT_SW2;
	INIT_SW3;
	INIT_SW4;
	INIT_SW5;

	/******************************************************************************
	 GPIO pin interrupts
	 *******************************************************************************
	 GPIO pin interrupt 0 set for: P0.1 triggered with FALLING EDGE
	 GPIO pin interrupt 1 set for: P0.20 triggered with FALLING EDGE
	 GPIO pin interrupt 2 set for: P0.2 triggered with FALLING EDGE
	 GPIO pin interrupt 3 set for: P1.26 triggered with FALLING EDGE
	 GPIO pin interrupt 4 set for: P1.27 triggered with FALLING EDGE
	 */

	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 19); /* enable clock for GPIO pin interrupt (default is disabled)*/

	LPC_GPIO_PIN_INT->ISEL = 0x00000000; /* binary: 00000000_00000000_00000000_00000000 */
	LPC_GPIO_PIN_INT->IENR = 0x0000001F; /* binary: 00000000_00000000_00000000_00000000 */
	LPC_GPIO_PIN_INT->IENF = 0x00000000; /* binary: 00000000_00000000_00000000_00011111 */

	LPC_SYSCON->PINTSEL[0] = 0x00000001; /* binary: 00000000_00000000_00000000_00000001 */
	LPC_SYSCON->PINTSEL[1] = 0x00000014; /* binary: 00000000_00000000_00000000_00010100 */
	LPC_SYSCON->PINTSEL[2] = 0x00000002; /* binary: 00000000_00000000_00000000_00000010 */
	LPC_SYSCON->PINTSEL[3] = 0x00000032; /* binary: 00000000_00000000_00000000_00110010 */
	LPC_SYSCON->PINTSEL[4] = 0x00000033; /* binary: 00000000_00000000_00000000_00110011 */

	/******************************************************************************
	 Timer0(CT32B0) (32bit)
	 *******************************************************************************
	 Counter Enabled,    Counter Reset=0
	 Timer mode: count on rising edge of PCLK
	 Counter clk: 100 Hz, Counts every: 10 ms  (calculated with peripheral clock: 40MHz)
	 Clear on Rising Edge of CAP0.0
	 MCR0.0 : reset, generate interrupt on compare match
	 */

	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 9); /* Enable clock for CT32B0 (default is disabled) */

	LPC_CT32B0->CTCR = 0x10; /* binary: 00010000 */
	LPC_CT32B0->TC = 0x00000000; /* decimal 0 */
	LPC_CT32B0->PR = 0x00030D3F;     /* decimal 199999 */
	LPC_CT32B0->MCR = 0x0003; /* binary: 00000000_00000011 */
	LPC_CT32B0->MR0 = 0x00000001; /* decimal 1 */
	LPC_CT32B0->MR1 = 0x00000000; /* decimal 0 */
	LPC_CT32B0->MR2 = 0x00000000; /* decimal 0 */
	LPC_CT32B0->MR3 = 0x00000000; /* decimal 0 */
	LPC_CT32B0->CCR = 0x0000; /* binary: 00000000_00000000 */
	LPC_CT32B0->EMR = 0x0000; /* binary: 00000000_00000000 */
	LPC_CT32B0->PWMC = 0x00000000; /* binary: 00000000_00000000_00000000_00000000 */
	LPC_CT32B0->TCR = 0x01; /* binary: 00000001 */

	/******************************************************************************
	 Timer1(CT32B1) (32bit)
	 *******************************************************************************
	 Counter Enabled,    Counter Reset=0
	 Timer mode: count on rising edge of PCLK
	 Counter clk: 40 MHz, Counts every: 25 ns  (calculated with peripheral clock: 40MHz)
	 Clear on Rising Edge of CAP1.0
	 MCR1.1 : reset, generate interrupt on compare match
	 */

	LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & 0x098DFFFF)
			| (1UL << 10); /* Enable clock for CT32B1 (default is disabled) */

	LPC_CT32B1->CTCR = 0x10; /* binary: 00010000 */
	LPC_CT32B1->TC = 0x00000000; /* decimal 0 */
	LPC_CT32B1->PR = 0x00000000; /* decimal 0 */
	LPC_CT32B1->MCR = 0x0018; /* binary: 00000000_00011000 */
	LPC_CT32B1->MR0 = 0x00000000; /* decimal 0 */
	LPC_CT32B1->MR1 = 0x00000001; /* decimal 1 */
	LPC_CT32B1->MR2 = 0x00000000; /* decimal 0 */
	LPC_CT32B1->MR3 = 0x00000000; /* decimal 0 */
	LPC_CT32B1->CCR = 0x0000; /* binary: 00000000_00000000 */
	LPC_CT32B1->EMR = 0x0000; /* binary: 00000000_00000000 */
	LPC_CT32B1->PWMC = 0x00000000; /* binary: 00000000_00000000_00000000_00000000 */
	LPC_CT32B1->TCR = 0x01; /* binary: 00000001 */

	/******************************************************************************
	 Vectored Interrupt initialization
	 ******************************************************************************/

//	NVIC_SetPriority(SysTick_IRQn, 0); /* Default priority 0, can be 0(highest) - 3(lowest) */
//	NVIC_EnableIRQ(SysTick_IRQn); /* Enable System Tick Interrupt */
	NVIC_SetPriority(FLEX_INT0_IRQn, 0); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(FLEX_INT0_IRQn); /* Enable GPIO pin interrupt 0 */

	NVIC_SetPriority(FLEX_INT1_IRQn, 2); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(FLEX_INT1_IRQn); /* Enable GPIO pin interrupt 1 */

	NVIC_SetPriority(FLEX_INT2_IRQn, 2); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(FLEX_INT2_IRQn); /* Enable GPIO pin interrupt 2 */

	NVIC_SetPriority(FLEX_INT3_IRQn, 2); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(FLEX_INT3_IRQn); /* Enable GPIO pin interrupt 3 */

	NVIC_SetPriority(FLEX_INT4_IRQn, 2); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(FLEX_INT4_IRQn); /* Enable GPIO pin interrupt 4 */

	NVIC_SetPriority(TIMER_32_0_IRQn, 0); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(TIMER_32_0_IRQn); /* Enable 32-bit Timer0 (CT32B0) Interrupt */

	NVIC_SetPriority(TIMER_32_1_IRQn, 1); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(TIMER_32_1_IRQn); /* Enable 32-bit Timer1 (CT32B1) Interrupt */

	NVIC_SetPriority(UART_IRQn, 1); /* Default priority 0, can be 0(highest) - 3(lowest) */
	NVIC_EnableIRQ(UART_IRQn); /* Enable UART Interrupt */
}

void usart_senddata(char send) {
	LPC_USART->THR = send;
}
