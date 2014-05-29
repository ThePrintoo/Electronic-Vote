/**********************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Electronic_Vote.ino
* Dependencies:    CapacitiveSensor.h, YNDISPLAY.h
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Vote counter based on capacitive touch and 
* Ynvisible Electrochromic Displays
**********************************************************************/

#include <CapacitiveSensor.h>
#include "YNDISPLAY.h"        //insert Ynvisible library in the same folder

unsigned int i=0, j=0;
const int num_displays=2;
int data[num_displays];
YNDISPLAY Display(num_displays); //initialize an instance of the class

CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10M resistor between pins 4 & 5, pin 5 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil if desired

void setup() 
{     
  cs_4_5.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an exampl
  cs_4_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an exampl
  Display.init(9,11,8,13,12);                   //initialize (int latchPinIN,int clockPinIN,int dataPinIN,int enPinIN,int en_regPinIN)                        
  Display.update(0,'d',2,data);
  Display.update(0,'i',1,data);
  Display.refresh(data); 
  Display.clean(2000);                          //Initial update time - restart to Zero
}


void loop() 
{
  long start = millis();
  long total1 =  cs_4_5.capacitiveSensor(100);
  long total2 =  cs_4_6.capacitiveSensor(100);

  if(total1>10){
    j++; 
    //DISPLAYS REVERSE
    Display.reverse(1000);
    //DISPLAYS CLEAN
    Display.clean(1000);
    //UPDATE DATA=i;TYPE:DIGIT, DISPLAY 2 
    Display.update(j,'d',2,data);
    //DISPLAYS REFRESH
    Display.refresh(data);
    if(j==10){
       j=0;
    } 
  }
  if(total2>20){
    i++;
    //DISPLAYS REVERSE
    Display.reverse(1000);
    //DISPLAYS CLEAN7
    Display.clean(1000);
    //UPDATE DATA=i;TYPE: INVERTED DIGIT, DISPLAY 1 
    Display.update(i,'i',1,data);
    //DISPLAYS REFRESH
    Display.refresh(data);
    if(i==10){
       i=0;
    }
  }      
}
