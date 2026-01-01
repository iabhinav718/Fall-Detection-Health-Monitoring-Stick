#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_NeoPixel.h>
#include <PulseSensorPlayground.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

/* ---------- Bluetooth (HC-05) ---------- */
#define BT_RX 10
#define BT_TX 11
SoftwareSerial BT(BT_RX, BT_TX);

/* ---------- Ultrasonic Sensor ---------- */
#define TRIG_PIN 6
#define ECHO_PIN 7
#define DISTANCE_THRESHOLD 50   // cm

/* ---------- Other Pins ---------- */
#define RGB_PIN 5
#define BUZZER_PIN 8
#define PULSE_PIN A0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define NUM_LEDS 8

/* ---------- Objects ---------- */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_NeoPixel rgb(NUM_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);
PulseSensorPlayground pulseSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ---------- Thresholds ---------- */
const int FALL_THRESHOLD = 20;     // g
const int MOTION_THRESHOLD = 2;    // g
const int BPM_THRESHOLD = 550;

String ownerName = "Jithu, 6282543160";
unsigned long lastActivityTime = 0;
const unsigned long IDLE_TIMEOUT = 5000;
unsigned long lastBTUpdate = 0;
const unsigned long BT_UPDATE_INTERVAL = 1000;

/* ---------- Setup ---------- */
void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  rgb.begin();
  rgb.setBrightness(50);
  setRGBColor(0, 255, 0);

  pulseSensor.analogInput(PULSE_PIN);
  pulseSensor.setThreshold(BPM_THRESHOLD);
  pulseSensor.begin();

  if (!accel.begin()) {
    sendToDevices("ADXL345 not detected");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    sendToDevices("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("System Ready");
  display.display();

  sendToDevices("System Ready");
}

/* ---------- Loop ---------- */
void loop() {

  /* Ultrasonic distance */
  long distance = readUltrasonic();

  /* Accelerometer */
  sensors_event_t event;
  accel.getEvent(&event);
  float magnitude = sqrt(
    pow(event.acceleration.x, 2) +
    pow(event.acceleration.y, 2) +
    pow(event.acceleration.z, 2)
  ) / 9.81;

  /* Pulse sensor */
  int bpm = pulseSensor.getBeatsPerMinute();
  bool beatDetected = pulseSensor.sawStartOfBeat();

  /* Bluetooth periodic update */
  if (millis() - lastBTUpdate > BT_UPDATE_INTERVAL) {
    sendToDevices("DIST:" + String(distance) +
                  "cm | BPM:" + String(bpm) +
                  " | G:" + String(magnitude));
    lastBTUpdate = millis();
  }

  /* ---- Priority Logic ---- */

  // FALL DETECTION
  if (magnitude > FALL_THRESHOLD) {
    setRGBColor(255, 0, 0);
    digitalWrite(BUZZER_PIN, HIGH);
    showText("FALL DETECTED");
    sendToDevices("ALERT: FALL DETECTED");
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // OBSTACLE DETECTION
  else if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    setRGBColor(255, 0, 0);
    digitalWrite(BUZZER_PIN, HIGH);
    showText("Obstacle: " + String(distance) + "cm");
    sendToDevices("Obstacle detected: " + String(distance) + "cm");
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // NORMAL BPM DISPLAY
  else if (beatDetected) {
    setRGBColor(0, 255, 0);
    showText("BPM: " + String(bpm));
  }

  // IDLE
  else if (millis() - lastActivityTime > IDLE_TIMEOUT) {
    setRGBColor(0, 0, 255);
    showText(ownerName);
  }
}

/* ---------- Functions ---------- */

long readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void sendToDevices(String msg) {
  Serial.println(msg);
  BT.println(msg);
}

void setRGBColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++)
    rgb.setPixelColor(i, rgb.Color(r, g, b));
  rgb.show();
}

void showText(String text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}
