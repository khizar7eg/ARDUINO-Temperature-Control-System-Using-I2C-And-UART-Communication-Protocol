#include <Wire.h>
int tempPin=A0;
int temp=0;
int in1=13;
int in2=12;
int en=11;
int value;    
int x = 0;   
int LED = 7;                       
String state;

void setup()
{
  Serial.begin(9600);
  Serial.println("ESD-OEL#2 (Khizar Hayat)");
  Serial.println("1st Floor (1st Slave)");
  pinMode(LED, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(en, LOW); 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
value = Wire.read(); 
x = Wire.read();

}

void loop()
{
  
  temp = analogRead (tempPin); 
  temp = temp*0.48828125;
  if(x == 1){
    digitalWrite(LED, HIGH);
  
  
     if(value <= temp){  
  digitalWrite(en, HIGH); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  state = "ON";
  Serial.println(" ");
  Serial.print("Room Temperature: ");
  Serial.println(temp);
  Serial.print("Set Temperature: ");
  Serial.println(value);
  Serial.print("Air Conditioning: ");
  Serial.println(state);
  delay(1000);
  }

  else{
  digitalWrite(en, LOW); 
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  state = "OFF";
  Serial.println(" ");
  Serial.print("Room Temperature: ");
  Serial.println(temp);
  Serial.print("Set Temperature: ");
  Serial.println(value);
  Serial.print("Air Conditioning: ");
  Serial.println(state);
  delay(1000);
  }
  }
  else{
    digitalWrite(LED, LOW);
  }
  
}
