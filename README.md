🦯 Smart Stick for Visually Impaired
Project Description

This project is a Smart Assistive Stick for Visually Impaired People built using Arduino.
It helps the user to:

Detect obstacles in front

Detect falls

Monitor heart rate

Get alerts using buzzer, lights, display, and Bluetooth

The system improves safety, mobility, and emergency awareness.

Main Features

Obstacle detection using Ultrasonic sensor

Fall detection using Accelerometer

Heart rate monitoring using Pulse Sensor

Alerts using Buzzer

Visual feedback using RGB LED

Information display using OLED screen

Wireless data sharing using Bluetooth (HC-05)

Components Used

Arduino Uno / Nano

Ultrasonic Sensor (HC-SR04)

ADXL345 Accelerometer

Pulse Sensor

OLED Display (SSD1306)

HC-05 Bluetooth Module

RGB LED (WS2812)

Buzzer

Connecting wires

How the System Works

When an obstacle is detected → Buzzer beeps

When a fall is detected → Buzzer + Display + Bluetooth alert

When heartbeat is detected → BPM shown on display and sent via Bluetooth

When idle → Owner name scrolls on the OLED screen

Pin Connections
Ultrasonic Sensor (HC-SR04)
Sensor Pin	Arduino Pin
VCC	5V
GND	GND
TRIG	D6
ECHO	D7
Accelerometer (ADXL345 – I2C)
ADXL345 Pin	Arduino Pin
VCC	3.3V
GND	GND
SDA	A4
SCL	A5
Pulse Sensor
Pulse Sensor Pin	Arduino Pin
VCC	5V
GND	GND
SIGNAL	A0
OLED Display (SSD1306 – I2C)
OLED Pin	Arduino Pin
VCC	5V
GND	GND
SDA	A4
SCL	A5

(OLED and Accelerometer share the same I2C pins)

Bluetooth Module (HC-05)
HC-05 Pin	Arduino Pin
VCC	5V
GND	GND
TX	D10
RX	D11 (use voltage divider)
RGB LED (WS2812)
RGB Pin	Arduino Pin
DATA	D6
VCC	5V
GND	GND
Buzzer
Buzzer Pin	Arduino Pin
+	D8
−	GND
Software Requirements

Arduino IDE

Required Libraries:

Adafruit ADXL345

Adafruit SSD1306

Adafruit GFX

Adafruit NeoPixel

PulseSensor Playground

How to Upload the Code

Open Arduino IDE

Install required libraries

Open Fall_Detection_Health_Monitoring_Stick.ino

Select board and COM port

Click Upload

Bluetooth Output Example
ACC: 0.12, 0.08, 9.81
BPM: 72
Fall Detected!

Application

This project is mainly used to help visually impaired persons by improving:

Safety

Health monitoring

Emergency alerts

Author

Abhinav S
BCA – AI, ML & Robotics
Yenepoya University, Bangalore
