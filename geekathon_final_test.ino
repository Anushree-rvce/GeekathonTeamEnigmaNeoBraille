#include <SD.h> 
#include<elapsedMillis.h>
elapsedMillis t;
unsigned int interval;
String host = "192.168.43.173";
int httpPort = 1279;
int b1=3,b2=4,b3=5,b4=6,b5=7,b6=8,b7=9;
int v1,v2,v3,v4,v5,v6,v7; 
int chipSelect = 10; 
File file; 
char c;
char braille_array[64]={'K','U',' ','-','\"',';','9','0',
                        '1','5','2','8','3','4','6','7',
                        '@','.','/','+','\n','_','>','#',
                        'i','[','s','!','j','w','t',')',
                        'a','*','k','u','e',':','o','z',
                        'b','<','l','v','h',' ','r','(',
                        'c','%','m','x','d','?','n','y',
                        'f','B','p','&','g',']','q','='};
void setup() {
  // put your setup code here, to run once:
  pinMode(chipSelect, OUTPUT); 
  digitalWrite(chipSelect,1);
  SD.begin(chipSelect);
  file = SD.open("file.txt", FILE_WRITE); 
    interval = 60000;
    pinMode(b1,INPUT);
    pinMode(b2,INPUT);
    pinMode(b3,INPUT);
    pinMode(b4,INPUT);
    pinMode(b5,INPUT);
    pinMode(b6,INPUT);
    pinMode(b7,INPUT);
    v1 = v2 = v3 = v4 = v5 = v6 = 0;
    
}
void loop() {
  // put your main code here, to run repeatedly:
  if(v1!=1)
    v1 = digitalRead(b1);
  if(v2!=1)
    v2 = digitalRead(b2);
  if(v3!=1)
    v3 = digitalRead(b3);
  if(v4!=1)
    v4 = digitalRead(b4);
  if(v5!=1)
    v5 = digitalRead(b5);
  if(v6!=1)
    v6 = digitalRead(b6);
  v7 = digitalRead(b7);
  if(v7==1)
  {
    if(v1+v2+v3+v4+v5+v6!=0&&v1+v2+v3+v4+v5+v6!=6)
    {
      c = braille_to_english(v1,v2,v3,v4,v5,v6);
      v1 = v2 = v3 = v4 = v5 = v6 = 0;
      v7=0;
      file = SD.open("file.txt", FILE_WRITE);
      if (file) 
      {
        file.print(c);
        file.close();
      }
      delay(150);
    }
  }
  if(t>=interval)
  {
    sendData();
    while(1)
    {
      
    }
  }
}
char braille_to_english(int b1, int b2, int b3, int b4, int b5, int b6)
{
    int val=b1*32+b2*16+b3*8+b4*4+b5*2+b6*1;
    return braille_array[val];
    
}
void sendData()
{
  String text="";
  String recv="";
  int len;
  Serial.begin(115200);
  delay(1000);
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(100);
  file = SD.open("FILE.TXT",FILE_READ);
  if(!file)
  {
    Serial.print("AT+CIPSEND=");
    Serial.println(5);
    delay(100); // Wait a little for the ESP to respond
    text = "Error\r\n\r\n";
    Serial.print(text);
    while(!Serial.available())
      delay(5);
    while(Serial.available())
    {
      recv.concat(Serial.read());
    }
  }
  else
  {
    while (file.available())
    {
      char c = file.read();
      text.concat(c);
    }
    file.close();
    text = text+"\r\n\r\n";
    Serial.print("AT+CIPSEND=");
    len = text.length();
    Serial.println(len);
    delay(100); // Wait a little for the ESP to respond
    Serial.print(text);
    while(!Serial.available())
      delay(5);
    while(Serial.available())
    {
      recv.concat(Serial.read());
    }

    text = "Done\r\n\r\n";
    Serial.print("AT+CIPSEND=");
    len = text.length();
    Serial.println(len);
    delay(100); // Wait a little for the ESP to respond
    Serial.print(text);
    delay(100);
    while(!Serial.available())
      delay(5);
    while(Serial.available())
    {
      recv.concat(Serial.read());
    }

    Serial.println("AT+CIPCLOSE");
  }
}



