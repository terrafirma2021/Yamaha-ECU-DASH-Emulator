# Yamaha DASH and ECU Simulator

[![Video Demo](https://img.youtube.com/vi/b36fGeeoa00/0.jpg)](https://www.youtube.com/watch?v=b36fGeeoa00)


## Overview

This Arduino sketch serves as a versatile Yamaha DASH and ECU Simulator, primarily designed to facilitate the setup and rapid testing of UART bridging functionality on other devices. It enables the interception of K-line data between the DASH and the ECU. This tool is intended for assistance to enable another device to configure a bridge, witht he end result allowing real-time editing and manipulation of data in both directions: data presented to the DASH and data sent to the ECU.

## MCU Compatibility

### Primary MCU: Arduino Mega 2560 (or similar models)

**Reason for Compatibility:** This sketch relies on multiple hardware serial ports, a feature readily available on the Arduino Mega and similar models.

## Functionality

### Initial Delay

The simulation initiates with an initial delay, following the YDT standard software protocol specs. This delay ensures proper setup before communication begins.

### DASH Behavior

- The DASH sends an initial byte sequence (0xFE) and waits for a specific response from the ECU.
- If the expected response is not received within a specified timeout, it logs an error (ER-1).
- Upon receiving the correct response, the DASH continuously sends another byte (0x01) and monitors responses from the ECU.

### ECU Behavior

- The ECU listens for specific bytes from the DASH (0xFE or 0x01).
- Upon receiving these specific bytes, it responds with a predefined byte sequence (0x00 0x00 0x00 0x01 0x01).
- The response includes a delay to simulate processing time.
- The ECU does not send any response if it does not receive the expected bytes.

### Error Handling

- The simulator incorporates comprehensive error handling. If the DASH fails to receive the expected response after sending 0x01, it logs an ER-2 error.
- The DASH continues attempting to send 0x01 until it receives the correct response.
- The sketch differentiates between errors related to 0xFE and 0x01 transmissions, ensuring accurate error reporting.

### Serial Communication

The sketch utilizes two hardware serial ports: Serial1 and Serial2, labeled as DASH and ECU respectively for clarity. Serial communication is vital for debugging and monitoring the communication process.

## Setup and Operation

### Hardware Setup

To use this simulator, connect the respective TX and RX pins of the Arduino Mega's Serial1 and Serial2 to external devices that simulate the DASH and ECU. This setup allows for the rapid testing and configuration of the UART bridging functionality on the other device.

### Software Setup

Upload the sketch to the Arduino Mega using the Arduino IDE or a similar tool.

### Operation

Once uploaded, the Arduino will initiate the communication simulation as per the predefined protocol. Monitor the Serial Monitor at a baud rate of 115200 to view log messages and error reports.

## Primary Use - Rapid Testing for UART Bridging Configuration

The core purpose of this code is to serve as a bridge for intercepting K-line data between the DASH and the ECU, enabling rapid testing and configuration of UART bridging functionality on the other device. It allows users to set up and verify that the other device can effectively act as a bridge for the UART communication between the DASH and ECU.

This functionality is essential for:

- Quickly assessing the performance and compatibility of the other device as a UART bridge.
- Configuring and fine-tuning the bridging parameters on the other device.
- Ensuring that the bridging device can handle the K-line data communication between the DASH and ECU without errors.

## Applications

In addition to its primary use case, this sketch can be employed for:

- Developing and testing various automotive communication protocols.
- Educational purposes to illustrate serial communication and protocol design.
- Simulating DASH and ECU behavior in controlled lab setups without the need for physical automotive hardware.

This comprehensive README highlights the primary use case of the code, which is enabling rapid testing and configuration of UART bridging functionality on the other device, while also mentioning its broader applications.
