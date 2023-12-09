# Yamaha DASH and ECU Simulator

## Overview

This Arduino sketch simulates the K-line communication between the dash and the ECU. It is designed to run on Arduino Mega or any other Arduino model that supports multiple hardware serial ports. The code illustrates a basic protocol of sending and receiving specific byte sequences between the DASH and ECU, implementing timeouts and error handling, using both ER-1 and ER-2 which would be displayed on the dash, when both loss of ECU reponse, or no init reponse form the ECU. This is needed when testing code without having to connect to the ECU, or dash

## MCU Compatibility

### Primary MCU: Arduino Mega 2560 (or similar models)

**Reason for Compatibility:** The sketch requires multiple hardware serial ports (at least two) which are available on the Arduino Mega and similar models.

## Functionality

### Initial Delay

The simulation starts with an initial delay, following the YDT standard software protocol specs

### DASH Behavior

- Sends a byte sequence (0xFE) and waits for a specific response from the ECU.
- If the expected response is not received within a specified timeout, it logs an error (ER-1).
- After receiving the correct response, the DASH continuously sends another byte (0x01) and checks for responses from the ECU.

### ECU Behavior

- Listens for specific bytes from the DASH (0xFE or 0x01).
- Responds with a predefined byte sequence (0x00 0x00 0x00 0x01 0x01) only upon receiving these specific bytes. This response is delayed by a specified amount of time to simulate processing delay.
- Does not send any response if the expected bytes are not received.

### Error Handling

- If the DASH does not receive the expected response after sending 0x01, it logs an ER-2 error. The DASH will continue attempting to send 0x01 until a correct response is received.
- The sketch ensures that errors related to 0xFE and 0x01 transmissions are handled separately and correctly.

### Serial Communication

The sketch uses two hardware serial ports: Serial1 and Serial2, which are renamed to DASH and ECU respectively for clarity.
Serial is used for logging information to the Serial Monitor for debugging and monitoring the communication process.

## Setup and Operation

### Hardware Setup

Connect the respective TX and RX pins of the Arduino Mega's Serial1 and Serial2 to your external devices (simulating DASH and ECU) or loop them back for testing.

### Software Setup

Upload the sketch to the Arduino Mega using the Arduino IDE or a similar tool.

### Operation

Once uploaded, the Arduino will start the communication simulation according to the predefined protocol. Monitor the Serial Monitor at 115200 baud rate for log messages and error reports.

## Applications

This sketch can be used as a basis for:

- Developing and testing automotive communication protocols.
- Educational purposes to demonstrate serial communication and protocol design.
- Simulating DASH and ECU behavior in lab setups without the need for actual automotive hardware.
