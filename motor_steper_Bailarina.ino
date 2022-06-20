/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPinOne 4
#define stepPinOne 5
#define stepsPerRevolution 200

#define dirPinTwo 2
#define stepPinTwo 3

int stepCount = 0; 

enum { 
  STOP, LEFT, RIGHT
};

int timmings[4][3] = {{5, RIGHT, RIGHT}, {2, LEFT, STOP}, {3, LEFT, LEFT}, {4, RIGHT, RIGHT}};
int LengthOfTimmings = sizeof timmings / sizeof timmings[0];

void setup() {
  // Declare pins as output:
  pinMode(dirPinOne, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);
  pinMode(stepPinOne, OUTPUT);
  pinMode(stepPinTwo, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  if(stepCount < LengthOfTimmings) {

    int stopOne = timmings[stepCount][1] == STOP ?  1 : 0;
    int stopTwo = timmings[stepCount][2] == STOP ?  1 : 0;

    int dirOne = timmings[stepCount][1] == RIGHT ?  HIGH : LOW;
    int dirTwo = timmings[stepCount][2] == RIGHT ?  HIGH : HIGH;
    
    digitalWrite(dirPinOne, dirOne);
    digitalWrite(dirPinTwo, dirTwo);

    for (int i = 0; i < timmings[stepCount][0]; i++) {
      for (int i = 0; i < stepsPerRevolution/2; i++) {
        // These four lines result in 1 step:
        if(!stopOne) {
           digitalWrite(stepPinOne, dirOne);
        }
        if(!stopTwo) {
          digitalWrite(stepPinTwo, dirTwo);
        }
        delayMicroseconds(5000);
        if(!stopOne) {
          digitalWrite(stepPinOne, !dirOne);
        }
        if(!stopTwo) {
          digitalWrite(stepPinTwo, !dirTwo);
        }
        delayMicroseconds(5000);
      } 
    }
    
  }
 
  stepCount++;
  delay(500);

}
