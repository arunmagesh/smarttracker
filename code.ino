#include <TinyGPS.h>
#include <Servo.h> 
#include <Wire.h>
#include "rgb_lcd.h"
char inchar;
char message[160];
Servo myservo;
int pos = 0;                                              
int val = 0;
int x=0,y=0,z=0;
int a=A8,b=A9,c=A10;
int  param;
char *tel_nr = "\"+918220567919\""; 
TinyGPS gps;
float flat, flon;
unsigned long age;
int temp = A3;
int light = A1;  
int beep = 4;
int button=5;
int shock = 6;
rgb_lcd lcd;
void setup()
 {
 
    Serial2.begin(9600); 
    Serial1.begin(9600);  
    Serial.begin(9600); 
    pinMode(beep, OUTPUT);
    pinMode(button, INPUT);
    pinMode(shock, OUTPUT);
    myservo.attach(8); 
    delay(3000);  
      Serial1.println();
    Serial1.println("AT+CMGF=1");  // sets the SMS mode to text
    delay(100);
    delay(1200);
    pinMode(a,INPUT);
    pinMode(b,INPUT);
    pinMode(c,INPUT);
     lcd.begin(16, 2);
    
    lcd.setRGB(255,120,255 );
    lcd.setCursor(0, 1);
 lcd.print("Entering tracker ");
 delay(200);
 lcd.clear();
 lcd.print("loading");
 delay(200);
 lcd.clear();
   }

void loop()
 {

   int bstate=0;
   bstate=digitalRead(button);
   bool newData = false;
   unsigned long chars;
   unsigned short sentences, failed;
   for (unsigned long start = millis(); millis() - start < 1000;)
    {
     while (Serial2.available())
      {
      char c = Serial2.read();
        if (gps.encode(c)) 
           newData = true;
       }
    }
 
  if (newData)
   {
     float flat, flon;
     unsigned long age;
   gps.f_get_position(&flat, &flon, &age);
   lcd.setCursor(0,0);
     lcd.print("LAT=");
     lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
     lcd.setCursor(0,1);
     lcd.print("LON=");
     lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
   //  Serial.print(" SAT=");
 //    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    // Serial.print(" PREC=");
 //    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  } 
  else  
  {
    lcd.setCursor(0,0);
    lcd.print("Tracker ON");
  }
  
  char c;  
  char command[255] = {0};
  while (Serial1.available() > 0)
   {
     char ch = Serial1.read();
     sprintf(command, "%s%c", command, ch);
    }

  Serial.print(command); 
  if (bstate==1) 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Entering panic mode..");
      delay(100);
      lcd.clear();
           lcd.print("Panic Mode activated: ..");
                lcd.setCursor(0,1);
 lcd.print("Message sent");
     char message[160];
     int tt = analogRead(temp); 
     int ll = analogRead(light); 
     float flat, flon;
     unsigned long age;
     gps.f_get_position(&flat, &flon, &age);
     Serial.println(ll); 
     delay(100);
     flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
     flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
     Serial.println(flat); 
    Serial.println(flon); 
    int d1 = flat;            
    float f2 = flat - d1;    
    int d2 = trunc(f2 * 10000);   
    float f3 = f2 * 10000 - d2; 
    int d3 = trunc(f3 * 10000);  
    int d4 = flon;           
    float f4 = flat - d4;     
    int d5 = trunc(f4 * 10000);  
    float f6 = f4 * 10000 - d5;   
    int d6 = trunc(f6 * 10000);   
    float voltage = (tt * 5);
    float vt=voltage/1024;
    int tp = (vt - 0.5) * 100 ;
    tp=tp/10;
    Serial.println(tp); 
    sprintf(message, "trackerID:12345 panic : LAT= %d.%04d%04d Lon= %d.%04d%04d temp =%2d Light =%d  . ",d1, d2, d3,d4,d5,d6,tp,ll);
    delay(200);
    Serial.println(message); 
    sendSMS(message, tel_nr);
    digitalWrite(beep,HIGH);
    digitalWrite(shock, HIGH);   
    for(pos = 0; pos < 180; pos += 1)  
    {                                 
      myservo.write(pos);          
      delay(15);                  
      } 
    delay(500);
    delSMS();
   }
  if (strstr(command, "log8220")) 
   {
    char message[160];
    int tt = analogRead(temp); 
    int ll = analogRead(light); 
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.println(ll); 
    delay(100);
    flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
    flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
    Serial.println(flat); 
    Serial.println(flon); 
    int d1 = flat;            
    float f2 = flat - d1;     
    int d2 = trunc(f2 * 10000);   
    float f3 = f2 * 10000 - d2;   
    int d3 = trunc(f3 * 10000);   
    int d4 = flon;            
    float f4 = flat - d4;     
    int d5 = trunc(f4 * 10000);  
    float f6 = f4 * 10000 - d5;   
    int d6 = trunc(f6 * 10000);  
    float voltage = (tt * 5);
    float vt=voltage/1024;
    int tp = (vt - 0.5) * 100 ;
    tp=tp/10;
    Serial.println(tp); 
    sprintf(message, "TrackerID:12345 : LAT= %d.%04d%04d Lon= %d.%04d%04d temp =%2d Light =%d  . ",d1, d2, d3,d4,d5,d6,tp,ll);
    delay(200);
    Serial.println(message); 
    sendSMS(message, tel_nr);
    delay(1500);
    delSMS();
     }
    x=analogRead(a);
    y=analogRead(b);
    z=analogRead(c);
    
      if(x<=200) {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("User has fallen down");
           lcd.setCursor(0,0);
        lcd.print("Message Sent");
        delay(200);
    char message[160];
    int tt = analogRead(temp); 
    int ll = analogRead(light); 
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.println(ll); 
    delay(100);
    flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
    flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
    Serial.println(flat); 
    Serial.println(flon); 
    int d1 = flat;         
    float f2 = flat - d1;    
    int d2 = trunc(f2 * 10000);  
    float f3 = f2 * 10000 - d2;   
    int d3 = trunc(f3 * 10000);   
    int d4 = flon;        
    float f4 = flat - d4;     
    int d5 = trunc(f4 * 10000);  
    float f6 = f4 * 10000 - d5;  
    int d6 = trunc(f6 * 10000);  
    float voltage = (tt * 5);
    float vt=voltage/1024;
    int tp = (vt - 0.5) * 100 ;
    tp=tp/10;
    Serial.println(tp); 
    sprintf(message, "TrackerID:12345 has fallen : LAT= %d.%04d%04d Lon= %d.%04d%04d temp =%2d Light =%d  . ",d1, d2, d3,d4,d5,d6,tp,ll);
    delay(200);
    Serial.println(message); 
    sendSMS(message, tel_nr);
    delay(1500);
    delSMS();
     }
   
   if(strstr(command,"shock8220"))
    {
      digitalWrite(shock, HIGH);   
      delay(1000);             
      delSMS();
     }
  
   if(strstr(command,"lock8220"))
    {
      for(pos = 0; pos < 90; pos += 1) 
     {                                
       myservo.write(pos);          
       delay(15);                      
      } 
    delSMS();
     }
  
    if(strstr(command,"unlock8220"))
    {
      for(pos = 90; pos>=1; pos-=1)   
    {                                 
      myservo.write(pos);          
      delay(15);                   
      } 
    delSMS();
    } 

}
 void sendSMS(char *message, char *number)
  {
   Serial1.println();
    Serial1.print("AT+CMGS=\"");     // send the SMS number
    Serial1.print("+91number");
    Serial1.println("\"");
    delay(1000);
    Serial1.print(message); 
    delay(500);

    Serial1.write(0x1A);
    Serial1.write(0x0D);
    Serial1.write(0x0A);
           
    }
    
void delSMS() 
   { 
    Serial1.print("AT+CMGD=1,4"); 
    Serial.println("DEL ALL\"");
    delay(500);
    Serial.println( "All Messages Deleted" );
   }
