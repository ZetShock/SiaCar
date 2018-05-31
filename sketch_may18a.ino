
//#include "qfixDynamixelBoard.h"
#define PREPROCESS_DEBUG 0x1
#define EBOARD_BLUETOOTH 0x1
#define PIN_BLUETOOTH_STATE 9
#define PIN_BLUETOOTH_RX 9
#define PIN_BLUETOOTH_TX 11
#define EBOARD_DEBUG_SPEED 38400
#define EBOARD_CHECK_PINS 0x0
#define EBOARD_CHECK_PINS_PWM 0x0
#include <eBoard.h>
SoccerBoard board;
String endCommand;
// // RX | TX
int regel = 0;
int main() {
  int regel = 0;
  SoftwareSerial BTSerial(9, 11);
  BTSerial.begin(19200);
  pinMode(PIN_MOTOR_DIR, OUTPUT);
  //_servoHandler.begin();
  for(int i = 0; i  < 200; i++) {
       board.motor(1,150);
       board.motor(2,150);
       delay(10);
  }
  for (;;) {
    //Serial.println("AAAAAAAAAAAAAAA");
    //char_array[0] = BTSerial.read();   //length = char_array.length + 1;

    int Command = BTSerial.read();
    if (Command >= 0) {
      Serial.println(Command);
      Serial.println();

      if (Command < 21) { //Geschwindigkeit Command=10: 0
        board.motor(0, (Command - 10) * 20);
        digitalWrite(PIN_MOTOR_DIR, Command < 10);

      }
      else if (Command > 28 && Command < 32) { //Lenkung 31: Rechts | 30 Mitte | 29 Links
        board.motor(1,-(Command-31)*30 + 120);
        board.motor(2,-(Command-31)*30 + 120);
      }
      else { //Fehlerhafte Command: Stillstand
        board.motor(0, 0);

      }
    }
  }
}

/*
     case 29:
       board.motor(1,180);
       board.motor(2,180);
     break;
     case 30:
       board.motor(1,150);
       board.motor(2,150);
     break;
     case 31:
       board.motor(1,120);
       board.motor(2,120);
     break;
*/
/*regel=0;

  lcd.clear();

  if(board.analog(4) >15)
   regel = regel+1;

  if(board.analog(3) >30)
   regel = regel+2;
  if(board.analog(2) >15)
   regel = regel+4;


  switch(regel)
  {
   case 0:
     servoL.setPosition(511);
     servoR.setPosition(512);
     board.motor(0, 125);
     board.msleep(20); break;

   case 1:
     servoL.setPosition(724);
     servoR.setPosition(724);
     board.motor(0, 125);
     board.msleep(20); break;

   case 3:
     servoL.setPosition(724);
     servoR.setPosition(724);
     board.motor(0, 125);
     board.msleep(20); break;
   case 2:
   case 4:
     servoL.setPosition(300);
     servoR.setPosition(300);
     board.motor(0, 125);
     board.msleep(20); break;
   case 5:
   case 6:
     servoL.setPosition(724);
     servoR.setPosition(724);
     board.motor(0, 125);
     board.msleep(20); break;

   case 7:

     if(board.analog(5) >100)
       board.motorsOff();

     else
     {
       servoL.setPosition(512);
       servoR.setPosition(511);
       board.motor(0, -125);
       board.msleep(500); break;
     }
   default:
      board.motorsOff();
  }
     break;
     case 24:
       board.motorsOff();          //Notaus
     break;
     case 25:
                                   //Rücklichter an/aus
     break;
     case 26:
                                   //7Frontlichter an/aus
     break;
     case 27
                                   //Objekt finden
     break;
     case 28
     break;
     case 29:
     break;
     case 30:
       servoL.setPosition(724)
       servoR.setPosition(724)
     break;
     case 31:
       servoL.setPosition(511)
       servoR.setposition(512)
     break;
     case 32:
       servoL.setPosition(300)
       servoR.setPosition(300)
     break;*/
