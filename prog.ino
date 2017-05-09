/*
 * Manage fog lamp of car with roadlight situation, headlights lamp and timer
 * Author : Jérémie Décome - www.jeremie-decome.fr
 * AtTiny85 version
 */

// Output pins
const int relay = 0;

// Input pins
const int apc = 1;                // motor engine is ON ?
const int btn = 2;                // system switch
const int stateRoadLights = 3;    // roadlights stat

// Variables
long previous = 0;
long current = 0;

#define ON HIGH
#define OFF LOW

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  pinMode(apc, INPUT_PULLUP);
  pinMode(stateRoadLights, INPUT_PULLUP);
  digitalWrite(relay, LOW);
  Serial.begin(9600);
}

void loop() {
  
  if((digitalRead(apc) == LOW) && (digitalRead(btn) == LOW)) {
    current = millis();
    if(digitalRead(stateRoadLights) == LOW) {
      Serial.println((current - previous));
      if((current - previous) >= 5000) {    // fog lamp is ON after 5 seconds
        previous = current;
        digitalWrite(relay, ON);
      }
    }
    else {    // in another case, fog lamp is OFF
      previous = millis();
      current = 0;
      digitalWrite(relay, OFF);
    }
  }
  else {
    previous = millis();
    current = 0;
    digitalWrite(relay, OFF);
  }
  
}
