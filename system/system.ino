//--------------------------------------------------DHT -----------------------------------
#include <DHT.h>
DHT dht(13,DHT22);
#define buzz 2
//------------------------------------------------------------------------------
//----------------------------bluetooth--------------------------------------------------
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
//------------------------------------------------------------------------------
//-----------------------------led pin-------------------------------------------------
#define c3_led 21
#define c1_led 33
#define c2_led 0

//------------------------------------------------------------------------------
//-----------------------------------------------------------static ip address-------------
#include "web.h"

//const char* ssid = "ABCD Chocolate WIFI";
//const char* pw = "123456789";
const char* ssid = "Ojiya";
const char* pw = "ojith@1234";

#include <WiFi.h>


//-------------------------------------------------------------------------ESP Async Web Server--------------------------------------
  #include <AsyncTCP.h>

  #include <ESPAsyncWebServer.h>


// Create an instance of the AsyncWebServer
  AsyncWebServer server(80);


//-------------------------------------------------------------------------ESP Async Web Server--------------------------------------
//--------------------------------------------------------------------globle variables------------------------------------------------------

// Define global variables to hold the values received from the web page

   int variable1, variable2,variable3;// these variables for get the count of user inputs
  int tq1=10; //total quantity 1
  int tq2=10; //total quantity 2
  int tq3=10; //total quantity 3

  int av1=10; //available quantity 3
  int av2=10; //available quantity 3
  int av3=10; //available quantity 3
  
  int count1=0;// count of chochos
  int count2=0;// count of chochos
  int count3=0;// count of chochos

  int stp_time=5000; //stop time
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------servo part----------------------------------------------------------
  #include <ESP32_Servo.h> 
  Servo s1; //making a servo object
  Servo s2;
  Servo s3;
  
  #define s1_pin 19
  #define s2_pin 5
  #define s3_pin 23

//-------------------------------------------------------------------servo part end ----------------------------------------------------------
//-------------------------------------------------------------------ir sensor part----------------------------------------------------------
#define col1 17
#define col2 18
#define col3 22
#define stop1 15
#define stop2 16
//-------------------------------------------------------------------ir sensor part----------------------------------------------------------

void setup() {

  Serial.begin(115200);
  
//-------------------------------------------------------------------dht----------------------------------------
dht.begin();
pinMode(buzz,OUTPUT);
//--------------------------------------------------------wifi access point-----------------------  

  WiFi.begin(ssid,pw);
  SerialBT.begin("ESP32test", true);                            //esp32 bluetooth name

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
    digitalWrite(buzz,HIGH);
    delay(200);
    digitalWrite(buzz,LOW);  
    delay(200);
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  Serial.print(F(" Use 'http://"));
  Serial.print(WiFi.localIP());
  Serial.println(F("' to connect"));


  

  Serial.println(F("Make sure remote cart device is on!")); 

  while(!SerialBT.connect("OJIYA")){                                   // cart bluetooth name 
    Serial.println(F("Bluetooth Connection Failed! \n trying to connect "));
    digitalWrite(buzz,HIGH);
    delay(200);
    digitalWrite(buzz,LOW);  
    
    delay(1000);
  }
  Serial.println(F("Bluetooth Connected Succesfully!"));
  
//--------------------------------------------------------------------------------------------------------
//-----------------------------------------leds---------------------------------------------------------------

pinMode(c1_led,OUTPUT);
pinMode(c2_led,OUTPUT);
pinMode(c3_led,OUTPUT);

digitalWrite(c1_led,LOW);
  digitalWrite(c2_led,LOW);
  digitalWrite(c3_led,LOW);
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------ir sensors-----------------------------------------------
pinMode(col1,INPUT);
pinMode(col2,INPUT);
pinMode(col3,INPUT);
pinMode(stop1,INPUT);
pinMode(stop2,INPUT);

//---------------------------------------------------------servo attachments----------------------------------------------
s1.attach(s1_pin);
s2.attach(s2_pin);
s3.attach(s3_pin);

s1.write(0);// servo reload mode on
s2.write(0);
s3.write(0);
//--------------------------------------------------------------------------------------------------------

  server.on("/quantity1", HTTP_GET, [](AsyncWebServerRequest *request){
   
    
    if(request->getParam("val1")){
       variable1 = request->getParam("val1")->value().toInt();
    
      Serial.print(F("Variable 1: "));
      Serial.println(variable1); 
    }
    request->send(200);
  });
  server.on("/quantity2", HTTP_GET, [](AsyncWebServerRequest *request){
   
    if(request->getParam("val2")){
      variable2 = request->getParam("val2")->value().toInt();
    
       Serial.print(F("Variable 2: "));
      Serial.println(variable2);
    }
  
    request->send(200);
  });
  server.on("/quantity3", HTTP_GET, [](AsyncWebServerRequest *request){
  
    if(request->getParam("val3")){
      variable3 = request->getParam("val3")->value().toInt();
    
      Serial.print(F("Variable 3: "));
      Serial.println(variable3);
    }
  
    request->send(200);
  });
 
   // Send the updated chocolate counts to the web page
  server.on("/getCounts", HTTP_GET, [](AsyncWebServerRequest *request) {
    String counts = "{\"av1\": " + String(av1) + ", \"av2\": " + String(av2) + ", \"av3\": " + String(av3) + "}";
    request->send(200, "application/json", counts);
  });
  
  // Serve the web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", webpage);
  });

  // Start the server
  server.begin();

  
  
}

void loop() {

//-------------------------------------------------------------------------------defulat stop for cart-----------------------
 if(variable1==0&&variable2==0&&variable3==0){
       // SerialBT.write(2);
        Serial.println("nothing to get so cart isstoped");
  }else{
    SerialBT.write(1);
    Serial.println("go");
  }
//----------------------------------------------------------------------------dht---------------------------------------------------
float t = dht.readTemperature();
if(t>=40.0){
  digitalWrite(buzz,HIGH);
}else{
  digitalWrite(buzz,LOW);
}
//----------------------------------------------------------------------------dht---------------------------------------------------
//-------------------------------------------------------------low choco warning-----------------------------------------------------
if(digitalRead(col1)==LOW ||av1<=1){
  digitalWrite(c1_led,HIGH);
  Serial.println("col 1");
}else if(digitalRead(col2)==LOW ||av2<=1){
  digitalWrite(c2_led,HIGH);
  Serial.println("col 2");
}else if(digitalRead(col3)==LOW ||av3<=1){
  digitalWrite(c3_led,HIGH);
  Serial.println("col 3");
}else{
  digitalWrite(c1_led,LOW);
  digitalWrite(c2_led,LOW);
  digitalWrite(c3_led,LOW);
}

//----------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------drop chocholates part----------------------------

 
if((digitalRead(col1)==HIGH && variable1>0 &&(tq1-count1)>=variable1)||(digitalRead(col2)==HIGH && variable2>0 &&(tq2-count2)>=variable2)){ 
  // bluetooth commands
  if(digitalRead(stop1)==LOW){
    SerialBT.write(2);
    Serial.println("stoppppppppppppppp cartttttttt");
    for(byte i=variable1;i>0;i-- ){
        s1.write(180);
        Serial.println(i);
        delay(1000);
        s1.write(0);
        delay(1000);
        count1++;
      }
      variable1=0;
      av1=tq1-count1;
      
      for(byte i=variable2;i>0;i-- ){
        s2.write(180);
        Serial.println(i);
        delay(1000);
        s2.write(0);
        delay(1000);
        count2++;
     }
     variable2=0;
     av2=tq2-count2;
      
      SerialBT.write(1);
      Serial.println("cart moving");
      
    }
  }
      
  
/*
if(digitalRead(col2)==HIGH && variable2>0 &&(tq2-count2)>=variable2){ 
  // bluetooth commands
  if(digitalRead(stop1)==LOW){
      SerialBT.write(2);
      Serial.println("stoppppppppppppppp cartttttttt");
    for(byte i=variable2;i>0;i-- ){
        s2.write(180);
        Serial.println(i);
        delay(1000);
        s2.write(0);
        delay(1000);
        count2++;
     }
     variable2=0;
     av2=tq2-count2;
      SerialBT.write(1);
      Serial.println("cart moving");
  }  
}
*/
   if(digitalRead(col3)==HIGH&& variable3>0 &&(tq3-count3)>=variable3){ 
    if(digitalRead(stop2)==LOW){  // bluetooth commands
        SerialBT.write(2);
         Serial.println("stoppppppppppppppp cartttttttt");
      for(byte i=variable3;i>0;i-- ){
        s3.write(180);
        Serial.println(i);
        delay(1000);
        s3.write(0);
        delay(1000);
        count3++;
      }
      variable3=0;
      av3=tq3-count3;
      SerialBT.write(1);
      Serial.println("cart moving");
    } 
    }
    
    delay(stp_time);
    while(!(variable1>0 || variable2>0 ||variable3>0)){
      delay(5000);
      SerialBT.write(2);
      
    }  
     
  delay(1000);
}
