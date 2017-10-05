
//als je iets terug wilt zien van je programma gebruik je Serial.println('Hier is je bericht');
//Berekeningen worden in CM gemaakt

//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#include <AccelStepper.h>

// Some of the 'weird' variables.
  const float Pi = 3.14;
  int error = false;

// Afstandscencor pin definement
  const int trigPinLinks = 2;
  const int echoPinLinks = 3;
  const int trigPinVoor = 4;
  const int echoPinVoor = 5;
  const int trigPinRechts = 6;
  const int echoPinRechts = 7;

// const int's van de auto
  const int bandRadius = 0; // omtrek van de band;
  const int afstandWielDraaipunt = 0; // afstand van het wiel tot het draaipunt van de auto
  const int volledigeRotatieafstandWiel = 2*Pi*afstandWielDraaipunt; //De afstand die beide wielen afleggwen voor een voledig rondje om de AUTO zijn as;
  const int stappenPerRotatie = 4096; // aantal stappen in halfstep dat nodig is om een volledig rondje te maken (nog aanpassen als het 4096 is);
  const int gradenNaarStappen = stappenPerRotatie/360; //het omrekenen van graden naar stappen, dus 180graden*gradenNaarStappen=2048 als stappenPerRotatie 4096 is;
  const int stappenNaarGraden = 360/stappenPerRotatie; // het omrekenen van stappen naar graden, gebruiken voor doorgeven aan pi hoeveel stappen er zijn gezet

AccelStepper stepper1(AccelStepper::HALF4WIRE, A0, A2, A1, A3); // motor links
AccelStepper stepper2(AccelStepper::HALF4WIRE, 6, 8, 7, 9);     // motor rechts

// temp variables
  int inputR = 80; //this is a temporary testing variable resembles the pi's input for rotation(in degrees).
  int input = 80; //this is a temporary testing variable resembles the pi's input going forward(in cm).



void setup() {  
  //setup stepper
    Serial.begin(9600);
    stepper1.setMaxSpeed(5000); // motor links max stappen per sec
    stepper2.setMaxSpeed(5000); // motor rechts max stappen per sec

  //setup afsandsensor
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
    pinMode(trigPinLinks, OUTPUT); // Sets the trigPinLinks as an Output
    pinMode(echoPinLinks, INPUT); // Sets the echoPinLinks as an Input
    pinMode(trigPinVoor, OUTPUT); // Sets the trigPinVoor as an Output
    pinMode(echoPinVoor, INPUT); // Sets the echoPinVoor as an Input
    pinMode(trigPinRechts, OUTPUT); // Sets the trigPinRechts as an Output
    pinMode(echoPinRechts, INPUT); // Sets the echoPinRechts as an Input
}



void loop() {
  //http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
  // Clears the trigPinLinks
  digitalWrite(trigPinLinks, LOW);
  delayMicroseconds(2);
  // Sets the trigPinLinks on HIGH state for 10 micro seconds
  digitalWrite(trigPinLinks, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLinks, LOW);
  // Reads the echoPinLinks, returns the sound wave travel time in microseconds
  long durationLinks = pulseIn(echoPinLinks, HIGH);
  // Calculating the distance
  int distanceLinks= durationLinks*0.034/2;
    
  // Clears the trigPinVoor
  digitalWrite(trigPinVoor, LOW);
  delayMicroseconds(2);
  // Sets the trigPinVoor on HIGH state for 10 micro seconds
  digitalWrite(trigPinVoor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinVoor, LOW);
  // Reads the echoPinVoor, returns the sound wave travel time in microseconds
  long durationVoor = pulseIn(echoPinVoor, HIGH);
  // Calculating the distance
  int distanceVoor= durationVoor*0.034/2;
    
  // Clears the trigPinRechts
  digitalWrite(trigPinRechts, LOW);
  delayMicroseconds(2);
  // Sets the trigPinRechts on HIGH state for 10 micro seconds
  digitalWrite(trigPinRechts, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRechts, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long durationRechts = pulseIn(echoPinRechts, HIGH);
  // Calculating the distance
  int distanceRechts= durationRechts*0.034/2;

   
  // als de afstand kleiner is dan 2 cm dan moet het stoppen dat moet ik nog testen
  //hier moet ik er voor zorgen dat de loop stopt en dat hij een ander pad gaat kiezen 
  if ((distanceVoor < 2) || (distanceLinks < 2) || (distanceRechts <2)){ 
    //Run the code that gets you unstuck, when you are free you'll break
    while(true){
      //switchKey is a variable that is used to easily get the case function to know if eighter the front, the left or the right,
      // or a combination of these three is to close to a surface, we use the numbers 2, 3 and 4 because anny addition,
      // of these three numbers makes a unique number
      int switchKey = 0;
      if(distanceVoor < 3){switchKey += 2;}
      if(distanceLinks < 3){switchKey += 3;}
      if(distanceRechts < 3){switchKey += 4;}
      switch (switchKey){
        case 2: // voor
          break;
          
        case 3: // links
          break;
        
        case 4: // rechts
          break;
        
        case 5: // voor & links
          break;
        
        case 6: // voor & rechts
          break;
        
        case 7: // links & rechts
          break;
        
        case 9: // voor & links & rechts
          break;
        
        default: // glitch
          break;
      }
   
    }  
  
  }
   
}



// rotate functie opzet;
void rotation(int graden){
  if(error) return; //Breaks out of roation if there is an error
  stepper1.move( round(inputR * gradenNaarStappen) ); // het draaien van de linker stappenmotor tijdens het draaien
  stepper2.move( round(inputR * -gradenNaarStappen) ); // het draaien van de rechter stappenmotor tijdens het draaien
  //calling run for both steppers to make them actualy run.
  while(stepper1.isRunning() || stepper2.isRunning()){ 
    stepper1.run();
    stepper2.run();
  }
}



void drive (){
  if(error) return;
  stepper1.move( round(input * bandRadius) ); // het draaien van de linker stappenmotor klopt nog niet test
  stepper2.move( round(input * bandRadius) ); // het draaien van de rechter stappenmotor
  //calling run for both steppers to make them actualy run.
  while(stepper1.isRunning() || stepper2.isRunning()){
    stepper1.run();
    stepper2.run();
  }
}
