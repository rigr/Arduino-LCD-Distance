/*
 * Ultrasonic distance measuring, output to LCD via i2c
 * 
 * Merged two scripts I found on the net.
 * 
 * Hardware used: 
 * Arduino nano clone         from banggood  ID  940937
 * i2c 2x16 LCD               from banggood  ID  950726
 * Ultrasonic Module HC-SR04  from banggood  ID   40313
 * 
 * 
*/

#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>  // https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads

// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//pins for ultrasonic Module
const int trigPin = 2;
const int echoPin = 3;
//variables
long duration;
// int distanceCm, distanceInch;
float distanceCm, distanceInch;

void setup()
{
  Serial.begin(9600); 
  Serial.println("arduino_LCD-Distance script running"); //

  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines, turn on backlight

  for (int i = 0; i < 2; i++)  //two blinks
  {
    lcd.backlight();
    delay(50);
    lcd.noBacklight();
    delay(50);
  }
  
  lcd.backlight(); // finish with backlight on
  
  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Ultrasonic    cm");
  lcd.setCursor(0, 1);
  lcd.print("Distance    inch"); 
  delay(1000);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.clear();

}/*--(end setup )---*/


void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Dist: "); // Prints string "Distance" on the LCD
  lcd.print(distanceCm); // Prints the distance value from the sensor
  lcd.print(" cm");
  //delay(20);
  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(distanceInch);
  lcd.print(" inch");
  delay(300);
  lcd.clear();
}
