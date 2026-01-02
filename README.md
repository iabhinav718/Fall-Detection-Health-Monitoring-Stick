Smart Stick for Visually Impaired
Fall Detection & Health Monitoring with Obstacle Alert



📌 Project Overview

This project is an Arduino-based smart walking stick designed to assist visually impaired individuals.
It improves safety by detecting obstacles, falls, and health abnormalities, and provides audio, visual, and wireless alerts.

The system combines:

-Obstacle detection using an ultrasonic sensor

=Fall detection using an accelerometer

=Heart rate monitoring

=Alerts using buzzer, RGB LEDs, OLED display

=Emergency data transmission via Bluetooth (HC-05)

🎯 Objectives

Detect nearby obstacles and alert the user

Detect sudden falls and trigger emergency alerts

Monitor heart rate continuously

Provide clear feedback through sound, light, display, and Bluetooth

Improve independent mobility for visually impaired users

🧩 Components Used
Component	Purpose
Arduino Uno	Main controller
HC-SR04 Ultrasonic Sensor	Obstacle detection
ADXL345 Accelerometer	Fall detection
Pulse Sensor	Heart rate monitoring
HC-05 Bluetooth Module	Wireless data transmission
OLED Display (SSD1306)	Status & data display
WS2812 RGB LEDs	Visual indication
Buzzer	Audio alert
Resistors, jumper wires	Connections
🔌 Pin Connections (Very Important)
1️⃣ Ultrasonic Sensor (HC-SR04)
HC-SR04 Pin	Arduino Pin
VCC	5V
GND	GND
TRIG	D6
ECHO	D7

Purpose:
Detects obstacles in front of the user.
If an object is within 50 cm, an alert is triggered.

2️⃣ Accelerometer (ADXL345 – I2C)
ADXL345 Pin	Arduino Pin
VCC	3.3V
GND	GND
SDA	A4
SCL	A5

Purpose:
Detects sudden motion changes to identify falls.

3️⃣ Pulse Sensor
Pulse Sensor Pin	Arduino Pin
VCC	5V
GND	GND
Signal	A0

Purpose:
Continuously monitors the user’s heart rate (BPM).

4️⃣ Bluetooth Module (HC-05)
HC-05 Pin	Arduino Pin
VCC	5V
GND	GND
TXD	D10
RXD	D11 (via voltage divider)

Purpose:
Sends alerts and sensor data to a mobile phone.

5️⃣ OLED Display (SSD1306 – I2C)
OLED Pin	Arduino Pin
VCC	5V
GND	GND
SDA	A4
SCL	A5

Purpose:
Displays system status, BPM, alerts, and messages.

6️⃣ RGB LED (WS2812)
RGB Pin	Arduino Pin
DIN	D5
VCC	5V
GND	GND

Color Meaning:

🟢 Green → Normal

🔴 Red → Fall / danger

🔵 Blue → Idle / standby

7️⃣ Buzzer
Buzzer Pin	Arduino Pin

| D8 |
− | GND |

Purpose:
Provides audio alerts for obstacles, falls, and warnings.

⚙️ Working Principle

Ultrasonic sensor checks distance continuously

If an obstacle is detected → buzzer alerts user

Accelerometer detects sudden impact → fall alert

Pulse sensor measures BPM

OLED + RGB LED show system status

Bluetooth sends emergency and sensor data to phone

🛠️ Software & Libraries

Arduino IDE

Required Libraries:

Adafruit_ADXL345_U

Adafruit_NeoPixel

PulseSensorPlayground

Adafruit_GFX

Adafruit_SSD1306

👤 Target Users

This system is designed for:

Visually impaired individuals

Elderly users

People requiring assisted mobility and health monitoring

✅ Project Status

✔ Ultrasonic obstacle detection

✔ Fall detection

✔ Heart rate monitoring

✔ Bluetooth alerts

✔ Fully merged single Arduino code

📄 Author

Abhinav S
BCA | AI, ML & Robotics
Yenepoya University, Bangalore
