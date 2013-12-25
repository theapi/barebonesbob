/*
  ps3 cotroller for recording servo positions.
 */
 
// PWM pins
#define PIN_LEFT_A 5
#define PIN_LEFT_H 9
#define PIN_RIGHT_A 10
#define PIN_RIGHT_H 11

void setup() {                
  // initialize the led pins as an outputs.
  pinMode(PIN_LEFT_A, OUTPUT); 
  pinMode(PIN_LEFT_H, OUTPUT);
  pinMode(PIN_RIGHT_A, OUTPUT);
  pinMode(PIN_RIGHT_H, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("setup");
}


void loop() {
  while (Serial.available() > 0) {
    // csv of left ankle, left hip, right ankle, right hip
    // There are percentages: 0 - 100%
    
    int la = Serial.parseInt();
    int lh = Serial.parseInt();
    int ra = Serial.parseInt();
    int rh = Serial.parseInt();
    
    byte in = Serial.read();

    if (in == '-') {
      Serial.println('-');
      activateLeds(la, lh, ra, rh);

    }
  }     
}

/**
 * left ankle, left hip, right ankle, right hip
 */
void activateLeds(int la, int lh, int ra, int rh) {
  constrain(la, 0, 100);
  constrain(lh, 0, 100);
  constrain(ra, 0, 100);
  constrain(rh, 0, 100);

  analogWrite(PIN_LEFT_A, brightness(la));  
  analogWrite(PIN_LEFT_H, brightness(lh)); 
  analogWrite(PIN_RIGHT_A, brightness(ra)); 
  analogWrite(PIN_RIGHT_H, brightness(rh)); 

  
}

int brightness(int p) {
  if (p < 0) {
    p * -1; 
  }
  return round(float(p) / 100 * 255);
}
