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
const int trigPin = 4;
const int echoPin = 5;
// defines variables
long duration;
int distance;
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

int error = false;

// const int's van de auto
  const int bandRadius = 0; // omtrek van de band;
  const int afstandWielDraaipunt = 0; // afstand van het wiel tot het draaipunt van de auto
  const int volledigeRotatieafstandWiel = 2*Pi*afstandWielDraaipunt; //De afstand die beide wielen afleggwen voor een voledig rondje om de AUTO zijn as;
  const int stappenPerRotatie = 4096; // aantal stappen in halfstep dat nodig is om een volledig rondje te maken (nog aanpassen als het 4096 is);
  const int gradenNaarStappen = stappenPerRotatie/360; //het omrekenen van graden naar stappen, dus 180graden*gradenNaarStappen=2048 als stappenPerRotatie 4096 is;
  const int stappenNaarGraden = 360/stappenPerRotatie; // het omrekenen van stappen naar graden, gebruiken voor doorgeven aan pi hoeveel stappen er zijn gezet
  const int 
// const int's van de auto

// int's vam de auto
 

// int's vam de auto


void setup() {
// put your setup code here, to run once:
  
    //setup stepper
      Serial.begin(9600);
      stepper1.setMaxSpeed(1000); // motor links
      stepper2.setMaxSpeed(1000); // motor rechts
     //setup stepper

  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  //setup afsandsensor
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
  //setup afsandsensor
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  
// put your setup code here, to run once:
}

void loop() {
// put your main code here, to run repeatedly:
  rotation(input);
  while(!Serial.available()){}
  Serial.readString();
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
   // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
   // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
   // Calculating the distance
    distance= duration*0.034/2;
   // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
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
  



