# ESP32 Bluetooth Traffic Light Controller

## Video
<video src="ProiectPia.mp4" width="100%" controls></video>

## Overview
This project implements a smart traffic light system controlled via Classic Bluetooth.Built on an ESP32 microcontroller, it receives serial commands from a mobile device to change states and provides textual feedback back to the user.The project demonstrates direct GPIO manipulation, custom multiplexing for a 2-digit 7-segment display, and dynamic delay-based timing algorithms.

## Features
-Classic Bluetooth Control:Uses the `BluetoothSerial` library. The ESP32 broadcasts as "SEMAFOR" and accepts string commands via a Serial Bluetooth Terminal app.
-Two-Way Communication:The system sends confirmation messages back to the mobile device ("Este verde, puteti traversa strada!").
-Custom 7-Segment Multiplexing:Implements manual multiplexing (rapid switching) to display 2-letter states on a dual 7-segment display without using external driver ICs:
  * `St` (Start) for Green light.
  * `In` (Intermitent) for Yellow light.
  * `Sp` (Stop) for Red light.
-Dynamic Warning LED:A supplementary LED alerts users of an impending state change.The code dynamically calculates and increases the blinking frequency (0.5Hz, 1Hz, 1.5Hz) over a set duration.

## Hardware Requirements
-ESP32 Development Board
-2-Digit 7-Segment Display
-LEDs (Green, Red, Warning)
-Current-limiting Resistors
-Breadboard and Jumper wires

## How to Test / Usage
To interact with the traffic light system, you will need an Android device:

1.Download the App:Install 'Serial Bluetooth Terminal' from the Google Play Store.
2.Pair the Device:Turn on the ESP32 and pair your phone with the Bluetooth device named `SEMAFOR`.
3.Send Commands:Open the Serial Bluetooth Terminal app, connect to the ESP32, and send one of the following exact commands (case-sensitive):
   * `VERDE` - Triggers the Green light sequence.
   * `GALBEN` - Triggers the Yellow light sequence.
   * `ROSU` - Triggers the Red light sequence.
4.Read Feedback:The ESP32 will reply in the app terminal with a confirmation message.
