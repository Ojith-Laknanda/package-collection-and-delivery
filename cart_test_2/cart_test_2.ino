#include <SoftwareSerial.h>
SoftwareSerial BTSerial(0,1);  // RX, TX

int ll=A0;
int rr=A1;

int in1=7;
int in2=8;
int in3=9;
int in4=10;
int enA=5;
int enB=6;

int spd= 180;
int bt_data;

void setup() {
  Serial.begin(38400);
  BTSerial.begin(38400);
  
  pinMode(rr, INPUT); // declare if sensor as input  
  pinMode(ll, INPUT); // declare ir sensor as input
  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

}

void loop() {
  

  int ll=digitalRead(A0);
  int rr=digitalRead(A1);
     
   Serial.print("left sensor ");Serial.print(ll);
   Serial.println("");
   Serial.println("right sensor");Serial.print(rr);
   Serial.println();
 
   if(BTSerial.available() > 0){  //if some date is sent, reads it and saves in state     
      bt_data = BTSerial.read(); 
     Serial.println(bt_data);
   }else{
    Stop();
   }
  
   analogWrite(enB,spd);
   analogWrite(enA,spd);

   if(bt_data==1){
    Serial.println("line following started"); 
      if((digitalRead(rr) == 1)&&(digitalRead(ll) == 1)){
        forword();
      }else if((digitalRead(rr) == 1)&&(digitalRead(ll) == 0)){
        Right();
      }else if((digitalRead(rr) == 0)&&(digitalRead(ll) == 1)){
        Left();
      }else if((digitalRead(rr) == 0)&&(digitalRead(ll) == 0)){
        Stop();  
      }
   }else if(bt_data==3){
    Serial.println("forword");
    forword();
   }else if(bt_data==4){
    Serial.println("backword");
    backword();
   }else if(bt_data==5){
    Serial.println("Right");
    Right();
   }else if(bt_data==6){
    Serial.println("Left");
    Left();
   }else {
    Serial.println("Stop");
     Stop();
   }
   
}


void forword(){  //forword
  Serial.println("forword");
  analogWrite(enB,spd);
   analogWrite(enA,spd);
  digitalWrite(in1, HIGH); //Right Motor forword Pin 
  digitalWrite(in2, LOW);  //Right Motor backword Pin 
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin 
}

void backword(){ //backword
  Serial.println("backword");
  analogWrite(enB,spd);
   analogWrite(enA,spd);
  digitalWrite(in1, LOW);  //Right Motor forword Pin 
  digitalWrite(in2, HIGH); //Right Motor backword Pin 
  digitalWrite(in3, LOW); //Left Motor backword Pin 
  digitalWrite(in4, HIGH);  //Left Motor forword Pin 
}

void Right(){ //turnRight
  Serial.println("turnRight");
  analogWrite(enB,200);
   analogWrite(enA,200);
  Serial.println("right");
   digitalWrite(in1, LOW); //Right Motor forword Pin 
  digitalWrite(in2, HIGH);  //Right Motor backword Pin 
  digitalWrite(in3, HIGH);  //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin  
}

void Left(){ //turnLeft
  Serial.println("turnLeft");
  analogWrite(enB,200);
   analogWrite(enA,200);
  Serial.println("left");
   digitalWrite(in1, HIGH); //Right Motor forword Pin 
  digitalWrite(in2, LOW);  //Right Motor backword Pin 
  digitalWrite(in3, LOW);  //Left Motor backword Pin 
  digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void Stop(){ //stop
  Serial.println("stop");
  digitalWrite(in1, LOW); //Right Motor forword Pin 
  digitalWrite(in2, LOW); //Right Motor backword Pin 
  digitalWrite(in3, LOW); //Left Motor backword Pin 
  digitalWrite(in4, LOW); //Left Motor forword Pin 
}
