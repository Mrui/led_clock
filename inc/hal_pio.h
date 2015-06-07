/*
 * pin_mappings.h
 *
 *  Created on: Apr 26, 2015
 *      Author: heikkinen
 *
 *  Defines keypad pin mappings for different pcb revisions used
 *  Update: 11.5.2015,
 *  	Pin numbers corrected, 7 seg control fixed, added potentiometer.
 */

#ifndef HAL_PIO_
#define HAL_PIO_

#include "LPC11Uxx.h"

// 7 segment screen pin settings

#define A_SEG_PIN_NUMBER 		23 /* PIO0_23 */
#define INIT_A_SEG				LPC_GPIO->DIR[0] |= (1 << A_SEG_PIN_NUMBER)
#define A_SEG_ON				LPC_GPIO->SET[0] |= (1 << A_SEG_PIN_NUMBER) // Set PIN to 1 for output
#define A_SEG_OFF				LPC_GPIO->CLR[0] |= (1 << A_SEG_PIN_NUMBER) // Clear PIN, set to 0
#define A_SEG_TOGGLE			LPC_GPIO->NOT[0] |= (1 << A_SEG_PIN_NUMBER) // Toggle PIN value

#define B_SEG_PIN_NUMBER 		22 /* PIO1_22 */
#define INIT_B_SEG				LPC_GPIO->DIR[1] |= (1 << B_SEG_PIN_NUMBER)
#define B_SEG_ON				LPC_GPIO->SET[1] |= (1 << B_SEG_PIN_NUMBER)
#define B_SEG_OFF				LPC_GPIO->CLR[1] |= (1 << B_SEG_PIN_NUMBER)
#define B_SEG_TOGGLE			LPC_GPIO->NOT[1] |= (1 << B_SEG_PIN_NUMBER)

#define C_SEG_PIN_NUMBER 		13 /* PIO1_13 */
#define INIT_C_SEG				LPC_GPIO->DIR[1] |= (1 << C_SEG_PIN_NUMBER)
#define C_SEG_ON				LPC_GPIO->SET[1] |= (1 << C_SEG_PIN_NUMBER)
#define C_SEG_OFF				LPC_GPIO->CLR[1] |= (1 << C_SEG_PIN_NUMBER)
#define C_SEG_TOGGLE			LPC_GPIO->NOT[1] |= (1 << C_SEG_PIN_NUMBER)

#define D_SEG_PIN_NUMBER		13 /* PIO0_13 */
#define INIT_D_SEG				LPC_GPIO->DIR[0] |= (1 << D_SEG_PIN_NUMBER)
#define D_SEG_ON				LPC_GPIO->SET[0] |= (1 << D_SEG_PIN_NUMBER)
#define D_SEG_OFF				LPC_GPIO->CLR[0] |= (1 << D_SEG_PIN_NUMBER)
#define D_SEG_TOGGLE			LPC_GPIO->NOT[0] |= (1 << D_SEG_PIN_NUMBER)

#define E_SEG_PIN_NUMBER 		16 /* PIO0_16 */
#define INIT_E_SEG				LPC_GPIO->DIR[0] |= (1 << E_SEG_PIN_NUMBER)
#define E_SEG_ON				LPC_GPIO->SET[0] |= (1 << E_SEG_PIN_NUMBER)
#define E_SEG_OFF				LPC_GPIO->CLR[0] |= (1 << E_SEG_PIN_NUMBER)
#define E_SEG_TOGGLE			LPC_GPIO->NOT[0] |= (1 << E_SEG_PIN_NUMBER)

#define F_SEG_PIN_NUMBER 		12 /* PIO0_12 */
#define INIT_F_SEG				LPC_GPIO->DIR[0] |= (1 << F_SEG_PIN_NUMBER)
#define F_SEG_ON				LPC_GPIO->SET[0] |= (1 << F_SEG_PIN_NUMBER)
#define F_SEG_OFF				LPC_GPIO->CLR[0] |= (1 << F_SEG_PIN_NUMBER)
#define F_SEG_TOGGLE			LPC_GPIO->NOT[0] |= (1 << F_SEG_PIN_NUMBER)

#define G_SEG_PIN_NUMBER 		14 /* PIO1_14 */
#define INIT_G_SEG				LPC_GPIO->DIR[1] |= (1 << G_SEG_PIN_NUMBER)
#define G_SEG_ON				LPC_GPIO->SET[1] |= (1 << G_SEG_PIN_NUMBER)
#define G_SEG_OFF				LPC_GPIO->CLR[1] |= (1 << G_SEG_PIN_NUMBER)
#define G_SEG_TOGGLE			LPC_GPIO->NOT[1] |= (1 << G_SEG_PIN_NUMBER)

#define DP_SEG_PIN_NUMBER		15 /* PIO1_12 */
#define INIT_DP_SEG				LPC_GPIO->DIR[1] |= (1 << DP_SEG_PIN_NUMBER)
#define DP_SEG_ON				LPC_GPIO->SET[1] |= (1 << DP_SEG_PIN_NUMBER)
#define DP_SEG_OFF				LPC_GPIO->CLR[1] |= (1 << DP_SEG_PIN_NUMBER)
#define DP_SEG_TOGGLE			LPC_GPIO->NOT[1] |= (1 << DP_SEG_PIN_NUMBER)

#define SEG_CTRL_1_PIN_NUMBER	19 /* PIO1_19 */
#define INIT_7SEG_CTRL_1		LPC_GPIO->DIR[1] |= (1 << SEG_CTRL_1_PIN_NUMBER)
#define SEG_CTRL_1_OFF			LPC_GPIO->SET[1] |= (1 << SEG_CTRL_1_PIN_NUMBER)
#define SEG_CTRL_1_ON			LPC_GPIO->CLR[1] |= (1 << SEG_CTRL_1_PIN_NUMBER)
#define SEG_CTRL_1_TOGGLE		LPC_GPIO->NOT[1] |= (1 << SEG_CTRL_1_PIN_NUMBER)

#define SEG_CTRL_2_PIN_NUMBER	25 /* PIO1_25 */
#define INIT_7SEG_CTRL_2		LPC_GPIO->DIR[1] |= (1 << SEG_CTRL_2_PIN_NUMBER)
#define SEG_CTRL_2_OFF			LPC_GPIO->SET[1] |= (1 << SEG_CTRL_2_PIN_NUMBER)
#define SEG_CTRL_2_ON			LPC_GPIO->CLR[1] |= (1 << SEG_CTRL_2_PIN_NUMBER)
#define SEG_CTRL_2_TOGGLE		LPC_GPIO->NOT[1] |= (1 << SEG_CTRL_2_PIN_NUMBER)

#define SEG_CTRL_3_PIN_NUMBER	16 /* PIO1_16 */
#define INIT_7SEG_CTRL_3		LPC_GPIO->DIR[1] |= (1 << SEG_CTRL_3_PIN_NUMBER)
#define SEG_CTRL_3_OFF			LPC_GPIO->SET[1] |= (1 << SEG_CTRL_3_PIN_NUMBER)
#define SEG_CTRL_3_ON			LPC_GPIO->CLR[1] |= (1 << SEG_CTRL_3_PIN_NUMBER)
#define SEG_CTRL_3_TOGGLE		LPC_GPIO->NOT[1] |= (1 << SEG_CTRL_3_PIN_NUMBER)

#define SEG_CTRL_4_PIN_NUMBER	14 /* PIO0_14 */
#define INIT_7SEG_CTRL_4		LPC_GPIO->DIR[0] |= (1 << SEG_CTRL_4_PIN_NUMBER)
#define SEG_CTRL_4_OFF			LPC_GPIO->SET[0] |= (1 << SEG_CTRL_4_PIN_NUMBER)
#define SEG_CTRL_4_ON			LPC_GPIO->CLR[0] |= (1 << SEG_CTRL_4_PIN_NUMBER)
#define SEG_CTRL_4_TOGGLE		LPC_GPIO->NOT[0] |= (1 << SEG_CTRL_4_PIN_NUMBER)

#define DUAL_LEDS_PIN_NUMBER 	20 /* PIO1_20 */
#define INIT_DUAL_LEDS			LPC_GPIO->DIR[1] |= (1 << DUAL_LEDS_PIN_NUMBER)
#define DUAL_LEDS_ON			LPC_GPIO->SET[1] |= (1 << DUAL_LEDS_PIN_NUMBER)
#define DUAL_LEDS_OFF			LPC_GPIO->CLR[1] |= (1 << DUAL_LEDS_PIN_NUMBER)
#define DUAL_LEDS_TOGGLE		LPC_GPIO->NOT[1] |= (1 << DUAL_LEDS_PIN_NUMBER)

#define DEBUG_LED_PIN_NUMBER 	31 /* PIO1_24 */
#define INIT_DEBUG_LED			LPC_GPIO->DIR[1] |= (1 << DEBUG_LED_PIN_NUMBER)
#define DEBUG_LED_ON			LPC_GPIO->SET[1] |= (1 << DEBUG_LED_PIN_NUMBER)
#define DEBUG_LED_OFF			LPC_GPIO->CLR[1] |= (1 << DEBUG_LED_PIN_NUMBER)
#define DEBUG_LED_TOGGLE		LPC_GPIO->NOT[1] |= (1 << DEBUG_LED_PIN_NUMBER)

#define GPS_RST_PIN_NUMBER 		29 /* PIO1_29 */
#define INIT_GPS_RST			LPC_GPIO->DIR[1] |= (1 << GPS_RST_PIN_NUMBER)
#define GPS_RST					LPC_GPIO->SET[1] |= (1 << GPS_RST_PIN_NUMBER)

#define GPS_ON_OFF_PIN_NUMBER 	22 /* PIO0_22 */
#define INIT_GPS_ON_OFF			LPC_GPIO->DIR[0] |= (1 << GPS_ON_OFF_PIN_NUMBER)
#define GPS_ON					LPC_GPIO->SET[0] |= (1 << GPS_ON_OFF_PIN_NUMBER)
#define GPS_OFF 				LPC_GPIO->CLR[0] |= (1 << GPS_ON_OFF_PIN_NUMBER)

//Potentiometer
#define POT_PIN_NUMBER			11 /* PIO0_11 */
#define INIT_POT				LPC_GPIO->DIR[0] |= (1 << POT_PIN_NUMBER)
#define POT_DATA				LPC_GPIO->B0[POT_PIN_NUMBER]

//buttons are active low
#define SW1_PIN_NUMBER		1 /* PIO0_1 debug on board */
#define SW1_DATA			LPC_GPIO->B0[SW2_PIN_NUMBER]
#define INIT_SW1			LPC_GPIO->DIR[0] &= ~(1 << SW1_PIN_NUMBER)

#define SW2_PIN_NUMBER		20 /* PIO0_20 */
#define SW2_DATA			LPC_GPIO->B0[SW2_PIN_NUMBER]
#define INIT_SW2			LPC_GPIO->DIR[0] &= ~(1 << SW2_PIN_NUMBER)

#define SW3_PIN_NUMBER 		2 /* PIO0_2 fourth from left (minutes)*/
#define SW3_DATA			LPC_GPIO->B0[SW3_PIN_NUMBER]
#define INIT_SW3			LPC_GPIO->DIR[0] &= ~(1 << SW3_PIN_NUMBER)

#define SW4_PIN_NUMBER 		26 /* PIO1_26 first from left */
#define SW4_DATA			LPC_GPIO->B1[SW4_PIN_NUMBER]
#define INIT_SW4			LPC_GPIO->DIR[1] &= ~(1 << SW4_PIN_NUMBER)

#define SW5_PIN_NUMBER 		27 /* PIO1_27 third from left */
#define SW5_DATA			LPC_GPIO->B1[SW5_PIN_NUMBER]
#define INIT_SW5			LPC_GPIO->DIR[1] &= ~(1 << SW5_PIN_NUMBER)

#endif // HAL_PIO
