#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// TFT pins
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

// Ultrasonic sensor pins
#define TRIG_PIN 7
#define ECHO_PIN 6

// Button pin
#define BUTTON_PIN 5

// Initialize the TFT display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

bool initialDataRecorded = false;
bool finalDataRecorded = false;
float initialDistance = 0;
float finalDistance = 0;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Enable internal pull-up resistor

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.setCursor(10, 10);
  tft.print("Press button to record data");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200); // Simple debouncing
    if (!initialDataRecorded) {
      initialDistance = getDistance();
      initialDataRecorded = true;
      tft.fillScreen(ILI9341_BLACK);
      tft.setCursor(10, 10);
      tft.print("Initial data: ");
      tft.print(initialDistance);
      tft.print(" cm");
    } else if (!finalDataRecorded) {
      finalDistance = getDistance();
      finalDataRecorded = true;
      tft.setCursor(10, 50);
      tft.print("Final data: ");
      tft.print(finalDistance);
      tft.print(" cm");
    }
    while (digitalRead(BUTTON_PIN) == LOW); // Wait for button release
    delay(200); // Simple debouncing
  }
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) * 0.0343; // Speed of sound in cm/us
  return distance;
}
