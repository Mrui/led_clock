/*
 * 7seg.h
 *
 *  Created on: 11.5.2015
 *      Author: mrui
 */

#ifndef SEG_H_
#define SEG_H_

void show1 ();
void show2 ();
void show3 ();
void show4 ();
void show5 ();
void show6 ();
void show7 ();
void show8 ();
void show9 ();
void show0 ();

void chooseScreen(uint8_t screen);
void showMinute1(uint8_t minute);
void showMinute2(uint8_t minute);
void showHour1(uint8_t hour);
void showHour2(uint8_t hour);

#endif /* 7SEG_H_ */
