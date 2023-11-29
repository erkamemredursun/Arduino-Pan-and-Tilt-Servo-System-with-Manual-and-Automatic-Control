#include <Servo.h>

int potPin = A0;
int potValue;

Servo myServo;

int servoKucuk = 0;
int servoBuyuk = 0;
int ayar = 0;
bool bservoKucuk = false;
bool bservoBuyuk = false;

int step = 5;

int control = 0;

int Buton1 =3;
int Buton2 = 4;
int Buton3 = 5;
int Buton4 = 6;
int Buton5 = 7;

int ledkirmizi = 10;
int ledsari = 11;

/*
control 1 = manuel kontrol
control 2 = otomatik kontrol
control 3 = servo ilk aciyi ayarla
control 4 = servo ikinci aciyi ayarla
control 5 = ayarlari sifirla
*/
void setup() {
  // put your setup code here, to run once:
 pinMode(Buton1, INPUT);
 pinMode(Buton2, INPUT);
 pinMode(Buton3, INPUT);
 pinMode(Buton4, INPUT);
 pinMode(Buton5, INPUT);
 pinMode(ledkirmizi, OUTPUT);
 pinMode(ledsari, OUTPUT);

pinMode(potPin, INPUT);
 myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  
  potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);

 if (digitalRead(Buton5) == 1)
  control = 5;
  if(digitalRead(Buton1) == 1)
  control = 1;
 if(digitalRead(Buton2) == 1){
  if(bservoKucuk){
    digitalWrite(ledkirmizi, HIGH);
  }else {
    digitalWrite(ledkirmizi, LOW);
    delay(500);
    digitalWrite(ledkirmizi, HIGH);
  }
   if(bservoBuyuk){
    digitalWrite(ledsari, HIGH);
  }else {
     digitalWrite(ledsari, LOW);
    delay(500);
    digitalWrite(ledsari, HIGH);
  }
  control = 2;
 }

 if(digitalRead(Buton3) == 1)
  control = 3;
 if(digitalRead(Buton4) == 1)
  control = 4;
  


  
if(ayar == 0 && !bservoKucuk){
if(control ==3){
  servoKucuk = angle;
  bservoKucuk = true;
}
}

if(control == 4 && bservoKucuk && !bservoBuyuk){
servoBuyuk = angle;
bservoBuyuk = true;
}

if(control == 5){
  ayar = 0;
  bservoKucuk = false;
  bservoBuyuk = false;
}

if(control == 2 && bservoBuyuk && bservoKucuk){
  int maks;
  int min;
  if(servoKucuk < servoBuyuk){
   maks = servoBuyuk;
   min = servoKucuk;
  }else {
      maks = servoKucuk;
   min = servoBuyuk;
  }

for (int anglex = min; anglex < maks; anglex += step) {
    myServo.write(anglex); 
    delay(15); 
    if(control!=2){
      break;
    }
  }
  delay(1000); 

  for (int anglex = maks; anglex >= min; anglex -= step) {
    myServo.write(anglex); 
    delay(150); 
     if(control!=2){
      break;
    }
  }

}

if(control == 1){
myServo.write(angle); 
delay(15);
}

  delay(100);

}
