#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_NeoPixel.h>
#include <PulseSensorPlayground.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

// Bluetooth HC-05 setup
#define BT_RX 10  // Connect to HC-05 TX
#define BT_TX 11  // Connect to HC-05 RX
SoftwareSerial BT(BT_RX, BT_TX);  // Create SoftwareSerial object

// Pin definitions
#define RGB_PIN 6
#define BUZZER_PIN 8
#define PULSE_PIN A0
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define NUM_LEDS 8

// Object initializations
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_NeoPixel rgb(NUM_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);
PulseSensorPlayground pulseSensor;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Constants and variables
const int FALL_THRESHOLD = 20;
const int MOTION_THRESHOLD = 2;
const int BPM_THRESHOLD = 550;
String ownerName = "Jithu, 6282543160";
int scrollPos = SCREEN_WIDTH;
unsigned long lastActivityTime = 0;
const unsigned long IDLE_TIMEOUT = 5000;
unsigned long lastBTUpdate = 0;
const unsigned long BT_UPDATE_INTERVAL = 1000; // Send data every 1 second

void setup() {
  Serial.begin(9600);
  BT.begin(9600);  // Initialize Bluetooth communication

  // Initialize ADXL345
  if (!accel.begin()) {
    sendToDevices("ADXL345 not detected!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  // Initialize RGB LED
  rgb.begin();
  rgb.setBrightness(50);
  setRGBColor(0, 255, 0);

  // Initialize Pulse Sensor
  pulseSensor.analogInput(PULSE_PIN);
  pulseSensor.setThreshold(BPM_THRESHOLD);
  if (!pulseSensor.begin()) {
    sendToDevices("Pulse Sensor not started!");
  }

  // Initialize Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    sendToDevices("SSD1306 allocation failed");
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

void loop() {
  // Read accelerometer data
  sensors_event_t event;
  accel.getEvent(&event);
  float magnitude = sqrt(pow(event.acceleration.x, 2) + 
                   pow(event.acceleration.y, 2) + 
                   pow(event.acceleration.z, 2)) / 9.81;

  // Read pulse sensor
  int bpm = pulseSensor.getBeatsPerMinute();
  bool beatDetected = pulseSensor.sawStartOfBeat();

  // Regular Bluetooth data transmission
  if (millis() - lastBTUpdate > BT_UPDATE_INTERVAL) {
    String btData = "ACC:" + String(event.acceleration.x) + "," + 
                   String(event.acceleration.y) + "," + 
                   String(event.acceleration.z) + 
                   "|BPM:" + String(bpm) + 
                   "|MAG:" + String(magnitude);
    sendToDevices(btData);
    lastBTUpdate = millis();
  }

  // Check for fall detection
  if (magnitude > FALL_THRESHOLD) {
    setRGBColor(255, 0, 0);
    digitalWrite(BUZZER_PIN, HIGH);
    displayImpact(magnitude);
    sendToDevices("ALERT! Fall detected: " + String(magnitude) + "g");
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    lastActivityTime = millis();
  }
  // Check for motion detection
  else if (magnitude > MOTION_THRESHOLD) {
    setRGBColor(255, 0, 0);
    displayImpact(magnitude);
    sendToDevices("Motion detected: " + String(magnitude) + "g");
    lastActivityTime = millis();
  }
  // Normal state: Show BPM
  else if (beatDetected) {
    setRGBColor(0, 255, 0);
    displayBPM(bpm);
    sendToDevices("Heartbeat detected: " + String(bpm) + " BPM");
    lastActivityTime = millis();
  }
  // Idle state: Scroll owner's name
  else if (millis() - lastActivityTime > IDLE_TIMEOUT) {
    setRGBColor(0, 0, 255);
    scrollName();
  }
}

// Send data to both Serial Monitor and Bluetooth
void sendToDevices(String message) {
  Serial.println(message);  // Send to Serial Monitor
  BT.println(message);     // Send to Bluetooth
}

// Set RGB LED color
void setRGBColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    rgb.setPixelColor(i, rgb.Color(r, g, b));
  }
  rgb.show();
}

// Display impact value
void displayImpact(float impact) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Impact: ");
  display.print(impact);
  display.println(" g");
  display.display();
}

// Display BPM
void displayBPM(int bpm) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("BPM: ");
  display.println(bpm);
  display.display();
}

// Scroll owner's name
void scrollName() {
  display.clearDisplay();
  display.setCursor(scrollPos, 0);
  display.print(ownerName);
  display.display();
  scrollPos--;
  if (scrollPos < -ownerName.length() * 6) {
    scrollPos = SCREEN_WIDTH;
  }
  delay(500);
}