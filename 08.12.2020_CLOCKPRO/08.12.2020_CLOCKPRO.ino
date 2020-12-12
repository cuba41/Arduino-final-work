//08.12.2020 Testing 
#include <LiquidCrystal.h>
int buttonHrs = 7; //this will be the button used for hours
int prevbuttonHrs = 0; //increase hours by one every push
int buttonMin = 8; //this is for minutes
int prevbuttonMin = 0;
int secs = 0; //starting point
int mins = -1; //incremment by 1
int hrs = 0;
int milliDivsecs = 1000; 
unsigned long currmillis;
boolean minlock = false; 
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, DB4 = 5, DB5 = 4, DB6 = 3, DB7 = 2;
LiquidCrystal lcd(rs, en, DB4, DB5, DB6, DB7);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(2, 0); //Where the display begin
  lcd.print("00.00.00"); //for when powering on
  lcd.setCursor(0, 0); 
  lcd.print("T:"); //this will come from TIME
  lcd.setCursor(0,2);
  lcd.print("Hello There!");
  //Down here is for the buttonPin
  pinMode(buttonHrs,INPUT);
  pinMode(buttonMin, INPUT);
  Serial.begin(9600);
}
void loop() {
  currmillis=millis(); // will be used to track milliseconds
  secs=(millis()/milliDivsecs) %60; 
  if ((secs==0) && (minlock==false)) // will be used to make it lock so it wont pass go up by 1
  {  
    mins=mins+1; // so when it starts 0 minutes become 0
    updateMin(); 
    minlock=true; // prevents minutes from always going up
  } else if(secs !=0)
{
  minlock=false; // 
  }
  if(secs<10)
  {
    lcd.setCursor(9,0);
    lcd.print(secs);
    lcd.setCursor(8,0);
    lcd.print(0);
  }
  else 
  {
    lcd.setCursor(8,0);
    lcd.print(secs);
  } 
  if(digitalRead(buttonMin)==HIGH && prevbuttonMin==LOW) // used to check the minute is being push
  { mins=mins+1; //increasing minutes 
  updateMin(); //this will update the minute 
  } 
  prevbuttonMin=digitalRead(buttonMin);
  if (digitalRead(buttonHrs)==HIGH && prevbuttonHrs==LOW) //Now this will check if the hours button is being pushed
  { 
    hrs=hrs+1;
    updateHrs(); //call the hours to update the hours
  }
    prevbuttonHrs=digitalRead(buttonHrs);
}
  void updateMin() {
    
if(mins>59)// when minutes take a value bigger than 59 it returns to 0 and hours are incremented by 1
 {
  mins=0;
    hrs=hrs+1;// hours incremented by 1
    updateHrs();// call the hours function to update the value of hours
  }
  if(mins<10)
  {
    lcd.setCursor(6,0);
    lcd.print(mins);
    lcd.setCursor(5,0);
    lcd.print(0); 
} 
  else
  {
    lcd.setCursor(5,0);
  lcd.print(mins);
  }
}
  void updateHrs() {
    Serial.println(hrs);
    if(hrs>23) // this will make it go from 23:59 back t0 0
    {
      hrs=0; 
      }
      if(hrs<10) 
      {
        lcd.setCursor(2,0);
        lcd.print(" ");
        lcd.setCursor(3,0);
    }
    else 
    { 
      lcd.setCursor(2,0); 
    }
    lcd.print(hrs);
    }
