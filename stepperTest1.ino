//als je iets terug wilt zien van je programma gebruik je Serial.println('Hier is je bericht');
//Berekeningen worden in CM gemaakt
//

int inputR = 80; //this is a temporary testing variable resembles the pi's input for rotation(in degrees).
int input = 80; //this is a temporary testing variable resembles the pi's input going forward(in cm).
#include <AccelStepper.h>

AccelStepper stepper1(AccelStepper::HALF4WIRE, A0, A2, A1, A3); // motor links
AccelStepper stepper2(AccelStepper::HALF4WIRE, 6, 7, 8, 9);     // motor rechts

const int Pi = 3.14159265359; // pi tot in een paar digids

//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
// defines pins numbers
const int trigPinLinks = 2;
const int echoPinLinks = 3;
const int trigPinVoor = 4;
const int echoPinVoor = 5;
const int trigPinRechts = 6;
const int echoPinRechts = 7;
// defines variables
long durationLinks;
int distanceLinks;
long durationVoor;
int distanceVoor;
long durationRechts;
int distanceRechts;
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

int error = false;

// const int's van de auto
  const int bandRadius = 0; // omtrek van de band;
  const int afstandWielDraaipunt = 0; // afstand van het wiel tot het draaipunt van de auto
  const int volledigeRotatieafstandWiel = 2*Pi*afstandWielDraaipunt; //De afstand die beide wielen afleggwen voor een voledig rondje om de AUTO zijn as;
  const int stappenPerRotatie = 4096; // aantal stappen in halfstep dat nodig is om een volledig rondje te maken (nog aanpassen als het 4096 is);
  const int gradenNaarStappen = stappenPerRotatie/360; //het omrekenen van graden naar stappen, dus 180graden*gradenNaarStappen=2048 als stappenPerRotatie 4096 is;
  const int stappenNaarGraden = 360/stappenPerRotatie; // het omrekenen van stappen naar graden, gebruiken voor doorgeven aan pi hoeveel stappen er zijn gezet
// const int's van de auto

// int's vam de auto
 

// int's vam de auto


void setup() {
// put your setup code here, to run once:
  
    //setup stepper
      Serial.begin(9600);
      stepper1.setMaxSpeed(1000); // motor links max stappen per sec
      stepper2.setMaxSpeed(1000); // motor rechts max stappen per sec
     //setup stepper

  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  //setup afsandsensor
    pinMode(trigPinLinks, OUTPUT); // Sets the trigPinLinks as an Output
    pinMode(echoPinLinks, INPUT); // Sets the echoPinLinks as an Input
    pinMode(trigPinVoor, OUTPUT); // Sets the trigPinVoor as an Output
    pinMode(echoPinVoor, INPUT); // Sets the echoPinVoor as an Input
    pinMode(trigPinRechts, OUTPUT); // Sets the trigPinRechts as an Output
    pinMode(echoPinRechts, INPUT); // Sets the echoPinRechts as an Input
  //setup afsandsensor
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  
// put your setup code here, to run once:
}

void loop() {
// put your main code here, to run repeatedly:
  while(!Serial.available()){}
  Serial.readString();
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
   // Clears the trigPinLinks
    digitalWrite(trigPinLinks, LOW);
    delayMicroseconds(2);
   // Sets the trigPinLinks on HIGH state for 10 micro seconds
    digitalWrite(trigPinLinks, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinLinks, LOW);
   // Reads the echoPinLinks, returns the sound wave travel time in microseconds
    durationLinks = pulseIn(echoPinLinks, HIGH);
   // Calculating the distance
    distanceLinks= durationLinks*0.034/2;
    
    // Clears the trigPinVoor
    digitalWrite(trigPinVoor, LOW);
    delayMicroseconds(2);
   // Sets the trigPinVoor on HIGH state for 10 micro seconds
    digitalWrite(trigPinVoor, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinVoor, LOW);
   // Reads the echoPinVoor, returns the sound wave travel time in microseconds
    durationVoor = pulseIn(echoPinVoor, HIGH);
   // Calculating the distance
    distanceVoor= durationVoor*0.034/2;
    
    // Clears the trigPinRechts
    digitalWrite(trigPinRechts, LOW);
    delayMicroseconds(2);
   // Sets the trigPinRechts on HIGH state for 10 micro seconds
    digitalWrite(trigPinRechts, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinRechts, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
    durationRechts = pulseIn(echoPinRechts, HIGH);
   // Calculating the distance
    distanceRechts= durationRechts*0.034/2;

    if (distanceVoor < 2){ // als de afstand kleiner is dan 2 cm dan moet het stoppen dat moet ik nog testen
    // hier moet ik er voor zorgen dat de loop stopt en dat hij een ander pad gaat kiezen
    // wat is het handigst hier switch met cases of while??????
    switch(){
      case ;
    }
    while(distanceRechts < 2, distanceLinks < 2 ){
     stepper1.move(-10);
     stepper2.move(-10);
    }
    }
    }
   
   // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/


  

  

}

// rotate functie opzet;

void rotation(int graden){
  if(error){
    // als error laat hem niks doen
    return;
  }
 stepper1.move( round(inputR * gradenNaarStappen) ); // het draaien van de linker stappenmotor tijdens het draaien
 stepper2.move( round(inputR * -gradenNaarStappen) ); // het draaien van de rechter stappenmotor tijdens het draaien
 //nog doorgeven dat het is uitgevoerd
  return  Serial.println(  round(inputR*gradenNaarStappen) * stappenNaarGraden  ); // aan de pi laten weten hoeveel graden hij is gedraaid
}

void drive (){
 if(error){
  // als error laat hem niks doen
    return;
    
    stepper1.move( round(input * bandRadius) ); // het draaien van de linker stappenmotor klopt nog niet test
    stepper2.move( round(input * bandradius) ); // het draaien van de rechter stappenmotor
  

    return Serial.println(  round(input*bandRadius) * stappenNaarGraden  ); // aan de pi doorgeven hoeveel hij is 
  }


  return;
}
  



