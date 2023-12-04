/*
https://www.tinkercad.com/things/4c3dclKU9Ch-copy-of-engr-2304-final-project/editel
2023FA-ENGR-2304-81001-DYER-JOSHUA-P09
*/
// make changes to git hub
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int pressurePotPin = A0;
const int compressorPotPin = A1;
const int pressurePin = 9;
const int compressorPin = 10;
const int ledPin = 7;
const int launchPin = 11;

const int maxPressure = 120;
const int launchThreshold = 5;

LiquidCrystal_I2C lcd(0x20, 20, 4);

int leds[] = {13, 12, 8, 4};
int countdown = 0;

void setup() {
  pinMode(pressurePin, OUTPUT);
  pinMode(compressorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(launchPin, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Desired: ");

  // initialize LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int pressureValue = analogRead(pressurePotPin);
  int compressorValue = analogRead(compressorPotPin);

  int mappedPressure = map(pressureValue, 0, 1023, 0, maxPressure);
  int mappedCompressor = map(compressorValue, 0, 1023, 0, maxPressure);

  analogWrite(pressurePin, mappedPressure);
  analogWrite(compressorPin, mappedCompressor);

  Serial.print("Pressure: ");
  Serial.print(mappedPressure);
  Serial.print("\tCompressor: ");
  Serial.println(mappedCompressor);

  // Check if pressures match within the threshold
  if (abs(mappedPressure - mappedCompressor) < launchThreshold) {
    launchCountdown(mappedPressure, mappedCompressor);
  } else {
    // Update LCD with both desired and current pressure
    updateLCD(mappedPressure, mappedCompressor);
  }

  delay(500);  // Adjust this delay based on your preference
}

void updateLCD(int desiredPressure, int currentPressure) {
  lcd.setCursor(9, 0);
  lcd.print("    ");
  lcd.setCursor(9, 0);
  lcd.print(desiredPressure);

  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(currentPressure);

  lcd.setCursor(0, 2);
  lcd.print("Countdown: ");
  lcd.print("   ");  // Clear the countdown

  lcd.setCursor(0, 3);
  lcd.print("                    "); // Clear additional lines
}

void launchCountdown(int desiredPressure, int currentPressure) {
  Serial.println("Pressures Match! Initiating Launch Countdown...");

  for (countdown = 10; countdown > 0; countdown--) {
    Serial.println(countdown);

    // Display the countdown on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Countdown: ");
    lcd.print("    ");
    lcd.setCursor(9, 0);
    lcd.print(countdown);

    // LED Countdown Logic
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], bitRead(countdown, i));
    }

    delay(1000);
  }

  countdown = 0;

  lcd.setCursor(0, 2);
  lcd.print("                    "); // Clear the countdown
  lcd.setCursor(0, 2);
  lcd.print("LIFTOFF!");

  lcd.setCursor(0, 3);
  lcd.print("Launch Sequence Complete!");

  // Reset LEDs after countdown
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }

  digitalWrite(launchPin, HIGH);
  delay(1000);
  digitalWrite(launchPin, LOW);

  digitalWrite(ledPin, HIGH);
  delay(3000);  // Keep the LED on for 3 seconds
  digitalWrite(ledPin, LOW);

  Serial.println("Launch Sequence Complete!");
}
