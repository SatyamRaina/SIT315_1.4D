//Satyam Raina
//2110994809

#define Soil_Pin A0

const int PIR1 = 2; // PIR sensor 1 input pin
const int PIR2 = 8; // PIR sensor 2 input pin
int Soilmois = 0;
const int LED1 = 13; // LED light 1 output pin
const int LED2 = 10; // LED light 2 output pin
const int LED3 = 3; // LED light 3 output pin

void setup() {
  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(Soil_Pin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIR1), pir1_ISR, CHANGE); // attach interrupt for PIR1
  
  //Enabling the PCINT library for PIR1 sensor
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

  //Enabling the PCINT library for PIR2 sensor
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT8);
  
  //Enabling the PCINT library for soil moisture sensor
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8);
  
  Serial.begin(9600);
}

void loop() {
  
}

void pir1_ISR() {
  if (digitalRead(PIR1) == HIGH) {
    digitalWrite(LED1, HIGH);
    Serial.println("PIR Sensor 1 interrupted!");
  } else {
    digitalWrite(LED1, LOW);
  }
}

ISR(PCINT0_vect) {
  if (digitalRead(PIR2) == HIGH) {
    digitalWrite(LED2, HIGH);
    Serial.println("PIR Sensor 2 interrupted!");
  } else {
    digitalWrite(LED2, LOW);
  }
}

ISR(PCINT1_vect){
  Soilmois = analogRead(Soil_Pin);
  if(Soilmois < 500){
    digitalWrite(LED3, HIGH);
    Serial.println("Soil moisture level is low!!");
  }else{
    digitalWrite(LED3, LOW);
  }
}
