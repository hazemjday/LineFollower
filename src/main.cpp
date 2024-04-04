
#include <Arduino.h>
//declarations des variables de moteur

const int rav = 10;
const int rar = 11;
const int lav = 9;
const int lar = 6;
int rr;
int ll;
int basespeed = 120;
int a1;
int a2;
int a3;
int a4;
int a5;
int a6;
int a7;
int a8;
float lastError;
float lasttime;
//declaration des variables  PID
float u = 0 ;
float leftspeed = 0 ;
float rightspeed = 0 ;
float P = 0 ;
float I = 0 ;
float D = 0 ;
float kp = 4.3;
float kd =2.3 ;
float ki = 0;
float error;

//declaration des capteurs
int c1=A0;
int c2=A1;
int c3=A2;
int c4=A3;
int c5=A4;
int c6=A5;
int c7=2;
int c8=4;
int n=0;
int s;


void readSensors(){
  //retourne  1 ou 0
   a1= digitalRead(c1);
   a2= digitalRead(c2);
   a3= digitalRead(c3);
   a4= digitalRead(c4);
   a5= digitalRead(c5);
   a6= digitalRead(c6);
   a7=digitalRead(c7);
   a8=digitalRead(c8);
   
   
}

 

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rav, OUTPUT);
  pinMode(rar, OUTPUT);
  pinMode(lav, OUTPUT);
  pinMode(lar, OUTPUT);
  pinMode(c1,INPUT);
  pinMode(c2,INPUT);
  pinMode(c3,INPUT);
  pinMode(c4,INPUT);
  pinMode(c5,INPUT);
  pinMode(c6,INPUT);
  pinMode(c7,INPUT);
  pinMode(c8,INPUT);
  forward (100);
  n=1;

  
}


void loop() {
 rr =a1+a2+a3;
 ll =a8+a7+a6;
 s =a1+a2+a3+a4+a5+a6+a7+a8;
 float currenttime=millis();
   




   readSensors();
   //printSensors();
   
  
   if (n==1 && ll>=2 && currenttime>300){
     left1 (250);
     n=2;
     lasttime=currenttime;
   }

 
    else if (n==2 && rr>=2 && currenttime-lasttime>150){

      right1 (300);
      
       n=3;
       lasttime=currenttime;
    }



    else if (n==3 && ll>=2 && currenttime-lasttime>150){
    
      left1 (100);
      
      n=4;
      lasttime=currenttime;
    }


    else if (n==4 && rr>=2 && currenttime-lasttime>150){
      stop(80);
      right1 (150);
      n=5;
      lasttime=currenttime;
    }


     else if (n==5  && s>=5 && currenttime-lasttime>500){
       stop(50);
       right (150);
       n=6;
       lasttime=currenttime;

     }



      else if (n==6  && rr>=2 && currenttime - lasttime > 400){
      right (200);
      stop (50);
      forward (100);
       
      n=7;
      lasttime=currenttime;
     }
     else if (n==7 && a8==1 && a7==1 ){
       
       left1 (250);
       
       n=8;
       lasttime=currenttime;
     }
      
     else if (n==8 && rr>=3 ){
       
       right1 (280);
       stop(50);
       n=9;
       lasttime=currenttime;
     }


     else if (n==9 && rr +ll >=4){
       right1 (90);
       stop (50);

       forward (330);
       stop (5000);
       lasttime =currenttime;
       n=10;
     }

     else if (n==10 && rr>=2 && currenttime - lasttime > 500 ){
       right1 (240);
       lasttime =currenttime;
       n=11;
     }
     else if (n==11 && rr>=2 && currenttime - lasttime > 500 ){
       right1 (240);
       lasttime =currenttime;
       n=12;

     }

     
     else if (n==12 && currenttime - lasttime > 700){
       right1 (200);
       lasttime =currenttime;
       n=13;
       
     }
     else if (n==13 && currenttime - lasttime > 900){
       left1 (300);
       lasttime =currenttime;
       n=14;
       }
      else if (n==14 && s>=4 && currenttime - lasttime > 450){
        right1 (270);
        forward (100);
        stop (500000);

      }


     

     
      

    
    else {
    
    kp=2.5;
    kd=1.1;
    PID();
   forwardPID(); 
          }

}

 
void PID(){
  error=120*a1+80*a2+30*a3+10*a4-10*a5-30*a6-80*a7-120*a8;
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  u=kp*P+kd*D+ki*I;
  leftspeed=basespeed-u;
  rightspeed=basespeed+u;
  leftspeed=min(255,max(0,leftspeed));
  rightspeed=min(255,max(0,rightspeed));
}
void forwardPID(){
  analogWrite(rav,rightspeed);
  analogWrite(lav,leftspeed);
  analogWrite(rar,0);
  analogWrite(lar,0);
}
void stop (int x){
  analogWrite(rav,0);
  analogWrite(lav,0);
  analogWrite(rar,0);
  analogWrite(lar,0);
  
  delay (x);
}
void forward (int x){
  analogWrite(rav,120);
  analogWrite(lav,120);
  analogWrite(rar,0);
  analogWrite(lar,0);
  delay (x);
}
void forward1 (int x){
  analogWrite(rav,200);
  analogWrite(lav,200);
  analogWrite(rar,0);
  analogWrite(lar,0);
  delay (x);
}
void right1 (int x){
  analogWrite(rav,120);
  analogWrite(lav,0);
  analogWrite(rar,0);
  analogWrite(lar,120);
  delay (x);
}
void right (int x){
  analogWrite(rav,120);
  analogWrite(lav,0);
  analogWrite(rar,0);
  analogWrite(lar,0);
  delay (x);
}
void left1 (int x){
  analogWrite(rav,0);
  analogWrite(lav,120);
  analogWrite(rar,120);
  analogWrite(lar,0);
  delay (x);
}
void left (int x){
  analogWrite(rav,0);
  analogWrite(lav,120);
  analogWrite(rar,0);
  analogWrite(lar,0);
  delay (x);
}