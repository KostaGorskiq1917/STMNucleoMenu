/*
 * LCDControl.h
 *
 *  Created on: Mar 20, 2025
 *      Author: drebniqv
 */

#ifndef INC_LCDCONTROL_H_
#define INC_LCDCONTROL_H_

#endif /* INC_LCDCONTROL_H_ */

#include "main.h"

#define RS_PORT RS_GPIO_Port
#define RS_PIN RS_Pin
#define RW_PORT RW_GPIO_Port
#define RW_PIN RW_Pin
#define EN_PORT EN_GPIO_Port
#define EN_PIN EN_Pin

#define D4_PORT D4_GPIO_Port
#define D4_PIN D4_Pin
#define D5_PORT D5_GPIO_Port
#define D5_PIN D5_Pin
#define D6_PORT D6_GPIO_Port
#define D6_PIN D6_Pin
#define D7_PORT D7_GPIO_Port
#define D7_PIN D7_Pin

void lcd_init (void);   // initialize lcd
void lcd_send_cmd (char cmd);  // send command to the lcd
void lcd_send_data (char data);  // send data to the lcd
void lcd_send_string (char *str);  // send string to the lcd
void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);
void lcd_clear (void);
