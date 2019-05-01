/**
  firmware.ino
  Purpose: Monitors LDR, cuts charging power if above threshold

  @author Ben James
*/
#define FET 3
#define LED 11
#define ARM_BTN 5
#define LDR A0

#define LDR_THRESH 60

bool powerOn = true;

void setup() {
  setupIO();
  // Turn FET on initially
  digitalWrite(FET, HIGH);

  // Serial.begin(115200);
  flashLED(2);
}

void loop() {
  if(powerOn){
    checkPowerOnIO();
  }else{
    checkPowerOffIO();
  }
}

void checkPowerOnIO(){
  if(analogRead(LDR) < LDR_THRESH){
    // Do more intelligent detection/confirmation here - ie wait for 3 flashes
    digitalWrite(FET, LOW);
    powerOn = false;
    flashLED(1);
  }
}

void checkPowerOffIO(){
  if(digitalRead(ARM_BTN) == LOW){
    digitalWrite(FET, HIGH);
    powerOn = true;
    flashLED(2);
  }
}

void setupIO() {
  pinMode(FET, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ARM_BTN, INPUT_PULLUP);
  pinMode(LDR, INPUT);
}

// Flash LED n times
void flashLED(int n){
  for(int i = 0; i < n; i++){
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
}
