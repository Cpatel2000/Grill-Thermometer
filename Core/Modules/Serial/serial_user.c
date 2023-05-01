// serial_user.c

#include "serial.h"
#include "serial_user.h"
#include "ASCII_numbers.h"
#include "ux_manager.h"


uint8_t packetBuffer[16];
uint8_t inPacket = false;
uint8_t nextPacketChar = 0;
uint8_t processPacket = false;
float data =0.0;

extern DWfloat humidity;
extern DWfloat tempInF;
extern char message[25];


// function to process the input buffer
uint8_t ProcessReceiveBuffer(void)
{
//  SendString((char const *)&rxBuffer[nextSerialRx2Proc], 1, StripZeros, NoAddCRLF);
  if (rxBuffer[nextSerialRx2Proc] == '$') {
    inPacket = true;
    packetBuffer[0] = rxBuffer[nextSerialRx2Proc];
    nextPacketChar = 1;
  }
  else {
    if (inPacket == true) {
      if (((rxBuffer[nextSerialRx2Proc] >= '0') && (rxBuffer[nextSerialRx2Proc] <= '9')) || 
          ((rxBuffer[nextSerialRx2Proc] >= 'r') && (rxBuffer[nextSerialRx2Proc] <= 'v')) ||
          ((rxBuffer[nextSerialRx2Proc] >= 'R') && (rxBuffer[nextSerialRx2Proc] <= 'V')) ||
          (rxBuffer[nextSerialRx2Proc] >= '\n') || (rxBuffer[nextSerialRx2Proc] <= '\r')) {
        
            packetBuffer[nextPacketChar++] = rxBuffer[nextSerialRx2Proc];

            if (rxBuffer[nextSerialRx2Proc] == '\n') {
              processPacket = true;
              inPacket = false;
            }
          }
      else {
        inPacket = false;
      }
    }
  }
  
  
  if (++nextSerialRx2Proc >= RX_BUFFER_SIZE) {
    nextSerialRx2Proc = 0;
  }
  return 0;

}


uint8_t ProcessPacket(void)
{
  switch (packetBuffer[1]) {
  // list of commands
  // each command has intentional fallthru for upper/lower case
  case 't':     // t = send new temp data
  case 'T':     
    data = 0.0;
    int k =2;
    while(packetBuffer[k] != '\n'){
      data = data*10.0;
      data += (0.1*(float)(packetBuffer[k]-'0'));
      k++;
    }
    tempInF.data = data;
    break;
  case 'm':     // m = send new message to dispaly
  case 'M':     
    for(int i= 0;i<25;i++){
      message[i] = 0;
    }
    int j =2;
    while(packetBuffer[j] != '\n'){
      message[j-2] = (char)packetBuffer[j];
      j++;
    }
    SwitchScreens(MESSAGE);
    break;
  case 'r':     // r = request humidity
  case 'R':     
    char temp[25];
    sprintf(temp, humidity.format, humidity.data);
    SendString(temp, 10, StripZeros, AddCRLF);
    break;
  }
  processPacket = false;

  return 0;
}


