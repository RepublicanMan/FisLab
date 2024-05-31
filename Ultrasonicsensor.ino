#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Initialize the Adafruit LiquidCrystal library with the I2C address
Adafruit_LiquidCrystal lcd(0);

// Define pins for the buttons
const int buttonInitial = 13;
const int buttonFinal = 12;
const int buttonClear = 11;
const int buttonReset = 10;

// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 8;

// Variables to store distance data
float initialDistance = 0;
float finalDistance = 0;
bool initialRecorded = false;
bool finalRecorded = false;

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.setBacklight(LOW);

  // Initialize the button pins as input with internal pull-up resistors
  pinMode(buttonInitial, INPUT_PULLUP);
  pinMode(buttonFinal, INPUT_PULLUP);
  pinMode(buttonClear, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Display initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Press Btn 13 to");
  lcd.setCursor(0, 1);
  lcd.print("Get initial Dist:");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Check if the initial distance button is pressed
  if (digitalRead(buttonInitial) == LOW) {
    initialDistance = getDistance();
    initialRecorded = true;
    lcd.setCursor(0, 0);
    lcd.print("Initial: ");
    lcd.print(initialDistance);
    lcd.print(" cm");
    delay(500); // Debounce delay
  }

  // Check if the final distance button is pressed
  if (digitalRead(buttonFinal) == LOW) {
    finalDistance = getDistance();
    finalRecorded = true;
    lcd.setCursor(0, 1);
    lcd.print("Final: ");
    lcd.print(finalDistance);
    lcd.print(" cm");
    delay(500); // Debounce delay
  }

  // Check if the clear button is pressed
  if (digitalRead(buttonClear) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Btn 13 to");
    lcd.setCursor(0, 1);
    lcd.print("Get initial Dist");
    delay(500); // Debounce delay
  }

  // Check if the reset button is pressed
  if (digitalRead(buttonReset) == LOW) {
    initialDistance = 0;
    finalDistance = 0;
    initialRecorded = false;
    finalRecorded = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data Reset");
    delay(1000);
    lcd.clear();
    delay(500); // Debounce delay
  }
}

float getDistance() {
  // Send a 10us pulse to trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (cm)
  float distance = duration * 0.034 / 2;

  return distance;
}

