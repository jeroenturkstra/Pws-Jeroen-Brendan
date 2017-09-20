

#include <AccelStepper.h>

AccelStepper stepper1(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

int command = 0;

int plek = 180;
int i = 0;
const int bandRadius = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
stepper1.setMaxSpeed(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper1.move(10000);
  stepper1.runSpeed();

}
