/***********************************************************************************************************************
* File Name    : KeyboardHoldRepeat.c
* Version      : 
* Device(s)    : Keyboard Handler code
* Tool-Chain   : IAR Systems ARM
* Description  : This file implements support code for a keyCode that is a result of a keyboard or button scan
*              : 
* Creation Date: 10OCT2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "main.h"
#include "KeyboardHoldRepeat.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>




/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/


/***********************************************************************************************************************
Global/module variables
***********************************************************************************************************************/
extern uint8_t processKeyCode;
extern uint8_t keyCodeProcessed;

extern uint8_t Left_Button_Pressed;
extern uint8_t Right_Button_Pressed;
extern uint8_t Center_Button_Pressed;
extern uint8_t Back_Button_Pressed;

/***********************************************************************************************************************
module function prototypes
***********************************************************************************************************************/



/***********************************************************************************************************************
code start
***********************************************************************************************************************/
void ProcessKeyCode(uint8_t _kcode)
{
  
  switch (_kcode) {
  case 0x0E:  //                Left
    Left_Button_Pressed = true;
    break;
  case 0x0D:  //                Select
    Center_Button_Pressed = true;
    break;
  case 0x0B:  //                Right
    Right_Button_Pressed = true;
    break;
  case 0x07:  //                Back
    Back_Button_Pressed = true;
    break;
  default:
    break;
  }
  
  processKeyCode = false;
  keyCodeProcessed = true;
  
}



uint8_t ValidKeyCode(uint8_t _kcode)
{
  uint8_t validKeyCode = false;
  
  switch (_kcode) {
  case 0x07:  //                Back
  case 0x0E:  //                Left
  case 0x0D:  //                Center
  case 0x0B:  //                Right
    validKeyCode = true;
    break;
  default:
    break;
  }
  return validKeyCode;
}


uint8_t ScanKeyboard(void)
{
  uint8_t keyCode = NO_KEY_PRESSED;
  
  keyCode = ((HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 3) | (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) << 2) | (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) << 1 | (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) << 0)));
//  HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) << 3) |
  return keyCode;
}
