// IoT Based Circuit Breaker using Arduino UNO
// Components Used:
// Arduino UNO
// Relay Module
// Current Sensor
// WiFi Module (ESP8266)
// LCD Display
// Buzzer

#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Relay Pin
int relayPin = 8;

// Buzzer Pin
int buzzerPin = 9;

// Current Sensor Pin
int sensorPin = A0;

// Current Limit
float currentLimit = 2.0;

void setup() {
  
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, HIGH);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("IoT Circuit");
  lcd.setCursor(0, 1);
  lcd.print("Breaker System");

  delay(3000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(sensorPin);

  // Convert Sensor Value
  float voltage = sensorValue * (5.0 / 1023.0);

  // Example Current Calculation
  float current = voltage * 2;

  lcd.setCursor(0, 0);
  lcd.print("Current: ");
  lcd.print(current);
  lcd.print("A ");

  Serial.print("Current Value: ");
  Serial.println(current);

  // Overload Condition
  if (current > currentLimit) {

    digitalWrite(relayPin, LOW);

    digitalWrite(buzzerPin, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("OVERLOAD ALERT");

    Serial.println("Circuit Breaker OFF");

  } 
  else {

    digitalWrite(relayPin, HIGH);

    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("System Normal  ");
  }

  delay(1000);
}
