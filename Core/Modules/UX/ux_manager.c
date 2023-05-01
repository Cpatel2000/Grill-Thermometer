// ux_manager.c

 

 

#include "main.h"

#include "ux_manager.h"

#include <stdio.h>

 

// private defines

#define TOTAL_MEALS 3

 

// Global Constants

 

 

// Modular Constants

 

 

// global variables

 

extern uint8_t beepActive;

 

uint8_t COOKING = false;

 

// Screens

ui_screen currentScreen;

ui_screen lastScreen;

ui_screen screenNumber;

extern uint8_t Timer;

 

Cooking_Meal MEAL_1 = {

    .Meal_Name = {"%s", "!!!!", 0, 0, true, "Burger"},

    .Final_Temp = 140

};

Cooking_Meal MEAL_2 = {

    .Meal_Name = {"%s", "!!!!", 0, 0, true, " Paneer "},

    .Final_Temp = 170

};

Cooking_Meal MEAL_3 = {

    .Meal_Name = {"%s", "!!!!", 0, 0, true, "   Tea   "},

    .Final_Temp = 110

};

 

Cooking_Meal Meal_Book[TOTAL_MEALS];

Cooking_Meal Current_Meal = {0};

uint8_t Meal_No = 0;

 

char message[25] = "";

 

// Display-wrapped values

// format seq (numeric): {<format string>, <error message>, <Xpos>, <Ypos>, <valid?>, <init value>}

DWfloat counter = {"%5.2f", "----", 0, 0, true, 0};

DWfloat tempInF = {"%4.1f", "----", 0, 0, true, 72.3};

DWint16_t Meal_F = {"%3d", "!!!!", 0,0, true, 0};



 

DWint8_t Seconds = {"%2d", "----", 0, 0, true, 0};

DWint8_t Minutes = {"%2d", "----", 0, 0, true, 0};

DWint8_t Hours   = {"%2d", "----", 0, 0, true, 0};

 

 

// modular variables

 

 

// module prototypes

 

 

 

// ***************

// Start Of Code

// ***************

// Screen switching utility that manages pre-, post-, and screen switch conditions

void SwitchScreens(ui_screen screen_no)

{

  lastScreen = currentScreen;

 

 

#pragma diag_suppress= Pa149

  // what must be done before current screen is switched out

  switch (lastScreen) {

  }

 

  

  // what must be done before screen is switched in

  switch (screen_no) {

  }

#pragma diag_warning= Pa149

 

  // Switch the screens

  switch (screen_no) {

    case STARTUP_SCREEN:

      SSD1306_GotoXY (0,0);

      SSD1306_Puts ("WELCOME :)", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 30);

      SSD1306_Puts ("Namaste", &Font_7x10, SSD1306_COLOR_WHITE);

      //SSD1306_Puts ("Salmonella is bad.", &Font_7x10, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 50);

      SSD1306_Puts ("  what's cookin ", &Font_7x10, SSD1306_COLOR_WHITE);

      break;

    case MAIN:

      // clear the screen from the previos dispayed data

      SSD1306_Clear();

      // Put up the "persistant" info (like data labels)

      SSD1306_GotoXY (0,0);

      SSD1306_Puts ("PLEASE SELECT", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 30);

      SSD1306_Puts ("NEXT>>>", &Font_7x10, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 50);

      //SSD1306_Puts ("<= Custom Cook", &Font_7x10, SSD1306_COLOR_WHITE);

 

      tempInF.xPos = 55;

      tempInF.yPos = 30;

      break;

    case MEAL_LIST:

      Meal_Book[0] = MEAL_1;

      Meal_Book[1] = MEAL_2;

      Meal_Book[2] = MEAL_3;

      SSD1306_GotoXY (0,0);

      SSD1306_Puts ("CHOOSE MEAL", &Font_11x18, SSD1306_COLOR_WHITE);

      if(Meal_No == 0){

        SSD1306_GotoXY (0, 50);

        SSD1306_Puts ("           Next =>", &Font_7x10, SSD1306_COLOR_WHITE);

      }

      else if (Meal_No == (TOTAL_MEALS-1)){

        SSD1306_GotoXY (0, 50);

        SSD1306_Puts ("<<<Back          ", &Font_7x10, SSD1306_COLOR_WHITE);

      }

      else{

        SSD1306_GotoXY (0, 50);

        SSD1306_Puts ("<<<Back   Next >>>", &Font_7x10, SSD1306_COLOR_WHITE);

      }

      break;

    case CUSTOM_COOK:

      break;

     //18 letter max

    case COOKING_READY:

      SSD1306_Clear();

      SSD1306_Clear();

      SSD1306_GotoXY (0,0);

      SSD1306_Puts ("Yummy", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 30);

      SSD1306_Puts ("Press The Key", &Font_7x10, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 50);

      SSD1306_Puts ("To View Temp", &Font_7x10, SSD1306_COLOR_WHITE);

      break;

    case COOKING_TEMP:

      SSD1306_Clear();

      SSD1306_GotoXY (0,0);

      SSD1306_Puts (" Meal Temp ", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 30);

      SSD1306_Puts ("MEAL: ", &Font_7x10, SSD1306_COLOR_WHITE);

      Meal_F.xPos = 32;

      Meal_F.yPos = 30;

      

      break;

    
     case COOKING_COMPLETE:

      beepActive = true;

      SSD1306_Clear();

      SSD1306_GotoXY (0,0);

      SSD1306_Puts (" Meal Cooked ", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 30);

      SSD1306_Puts (" Press any key to ", &Font_7x10, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (0, 50);

      SSD1306_Puts ("   stop Beeper   ", &Font_7x10, SSD1306_COLOR_WHITE);

      break;

    default:

      break;

  }

/*

  case MESSAGE:

    SSD1306_Clear();

    SSD1306_GotoXY (0,0);

    SSD1306_Puts ("Message", &Font_11x18, SSD1306_COLOR_WHITE);

    count.xPos = 60;

    count.yPos = 40;

    break;

  }*/

  currentScreen = screen_no;

  SSD1306_UpdateScreen();

  //Timer = 0;

 

#pragma diag_suppress= Pa149

  // what must be done after screen is switched in

  switch (currentScreen) {

  }

#pragma diag_warning= Pa149

 

}

 

 

//// Keyboard Processor

//

//uint8_t ProcessKeyCode (uint16_t key_code)

//{

//  switch (key_code) {

//  case 0:

//    break;

//  case 1:

//    break;

//  case 2:

//    break;

//  case 3:

//    break;

//  }

// 

//  return true;

//}

 

 

// context sensitive keyboard processor

//0x0E: LEFT

//0x0D: SELECT

//0x0B: RIGHT

//0x07: BACK

uint8_t ProcessKeyCodeInContext (uint16_t key_code)

{

  switch (currentScreen) {

  case  MAIN:

    switch (key_code) {

    case 0x0E:

      //SwitchScreens(CUSTOM_COOK);

      break;

    case 0x0D:

      break;

    case 0x0B:

      SSD1306_Clear();

      Current_Meal = MEAL_1;

      SwitchScreens(MEAL_LIST);

      break;

    case 0x07:

      SwitchScreens(MAIN);

      break;

    }

    break;

  case  MEAL_LIST:

    switch (key_code) {

    case 0x0E:

      if(Meal_No){

        Meal_No--;

        Current_Meal = Meal_Book[Meal_No];

        SwitchScreens(MEAL_LIST);

      }

      break;

    case 0x0D:

      SwitchScreens(COOKING_READY);

      break;

    case 0x0B:

      if(Meal_No != (TOTAL_MEALS-1)){

        Meal_No++;

        Current_Meal = Meal_Book[Meal_No];

        SwitchScreens(MEAL_LIST);

      }

      break;

    case 0x07:

      SwitchScreens(MAIN);

      break;

    }

    break;

   case  CUSTOM_COOK:

    switch (key_code) {

    case 0x0E:

      //[INTENTIONALLY EMPTY]

      break;

    case 0x0D:

      //[CUSTOM COOK LOGIC]

      break;

    case 0x0B:

      SwitchScreens(MAIN);

      break;

    case 0x07:

      SwitchScreens(MAIN);

      break;

    }

    break;

   case  COOKING_READY:

    switch (key_code) {

    case 0x0E:

    case 0x0D:

    case 0x0B:

      COOKING = true;

     

      SwitchScreens(COOKING_TEMP);

      break;

    case 0x07:

      SwitchScreens(MAIN);

      break;

    }

    break;

   case  COOKING_TEMP:

    switch (key_code) {

    case 0x0E:

      
    case 0x0D:

      SwitchScreens(COOKING_TEMP);

      break;

    case 0x0B:

    

    case 0x07:

  

    break;
    }
   

   


    break;

   case COOKING_COMPLETE:

     beepActive = false;

     //STOP_COOKING_TIMER

     COOKING = false;

     SwitchScreens(MAIN);

     break;

  }

 

  return true;

}

 

 

 

void UpdateScreenValues(void)

{

  if(COOKING && Meal_F.data >= (Current_Meal.Final_Temp - 3)) {

    SwitchScreens(COOKING_COMPLETE);

  }

  float progress;

  char displayString[25];

    switch (currentScreen) {

    case STARTUP_SCREEN:

      break;

    case MAIN:

      break;

    case MEAL_LIST:

      SSD1306_GotoXY(0,25);

      sprintf(displayString, Current_Meal.Meal_Name.format, Current_Meal.Meal_Name.data);

      SSD1306_Puts(Current_Meal.Meal_Name.data, &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_UpdateScreen();

      break;

    case CUSTOM_COOK:

      break;

    case COOKING_READY:

      break;

    case COOKING_TEMP:

      sprintf(displayString, Meal_F.format, Meal_F.data);

      SSD1306_GotoXY(Meal_F.xPos,Meal_F.yPos);

      SSD1306_Puts(displayString, &Font_7x10, SSD1306_COLOR_WHITE);

      
      SSD1306_UpdateScreen();

      break;

    
    

    }

    //SSD1306_UpdateScreen(); //display

}

  /*

    case SETTINGS:

      SSD1306_GotoXY (0,40);

      SSD1306_Puts("DegF", &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_UpdateScreen();

      break;

    case MESSAGE:

      SSD1306_GotoXY (0,20);

      SSD1306_Puts(message, &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_GotoXY (count.xPos,count.yPos);

      sprintf(displayString, count.format, count.data);

      SSD1306_Puts(displayString, &Font_11x18, SSD1306_COLOR_WHITE);

      SSD1306_UpdateScreen();

      break;

    }

      if (counter.valid) {

        sprintf(displayString, counter.format, counter.data);

        SSD1306_Puts(displayString, &Font_11x18, SSD1306_COLOR_WHITE);

      }*/