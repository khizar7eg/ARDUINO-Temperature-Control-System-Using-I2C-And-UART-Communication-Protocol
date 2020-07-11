#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

int value = 0;   
int x = 0;                             
int keyval;                                     
int isnum;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] =
{
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {A0,A1,A2,A3};
byte colPins[COLS] = {4, 5, 6};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup()
{

  Wire.begin();
  pinMode(7, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("*ESD FINALTERM*");
  lcd.setCursor(0, 1);
  lcd.print("KHIZAR HAYAT");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter S-T:");
}

void loop()
{
  
  lcd.setCursor(0, 1);
char key = keypad.getKey();
do
  {
    keyval = keypad.getKey();                          
    isnum = (keyval >= '0' && keyval <= '9');         
    if (isnum)
    {
      lcd.print(keyval - '0');
      value = value * 10 + keyval - '0';              
    }

  } while (isnum || !keyval);                          
  lcd.print("->Saved"); 
  delay(1000);
  Display();
  digitalWrite(7, HIGH);
  x = digitalRead(7);
  Wire.beginTransmission(1); // transmit to device #1
  Wire.write(value); // sends value
  Wire.write(x); 
  Wire.endTransmission(); // stop transmitting
  Wire.beginTransmission(2); // transmit to device #2
  Wire.write(value); // sends value
  Wire.write(x); 
  Wire.endTransmission(); // stop transmitting
  return value; 
  

}

void Display(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Temp: ");
  lcd.print(value);
  lcd.print((char)+223);
  lcd.print("C");
  
}
