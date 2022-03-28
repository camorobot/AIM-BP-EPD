#include <Servo.h>

int servoPos = 0;
Servo myservo;

void setup(){

    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(A4,OUTPUT);
    pinMode(A5,OUTPUT);
    pinMode(A1,OUTPUT);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    digitalWrite(A4,HIGH);
    digitalWrite(A5,HIGH);
    myservo.attach(A0);
    myservo.write(180);
}

void loop(){
    // tone(A1, 1000);
}