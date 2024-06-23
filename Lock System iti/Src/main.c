/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mina Saad
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

//----------------------------------<Include>
#include "Stm32f103c6_GPIO_Driver.h"
#include "Stm32f103x6.h"
#include "Keypad.h"
#include "LCD.h"
#include "_7_Segment.h"

//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//--------------------------*                     Generic Macros                    *------------------------------
//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

#define Motor_Pin GPIO_PIN_15
#define Motor_Port GPIOB

#define Buzzer_Pin GPIO_PIN_15
#define Buzzer_Port GPIOA

#define Reset_Pin GPIO_PIN_1
#define Reset_Port GPIOB

#define Mode_Pin GPIO_PIN_7
#define Mode_Port GPIOB

//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//--------------------------*                 Generic variables                     *------------------------------
//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
extern uint32_t _7_Segment[10];

//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//--------------------------*                 Generic Function                     *------------------------------
//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*


//===============================<_delay_ms Function>
void _delay_ms(uint32_t Time )
{
	uint32_t i, j;
	for(i = 0;i < 100;i++)
	for(j = 0;j < 150;j++);
}

//===============================<Clock_Init Function>
void Clock_Init()
{
	//Enable Clocks
	E_GPIOA_CLK();
	E_GPIOB_CLK();
}

/*                                             ============================
 *============================================*        Main Implement      *============================================
 *                                             ============================
 */
int main(void)
{
	int Count = 0, Flag = 1, i = 0, Faild_Num = 0, Flag_2 = 1;
	GPIO_Config_t Pin;
	char Password[15] = "292003", Character;               /*The Password*/

	Clock_Init();                                          /*Clock init*/
	LCD_GPIO_Init();                                       /*LCD GPIO init*/
	_7_Segment_GPIO_Init();                                /*_7_Segment init*/
	Keypad_GPIO_Init();                                    /*Keypad GPIO init*/
    LCD_Init();                                            /*LCD Init*/

	//==========Init Motor Pin
	Pin.GPIO_PinNumber = GPIO_PIN_15;
	Pin.GPIO_Output_SPEED = GPIO_OUTPUT_SPEED_10M;
	Pin.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_INIT(GPIOB, &Pin);

	//==========Init Mode Pin
	Pin.GPIO_PinNumber = GPIO_PIN_7;
	Pin.GPIO_Output_SPEED = GPIO_OUTPUT_SPEED_10M;
	Pin.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_INIT(GPIOB, &Pin);

	//==========Reset Mode Pin
	Pin.GPIO_PinNumber = GPIO_PIN_1;
	Pin.GPIO_Output_SPEED = GPIO_OUTPUT_SPEED_10M;
	Pin.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_INIT(GPIOB, &Pin);

	//==========Buzzer Pin
	Pin.GPIO_PinNumber = GPIO_PIN_15;
	Pin.GPIO_Output_SPEED = GPIO_OUTPUT_SPEED_10M;
	Pin.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_INIT(GPIOA, &Pin);

	while (1)
	{
		/*******************************Lock system implementation********************************/
		Enter_C_Check();                                       /*Check if he select C/on*/
		Flag_2 = 1;
		LCD_Send_Command(Display_on_Cursor_on);                /*Display_on_Cursor_on*/
		while (Flag_2)
		{
			LCD_Send_string("password:");                      /*Print Password*/
			LCD_Send_Command(Cursor_in_begining_of_Line_2);    /*Go to Second Line*/
			LCD_Send_string("         ");                      /*Print Spaces*/
			while (Flag)
			{
				Character = Keypad_Selected_char();
				switch (Character)
				{

				case 'N':           /*No character is Selected*/
					break;
					//==============
				case '=':           /*Finish from Entering password*/

					Flag = 0;
					break;
					//==============
				default:            /*Write character on screen*/
					LCD_Send_char(Character);
					if (Character == Password[i])
					{
						Count++;
					}
					i++;
					while (Keypad_Selected_char() == Character)
						;
					break;
					//==============
				}
			}
			LCD_Send_Command(Clear_Display);
			if (Count == 6)
			{
				/************************Printing Password is Correct**************************/
				LCD_Send_string("Password is");
				LCD_Send_Command(Cursor_in_begining_of_Line_2);     /*Go to Second Line*/
				LCD_Send_string("         Correct");
				_delay_ms(5);
				LCD_Send_Command(Clear_Display);                    /*Clear Display*/
				Character = '0';
				while (Character != '1' && Character != '2')
				{
					LCD_Send_string("Choose Mode:");                /*Print Question*/
					_delay_ms(5);
					LCD_Send_Command(Clear_Display);                /*Clear Display*/
					LCD_Send_string("1) Get out Fast");             /*Print First Mode*/
					LCD_Send_Command(Cursor_in_begining_of_Line_2); /*Go to Second Line*/
					LCD_Send_string("2) Resident");                 /*Print second Mode*/
					_delay_ms(5);
					LCD_Send_Command(Clear_Display);                /*Clear Display*/
					LCD_Send_string("Your Choice : ");              /*User answer*/
					Flag = 1;
					while (Flag)
					{
						Character = Keypad_Selected_char();         /*Get Mode*/
						switch (Character)
						{
						case 'N':
							break;
						default:
							Flag = 0;
							LCD_Send_char(Character);
							while (Character == Keypad_Selected_char());
						}
					}
					if (Character == '1')
					{
						MCAL_GPIO_WritePin(GPIOB, LOW, GPIO_PIN_14);  /*Mode_1*/

					} else if (Character == '2')
					{
						MCAL_GPIO_WritePin(GPIOB, HIGH, GPIO_PIN_14);  /*Mode_2*/
					} else
					{
						LCD_Send_Command(Clear_Display);               /*Clear Display*/
						LCD_Send_string("Wrong Choice");
						_delay_ms(1);
					}
					LCD_Send_Command(Clear_Display);                   /*Clear Display*/

				}
				Flag_2 = 0;
				MCAL_GPIO_WritePin(Motor_Port, HIGH, Motor_Pin);       /*Turn Motor on*/
				MCAL_GPIO_WritePin(Reset_Port, HIGH, Reset_Pin);       /*Init Reset*/
				LCD_Send_string("WaitinG...");
                LCD_Send_Command(Display_on_Cursor_off);               /*Cursor off*/
                _delay_ms(40);
				MCAL_GPIO_WritePin(Motor_Port, LOW, Motor_Pin);        /*Turn Motor off*/
				Enter_C_Check();                                       /*Check if he select C/on*/
				MCAL_GPIO_WritePin(Reset_Port, LOW, Reset_Pin);        /*Reset on/
				MCAL_GPIO_WritePin(Mode_Port, LOW, Mode_Pin);          /*Turn Modes off*/

			} else
			{
				/************************Printing Password is Wrong***************************/
				LCD_Send_string("Password is");
				LCD_Send_Command(Cursor_in_begining_of_Line_2);         /*Go to Second Line*/
				LCD_Send_string("       WronG");
				_delay_ms(5);
				Faild_Num++;
				_7_Segment_Display(Faild_Num);
				if (Faild_Num == 3)
				{
					_delay_ms(20);
					MCAL_GPIO_WritePin(Buzzer_Port, HIGH, Buzzer_Pin);   /*Buzzer on*/
					_delay_ms(100);
					MCAL_GPIO_WritePin(Buzzer_Port, LOW, Buzzer_Pin);    /*Buzzer off*/
					MCAL_GPIO_Set_Output_Particular(GPIOB, 0xEf << 8);   /*Clean 7_segment*/
					Faild_Num = 0;
				}
			}
			i = 0;
			Count = 0;
			Flag = 1;
			LCD_Send_Command(Clear_Display);                             /*Clear Display*/

		}
	}

	return 0;
}

//===================================================================
//(_   _)( )                   ( )       ( )   ( )               ( )
//  | |  | |__    ____   ___   | |/ )     \ \_/ /  ___    _   _  | |
//  | |  |  _  \ / _  )/  _  \ | | <        \ /   /   \  ( ) ( ) | |
//  | |  | | | |( (_| || ( ) | | |\ \       | |  ( (_) ) | (_) | | |
//  (_)  (_) (_) \___ )(_) (_) (_) (_)      (_)   \___/   \___/  (_)

