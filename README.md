# Master-Boot-Device
⚡ Master-Boot-Device-v116 ⚡
The Ultimate ESP32 Cybersecurity Multi-Tool

A professional-grade HID injection, RFID cloning, and system configuration tool built on the ESP32 (CYD) platform, featuring a custom Neon Purple Matrix GUI.
_______________________________________________________________________________
⚠️ LEGAL WARNING & DISCLAIMER
THIS TOOL IS FOR EDUCATIONAL AND ETHICAL TESTING PURPOSES ONLY.

- Unauthorized access to computer systems is illegal.

- The creator (TheLeduylamOfficial) is not responsible for any misuse or damage caused by this tool.

- By using this software, you agree to comply with all local and international laws regarding cybersecurity.

________________________________________________________________________________
🛠️ Hardware Specifications
- Controller: ESP32-WROOM (Dual Core).

- Display: 2.8" TFT Touchscreen with Matrix-Rain GUI.

- Storage: 7GB MicroSD Card support for payloads and configs.

- Connectivity: Bluetooth Low Energy (BLE) for wireless HID injection.

- RFID: MFRC522 Module for 13.56MHz card interaction.

________________________________________________________________________________
📂 SD Card File Structure
For the device to function correctly, your SD card must be formatted to FAT32 and contain:

 1.config.json: Stores your device name (Master Boot Device-v116) and theme colors.

 2.Update.txt: The "BadUSB" payload script (Ducky Script format).

__________________________________________________________________________________
🚀 1. Arduino IDE Setup
To compile the code successfully, you must have the Arduino IDE installed and add the following libraries via the Library Manager (Ctrl+Shift+I):

- TFT_eSPI: The core driver for your purple Matrix display.

- MFRC522: Required for the RFID scanning and cloning features.

- BleKeyboard: Enables the Bluetooth "BadUSB" HID injection.

- ArduinoJson: Allows the device to read your config.json from the SD card.

- SD: Built-in library used to communicate with your 7GB SD card.

Note: For the TFT_eSPI library, ensure you have configured your User_Setup.h file to match your ESP32 pinout, otherwise the screen will remain blank.
____________________________________________________________________________________
💻 2. Deployment
- Connect your ESP32 via USB and click Upload.

- Insert the SD card before powering on the device.

- The device will automatically load your settings from config.json on boot.
____________________________________________________________________________________
📜 License
This project is licensed under the MIT License. See the LICENSE file for details.
____________________________________________________________________________________
✅ Ready to go!
