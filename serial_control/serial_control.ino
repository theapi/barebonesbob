#include <Servo.h>



const byte servoPinLeftHip    = 7;  
const byte servoPinRightHip   = 8;
const byte servoPinLeftAnkle = 13;
const byte servoPinRightAnkle = 12;

// debug leds (pwm)
const byte ledPinLeftAnkle  = 5;
const byte ledPinLeftHip    = 9;
const byte ledPinRightAnkle = 10;
const byte ledPinRightHip   = 11;

// servo centers (todo: one for each servo)
const byte servoCenter = 90;
const byte servoMin = 60;
const byte servoMax = 120;

//Servo servo;
Servo LeftHip;
Servo LeftAnkle;
Servo RightHip;
Servo RightAnkle;


byte lastLh = 0;
byte lastLa = 0;
byte lastRh = 0;
byte lastRa = 0;

//byte moveSpeed = 20;

void setup()
{
  Serial.begin(9600);
  

  LeftHip.attach(servoPinLeftHip);
  LeftAnkle.attach(servoPinLeftAnkle);
  RightHip.attach(servoPinRightHip);     
  RightAnkle.attach(servoPinRightAnkle);

  servosCenter();
}


void loop()
{     
  while (Serial.available() > 0) {
    // csv of left ankle, left hip, right ankle, right hip
    // There are percentages: 0 - 100%
    
    int la = Serial.parseInt();
    int lh = Serial.parseInt();
    int ra = Serial.parseInt();
    int rh = Serial.parseInt();
    
    byte in = Serial.read();

    if (in == '-') {
      //Serial.println('-');
      activateLeds(la, lh, ra, rh);
      activateServos(la, lh, ra, rh);
    }
  } 

}

void servosCenter() {
  servosPosition(servoCenter,servoCenter,servoCenter,servoCenter); 
}


/**
 * csv of left ankle, left hip, right ankle, right hip
 */
void servosPosition(int la, int lh, int ra, int rh) {

  Serial.print(la); Serial.print(",");
  Serial.print(lh); Serial.print(",");
  Serial.print(ra); Serial.print(",");
  Serial.print(rh); Serial.println("-");
  
  // Ankles first, one servo at a time.
  
  
  if (la > 59 && lastLa != la) {
    constrain(la, 60, 120);
    LeftAnkle.write(la);
    
    //LeftAnkle.attach(LeftAnklePin);
    //LeftAnkle.write(la, moveSpeed, true);
    //LeftAnkle.detach();
    lastLa = la;
  }
  
  if (ra > 59 && lastRa != ra) {
    constrain(ra, 60, 120);
    RightAnkle.write(ra);
    
    //RightAnkle.attach(RightAnklePin);
    //RightAnkle.write(ra, moveSpeed, true);
    //RightAnkle.detach();
    lastRa = ra;
  }
  
  if (lh > 59 && lastLh != lh) {
    constrain(lh, 60, 120);
    LeftHip.write(lh);
    
    //LeftHip.attach(LeftHipPin);
    //LeftHip.write(lh, moveSpeed +20, true);
    //LeftHip.detach();
    lastLh = lh;
  }
  
  if (rh > 59 && lastRh != rh) {
    constrain(rh, 60, 120);
    RightHip.write(rh);
    
    //RightHip.attach(RightHipPin); 
    //RightHip.write(rh, moveSpeed +20, true);
    //RightHip.detach();
    lastRh = rh;
  }
  
}

/**
 * left ankle, left hip, right ankle, right hip
 */
void activateServos(int la, int lh, int ra, int rh) {
  constrain(la, 0, 100);
  constrain(lh, 0, 100);
  constrain(ra, 0, 100);
  constrain(rh, 0, 100);

  int angleLa = angle(la, servoMin, servoCenter, servoMax);
  int angleLh = angle(lh, servoMin, servoCenter, servoMax);
  int angleRa = angle(ra, servoMin, servoCenter, servoMax);
  int angleRh = angle(rh, servoMin, servoCenter, servoMax);
  servosPosition(angleLa, angleLh, angleRa, angleRh);
}

/*
 * Determine the angle to move the servo from the given percentage.
 */
int angle(int p, byte minAngle, byte center, byte maxAngle) {
  
  if (p == 0) {
    return center; 
  }
  
  if (p < 0) {
    return map(p, -100, 0, minAngle, center);
  }
  
  return map(p, 0, 100, center, maxAngle);
}

/**
 * left ankle, left hip, right ankle, right hip
 */
void activateLeds(int la, int lh, int ra, int rh) {
  constrain(la, 0, 100);
  constrain(lh, 0, 100);
  constrain(ra, 0, 100);
  constrain(rh, 0, 100);

  analogWrite(ledPinLeftAnkle, brightness(la));  
  analogWrite(ledPinLeftHip, brightness(lh)); 
  analogWrite(ledPinRightAnkle, brightness(ra)); 
  analogWrite(ledPinRightHip, brightness(rh));  
}

int brightness(int p) {
  if (p < 0) {
    p = p * -1; 
  }
  return round(float(p) / 100 * 255);
}
