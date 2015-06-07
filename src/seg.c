/*
 * 7seg.c
 *
 *  Created on: 11.5.2015
 *      Author: heikkinen
 */

#include "hal_pio.h"
#include "seg.h"



void show1(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		B_SEG_ON;
		break;
	case 1:
		C_SEG_ON;
		break;
//	case 2:
//		break;
//	case 3:
//		break;
//	case 4:
//		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show2(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		G_SEG_ON;
		break;
	case 3:
		E_SEG_ON;
		break;
	case 4:
		D_SEG_ON;
		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show3(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		G_SEG_ON;
		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show4(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		F_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		G_SEG_ON;
		break;
//	case 4:
//		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show5(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		F_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		G_SEG_ON;
		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show6(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		F_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		G_SEG_ON;
		break;
	case 5:
		E_SEG_ON;
		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show7(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
//	case 3:
//		break;
//	case 4:
//		break;
//	case 5:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show8(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		E_SEG_ON;
		break;
	case 5:
		F_SEG_ON;
		break;
	case 6:
		G_SEG_ON;
		break;
//	case 7:
//		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show9(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		G_SEG_ON;
		break;
	case 5:
		F_SEG_ON;
		break;
	default:
		p[choose] = 0;
		break;
	}
}
void show0(int choose) {
	static int p[4] = {0, 0, 0, 0};
	switch (p[choose]++) {
	case 0:
		A_SEG_ON;
		break;
	case 1:
		B_SEG_ON;
		break;
	case 2:
		C_SEG_ON;
		break;
	case 3:
		D_SEG_ON;
		break;
	case 4:
		E_SEG_ON;
		break;
	case 5:
		F_SEG_ON;
		break;
	default:
		p[choose] = 0;
		break;
	}
}

void showScreen(uint8_t screen){
	switch(screen) {
	case 1:
		SEG_CTRL_1_ON;
		SEG_CTRL_2_OFF;
		SEG_CTRL_3_OFF;
		SEG_CTRL_4_OFF;
		break;
	case 2:
		SEG_CTRL_1_OFF;
		SEG_CTRL_2_ON;
		SEG_CTRL_3_OFF;
		SEG_CTRL_4_OFF;
		break;
	case 3:
		SEG_CTRL_1_OFF;
		SEG_CTRL_2_OFF;
		SEG_CTRL_3_ON;
		SEG_CTRL_4_OFF;
		break;
	case 4:
		SEG_CTRL_1_OFF;
		SEG_CTRL_2_OFF;
		SEG_CTRL_3_OFF;
		SEG_CTRL_4_ON;
		break;
	default:
		SEG_CTRL_1_OFF;
		SEG_CTRL_2_OFF;
		SEG_CTRL_3_OFF;
		SEG_CTRL_4_OFF;
		break;
	}
}

void showMinute2(uint8_t minute) {
	A_SEG_OFF;
	B_SEG_OFF;
	C_SEG_OFF;
	D_SEG_OFF;
	E_SEG_OFF;
	F_SEG_OFF;
	G_SEG_OFF;
	DP_SEG_OFF;
	showScreen(1);
	switch (minute) {
	case 0:
		show0(0);
		break;
	case 1:
		show1(0);
		break;
	case 2:
		show2(0);
		break;
	case 3:
		show3(0);
		break;
	case 4:
		show4(0);
		break;
	case 5:
		show5(0);
		break;
	case 6:
		show6(0);
		break;
	case 7:
		show7(0);
		break;
	case 8:
		show8(0);
		break;
	case 9:
		show9(0);
		break;
	default:
		break;
	}
}

void showMinute1(uint8_t minute){
	A_SEG_OFF;
	B_SEG_OFF;
	C_SEG_OFF;
	D_SEG_OFF;
	E_SEG_OFF;
	F_SEG_OFF;
	G_SEG_OFF;
	DP_SEG_OFF;
	showScreen(2);
	switch (minute) {
	case 0:
		show0(1);
		break;
	case 1:
		show1(1);
		break;
	case 2:
		show2(1);
		break;
	case 3:
		show3(1);
		break;
	case 4:
		show4(1);
		break;
	case 5:
		show5(1);
		break;
	case 6:
		show6(1);
		break;
	case 7:
		show7(1);
		break;
	case 8:
		show8(1);
		break;
	case 9:
		show9(1);
		break;
	default:
		break;
	}
}

void showHour1(uint8_t hour){
	A_SEG_OFF;
	B_SEG_OFF;
	C_SEG_OFF;
	D_SEG_OFF;
	E_SEG_OFF;
	F_SEG_OFF;
	G_SEG_OFF;
	DP_SEG_OFF;
	showScreen(3);
	switch (hour) {
	case 0:
		show0(2);
		break;
	case 1:
		show1(2);
		break;
	case 2:
		show2(2);
		break;
	case 3:
		show3(2);
		break;
	case 4:
		show4(2);
		break;
	case 5:
		show5(2);
		break;
	case 6:
		show6(2);
		break;
	case 7:
		show7(2);
		break;
	case 8:
		show8(2);
		break;
	case 9:
		show9(2);
		break;
	default:
		break;
	}
}

void showHour2(uint8_t hour){
	A_SEG_OFF;
	B_SEG_OFF;
	C_SEG_OFF;
	D_SEG_OFF;
	E_SEG_OFF;
	F_SEG_OFF;
	G_SEG_OFF;
	DP_SEG_OFF;
	showScreen(4);
	switch (hour) {
	case 0:
		show0(3);
		break;
	case 1:
		show1(3);
		break;
	case 2:
		show2(3);
		break;
	case 3:
		show3(3);
		break;
	case 4:
		show4(3);
		break;
	case 5:
		show5(3);
		break;
	case 6:
		show6(3);
		break;
	case 7:
		show7(3);
		break;
	case 8:
		show8(3);
		break;
	case 9:
		show9(3);
		break;
	default:
		break;
	}
}
