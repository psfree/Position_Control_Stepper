#define PanMove 3
#define PanDir 4
#define TiltMove 6
#define TiltDir 7
#define Steps 48
#define Speed 4000 // see Max Speed is faster
#define PanIn 1
#define TiltIn 5
// Sets Our Variables
int PosTilt = 0;
int PosPan = 0;
int long val = 0;
int old1 = 0;
int old2 = 0;
unsigned int y;

#include "AccelStepper.h"
// AccelStepper Setup
AccelStepper Pan1(1, PanMove, PanDir);
AccelStepper Tilt1(1, TiltMove, TiltDir);


void setup() {

  digitalWrite(PanMove, LOW);
  digitalWrite(TiltMove, LOW);

  // Sets Max speeds
  Pan1.setMaxSpeed(Speed);
  Pan1.setAcceleration(Speed);

  Tilt1.setMaxSpeed(Speed);
  Tilt1.setAcceleration(Speed);
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Ready to initiate");
  Serial.println("Type Anything to Begin");
  while (Serial.available() == 0) {}

}


void loop() {

  //  unsigned long currentTtime = millis();
  // if{
  PosPan = GetPos(PanIn);

//  Serial.print("Your Pan Value is");
//  Serial.println(PosPan);
    Pan1.moveTo(PosPan);
    Pan1.run();// waits till we get to this new position, seems to be weird out by
  //  //Pan1.runToNewPosition(PosPan);

  PosTilt = GetPos(TiltIn);
//  Serial.print("Your Tilt Value is");
//  Serial.println(PosTilt);
  Tilt1.moveTo(PosTilt);
  Tilt1.run();
  //  Tilt1.runToNewPosition(PosTilt);
  
}
long GetPos(int pin) {


  int val = analogRead(pin);

  if (pin == PanIn) {
    if ((val > old1 + 9) || (val < old1 - 9)) {
      y = map (val, 0, 1023, 0, Steps );
      old1 = val;

    }
    else y = map(old1, 0, 1023, 0, Steps);;
  }
  else if (pin == TiltIn) { // figure this out
    if ((val > old2 + 7) || (val < old2 - 7)) {
      y = map (val, 0, 1023, 0, Steps );
      old2 = val;
    }
    else y = map(old2, 0, 1023, 0, Steps);
  }
  return y;

}
