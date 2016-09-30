/*
Test code for running a bipolar stepper motor with A4988 driver and Arduino.
*/

const int stepPin = 13;
const int dirPin =  12;
// The number of steps in one full motor rotation
const int stepsInFullRound = 400;

void setup() {
  pinMode(stepPin, OUTPUT);      
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);  
}

// Runs the motor according to a chosen direction, speed (rounds per seconds) and the number of steps
void run(boolean runForward, double speedRPS, int stepCount) {
  digitalWrite(dirPin, runForward);
  for (int i = 0; i < stepCount; i++) {
    digitalWrite(stepPin, HIGH);
    holdHalfCylce(speedRPS);
    digitalWrite(stepPin, LOW);
    holdHalfCylce(speedRPS);
  }
}

// A delay function used in the run()-method
void holdHalfCylce(double speedRPS) {
  long holdTime_us = (long)(1.0 / (double) stepsInFullRound / speedRPS / 2.0 * 1E6);
  int overflowCount = holdTime_us / 65535;
  for (int i = 0; i < overflowCount; i++) {
    delayMicroseconds(65535);
  }
  delayMicroseconds((unsigned int) holdTime_us);
}

// Runs the motor once in forward direction and once to the opposite direction. 
// Holds the motor still for 1 sec after both movements. 
void runBackAndForth(double speedRPS, int rounds) {
  run(true, speedRPS, stepsInFullRound * rounds);
  delay(1000);
  run(false, speedRPS, stepsInFullRound * rounds);
  delay(1000);
}

// Tests various speeds for 3 full rotations
void loop(){
  runBackAndForth(1, 3);
  runBackAndForth(2, 3);
  runBackAndForth(3, 3);
  //runBackAndForth(7, 3); // doesn't work on my stepper motor
}

// another way to test it out. lowering delayMicroseconds(800) to e.g. (600) will make the motor spin faster. I can go till 550, lower than that, the step motor will stop spinning. 
//int dirPin = 12;
//int stepperPin = 13;
//void setup() {
// pinMode(dirPin, OUTPUT);
// pinMode(stepperPin, OUTPUT);
//}
// void step(boolean dir,int steps){
// digitalWrite(dirPin,dir);
// delay(50);
// for(int i=0;i<steps;i++){
//   digitalWrite(stepperPin, HIGH);
//   delayMicroseconds(800);
//   digitalWrite(stepperPin, LOW);
//   delayMicroseconds(800);
// }
//}
//void loop(){
// step(true,1600);
// delay(500);
// step(false,1600*5);
// delay(500);
//}
