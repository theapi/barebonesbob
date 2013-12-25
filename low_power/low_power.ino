// https://github.com/netlabtoolkit/VarSpeedServo
#include <VarSpeedServo.h>

#define LEFT_HIP_PIN 9
#define LEFT_ANKLE_PIN 11

#define LEFT_ANKLE_CENTRE 90


//Servo servo;
VarSpeedServo LeftHip;
VarSpeedServo LeftAnkle;

VarSpeedServo RightHip;
VarSpeedServo RightAnkle;

//byte LeftHipPin          = 9;  
byte RightHipPin         = 10;
//byte LeftAnklePin        = 11;
byte RightAnklePin       = 12;

byte lastLh = 0;
byte lastLa = 0;
byte lastRh = 0;
byte lastRa = 0;

byte moveSpeed = 20;

void setup()
{
  Serial.begin(9600);
  servosCenter();

  
  /*
  LeftHip.attach(LeftHipPin);		// config the left/right/center leg servos
  LeftAnkle.attach(LeftAnklePin);

  RightHip.attach(RightHipPin);         // config the right leg
  RightAnkle.attach(RightAnklePin);
  */
//XXservosCenter();
  
  
}


void loop()
{     

  
  while (Serial.available() > 0) {
    // csv of left ankle, left hip, right ankle, right hip
    // 60,0,0,0-
    
    int la = Serial.parseInt();
    int lh = Serial.parseInt();
    int ra = Serial.parseInt();
    int rh = Serial.parseInt();
    
    byte in = Serial.read();

    if (in == 'w') { 
      walk();
    } else if (in == 'd') { 
      LeftHip.detach();
      LeftAnkle.detach();
      RightHip.detach();
      RightAnkle.detach();
    } else if (in == '-') {
      Serial.println('-');
      servosPosition(la, lh, ra, rh);

    }
  }

}

void servosCenter() {
  servosPosition(LEFT_ANKLE_CENTRE,90,90,90); 
}


/**
 * csv of left ankle, left hip, right ankle, right hip
 */
void servosPosition(int la, int lh, int ra, int rh) {

  // Ankles first, one servo at a time.
  
  if (la > 59 && lastLa != la) {
    constrain(la, 60, 120);
    LeftAnkle.attach(LEFT_ANKLE_PIN);
    LeftAnkle.write(la, moveSpeed, true);
    //LeftAnkle.detach();
    lastLa = la;
  }
  
  if (ra > 59 && lastRa != ra) {
    constrain(ra, 60, 120);
    RightAnkle.attach(RightAnklePin);
    RightAnkle.write(ra, moveSpeed, true);
    //RightAnkle.detach();
    lastRa = ra;
  }
  
  if (lh > 59 && lastLh != lh) {
    constrain(lh, 60, 120);
    LeftHip.attach(LEFT_HIP_PIN);
    LeftHip.write(lh, moveSpeed +20, true);
    LeftHip.detach();
    lastLh = lh;
  }
  
  if (rh > 59 && lastRh != rh) {
    constrain(rh, 60, 120);
    RightHip.attach(RightHipPin); 
    RightHip.write(rh, moveSpeed +20, true);
    RightHip.detach();
    lastRh = rh;
  }
   
   /*
  //delay(1000);
  LeftHip.detach();
  LeftAnkle.detach();
  RightHip.detach();
  RightAnkle.detach();  
      */
}

void walk() {
  // left ankle, left hip, right ankle, right hip
  

  servosPosition(90,105,90,100); 
  //delay(1000);

  servosPosition(90,105,105,70);

  servosPosition(100,80,105,70);
  //delay(1000);

  servosPosition(90,80,90,70);
  //delay(1000);
  
  servosPosition(75,90,90,70);

  servosPosition(75,105,80,100);
  //delay(1000);

  servosPosition(90,105,90,100);
  //delay(1000);
 
  // back to the start
  servosPosition(90,105,90,100); 

  
}

